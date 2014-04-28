#pragma once
class Figure;
class King;
#include "Cell.h"
#include <cstddef>
enum ChessColor;

class Board
{
public:
	Board();

	const Figure *at(char,char) const;
	const Figure *at(int,int) const;
	const Cell *cellAt(char,char) const;
	const Cell *cellAt(int,int) const;

	static ChessColor flipColor(ChessColor);

	bool isUnderAttack(ChessColor) const;

	bool fieldUnderAttack(const Cell *,ChessColor) const;
	ChessColor getOnMove() const;
	bool isMate();

	bool move(int,int,int,int);

	void registerPromotionCall(Figure *(*)(const Board *));

	~Board();
protected:
	const void *_at(char,char,void ***) const;
	static const int _bSize = 8;

	void _save();
	void _restore();
	Figure ***_state;

	Figure *(*getPromotionPick)(const Board *);

	void _fill();
	ChessColor onMove;
	Cell *cells[Board::_bSize][Board::_bSize];
	Figure *field[Board::_bSize][Board::_bSize];
}; 

