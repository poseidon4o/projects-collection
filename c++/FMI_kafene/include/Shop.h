#ifndef SHOP_H
#define SHOP_H
#include "Drink.h"

class Shop
{
public:
    Shop();
    void has(const char *) const;
    void add(const Drink *);
    ~Shop();

protected:
    int cnt;
    Drink *catalog[100];
};

#endif // SHOP_H
