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

const int FPS = 120;
const int delay = 1000 / FPS;
const int width = 80;
int height;

unsigned SCORE = 0;
double gameTickInterval = 300;

bool isNextGameTick();
bool showNextFrame();

Block** positionBlocks(int,Engine &);
int getHorizonalBlockPos(Block *);
void moveFrame(Block **,int,Character &);
void drawBlocks(Block **,int);

int _tmain(int argc, _TCHAR* argv[]) {
	srand(GetTickCount());
	SetConsoleTitle(TEXT("Console Tower"));

	RECT desktop;
	GetWindowRect(GetDesktopWindow(), &desktop);
	height = (desktop.bottom/12) - 15;
	Engine dr(width,height);
	Character ch(dr,0,0);
	ch.setX( width/2 + ch.getWidth()/2 );
	ch.setY( height - ch.getHeight() - 3 );

	int blockCount = 11;
	Block **blocks = positionBlocks(blockCount,dr);

	bool isStarted = false;
	double normalTickInterval = gameTickInterval;
	bool isSpeeding = false;
	while (true) {
		if( !isStarted && ( GetAsyncKeyState(VK_SPACE) || GetAsyncKeyState(VK_UP) ) )
			isStarted = true;
		bool gameTick = isNextGameTick();

		if( ch.getY() < 4 && !isSpeeding ){
			normalTickInterval = gameTickInterval;
			gameTickInterval = 10;
			isSpeeding = true;
		}
		if( ch.getY() >= 4 && isSpeeding) {
			isSpeeding = false;
			gameTickInterval = normalTickInterval;
		}


		if( gameTick && isStarted )
			moveFrame(blocks,blockCount,ch);

		drawBlocks(blocks,blockCount);

		ch.erase();
		if(!ch.move(blocks,blockCount)) break;
		ch.draw();

		if( showNextFrame() ){
			if( isStarted ){
				SCORE += 1/gameTickInterval * 1000 * ( isSpeeding ? 2 : 1);
				if(gameTickInterval > 100) {
					gameTickInterval -= 0.5;
					normalTickInterval -= 0.5;
				}
			}
			dr.draw();
		}


	}
	for(int c = 0; c < width; c++)
		for(int r = 0; r < height; r++)
			dr(c,r,' ');
	dr(width/2-5,height/2-1,"You lost!");
	dr(width/2-8,height/2,"Score: ");
	dr((int)SCORE);
	dr(width/2-11,height/2+2,"Press [enter] to exit.");
	dr.draw();
	cin.get();
	return 1;

}

Block** positionBlocks(int n,Engine &e){
	Block **blocks = new Block*[n];
	for(int c = 0; c < n; c++){
		if( c > 0 ) {
			blocks[c] = new Block(e,-1,-1);
			blocks[c]->setX(getHorizonalBlockPos(blocks[c]));
			blocks[c]->setY( c * (height/n) );
		} else {
			blocks[c] = new Block(e,0,height-3,width);
		}
	}
	return blocks;
}

void drawBlocks(Block **blocks,int n){
	for(int c = 0; c < n; c++)
		blocks[c]->draw();
}

int getHorizonalBlockPos(Block *bl){
	switch (rand() % 3)	{
	case 0:
		return 0;
		break;
	case 1:
		return width - bl->getWidth();
		break;
	default:
		return width/2 - bl->getWidth()/2 ;
		break;
	}
}

void moveFrame(Block **blocks,int n,Character &ch){
	if( blocks[0]->getWidth() == width && blocks[0]->getY() >= height){
		blocks[0]->erase();
		blocks[0]->setWidth(18);
	}

	for(int c = 0; c < n; c++){
		blocks[c]->erase();
		if( blocks[c]->getY() >= height || blocks[c]->getY() < 0){
			int minHeight = height;
			for(int r = 0; r < n; r++)
				if( blocks[r]->getY() < minHeight && blocks[r]->getY() > 0 )
					minHeight = blocks[r]->getY();
			minHeight = minHeight/2;
			blocks[c]->setY(minHeight);
			blocks[c]->setX(getHorizonalBlockPos(blocks[c]));

		}
		blocks[c]->setY(blocks[c]->getY() + 1);
	}
}

bool showNextFrame() {
	static int time = GetTickCount();
	if( GetTickCount() - time > delay ){
		time = GetTickCount();
		return true;
	}
	return false;
}

bool isNextGameTick(){
	static int time = GetTickCount();
	if( GetTickCount() - time > gameTickInterval ){
		time = GetTickCount();
		return true;
	}
	return false;

}
