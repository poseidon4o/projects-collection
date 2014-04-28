#pragma once
#include "stdafx.h"
class Object
{
public:
	Object(Engine &,Texture &,int x = 0,int y = 0);
	void setX(int);
	void setY(int);
	int getX() const;
	int getY() const;
	int getWidth() const;
	int getHeight() const;
	void setWidth(int);
	void setHeight(int);
	void draw() const;
	void erase() const;
protected:
	void _setWidth(int);
	void _setHeight(int);
	void _initTexture();
	Texture texture;
	Engine *engine;
	const float G;
	int h;
	int w;
	int height;
	int width;
	struct {int x,y;} position;
};

