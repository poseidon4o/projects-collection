#include "../include/HotDrink.h"

HotDrink::HotDrink(const char *name,double multiplier): Drink(name) {
    this->multiplier = multiplier >= 1 ? multiplier : 1;
}

double HotDrink::getPrice() const {
    return this->price * this->multiplier;
}

Drink* HotDrink::clone() const {
    return new HotDrink(*this);
}
