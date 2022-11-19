This is the README file for the implementation of CS 230 project 1 'CLUE'.



This project has 3 authors:
1) Shamanth Kuthpadi - SPIRE ID 33283988 (responsible for coding, debugging, and documentation)
2) Taru Meshram      - SPIRE ID 33298885 (responsible for coding and documentation)
3) Quang Dang        - SPIRE ID 33296828 (responsible for coding and debugging)

Official permission to work on this project in a group of 3 people has been granted by Professor Marc Liberatore. 
Professor Liberatore advised us to submit two identical submissions on gradescope and indicate that 3 people worked on the project in the README file.

Link to Google Drive containing screenshots of official permission from Professor Liberatore through email exchanges: 
https://drive.google.com/drive/folders/14rLurYei7PJAvtm8ksfd4Nf_dRvi7hZu?usp=sharing



The architecture/file content of the project is as follows-

adventure.c : primary/source file containing main and functions to interpret user input commands including starting the game, moving through the grid, looking for items in a room, taking and dropping items, moving characters through the grid, checking inventory, displaying the help menu, listing the game details, freeing the items linked list, and clearing the memory.

items.c : file containing functions to implement creating a new item string, adding an item to the items linkedlist , dropping an item from the items linkedlist, and printing the contents of the item list. 

rooms.c : file containing functions to implement the 3 by 3 grid of 9 rooms wherein each room has a pointer corresponding to a cardinal direction that links it to another room. This file also contains functions for randomly spawning the user in a room, randomizing the characters and items, and for adding characters to a particular room. 

items.h : header file containing item name and specifications shared by adventure.c , items.c , and rooms.c .

rooms.h : header file containing room structure specifications shared by adventure.c , items.c , and rooms.c . 


The user input is managed primarily through the ‘input’ function within the adventure.c file as follows:
 
-) The player is prompted to enter a command at the beginning of the game. If the player enters “go” (no whitespaces included), then they are prompted to enter the direction they want to go in. They can reply with “North” , “South”, “East”, “West”. Appropriate message is displayed for invalid input. 

-) The players can pick and drop items using “take” and “drop” inputs respectively. They can check their inventory using “inventory” input. They can also get a list of all possible characters, rooms, and items using the “list” input.

-) If the player enters “clue” input, they will be prompted to decide which character they would like to move and which item they would like to check.

-) If the player enters “help” input, then the game manual contains commands and instructions will be displayed. If the player enters “quit”, they will be exited from the game with a thank you message.



The code requirement for the program were fulfilled as follows-

1) using C structures within code: Rooms were created using C structures rooms.c and rooms.h . Similarly, items were created using items.c and items.h . Characters were implemented using characters[] string array. Items list and avatar inventory were implemented using linked list data structures. Avatar control and decision making implemented through several functions within the adventure.c file.

2) using pointer within code: All the linkedlist implementations work with pointers. All the rooms are connected via pointers. Character array involves pointers. functions took in pointers and either returned pointers or nothing.

3) using dynamic allocation within code: all instances of room, character, and items were allocated memory space through dynamic allocation involving the usage of malloc.

4) deallocating dynamically allocated memory: free function was used within the 'freeList' function of adventure.c file. An input string was temporarily stored and freed after being processed. 



The game requirements for the program were fulfilled as follows-

1) The game must have 9 rooms connected via pointers: fulfilled in the rooms.c file within the 'randomizeGame' function. The rooms are connected to one another within this aforementioned function. They are assigned their corresponding names within the 'start' function in adventure.c file. 

2) Randomly initializing room location: fulfilled in the rooms.c file within the 'randomizeGame' function as well. Randomization done through the Fisher-Yates shuffle

3) The game must contain atleast 6 items: fulfilled in the 'makeItem' function in items.c wherein memory is allocated, in the 'list' function within adventure.c wherein atleast 6 items are listed out, and 'randomizeItems' function in rooms.c wherein the items are randomly distributed. 

4) game must allow each room to contain items: fulfilled through the 'itemList' linked list corresponding to each specific room. Items can be added or dropped from this linked list through functions within the items.c file.

5) game must allow each room contain characters: fulfilled through the 'characters[]' string array used at multiple instances within the adventure.c file.

6) item placed in a random room: fulfilled through the 'randomizeItems' function within rooms.c file. 

7) one or multiple characters placed in a random room: fulfilled through the 'randomizeCharacters' function within rooms.c file.

8) game must pick a random answer: random character answer picked through the last line of 'randomizeCharacters' function. random room answer picked through the last line of 'randomizeGame' function. random item answer picked through the last line of 'randomizeItems' function. All three functions are present within rooms.c file.

9) implementation of avatar: fulfilled throughout the adventure.c file. inventory implemented through a seperate linked list 'itemList' specific to the user avatar.

10) a) look up commands: fulfilled through 'help' function within adventure.c
    b) look up items, rooms, and characters: fulfilled through 'list' function within adventure.c
    c) avatars to see rooms they are in: fulfilled through 'look' function within adventure.c
    d) avatars to move through rooms: fulfilled through 'move' function within adventure.c
    e) avatars to pick up items: fulfilled through 'take' function within adventure.c
    f) avatars to drop items: fulfilled through 'drop' function within adventure.c
    g) list inventory items: fulfilled through 'check_inventory' function within adventure.c
    h) "who done it" command: fulfilled through 'clue' function within adventure.c
    i) retype new command: fulfilled through the else part of the conditional statement present in the 'input' function within adventure.c 

11) a) move characters to same room as avatar: fulfilled through the 'moveCharacter' function within adventure.c
    b) tell player matching details about answer and guess: fulfilled through the 'checkAnswer' function within adventure.c
    c) check winning or losing status: fulfilled through the last part of the 'checkAnswer' function within adventure.c

12) Program organized into the following files: adventure.c , items.c , rooms.c , items.h , rooms.h , README.txt .