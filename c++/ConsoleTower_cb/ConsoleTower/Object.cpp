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

Object::Object(Engine &e,int x,int y): x(0), y(0), engine(&e), G(9.81), texture(NULL) {
	this->setX(x);
	this->setY(y);
}


void Object::erase() const{
	for(int x = 0; x < this->width; ++x )
		for(int y = 0; y < this->height; ++y)
			(*this->engine)(this->x+x,this->y+y,' ');
}

void Object::draw() const{
	for(int x = 0; x < this->width; ++x )
		for(int y = 0; y < this->height; ++y)
			(*this->engine)(this->x+x,this->y+y,this->texture[y][x]);
}

void Object::setX(int x) {
	this->x = x;
}
void Object::setY(int y) {
	this->y = y;
}

int Object::getX() const{
	return this->x;
}

int Object::getY() const{
	return this->y;
}

void Object::_setWidth(int w){
	this->width = this->w = w;
}
void Object::_setHeight(int h){
	this->height = this->h = h;
}

void Object::setWidth(int w) {
	this->width = w <= this->w ? w : this->width;
}

void Object::setHeight(int h){
	this->height = h <= this->h ? h : this->height;
}

int Object::getWidth() const{
	return this->width;
}

int Object::getHeight() const{
	return this->height;
}

void Object::_initTexture() {
	this->texture = new char*[this->height];
	for(int c = 0; c < this->height; ++c)
		this->texture[c] = new char[this->width];
}

Object::~Object() {
	if( this->texture ) {
		for (int c = 0; c < this->h; ++c) {
			delete[] this->texture[c];
		}
		delete[] this->texture;
	}
}
