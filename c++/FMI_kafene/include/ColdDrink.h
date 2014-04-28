#ifndef COLDDRINK_H
#define COLDDRINK_H
#include "Drink.h"

class ColdDrink:
    public virtual Drink
{
public:
    ColdDrink(const char *n);
    virtual Drink* clone() const;
};

#endif // COLDDRINK_H
