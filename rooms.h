// Basic libraries
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
Defines the struct for a room.
To identify the room, there is a character pointer to a name string.
There are 4 pointers that are used to represent rooms to the North, South, East, West.
Additionally, there is a pointer to struct Item to represent any items that are present in the room.
Finally, there is another character pointer to a characters string to represent any characters present in the room.
*/
struct room {
      char* name;
      struct room * North;
      struct room * South;
      struct room * East;
      struct room * West;
      struct Item * itemList;
      char * characters[10];
};

// Function declarations to be used in other files
void randomizeGame(struct room* rooms[9], char *answer[3]);
void randomizeItems(struct room* rooms[9], char *answer[3]);
void randomizeCharacters(char* charac[6], char* answer[3], struct room* rooms[9]);
void addCharacter(char *character, int index, struct room* rooms[9]);
