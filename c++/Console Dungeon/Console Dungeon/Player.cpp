#include "stdafx.h"
#include "Player.h"

Player::Player(Engine &e,Texture &t, int x, int y,Map &m): Object(e,t,x,y), Creature(), map(m) {
	this->speed = 3;
	
}

int Player::_x() const {
	return (GetAsyncKeyState(VK_LEFT) ? -1 : GetAsyncKeyState(VK_RIGHT) ? 1 : 0) * this->speed;
}

bool Player::_j() const {
	return (bool) GetAsyncKeyState(VK_SPACE);
}

bool Player::_inAir() const {
	return this->position.y < this->engine->getHeight() - this->map.getHighestBetweenRelative(this->position.x,this->position.x + this->width-1) - this->height;
}

bool Player::_inGround() const {
	return this->position.y > this->engine->getHeight() - this->map.getHighestBetweenRelative(this->position.x,this->position.x + this->width-1) - this->height;
}

void Player::move() {
	static int lastCall = GetTickCount();

	if( GetTickCount() - lastCall < 1000/30 )
		return;

	lastCall = GetTickCount();
	this->_moveX();
	this->_moveY();
}

void Player::_moveX() {
	int mv = this->_x();
	if( !mv ) return;	

	if( this->position.x + mv < 0 ) {
		this->position.x = 0;
		return;
	}
	if( this->position.x + this->width + mv > this->engine->getWidth() ) {
		this->position.x = this->engine->getWidth() - this->width;
		return;
	}
	

	if(mv > 0) {
		// moving right
		if( this->position.x > this->engine->getWidth() * 0.8 ) {
			this->map += mv;
		} else {
			this->position.x += mv;
		}
	} else {
		// moving left
		if( this->position.x < this->engine->getWidth() * 0.2 && this->map.getOffset() ) {
			this->map += mv;
		} else {
			this->position.x += mv;
		}
	}
}

void Player::_moveY() {
	if( this->_inAir() ) 
		this->position.y++;

	if( this->_inGround() )
		this->position.y = this->engine->getHeight() - this->map.getHighestBetweenRelative(this->position.x,this->position.x + this->width-1) - this->height;

	if( !this->_inAir() && this->_j() ) {


	}
}
