#include "../include/Ingredient.h"
#include <cstring>

Ingredient::Ingredient(const char *name,double price): name(NULL) {
    this->setName(name);
    this->price = price >= 0 ? price : 0;
}

Ingredient::Ingredient(const Ingredient &in): name(NULL) {
    this->price = in.price;
    this->setName(in.name);
}

Ingredient& Ingredient::operator=(const Ingredient &in) {
    if( this == &in )
        return *this;
    this->price = in.price;
    this->setName(in.name);
}

void Ingredient::setName(const char *name) {
    delete[] this->name;
    name = name ? name : "";
    this->name = new char[strlen(name)+1];
    strcpy(this->name,name);
}

const char *Ingredient::getName() const {
    return this->name;
}

double Ingredient::getPrice() const {
    return this->price;
}

Ingredient::~Ingredient() {
    delete[] this->name;
}
