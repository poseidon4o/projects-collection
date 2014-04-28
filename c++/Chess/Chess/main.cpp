#include <iostream>
#include "Board.h"
#include "Figure.h"
#include "Engine.h"
#include "Renderer.h"
#include "Queen.h"
#include "Knight.h"
#include "Pawn.h"
#include <Windows.h>

using namespace std;

Direction readSelectorMove();
POINT mReadSelectorMove(Engine *);
bool readTargetMove();
bool mReadTargetMove(Engine *);

POINT getNormalizedPoint(Engine *);

Figure *getPromotionPick(const Board *);

enum { KEYBOARD, MOUSE, BOTH} controlMode;


int main() {

	controlMode = MOUSE;

	Board board;
	board.registerPromotionCall(getPromotionPick);
	Engine engine(80,80,true);
	Renderer renderer(&engine,&board);

	while(true) {

		switch (controlMode) {
			case KEYBOARD:
				renderer.moveSelector(readSelectorMove());
				renderer.moveTarget(readTargetMove());
				break;
			case MOUSE:
				renderer.moveSelector(mReadSelectorMove(&engine));
				renderer.moveTarget(mReadTargetMove(&engine));
				break;
			default:
				break;
		}

		renderer.draw();
		engine.draw(Clean);

		if( board.isMate() ) {
			engine.clear();
			engine.draw();

			break;
		}
			

		Sleep(1000/60);
	}

	cout << (board.getOnMove() == WHITE  ? "WHITE" : "BLACK") << " is winner.";
	cin.get();
	return 0;
}

Figure *getPromotionPick(const Board *board) {
	// TODO: complete
	return new Queen(board->getOnMove());
}

bool readTargetMove() {
	return (bool)GetAsyncKeyState(VK_RETURN);
}

bool mReadTargetMove(Engine *e) {
	POINT mouse = getNormalizedPoint(e);
	static HWND cons = GetConsoleWindow();
	static RECT win;
	GetWindowRect(cons,&win);
	return GetAsyncKeyState(VK_LBUTTON) && mouse.x > 0 && mouse.y > 0 && mouse.x < win.right-win.left && mouse.y < win.bottom - win.top;
}

Direction readSelectorMove() {
	static int lastRead = GetTickCount();
	if( GetTickCount() - lastRead < 200 )
		return NONE;
	lastRead = GetTickCount();
	return GetAsyncKeyState(VK_LEFT) ? LEFT : GetAsyncKeyState(VK_RIGHT) ? RIGHT : GetAsyncKeyState(VK_UP) ? UP : GetAsyncKeyState(VK_DOWN) ? DOWN : NONE;
}

POINT mReadSelectorMove(Engine *e) {
	POINT mouse = getNormalizedPoint(e);
	mouse.x /= e->getPixelWidth();
	mouse.y /= e->getPixelHeight();
	return mouse;
}

POINT getNormalizedPoint(Engine *e) {
	static POINT mouse;
	static HWND cons = GetConsoleWindow();
	GetCursorPos(&mouse);
	ScreenToClient(cons,&mouse);
	return mouse;
}