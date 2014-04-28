#pragma once
#include "stdafx.h"
class Player :
	public Creature,
	public Object
{
public:
	Player(Engine &,Texture &, int, int,Map &);

	void move();
protected:
	void _moveY();
	void _moveX();

	int _x() const;
	bool _j() const;

	void _right();
	void _left();

	int speed;


	bool _inAir() const;
	bool _inGround() const;

	int _fallTime;

	Map &map;
};

