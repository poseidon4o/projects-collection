#ifndef DRINK_H
#define DRINK_H
#include "../include/Ingredient.h"

class Drink
{
public:
    Drink(const char *);
    Drink(const Drink &);
    Drink& operator=(const Drink &);
    virtual Drink *clone() const = 0;
    virtual double getPrice() const;
    const char *getName() const;
    bool addIngredient(const Ingredient &in,int quantity = 1);
    void printIngredients() const;
    void setName(const char *);
    virtual ~Drink();
protected:
    void init();
    static const int max;
    int count;
    char *name;
    int *quantity;
    Ingredient *ing;
    double price;
};

#endif // DRINK_H
