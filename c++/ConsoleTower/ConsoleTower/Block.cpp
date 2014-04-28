#include "stdafx.h"
#include "Block.h"
#pragma warning(disable: 4996)

Block::Block(Engine &e,int x,int y,int w): Object(e,x,y){
	this->_setHeight(1);
	if( w == -1 ){
		int size = rand() % 4;
		switch (size) {
		case 0:
			this->_setWidth(10);
			break;
		case 1:
			this->_setWidth(26);
			break;
		default:
			this->_setWidth(18);
			break;
		}
		if( this->x + this->width > this->engine->getWidth() ){
			this->x = this->engine->getWidth() - this->width;
		}
	} else {
		this->_setWidth(w);
	}
	
	this->_initTexture();
	for (int h = 0; h < this->height; ++h) {
		strncpy(this->texture[h],"==========================================================================================",this->width);
	}
}
