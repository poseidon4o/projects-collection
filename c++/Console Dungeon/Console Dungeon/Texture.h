#pragma once
class Texture
{
public:
	Texture(int,int,const char *);
	Texture();
	Texture(const Texture &);
	Texture& operator=(const Texture &);
	void init(int,int,const char *);
	const char **getTexture() const;
	int getWidth() const;
	int getHeight() const;
	~Texture();
protected:
	int width;
	int height;
	char **texture;
private:
	bool isInit;
};

