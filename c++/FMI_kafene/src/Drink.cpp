#include "../include/Drink.h"
#include <cstring>
#include <iostream>

const int Drink::max = 100;

Drink::Drink(const char *name): name(NULL), quantity(NULL), ing(NULL) {
    this->setName(name);
    this->init();
}

Drink::Drink(const Drink &dr): name(NULL), quantity(NULL), ing(NULL) {
    this->setName(dr.name);
    this->init();
    this->count = dr.count;
    for(int c = 0; c < this->count;++c) {
        this->ing[c] = dr.ing[c];
        this->quantity[c] = dr.quantity[c];
    }
    this->price = dr.price;
}

Drink& Drink::operator=(const Drink &dr) {
    if( this == &dr )
        return *this;
    this->setName(dr.name);
    this->count = dr.count;
    for(int c = 0; c < this->count; ++c) {
        this->ing[c] = dr.ing[c];
        this->quantity[c] = dr.quantity[c];
    }
    this->price = dr.price;
}

void Drink::init() {
    this->count = 0;
    this->quantity = new int[Drink::max];
    this->ing = new Ingredient[Drink::max];
}

void Drink::setName(const char *name) {
    name = name ? name : "";
    delete[] this->name;
    this->name = new char[strlen(name)+1];
    strcpy(this->name,name);
}

bool Drink::addIngredient(const Ingredient &in,int qa) {
    if( this->count == Drink::max )
        return false;
    if( qa < 1 )
        return false;
    this->ing[this->count] = in;
    this->quantity[this->count] = qa;
    this->price += in.getPrice() * qa;
    this->count++;
    return true;
}

void Drink::printIngredients() const {
    using namespace std;
    cout << "Recepie for " << this->name << endl;
    for(int c = 0; c < this->count; ++c){
        cout << (c+1) << ": " << this->quantity[c] << "x" << this->ing[c].getName() << endl;
    }
}

const char *Drink::getName() const {
    return this->name;
}

double Drink::getPrice() const {
    return this->price;
}

Drink::~Drink() {
    delete[] this->name;
    delete[] this->quantity;
    delete[] this->ing;
}
