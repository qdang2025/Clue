/// File inclusions
#include "rooms.h"
#include "items.h"

/*
* @param struct room* rooms[9]
* @param char *answer[3]
* @returns void
* @description
randomizeGame() randomizes the room positions so that at the start of every game, there are new locations for every room.
The shuffling was done via the Fisher-Yates algorithm.
*/
void randomizeGame(struct room* rooms[9], char *answer[3]){
      int i, j;
      struct room *temp;
      for (i = 8; i > 0; i--){
            j = rand() % 9;
            temp = rooms[i];
            rooms[i] = rooms[j];
            rooms[j] = temp;
      }
      // intialize the connections for room 0
      rooms[0]->South = rooms[3];
      rooms[0]->East = rooms[1];

      // rooms 1
      rooms[1]->West = rooms[0];
      rooms[1]->East = rooms[2];
      rooms[1]->South = rooms[4];

      // room 2
      rooms[2]->West = rooms[1];
      rooms[2]->South = rooms[5];

      // room 3
      rooms[3]->North = rooms[0];
      rooms[3]->South = rooms[6];
      rooms[3]->East = rooms[4];

      // room 4
      rooms[4]->West = rooms[3];
      rooms[4]->East = rooms[5];
      rooms[4]->North = rooms[1];

      // room 5
      rooms[5]->West = rooms[4];
      rooms[5]->North = rooms[2];
      rooms[5]->South = rooms[8];

      // room 6
      rooms[6]->North = rooms[3];
      rooms[6]->East = rooms[7];

      // room 7
      rooms[7]->West = rooms[6];
      rooms[7]->North = rooms[4];
      rooms[7]->East = rooms[8];

      // and finally room 8
      rooms[8]->West = rooms[7];
      rooms[8]->North = rooms[5];

      answer[2] = rooms[rand() % 9]->name;
}

/*
* @param struct room* rooms[9]
* @param char *answer[3]
* @returns void
* @description
randomizeItems() distributes the items randomly into 6 of the 9 rooms.
The items distributed are: Wrench, Dagger, Revolver, Lead Pipe, Candle Stick, and Rope
*/
void randomizeItems(struct room* rooms[9], char *answer[3]){
      bool check[9] = {false, false, false, false, false, false, false, false, false};
      bool check1[6] = {false, false, false, false, false, false};
      char *items[6] = {"Wrench", "Dagger", "Revolver", "Lead Pipe", "Candle Stick", "Rope"};
      int t = 6;
      while (t != 0){
            int random = rand() % 6;
            int random2 = rand() % 9;
            if (!check[random2] && !check1[random]){
                  struct Item **temp = &(rooms[random2]->itemList);
                  add_item(temp, items[random]);
                  check[random2] = true;
                  check1[random] = true;
                  t--;
            }
      }
      answer[1] = items[rand() % 6];
}

/*
* @param char *character
* @param int index
* @param struct room* rooms[9]
* @returns void
* @description
addCharacter() is a helper function to set a Room struct -> character to @param character.
This function is used in the randomizeCharacters() located in the same file.
*/
void addCharacter(char *character, int index, struct room* rooms[9]){
      int i;
      for (i = 0; i < 6; i++){
            if (rooms[index]->characters[i] == NULL){
                  rooms[index]->characters[i] = character;
                  break;
            }
      }
}

/*
* @param char* charac[6]
* @param char* answer[3]
* @param struct room* rooms[9]
* @returns void
* @description
randomizeCharacters() uses the helper function addCharacter() to randomly distribute characters to the rooms.
The randomization process is done via the Fisher-Yates shuffle
*/
void randomizeCharacters(char* charac[6], char* answer[3], struct room* rooms[9]){
      bool check[9] = {false, false, false, false, false, false, false, false, false};
      bool check1[6] = {false, false, false, false, false, false};
      //char *charac[6] = {"John", "Joe", "Meg", "Scarlet", "Michael", "Mitch"};
      int t = 6;
      while (t != 0){
            int random = rand() % 6;
            int random2 = rand() % 9;
            if (!check[random2] && !check1[random]){
                  addCharacter(charac[random], random2, rooms);
                  check[random2] = true;
                  check1[random] = true;
                  t--;
            }
      }
      answer[0] = charac[rand() % 6];
}