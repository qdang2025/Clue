// File inclusions
#include "items.h"
#include "rooms.h"


//This flag allows the add function in adventure.c to add the item to the targeted list if the item is successfully
//removed from the previous list. Otherwise, this variable prevents adding.
bool check = false;

/*
* @param char* string
* @returns struct Item *
* @description
The function is intended to be used as a helper to allocate memory for a new Item struct.
It is simply to decrease code duplicity.
*/
struct Item *makeItem(char *string){
  struct Item *node = (struct Item *)malloc(sizeof(struct Item));
  if (node == NULL){
    printf("Malloc failed");
    exit(1);
  }
  node->name = string;
  node->next = NULL;
  return node;
}

/*
* @param struct Item **
* @param char* string
* @returns void
* @description
The add_item function is a way to add [makeItem(string)] to a linked-list of Item structs.
The [makeItem(string)] is added to the end of the linked list.
*/
void add_item(struct Item **head, char *string){
  struct Item *newNode = makeItem(string);
  struct Item *current = *head;
  if (current == NULL){
    *head = newNode;
    return;
  }
  while (current->next != NULL){
    current = current->next;
  }
  current->next = newNode;
}

/*
* @param struct Item ** head
* @param char* string
* @returns void
The add_item function is a way to remove and Item with -> name = string from a linked-list of Item structs.
*/
void drop_item(struct Item **head, char *string){
  struct Item *current = *head;
  struct Item *previous = NULL;
  while (current != NULL){
    if (strcmp(current->name, string) == 0){
      if (previous == NULL){
        *head = current->next;
      }
      else{
        previous->next = current->next;
      }
      free(current);
      return;
    }
    previous = current;
    current = current->next;
  }
  printf("The item you wanted does not exist! \n");
  check = true;
  return;
}

// This is simply a way to print the linked-list of Items.
void printItemList(struct Item *head){
  struct Item *current = head;
  while (current != NULL){
    if (current->next == NULL){
      printf("%s\n", current->name);
    }
    printf("%s", current->name);
    current = current->next;
  }
}