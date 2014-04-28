// Console Dungeon.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

const int height = 80;
const int width = 200;
const int hudHeight = 15;

int _tmain(int argc, _TCHAR* argv[])
{
	
	Engine p(width,height,1);
	Map map(p,width*20,height-hudHeight);
	char t_data[1000] = "                                                                                                                                             /O\           x ^ x     (@@)x  |  x(@@) (@)x  |  x(@)      x | x            x       ";
	//char t_data[90] = "  (     @(    @@    ))    xx   x  x /     O^|||x\      x  x   xx    ((    @@    @)    )   ";
	Texture text(15,15,t_data);

	Player obj(p,text,10,30,map);


	p.clear();
	while (true) {
		
		map.erase();
		obj.erase();		
		
		obj.move();

		map.draw();
		obj.draw();
		
		p.draw();
		Sleep(1000/60);
	}


	cin.get();

	return 0;
}