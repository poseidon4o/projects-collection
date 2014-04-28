#include "Bishop.h"
#include <algorithm>

Bishop::Bishop(ChessColor color): Figure(color) {

}

bool Bishop::isValid(const Cell *from,const Cell *to,const Board *board) const {

	if( !Figure::isValid(from,to,board) ) return false;

	if( abs(from->col() - to->col()) != abs(from->row() - to->row()) ) // not diagonal move
		return false;
	
	if( from->col() > to->col() ) {
		if( from->row() > to->row() ) {
			for(int c = from->col() -1, r = from->row()-1; c > to->col() && r > to->row(); --c, --r)
				if( board->at(c,r) )
					return false;
		} else {
			for(int c = from->col()-1, r = from->row()+1; c > to->col() && r < to->row(); --c, ++r)
				if( board->at(c,r) )
					return false;
		}
	} else {
		if( from->row() > to->row() ) {
			for(int c = from->col()+1, r = from->row()-1; c < to->col() && r > to->row(); ++c, --r)
				if( board->at(c,r) )
					return false;
		} else {
			for(int c = from->col()+1, r = from->row()+1; c < to->col() && r < to->row(); ++c, ++r)
				if( board->at(c,r) )
					return false;
		}
	}

	return true;
}
