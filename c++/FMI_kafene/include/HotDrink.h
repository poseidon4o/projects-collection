#ifndef HOTDRINK_H
#define HOTDRINK_H
#include "Drink.h"

class HotDrink:
    public virtual Drink
{
public:
    HotDrink(const char *,double multiplier = 1);
    double getPrice() const;
    virtual Drink* clone() const;
protected:
    float multiplier;
};

#endif // HOTDRINK_H
