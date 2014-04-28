#include "stdafx.h"
#include "Map.h"

Map::Map(Engine &e,int width,int height): floor(NULL), ceiling(NULL), maxInclination(10), engine(&e), offset(0) {
	this->width = this->engine->getWidth() <= width ? width : this->engine->getWidth();
	this->height = height > 0 && height < this->engine->getHeight() ? height : this->engine->getHeight();
	this->floorPixel = this->ceilingPixel = '+';
	this->_generate();
	this->lastDrawnOffset = 0;
	this->isDrawn = false;
}

void Map::_generate() {
	srand(GetTickCount());
	if( this->floor ) delete[] this->floor;
	if( this->ceiling ) delete[] this->ceiling;
	this->floor = new char[this->width];
	this->ceiling = new char[this->width];
	this->ceiling[0] = this->floor[0] = this->maxInclination/2;
	for (int c = 1; c < this->width; ++c) {
		int move = this->floor[c-1] + rand() % 3 - 1;
		this->floor[c] = move > 0 && move <= this->maxInclination ? move : this->floor[c-1];
		move = this->ceiling[c-1] + rand() % 3 - 1; 
		this->ceiling[c] = move > 0 && move <= this->maxInclination ? move : this->ceiling[c-1];
	}
}

void Map::draw() {
	this->_showStats();
	if( this->isDrawn ) this->erase();
	this->isDrawn = true;
	int w = this->engine->getWidth();
	int h = this->engine->getHeight();
	this->lastDrawnOffset = this->offset;
	for (int c = 0; c < w; ++c) {
		for (int r = h - this->floor[c + this->offset]; r < h; ++r) {
			(*this->engine)(c,r,this->floorPixel);
		}
		
		for (int r = h - this->height+1; r <= h - this->height + this->ceiling[c + this->offset]; ++r) {
			(*this->engine)(c,r,this->ceilingPixel);
		}
			


		(*this->engine)(c,h - this->height,'_');
		(*this->engine)(c,h-1,'-');
	}

}

void Map::fullErase() {
	RECT area;
	area.top = this->engine->getHeight() - this->height;
	area.left = 0;
	area.right = this->engine->getWidth()-1;
	area.bottom = this->engine->getHeight()-1;
	this->engine->fill(area,' ');
}

void Map::erase() {
	this->isDrawn = false;
	int w = this->engine->getWidth();
	int h = this->engine->getHeight();
	for (int c = 0; c < w; ++c) {
		(*this->engine)(c,h - this->floor[c + this->lastDrawnOffset],' ');
		(*this->engine)(c,h - this->height + this->ceiling[c + this->lastDrawnOffset],' ');
	}
}

int Map::getWidth() const {
	return this->width;
}

Map& Map::operator++(){
	this->setOffset(this->offset + 1);
	return *this;
}

Map& Map::operator--() {
	this->setOffset(this->offset - 1);
	return *this;
}

Map& Map::operator+=(int move) {
	this->setOffset(this->offset + move);
	this->fullErase();
	return *this;
}

Map& Map::operator-=(int move) {
	return (*this) += move;
}

int Map::getOffset() const {
	return this->offset;
}

void Map::setOffset(int off) {
	this->offset = this->width - this->engine->getWidth() >= off && off >= 0 ? off : this->offset;
}

int Map::getHighestBetweenRelative(int start,int end) const {
	return this->getHighestBetween(start + this->offset, end + this->offset);
}

int Map::getHighestBetween(int start,int end) const {
	if( end < start ) {
		int tmp = start;
		start = end;
		end = tmp;
	}
	if( !this->_validPostion(start) || !this->_validPostion(end) )
		return -1;

	int max = -1;
	for(;start <= end; ++start)
		if( this->floor[start] > max )
			max = this->floor[start];

	return max;
}

int Map::getSliceHeight(int pos) const {
	if( this->_validPostion(pos) )
		return this->height - (int)this->floor[pos] - (int)this->ceiling[pos];
	else
		return -1;
}

int Map::operator()(int pos) const {
	return this->getFloorHeight(pos);
}

void Map::getSlice(int pos,int *top,int *bot) const{
	if( this->_validPostion(pos) ) {
		*top = (int) this->ceiling[pos];
		*bot = (int) this->floor[pos];
	} else {
		*bot = *top = -1;
	}
}

int Map::getCeilingHeight(int pos) const {
	if( this->_validPostion(pos) )
		return (int) this->ceiling[pos];
	else
		return -1;
}

int Map::getFloorHeight(int pos) const {
	if( this->_validPostion(pos) ) 
		return (int) this->floor[pos];
	else
		return -1;
}

int Map::getMaxInclination() const {
	return this->maxInclination;
}

void Map::_showStats() {
	(*this->engine)(0,0,"                       ");
	(*this->engine)(0,0,"Offset: ");
	(*this->engine)(this->offset);
}

bool Map::_validPostion(int pos) const {
	return pos >= 0 && pos < this->width;
}

Map::~Map() {
	if( this->floor )
		delete[] this->floor;
	if( this->ceiling )
		delete[] this->ceiling;
}