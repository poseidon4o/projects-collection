#include "Board.h"
#include "Figure.h"
#include "Pawn.h"
#include "Queen.h"
#include "Knight.h"
#include "King.h"
#include <cassert>
#include <cmath>

Board::Board(): getPromotionPick(NULL) {
	this->onMove = WHITE;
	this->_fill();
}

void Board::registerPromotionCall(Figure *(*func)(const Board *)) {
	this->getPromotionPick = func ? func : this->getPromotionPick;
}

ChessColor Board::flipColor(ChessColor color) {
	return (ChessColor)-((int)color);
} 

const Figure *Board::at(int c,int r) const{
	return (c != -1 && r != -1) ? this->field[c][r] : NULL;
}

const Figure *Board::at(char c,char r) const {
	return this->at(Cell::toIndex(c), Cell::toIndex(r));
}

const Cell *Board::cellAt(int c,int r) const {
	return (c != -1 && r != -1) ? this->cells[c][r] : NULL;
}

const Cell *Board::cellAt(char c,char r) const {
	return this->cellAt(Cell::toIndex(c),Cell::toIndex(r));
}

const void *Board::_at(char c,char r,void ***from) const{
	int col = Cell::toIndex(c);
	int row = Cell::toIndex(r);
	return (col != -1 && row != -1) ? from[col][row] : NULL;
}

ChessColor Board::getOnMove() const {
	return this->onMove;
}

bool Board::isMate() {
	if( !this->isUnderAttack(WHITE) && !this->isUnderAttack(BLACK) )
		return false;

	
	ChessColor attacked = this->isUnderAttack(WHITE) ? WHITE : BLACK;
	this->_save();

	for(int c = 0; c < Board::_bSize; ++c) {
		for(int r = 0; r < Board::_bSize; ++r) {
			const Figure *fig;
			if( (fig = this->at(c,r)) && fig->getColor() == attacked ) {
				for(int cTo = 0; cTo < Board::_bSize; ++cTo) {
					for(int rTo = 0; rTo < Board::_bSize; ++rTo) {
						if( this->move(c,r,cTo,rTo) ) {
							this->_restore();
							return false;
						}
					}
				}
			}
		}
	}

	return true;
}

void Board::_save() {
	this->_state = (Figure ***)this->field;
}

void Board::_restore() {
	if( !this->_state ) return;
	for(int c = 0; c < Board::_bSize; ++c)
		for(int r = 0; r < Board::_bSize; ++r)
			this->field[c][r] = this->_state[c][r];
}

bool Board::fieldUnderAttack(const Cell *target,ChessColor color) const {
	const Figure *fig;
	for (int c = 0; c < Board::_bSize; ++c)
		for (int r = 0; r < Board::_bSize; ++r)
			if(	(fig = this->at(c,r)) &&
				fig->getColor() == color && 
				fig->isValid(this->cellAt(c,r),target,this)  &&
				(	
					!dynamic_cast<const Pawn *>(fig) || 
					(
						dynamic_cast<const Pawn *>(fig) && 
						abs(c - target->col()) == 1 && 
						abs(r - target->row()) == 1
					)
				) 
			)
				return true;
	return false;
}

bool Board::isUnderAttack(ChessColor color) const {
	const King *king;
	for( int c = 0; c < Board::_bSize; ++c)
		for( int r = 0; r < Board::_bSize; ++r)
			if( this->at(c,r) && (king = dynamic_cast<const King *>(this->at(c,r))) && king->getColor() == color )
				return this->fieldUnderAttack(this->cellAt(c,r), Board::flipColor(color) );
	assert("Board::isUnderAttack() failed" && false);
}

