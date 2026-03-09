#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Drink {
    char name[24];
    float price;
    int8_t is_iced;
};

struct LineItem {
    const struct Drink* drink;
    int8_t quantity;
};

struct Order {
    char customer[24];

    struct LineItem* items;
    size_t num_items;
    size_t capacity;
};

void copy_name(char* dst, size_t dst_size, const char* src) {
    if (!dst || dst_size == 0) return;
    if (!src) src = "";
    strncpy(dst, src, dst_size - 1);
    dst[dst_size - 1] = '\0';
}

struct Drink makeDrink(const char* name, float price, int8_t is_iced) {
    struct Drink d;
    copy_name(d.name, sizeof(d.name), name);
    d.price = price;
    d.is_iced = is_iced ? 1 : 0;
    return d;
}

/*
    orderInit:
    - sets initial fields
    - allocates an initial items array
    - Returns 1 on success, 0 on failure.
*/
int orderInit(struct Order* o, const char* customer, size_t initial_capacity) {
    if (!o) return 0;

    strcpy(o->customer, customer);
    o->num_items = 0;
    o->capacity = 0;
    o->items = NULL;

    if (initial_capacity == 0) {
        return 1;  // this is valid: empty order with no allocation yet
    }

    o->items = malloc(initial_capacity * sizeof(struct LineItem));
    if (!o->items) {
        return 0;
    }
    o->capacity = initial_capacity;
    return 1;
}

/*
    orderDestroy:
    - frees owned heap memory
    - safe to call multiple times
*/
static void orderDestroy(struct Order* o) {
    if (!o) return;
    free(o->items);
    o->items = NULL;
    o->num_items = 0;
    o->capacity = 0;
}

/*
    orderEnsureCapacity:
    - grows items[] so it can hold at least min_capacity entries
    - typical growth strategy: double, starting from 4
    Returns 1 on success, 0 on failure (leaves old memory intact if realloc
   fails).
*/
static int orderEnsureCapacity(struct Order* o, size_t min_capacity) {
    if (!o) return 0;
    if (o->capacity >= min_capacity) return 1;

    size_t new_capacity = (o->capacity == 0) ? 4 : o->capacity;
    while (new_capacity < min_capacity) {
        new_capacity *= 2;
    }

    struct LineItem* new_items =
        realloc(o->items, new_capacity * sizeof(struct LineItem));

    if (!new_items) {
        return 0;  // realloc failed; o->items still valid
    }

    o->items = new_items;
    o->capacity = new_capacity;
    return 1;
}

/*
    orderAddItem:
    - adds a new line item (does not merge duplicates, good follow-up exercise
   you can do!) Returns 1 on success, 0 on failure.
*/
static int orderAddItem(struct Order* o, const struct Drink* d,
                        int8_t quantity) {
    if (!o || !d) return 0;
    if (quantity <= 0) return 0;

    if (!orderEnsureCapacity(o, o->num_items + 1)) {
        return 0;
    }

    o->items[o->num_items].drink = d;
    o->items[o->num_items].quantity = quantity;
    o->num_items++;
    return 1;
}

static float orderTotal(const struct Order* o) {
    if (!o) return 0.0f;

    float total = 0.0f;
    for (size_t i = 0; i < o->num_items; i++) {
        const struct LineItem* li = &o->items[i];
        total += (float)li->quantity * li->drink->price;
    }
    return total;
}

static void printOrder(const struct Order* o) {
    if (!o) return;

    printf("Order for %s\n", o->customer);
    for (size_t i = 0; i < o->num_items; i++) {
        const struct LineItem* li = &o->items[i];
        const struct Drink* d = li->drink;
        float line_total = (float)li->quantity * d->price;

        printf("  %d x %s (%s) @ $%.2f = $%.2f\n", li->quantity, d->name,
               d->is_iced ? "iced" : "hot", d->price, line_total);
    }
    printf("Total: $%.2f\n", orderTotal(o));
}

void increaseQuantity(struct Order* o, const char* drink_name, int amount) {
    if (amount <= 0) {
        return;  // nothing to increase
    }
    for (int i = 0; i < o->num_items; i++) {
        if (strcmp(o->items[i].drink->name, drink_name) == 0) {
            o->items[i].quantity += amount;
            return;
        }
    }
}

void removeDrink(struct Order* o, const char* drink_name) {
    for (int i = 0; i < o->num_items; i++) {
        if (strcmp(o->items[i].drink->name, drink_name) == 0) {
            // Shift everything left
            for (int j = i; j < o->num_items - 1; j++) {
                o->items[j] = o->items[j + 1];
            }
            o->num_items--;
            return;
        }
    }
}

int main(void) {
    /* Shared menu lives for the entire program */
    struct Drink menu[] = {
        makeDrink("Latte", 4.50f, 0),  makeDrink("Cold Brew", 4.25f, 1),
        makeDrink("Tea", 2.00f, 0),    makeDrink("Espresso", 3.00f, 0),
        makeDrink("Matcha", 5.25f, 0),
    };

    struct Order o;
    if (!orderInit(&o, "Amina", 2)) {
        fprintf(stderr, "Failed to initialize order\n");
        return 1;
    }

    /* Add more than initial capacity to show realloc growth. */
    if (!orderAddItem(&o, &menu[0], 2)) fprintf(stderr, "addItem failed\n");
    if (!orderAddItem(&o, &menu[1], 1)) fprintf(stderr, "addItem failed\n");
    if (!orderAddItem(&o, &menu[2], 3)) fprintf(stderr, "addItem failed\n");
    if (!orderAddItem(&o, &menu[3], 1)) fprintf(stderr, "addItem failed\n");
    if (!orderAddItem(&o, &menu[4], 2)) fprintf(stderr, "addItem failed\n");

    printf("\nOrder (original prices):\n");
    printOrder(&o);

    menu[0].price = 4.75f;  // Latte price increased

    printf("\nOrder (after menu price change):\n");
    printOrder(&o);

    increaseQuantity(&o, "Latte", 1);

    printf("\nOrder (after increase Latte quantity):\n");
    printOrder(&o);

    removeDrink(&o, "Tea");

    printf("\nOrder (after remove Tea):\n");
    printOrder(&o);

    orderDestroy(&o);  // free the dynamic array.
    return 0;
}
