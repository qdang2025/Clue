// File inclusions
#include "items.h"
#include "rooms.h"

// File-scope variable declarations

// Track the current room the player is in
struct room *track;

// Inventory
struct Item *inventory;

int tries = 0;
struct room *rooms[9];

// Store the randomly generated answers
char *answer[3];

// Drive the input loop until the game terminates
bool driver = true;
char *charac[6] = {"John", "Joe", "Meg", "Scarlet", "Michael", "Mitch"};

// Variable used to run the clue function
bool flag;

/*
* @param char *item
* @returns void
* @description
checkItem() is a way to intialize the flag variable declared up top.
This function checks if @param char* item is present in the player's inventory or the current room.
If it does exist, then flag is set to true.
Else, flag is set to false.
*/
void checkItem(char *item){
      struct Item *temp2 = inventory;
      struct Item *temp = track->itemList;
      while (temp != NULL){
            if (strcmp(temp->name, item) == 0){
                  flag = true;
                  return;
            }
            temp = temp->next;
      }

      while (temp2 != NULL){
            if (strcmp(temp2->name, item) == 0){
                  flag = true;
                  return;
            }
            temp2 = temp2->next;
      }
      flag = false;
      printf("That item is not in the room \n");
}

/*
* @returns void
* @description
start() intializes game settings by first allocating memory for room structs and then setting room names to each room.
Then, the randomizeGame() randomizeItems() randomizeCharacters() are all called.
*/
void start(){
      int i;
      for (i = 0; i < 9; i++){
            rooms[i] = (struct room *)malloc(sizeof(struct room));
      }
      rooms[0]->name = "Living Room";
      rooms[1]->name = "Kitchen";
      rooms[2]->name = "Dining Room";
      rooms[3]->name = "Bedroom";
      rooms[4]->name = "Bathroom";
      rooms[5]->name = "Attic";
      rooms[6]->name = "Basement";
      rooms[7]->name = "Garage";
      rooms[8]->name = "Pantry";

      // sets the item* of each room to NULL
      int j;
      for (j = 0; j < 9; j++){
            rooms[j]->itemList = NULL;
      }

      track = rooms[rand() % 9];

      randomizeGame(rooms, answer);
      randomizeItems(rooms, answer);
      randomizeCharacters(charac, answer, rooms);
}

/*
* @param char* direction
* @returns void
* @description
move() allows player to move to another room.
If a room does not exist in the direction desired, an error message is presented.
*/
void move(char *direction){
      if (strcmp(direction, "North") == 0){
            if (track->North != NULL){
                  track = track->North;
            }
            else{
                  printf("You cannot move in that direction");
            }
      }
      else if (strcmp(direction, "South") == 0){
            if (track->South != NULL){
                  track = track->South;
            }
            else{
                  printf("You cannot move in that direction");
            }
      }
      else if (strcmp(direction, "East") == 0){
            if (track->East != NULL){
                  track = track->East;
            }
            else{
                  printf("You cannot move in that direction");
            }
      }
      else if (strcmp(direction, "West") == 0){
            if (track->West != NULL){
                  track = track->West;
            }
            else{
                  printf("You cannot move in that direction");
            }
      }
}

// presents a list of commands
void help(){
      printf("go + direction: allows you to move to a different room to the direction specified \n");
      printf("take: allows you to take an item from the room and add it to your inventory \n");
      printf("drop: allows you to drop an item from your inventory and add it to the room \n");
      printf("inventory: allows you to see the items in your inventory \n");
      printf("list: allows you to see the list of items, rooms, and characters \n");
      printf("look: allows you to see the items in the room, the characters in the room, and the adjacent rooms \n");
      printf("clue: allows you to see a clue by summoning any character you want to your current room \n");
      printf("help: allows you to see the commands and their descriptions \n");
      printf("quit: ends the game\n");
}

// shows player the room items, characters, and any adjacent rooms
void look(){
      printf("You are in the %s \n", track->name);
      printf("Items in the room: ");
      struct Item *temp = track->itemList;
      while (temp != NULL){            
            printf("%s ", temp->name);
            temp = temp->next;
      }
      printf("\n");
      printf("Characters in the room: ");
      int i;
      for (i = 0; i < 6; i++){
            if (track->characters[i] != NULL){
                  printf("%s ", track->characters[i]);
            }
      }
      printf("\n");
      printf("Adjacent rooms: \n");
      if (track->North != NULL){
            printf("%s to the North \n", track->North->name);
      }
      if (track->South != NULL){
            printf("%s to the South \n", track->South->name);
      }
      if (track->East != NULL){
            printf("%s to the East \n", track->East->name);
      }
      if (track->West != NULL){
            printf("%s to the West \n", track->West->name);
      }
}

