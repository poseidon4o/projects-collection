#include "../include/ColdDrink.h"

ColdDrink::ColdDrink(const char *name): Drink(name){

}

Drink *ColdDrink::clone() const {
    return new ColdDrink(*this);
}
