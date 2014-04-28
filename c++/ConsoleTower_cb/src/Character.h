#pragma once
class Character:
	public Object
{
public:
	Character(Engine &e,int x = 0,int y = 0);
	bool move(Block **,int);
protected:
	bool isFast;
	bool isJumping;
	int currentVelocity;
	int jumpStart;
	int jumpVelocity;
	int sideSpeed;
	int fastSpeed;
};

