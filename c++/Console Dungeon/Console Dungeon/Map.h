#pragma once
class Map
{
public:
	Map(Engine &,int,int);
	Map(Engine &,const char *);
	~Map();
	int getWidth() const;
	int getMaxInclination() const;
	int getFloorHeight(int) const;
	int getCeilingHeight(int) const;
	void getSlice(int,int *,int *) const;
	int getSliceHeight(int) const;
	int operator()(int) const;
	int getOffset() const;

	int getHighestBetween(int,int) const;
	int getHighestBetweenRelative(int,int) const;

	void setOffset(int);
	void draw();
	void erase();
	void fullErase();

	Map& operator++();
	Map& operator--();
	Map& operator+=(int);
	Map& operator-=(int);
protected:
	char floorPixel;
	char ceilingPixel;
	int lastDrawnOffset;
	bool isDrawn;
	Engine *engine;
	char *floor;
	char *ceiling;
	int width;
	int height;
	int offset;
	const int maxInclination;
	bool _validPostion(int) const;
	void _generate() ;
	void _showStats();
};

