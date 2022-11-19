#include <stdbool.h>
// This variable is globalized and is used to as a way to ensure that an item exists when dropping or adding.
// If check = 0, the item doesn't exist.
// Else, check = 1, and the item exists.
extern bool check;

/*
Defines the struct for an Item.
To identify an Item, there is a character pointer to a name string.
Additionally, there is a pointer to the next Item in the linked list of Items [used later].
*/
struct Item {
      char * name;
      struct Item * next;
};

// Function declarations to use in different files
struct Item * makeItem(char * string);
void add_item(struct Item ** head, char * string);
void drop_item(struct Item ** head, char * string);
void printItemList(struct Item * head);