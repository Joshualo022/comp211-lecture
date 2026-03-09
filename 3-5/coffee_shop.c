#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 8

struct Drink {
    char name[24];
    float price;
    int8_t is_iced;  // 0 hot, 1 iced
};

struct LineItem {
    struct Drink drink;
    int8_t quantity;
};

struct Order {
    char customer[24];
    struct LineItem items[MAX_ITEMS];
    int8_t num_items;
};

/* -------------------- functions -------------------- */

struct Drink makeDrink(const char* name, float price, int8_t is_iced) {}

struct Order initOrder(const char* customer) {}

struct Order addItem(struct Order o, struct Drink d, int8_t quantity) {}

float orderTotal(struct Order o) {}

void printOrder(struct Order o) {}

/* -------------------- main  -------------------- */
int main(void) {
    struct Drink latte = makeDrink("Latte", 4.50f, 0);
    struct Drink cold_brew = makeDrink("Cold Brew", 4.25f, 1);
    struct Drink tea = makeDrink("Tea", 2.00f, 0);

    struct Order o = initOrder("Amina");

    o = addItem(o, latte, 2);
    o = addItem(o, cold_brew, 1);
    o = addItem(o, tea, 3);

    printf("\nOrder:\n");
    printOrder(o);

    return 0;
}
