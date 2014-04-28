#define _WIN32_WINNT 0x0500
#include <Windows.h>
#include <cstring>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <cstdlib>
#include <tchar.h>
#include <cassert>
#include "wtypes.h"
#include "Engine.h"
#include "Object.h"
#include "Block.h"
#include "Character.h"
using namespace std;

Engine::Engine(int cols,int rows): field(NULL), nextFrame(NULL) {

	this->console = GetStdHandle(STD_OUTPUT_HANDLE);
	this->field = new char*[rows];
	this->nextFrame = new char*[rows];
	for (int c = 0; c < rows; ++c)	{
		this->field[c] = new char[cols];
		this->nextFrame[c] = new char[cols];
	}
	this->lastCol = this->lastRow = 0;
	this->pixelsDrawn = 0;
	this->rows = rows;
	this->cols = cols;
	this->drawBuff = new char[this->cols*this->rows + this->cols + 1];
	this->clear();
	RECT desktop;
	GetWindowRect(GetDesktopWindow(), &desktop);
	this->_moveConsole(desktop.right/2 - cols*8,20);
	this->_hideBrush();
	this->_resizeConsole(rows,cols);
	this->_moveConsole(desktop.right/2 - cols*8,20);
	this->_resizeConsole(rows,cols);
}

void Engine::draw(DrawMethod d) {
	this->pixelsDrawn = 0;
	if( d == Clean ){
		int c = 0;
		for (int row = 0; row < this->rows; ++row) {
			for (int col = 0; col < this->cols; ++col)
				this->field[row][col] = this->drawBuff[c++] = this->nextFrame[row][col];
			this->drawBuff[c++] = '\n';
		}
		this->drawBuff[c] = 0;
		this->pixelsDrawn = strlen(this->drawBuff);
		this->_moveBrush(0,0);
		cout << this->drawBuff << flush;
	} else {
		// TODO: optimise to draw larger blocks than 1 line

		for (int row = 0; row < this->rows; ++row)	{
			bool endLine = false;
			for (int col = 0; col < this->cols; ++col)	{
				if( this->field[row][col] != this->nextFrame[row][col] ){
					int len = 0;
					bool brushMoved = false;
					while( this->field[row][col] != this->nextFrame[row][col] && col < this->cols ){
						if( !brushMoved ){
							this->_moveBrush(row,col);
							brushMoved = true;
						}
						this->drawBuff[len++] = this->field[row][col] = this->nextFrame[row][col];
						++col;
						this->pixelsDrawn++;
					}
					this->drawBuff[len] = 0;
					if( len != 0 ){
						cout << this->drawBuff;
						endLine = true;
					}
				}
			}
			if( endLine )
				this->_endLine(row);
		}
	}
}

int Engine::getWidth() const {
	return this->cols;
}

int Engine::getHeight() const {
	return this->rows;
}

int Engine::getPixelsDrawn() const {
	return this->pixelsDrawn;
}

void Engine::_getNextBlock(int row,int col,char * buf){
	int counter = 0;
	while( this->nextFrame[row][col] != this->field[row][col] ){
		this->field[row][col] = this->nextFrame[row][col];
		buf[counter++] = this->nextFrame[row][col];
		if( col == this->cols -1 ){
			row++;
			col = 0;
		} else if( col < this->cols - 1 && row < this->rows - 1 ){
			col++;
		} else {
			break;
		}
	}
}

void Engine::clear(){
	for (int row = 0; row < this->rows; ++row)
		for (int col = 0; col < this->cols; ++col)
			this->field[row][col] = this->nextFrame[row][col] = ' ';

}

void Engine::operator()(int col,int row,char c){
	if( row >= this->rows || row < 0 || col >= this->cols || col < 0)
		return;
	this->nextFrame[row][col] = c;
	this->lastCol = col;
	this->lastRow = row;
}

void Engine::operator()(int col,int row,const char *str){
	this->operator()(col,row,str,strlen(str));
}

void Engine::operator()(int col,int row,const char *str,int len){
	int c = 0;
	for( ; c < len && (col + c) < this->cols; c++){
		this->nextFrame[row][col+c] = str[c];
	}
	this->lastRow = row;
	this->lastCol = col + c;
}

void Engine::operator()(int x){
	char str[40];
	snprintf(str, 10,"%d",x);
	this->operator()(this->lastCol,this->lastRow,str,strlen(str));
}

void Engine::operator()(char c){
	this->nextFrame[this->lastRow][this->lastCol++] = c;
}

void Engine::operator()(const char *str){
	this->operator()(this->lastCol,this->lastRow,str,strlen(str));
}

void Engine::operator()(const char *str,int len){
	this->operator()(this->lastCol,this->lastRow,str,len);
}

void Engine::_moveConsole(int x,int y) const{
	MoveWindow(GetConsoleWindow(),x,y,(this->cols+100)*8,(this->rows+1)*12,true);
}

void Engine::_hideBrush() const {
    CONSOLE_CURSOR_INFO cur;
    cur.dwSize = 1;
    cur.bVisible = false;
    SetConsoleCursorInfo(this->console, &cur);
}

void Engine::_endLine(int row){
	COORD position = {row,this->cols};
	SetConsoleCursorPosition(this->console, position);
	cout << '\n';
}

void Engine::_moveBrush(int row,int col) {
	COORD position;
	position.X = col;
	position.Y = row;
	SetConsoleCursorPosition(this->console, position);
}

void Engine::_resizeConsole(int rows,int cols) const{

	stringstream str;
	rows++;
	cols++;
	str << "mode " << cols << ", " << rows;

	str.seekg(0, ios::beg);
	str.seekg(0, ios::end);
	int size = str.tellg();
	char *buf = new char[size+1];
	buf[size] = 0;
	str.seekg(0, ios::beg);
	str.read( buf,size);
	system(buf);
	delete[] buf;

	SMALL_RECT Rect;
    Rect.Top = 0;
    Rect.Left = 0;
    Rect.Bottom = rows+1;
    Rect.Right = cols+1;
	SetConsoleWindowInfo(this->console, TRUE, &Rect);


}


Engine::~Engine() {
	if( this->field ){
		for (int c = 0; c < rows; ++c)
			if( this->field[c] )
				delete[] this->field[c];
		delete[] this->field;
	}

	if( this->nextFrame ) {
		for (int c = 0; c < rows; ++c)
			if( this->nextFrame[c] )
				delete[] this->nextFrame[c];
		delete[] this->nextFrame;
	}
}
