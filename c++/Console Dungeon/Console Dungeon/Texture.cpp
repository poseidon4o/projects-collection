#include "stdafx.h"
#include "Texture.h"


Texture::Texture(): texture(NULL) {
	this->isInit = false;
}

Texture::Texture(int width,int height,const char *buf): texture(NULL) {
	this->isInit = true;
	this->init(width,height,buf);
}

Texture::Texture(const Texture &t): texture(NULL) {
	this->texture = new char*[t.getWidth()];
	for(int w = 0; w < t.getWidth(); ++w){
		this->texture[w] = new char[t.getHeight()];
		for(int h = 0; h < t.getHeight(); ++h){
			this->texture[w][h] = t.getTexture()[w][h];
		}
	}			
}

Texture& Texture::operator=(const Texture &t) {
	if( this == &t )
		return *this;

	for(int w = 0; w < this->width; ++w)
		delete[] this->texture[w];
	delete[] this->texture;

	this->texture = new char*[t.getWidth()];
	for(int w = 0; w < t.getWidth(); ++w){
		this->texture[w] = new char[t.getHeight()];
		for(int h = 0; h < t.getHeight(); ++h){
			this->texture[w][h] = t.getTexture()[w][h];
		}
	}
}

int Texture::getWidth() const {
	return this->width;
}

int Texture::getHeight() const {
	return this->height;
}

const char **Texture::getTexture() const {
	return (const char **)this->texture;
}

void Texture::init(int width,int height,const char *buf) {
	this->isInit = true;
	if( width < 0 || height < 0 ) 
		return;
	this->width = width;
	this->height = height;
	this->texture = new char*[width];
	int c = 0;
	for(int w = 0; w < width; w++){
		this->texture[w] = new char[height];
		for(int h = 0; h < height; h++)
			this->texture[w][h] = buf[c++];
	}
}

Texture::~Texture() {
	if( this->isInit && this->texture ) {
		for (int w = 0; w < this->width; ++w)
			delete[] this->texture[w];
		delete[] this->texture;
	}
}
