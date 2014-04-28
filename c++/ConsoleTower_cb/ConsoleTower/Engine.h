#ifndef ENGINE_H
#define ENGINE_H


enum DrawMethod {Brush,Clean};
class Engine
{
public:
	Engine(int,int);
	void operator()(int);
	void operator()(char);
	void operator()(const char *);
	void operator()(const char *,int);
	void operator()(int,int,char);
	void operator()(int,int,const char*);
	void operator()(int,int,const char*,int);
	void draw(DrawMethod d = Brush);
	void clear();
	int getPixelsDrawn() const;
	int getWidth() const;
	int getHeight() const;
	~Engine();
protected:
	HANDLE console;
	int pixelsDrawn;
	int rows;
	int cols;
	int lastCol;
	int lastRow;
	char **nextFrame;
	char *drawBuff;
	char **field;
	void _moveBrush(int,int);
	void _endLine(int);
	void _resizeConsole(int,int) const;
	void _getNextBlock(int,int,char *);
	void _moveConsole(int,int) const;
	void _hideBrush() const;
};
#endif // ENGINE_H
