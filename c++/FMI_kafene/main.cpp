#include <iostream>
#include "include/Ingredient.h"
#include "include/ColdDrink.h"
#include "include/HotDrink.h"
#include "include/Shop.h"

using namespace std;

int main()
{
    try {
        Ingredient water_i("Water",0.5);
        Ingredient shugar_i("Shugar",3);
        Ingredient black_tea_i("Black tea",10);
        Ingredient coffee_i("Coffee",5);

        HotDrink tea("Tea",2);
        tea.addIngredient(shugar_i,2);
        tea.addIngredient(water_i);
        tea.addIngredient(black_tea_i);

        ColdDrink coffee("Cold Coffee");
        coffee.addIngredient(water_i);
        coffee.addIngredient(coffee_i);
        coffee.addIngredient(shugar_i,3);

        Shop kafeneto_pred_FMI;

        kafeneto_pred_FMI.add(&tea);
        kafeneto_pred_FMI.add(&coffee);

        kafeneto_pred_FMI.has("Tea");
        kafeneto_pred_FMI.has("Grog");

    } catch (bad_alloc) {
        cerr << "Can't allocate memmory for drinks, ingredients or shop!";
        return 1;
    }





    return 0;
}