// Shows player the characters, items, and rooms in the game
void list(){
      printf("Characters: John, Joe, Meg, Scarlet, Michael, Mitch \n");
      printf("Items: Wrench, Dagger, Revolver, Lead Pipe, Candle Stick, Rope \n");
      printf("Rooms: Living Room, Kitchen, Dining Room, Bedroom, Bathroom, Attic, Basement, Garage, Pantry \n");
}

// moves north
void goNorth(){
      if (track->North != NULL){
            track = track->North;
      }
      else{
            printf("You cannot move in that direction \n");
      }
}

// moves south
void goSouth(){
      if (track->South != NULL){
            track = track->South;
      }
      else{
            printf("You cannot move in that direction \n");
      }
}

// moves east
void goEast(){
      if (track->East != NULL){
            track = track->East;
      }
      else{
            printf("You cannot move in that direction \n");
      }
}

// moves west
void goWest(){
      if (track->West != NULL){
            track = track->West;
      }
      else{
            printf("You cannot move in that direction \n");
      }
}

// Allows player to check their inventory
void check_inventory(){
      printf("Items in your inventory: ");
      struct Item *temp = inventory;
      while (temp != NULL){
            if (temp->next == NULL){
                  printf("%s", temp->name);
                  break;
            }
            printf("%s, ", temp->name);
            temp = temp->next;
      }
      printf("\n");
}

// Allows player to take an item from the room
void take(char *item){
      struct Item **temp = &(inventory);
      struct Item **temp1 = &(track->itemList);
      drop_item(temp1, strdup(item));
      if (check){
            check = false;
            return;
      }
      add_item(temp, strdup(item));
}

// Allows player to drop an item from their invetory into the room.
void drop(char *item){
      struct Item **temp = &(inventory);
      struct Item **temp1 = &(track->itemList);
      drop_item(temp, strdup(item));
      if (check){
            check = false;
            return;
      }
      add_item(temp1, strdup(item));
}

// moves a character to the current room
void moveCharacter(char *character){
      char *str = strdup(character);
      int i, j, k, l;
      // Check if the NPC is a valid one
      for (l = 0; l < 6; l++){
            if (strcmp(charac[l], str) == 0){
                  break;
            }
      }
      if (l == 6){
            printf("The NPC does not exist!\n");
            return;
      }
      // Check if the NPC is already in the room
      for (k = 0; k < 10; k++){
            if (track->characters[k] != NULL && strcmp(track->characters[k], str) == 0){
                  printf("The player is already here! \n");
                  return;
            }
      }
      // Remove them
      for (i = 0; i < 9; i++){
            for (j = 0; j < 9; j++){
                  char *temp = rooms[i]->characters[j];
                  if (temp != NULL && strcmp(temp, str) == 0){
                        rooms[i]->characters[j] = NULL;
                        break;
                  }
            }
      }
      // Add them
      for (i = 0; i < 10; i++){
            if (track->characters[i] == NULL){
                  track->characters[i] = str;
                  break;
            }
      }
}

// helper function for clue() to check if the correct character is in the room and whether an item is correct.
void checkAnswer(){
      int k;
      int r, i, c = 0;
      for (k = 0; k < 6; k++){
            char *temp = track->characters[k];
            if (temp != NULL && strcmp(temp, answer[0]) == 0){
                  printf("Character Match \n");
                  c = 1;
                  break;
            }
      }
      struct Item *temp = track->itemList;
      struct Item *temp1 = inventory;
      while (temp != NULL){
            if (strcmp(temp->name, answer[1]) == 0){
                  printf("Item Match \n");
                  i = 1;
                  break;
            }
            temp = temp->next;
      }

      while (temp1 != NULL){
            if (strcmp(temp1->name, answer[1]) == 0){
                  printf("Item Match \n");
                  i = 1;
                  break;
            }
            temp1 = temp1->next;
      }

      if (strcmp(track->name, answer[2]) == 0){
            printf("Room Match \n");
            r = 1;
      }
      if (c == 1 && i == 1 && r == 1){
            printf("%s was the murderer who used the %s in the %s!\n", answer[0], answer[1], answer[2]);
            printf("You have solved the murder mystery!\n");
            printf("You win! \n");
            driver = false;
      }
      else{
            tries++;
            printf("You have %d tries left.\n", 10 - tries);
            if (tries == 10){
                  printf("The killer escaped!\n");
                  printf("%s was the murderer who used the %s in the %s!\n", answer[0],answer[1],answer[2]);
                  printf("You lose! \n");
                  driver = false;
            }
      }
}

