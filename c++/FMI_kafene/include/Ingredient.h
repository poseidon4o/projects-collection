#ifndef INGREDIENT_H
#define INGREDIENT_H


class Ingredient
{
public:
    Ingredient(const char *name = "",double price = 0.0);
    Ingredient(const Ingredient &);
    Ingredient& operator=(const Ingredient &);

    void setName(const char*);

    const char *getName() const;
    double getPrice() const;
    ~Ingredient();
protected:
    char *name;
    double price;

};

#endif // INGREDIENT_H