bool Board::move(int cFrom,int rFrom,int cTo,int rTo) {
	if( cFrom < 0 || cFrom >= Board::_bSize || rFrom < 0 || rFrom >= Board::_bSize || cTo < 0 
				  || cTo >= Board::_bSize || rTo < 0 || rTo > Board::_bSize)
		return false;
	
	const Cell *cellFrom = this->cellAt(cFrom,rFrom);
	const Cell *cellTo = this->cellAt(cTo,rTo);
	if( !cellFrom || !cellTo )
		return false;
	
	Figure *fig = this->field[cFrom][rFrom];
	Figure *target = this->field[cTo][rTo];

	if( !fig || this->onMove != fig->getColor() || !fig->isValid(cellFrom,cellTo,this) )
		return false;



	const Pawn *pwn;
	const King *king;
	if( pwn = dynamic_cast<const Pawn *>(fig) ) {
		// check for pawn special moves
		if( rTo == 0 || rTo == 7 ) {
			// promotion
			Figure *prom;
			if(false && this->getPromotionPick )
				prom = this->getPromotionPick(this);
			else 
				prom = new Queen(this->onMove);

			Figure *tmp = this->field[cTo][rTo];
			
			this->field[cFrom][rFrom] = NULL;
			this->field[cTo][rTo] = prom;

			if( this->isUnderAttack(this->onMove) ) {
				// can't move into check
				this->field[cFrom][rFrom] = fig;
				this->field[cTo][rTo] = tmp;
				delete prom;
				return false;
			} else {
				delete fig;
				delete tmp;
				this->onMove = Board::flipColor(this->onMove);
				return true;
			}
		}

		if( cFrom != cTo && !target) {
			// en passant
			const Figure *tmp = this->at(cTo,rFrom);
			this->field[cFrom][rFrom] = NULL;
			this->field[cTo][rFrom] = NULL;
			this->field[cTo][rTo] = fig;
			if( this->isUnderAttack(this->onMove) ) {
				// can't move into check
				this->field[cFrom][rFrom] = this->field[cTo][rTo];
				this->field[cTo][rTo] = NULL;
				this->field[cTo][rFrom] = (Figure*)tmp;
				return false;// failed en passant
			} else {
				this->onMove = Board::flipColor(this->onMove);
				fig->doMove();
				delete tmp;
				return true; // succesful en passant
			}
		}
	} else if( (king = dynamic_cast<const King *>(fig)) && abs(cFrom-cTo) == 2) {// if move is valid and it is more than 1 space long -> castle
		
		// move king
		this->field[cTo][rTo] = this->field[cFrom][rFrom];
		this->field[cFrom][rFrom] = NULL;
		
		// move rook
		int mv = cFrom < cTo ? -1 : 1;
		int rookCol = mv == 1 ? 0 : 7;
		this->field[cFrom - mv][rFrom] = this->field[rookCol][rFrom];
		this->field[rookCol][rFrom] = NULL;

		this->onMove = Board::flipColor(this->onMove);
		fig->doMove();
		return true;
		// no need to check for check state as castle is not valid when checked
	} 

	this->field[cTo][rTo] = fig;
	this->field[cFrom][rFrom] = NULL;
	if( this->isUnderAttack(this->onMove) ) {
		// can't move and become attacked
		this->field[cFrom][rFrom] = fig;
		this->field[cTo][rTo] = target;
		return false;
	} else {
		this->onMove = Board::flipColor(this->onMove);
		fig->doMove();
		return true;
	}

}

void Board::_fill() {
	for(int c = 0; c < Board::_bSize; ++c) {
		for(int r = 0; r < Board::_bSize; ++r) {
			this->field[c][r] = NULL;
			this->cells[c][r] = new Cell(c,r);
		}
	}
			

	for(int c = 0; c < Board::_bSize; ++c){
		this->field[c][1] = new Pawn(WHITE);
		this->field[c][6] = new Pawn(BLACK);
	}
	
	this->field[0][0] = new Rook(WHITE);
	this->field[7][0] = new Rook(WHITE);
	this->field[0][7] = new Rook(BLACK);
	this->field[7][7] = new Rook(BLACK);
	
	this->field[1][0] = new Knight(WHITE);
	this->field[6][0] = new Knight(WHITE);
	this->field[1][7] = new Knight(BLACK);
	this->field[6][7] = new Knight(BLACK);

	this->field[2][0] = new Bishop(WHITE);
	this->field[5][0] = new Bishop(WHITE);
	this->field[2][7] = new Bishop(BLACK);
	this->field[5][7] = new Bishop(BLACK);
	
	this->field[3][0] = new Queen(WHITE);
	this->field[3][7] = new Queen(BLACK);
	
	this->field[4][0] = new King(WHITE);
	this->field[4][7] = new King(BLACK);
}

Board::~Board() {
	for(int c = 0; c < Board::_bSize; ++c)
		for(int r = 0; r < Board::_bSize; ++r)
			delete this->field[c][r];
}