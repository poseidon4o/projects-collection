#include "../include/Shop.h"
#include <iostream>
#include <cstring>

Shop::Shop() {
    this->cnt = 0;
}

void Shop::has(const char* name) const{
    for(int c = 0; c < this->cnt; ++c) {
        if( !strcmp(name,this->catalog[c]->getName()) ){
            std::cout << name << " found! " << std::endl;
            std::cout << "Price: " << this->catalog[c]->getPrice() << std::endl;
            this->catalog[c]->printIngredients();
            return;
        }
    }
    std::cout << "Sorry! " << name << " was not found in our shop!" << std::endl;
}

void Shop::add(const Drink *dr) {
    if( this->cnt == 100 )
        return;
    this->catalog[this->cnt++] = dr->clone();
}

Shop::~Shop() {
    for(int c = 0; c < this->cnt; ++c)
        delete this->catalog[c];
}
