#include "stdafx.h"
#pragma warning(disable: 4996)


Object::Object(Engine &e,Texture &t,int x,int y): engine(&e), G(9.81) {
	this->texture = t;
	this->setX(x);
	this->setY(y);
	this->width = t.getWidth();
	this->height = t.getHeight();
}


void Object::erase() const{
	for(int x = 0; x < this->width; ++x )
		for(int y = 0; y < this->height; ++y)
			(*this->engine)(this->position.x + x,this->position.y+y,' ');
}

void Object::draw() const{
	const char **texture = this->texture.getTexture();
	for(int x = 0; x < this->width; ++x )
		for(int y = 0; y < this->height; ++y)
			(*this->engine)(this->position.x + x,this->position.y + y,texture[y][x]);
}

void Object::setX(int x) {
	this->position.x = x;
}
void Object::setY(int y) {
	this->position.y = y;
}

int Object::getX() const{
	return this->position.x;
}

int Object::getY() const{
	return this->position.y;
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
