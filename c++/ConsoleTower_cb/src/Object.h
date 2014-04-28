#pragma once
class Object
{
public:
	Object(Engine &e,int x = 0,int y = 0);
	~Object();
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
	Engine *engine;
	const float G;
	int h;
	int w;
	int height;
	int width;
	int x;
	int y;
	char **texture;
};