// performs the clue command to check a player answer
void clue(char *character){
      moveCharacter(character);
      checkAnswer();
}

// frees a linked list of Items
void freeList(struct Item *head){
      struct Item *tmp;
      while (head != NULL){
            tmp = head;
            head = head->next;
            free(tmp);
      }
}

// Used to clear memory once game is over
void memoryClear(){
      for (int i = 0; i < 9; i++)
      {
            struct Item *tf = rooms[i]->itemList;
            freeList(tf);
            free(rooms[i]);
      }
}

// Allows player to type in commands and the corresponding function activates in response.
void input(){
      char *command = malloc(100);
      char *item = malloc(100);
      char *character = malloc(100);
      char *direction = malloc(100);
      while (driver){
            printf("Please enter a command: ");
            fgets(command, 100, stdin);
            if ((strlen(command) > 0) && (command[strlen(command) - 1] == '\n'))
                  command[strlen(command) - 1] = '\0';
            if (strcmp(command, "go") == 0){
                  printf("Which direction would you like to go? ");
                  fgets(direction, 100, stdin);
                  if (strcmp(direction, "North\n") == 0){
                        goNorth();
                  }
                  else if (strcmp(direction, "South\n") == 0){
                        goSouth();
                  }
                  else if (strcmp(direction, "East\n") == 0){
                        goEast();
                  }
                  else if (strcmp(direction, "West\n") == 0){
                        goWest();
                  }
                  else{
                        printf("Invalid direction, try again!\n");
                  }
            }
            else if (strcmp(command, "take") == 0){
                  printf("Which item would you like to take? ");
                  fgets(item, 100, stdin);
                  item[strcspn(item, "\n")] = '\0';
                  take(item);
            }
            else if (strcmp(command, "drop") == 0){
                  printf("Which item would you like to drop? ");
                  fgets(item, 100, stdin);
                  item[strcspn(item, "\n")] = '\0';
                  drop(item);
            }
            else if (strcmp(command, "clue") == 0){
                  printf("Which character would you like to move? ");
                  fgets(character, 100, stdin);
                  character[strcspn(character, "\n")] = '\0';
                  printf("Which item would you like to check? ");
                  fgets(item, 100, stdin);
                  item[strcspn(item, "\n")] = '\0';
                  checkItem(strdup(item));
                  if (flag){
                        clue(character);
                  }
            }
            else if (strcmp(command, "inventory") == 0){
                  printf("-------------------------------------\n");
                  check_inventory();
                  printf("-------------------------------------\n");
            }
            else if (strcmp(command, "look") == 0){
                  printf("-------------------------------------\n");
                  look();
                  printf("-------------------------------------\n");
            }
            else if (strcmp(command, "help") == 0){
                  printf("-------------------------------------\n");
                  help();
                  printf("-------------------------------------\n");
            }
            else if (strcmp(command, "list") == 0){
                  printf("-------------------------------------\n");
                  list();
                  printf("-------------------------------------\n");
            }
            else if (strcmp(command, "quit") == 0){
                  printf("-------------------------------------\n");
                  printf("Thanks for playing!\n");
                  memoryClear();
                  printf("-------------------------------------\n");
                  exit(1);
            }
            else{
                  printf("-------------------------------------\n");
                  printf("That is not a valid command. Try one of these following commands: \n\n");
                  help();
                  printf("-------------------------------------\n");
            }
      }
      free(command);
      free(character);
      free(item);
      free(direction);
}

// Game begins here
int main(){
      srand(time(NULL));
      start();
      printf("You are a private detective, and you have been tasked with solving the murder of the manor's owner. \n");
      printf("You must traverse the manor and figure out who is the culprit before it is too late! \n");
      printf("Good luck detective! \n");
      input();
      memoryClear();
      return 0;
}