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

Character::Character(Engine &e,int x,int y): Object(e,x,y) {
	this->_setHeight(3);
	this->_setWidth(3);
	this->_initTexture();

	strncpy(this->texture[0]," o ",3);
	strncpy(this->texture[1],"-|-",3);
	strncpy(this->texture[2],"/ \\",3);

	this->isJumping = false;
	this->currentVelocity = this->jumpVelocity = 3;
	this->sideSpeed = 1;
	this->isFast = false;
	this->fastSpeed = 1;
}

bool Character::move(Block **blocks,int n) {
	static int accelSteps = 0;
	if( this->y + this->height >= this->engine->getHeight() )
		return false;
	static int lastHorizontalMove = GetTickCount();
	int change = 0;
	if ( GetTickCount() - lastHorizontalMove > 2 ){
		lastHorizontalMove = GetTickCount();
		change = (this->isFast*this->fastSpeed + this->sideSpeed)*(GetAsyncKeyState(VK_LEFT) ? -1 : GetAsyncKeyState(VK_RIGHT) ? 1 : 0);
		if( change == 0 )
			accelSteps = 0;
		else if( !this->isJumping )
			accelSteps++;
		if( accelSteps > 5 )
			this->isFast = true;
		else
			this->isFast = false;

		this->x += change;
		if( this->x < 0 )
			this->x = 0;
		if( this->x + this->width > this->engine->getWidth() )
			this->x = this->engine->getWidth() - this->width;
	}

	static int lastFallAction = GetTickCount();
	if( !this->isJumping && GetTickCount() - lastFallAction > 50){
		lastFallAction = GetTickCount();
		bool isFalling = true;
		for (int c = 0; c < n; ++c) {
			if( this->y + this->height == blocks[c]->getY() &&
				(this->x + this->width >= blocks[c]->getX() && this->x <= blocks[c]->getX() + blocks[c]->getWidth() ) ){
				isFalling = false;
				break;
			}
		}
		if( isFalling ){
			this->isJumping = true;
			this->currentVelocity = -this->jumpVelocity;
			this->jumpStart = GetTickCount();
		}
	}

	static int lastJumpAction = GetTickCount();
	if(  GetTickCount() - lastJumpAction > 35 ){
		lastJumpAction = GetTickCount();
		if( ( GetAsyncKeyState(VK_SPACE) || GetAsyncKeyState(VK_UP) ) && !this->isJumping){
			this->isJumping = true;
			this->currentVelocity = this->jumpVelocity;
			this->jumpStart = GetTickCount();
		}
		if( this->isJumping ){
			int nextY = this->y + -1*(this->currentVelocity - this->G*(GetTickCount() - this->jumpStart) / 1000 + this->isFast*this->fastSpeed);
			for (int c = 0; c < n; ++c) {
				if( this->y + this->height <= blocks[c]->getY() &&
					nextY + this->height > blocks[c]->getY() &&
					this->x + this->width >= blocks[c]->getX() &&
					this->x - this->width <= blocks[c]->getX() + blocks[c]->getWidth() ){

					this->y = blocks[c]->getY() - this->height;
					this->isJumping = false;
					return true;
				}
			}
			this->y = nextY;
			if( this->y + this->height >= this->engine->getHeight() ){
				return false;
			}
		}
	}

	return true;
}
