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
    int8_t num_items;  // how many entries in items[] are currently used
};

struct Drink makeDrink(const char* name, float price, int8_t is_iced) {
    struct Drink d;
    strcpy(d.name, name);
    d.price = price;
    d.is_iced = is_iced;
    return d;
}

struct Order initOrder(const char* customer) {
    struct Order o;
    strcpy(o.customer, customer);
    o.num_items = 0;
    return o;
}

struct Order addItem(struct Order o, struct Drink d, int8_t quantity) {
    if (quantity <= 0) {
        return o;
    }
    if (o.num_items >= MAX_ITEMS) {
        return o;
    }

    o.items[o.num_items].drink = d;  // struct assignment copies the whole Drink
    o.items[o.num_items].quantity = quantity;
    o.num_items++;

    return o;
}

float orderTotal(struct Order o) {
    float total = 0.0f;
    for (int i = 0; i < o.num_items; i++) {
        total += (float)o.items[i].quantity * o.items[i].drink.price;
    }
    return total;
}

void printOrder(struct Order o) {
    printf("Order for %s\n", o.customer);

    for (int i = 0; i < o.num_items; i++) {
        struct LineItem li = o.items[i];
        float line_total = (float)li.quantity * li.drink.price;

        printf("  %d x %s (%s) @ $%.2f = $%.2f\n", li.quantity, li.drink.name,
               li.drink.is_iced ? "iced" : "hot", li.drink.price, line_total);
    }

    printf("Total: $%.2f\n", orderTotal(o));
}

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
