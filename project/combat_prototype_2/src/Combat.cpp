//Combat.cpp

#include <raylib.h>
#include <fstream>
#include "Combat.h"
#include "Input.h"
// #include "inventory.h" (will be uncommented once inventory functionality is implemented)
#include "vector"
#include "nlohmann/json.hpp"
#include <iostream>

/*
    This code is used to simulate and draw combat onto the screen
    
    Combat is split into multiple parts
*/

//Constructor for the character stats when given the ppath to its json file
Char_Stat::Char_Stat(){
    std::cout << "\nno character path provided";
}

Char_Stat::Char_Stat(const std::string& path) {
    
    const std::string statFilePath = "./src/json/";
    const std::string jsonFileType = ".json";
    const std::string fullFilePath = statFilePath + path + jsonFileType;
    nlohmann::json root;

    std::ifstream inputFile(fullFilePath);

    if (inputFile.is_open()) {
    // Parse the JSON data
    try {
      inputFile >> root;

      // Deserialize the JSON data into member variables
      currentHp = root["currentHp"];
      std::cout << "\ncurrentHP parsed from JSON path " << path << " is: " << currentHp << std::endl;

      maxHp = root["maxHp"];
      std::cout << "\nmaxHp parsed from JSON path " << path << " is: " << maxHp << std::endl;

      atkDmg = root["atkDmg"];
      std::cout << "\natkDmg parsed from JSON path " << path << " is: " << atkDmg << std::endl;

      armor = root["armor"];
      std::cout << "\narmor parsed from JSON path " << path << " is: " << armor << std::endl;

      isPlayer = root["isPlayer"];
      std::cout << "\nisPlayer parsed from JSON path " << path << " is: " << isPlayer << std::endl;

      combat_texture_path = root.value("texture_path", "");
      std::cout << "\ncombat_texture_path parsed from JSON path " << path << " is: " << combat_texture_path << std::endl;

      // You can add more deserialization logic for other members here
      inputFile.close();
    }
    catch (const std::exception& e) {
      fprintf(stderr, "JSON parsing failed: %s\n", e.what());
      inputFile.close();
      // return false; // Loading failed
    }
  }
  else {
    fprintf(stderr, "Unable to open file for reading\n");
  }
}

// this function takes the given stat array of both party members and enemies and 
// puts them into an initiative array that determines whos turn it is
void Combat::initialize_combat(std::vector<std::string> party, std::vector<std::string> enemy) {

    pSize = party.size();
    eSize = enemy.size();
    int pAdd = 0;
    int eAdd = 0;
    initiative.resize(pSize + eSize);

    // some additional likes may be added to sort this array if we ever
    // determine turn order based on a speed stat
    for (int i = 0; i < pSize + eSize; i++) {
        std::cout << "\n i = " << i;

        if (pAdd < pSize) {
            std::cout << "\nparty[pAdd] = " << party[pAdd];
            Char_Stat add = Char_Stat(party[pAdd]);
            initiative[i] = add;
            pAdd++; 
        }
        else {
            std::cout << "\nenemy[eAdd] = " << enemy[eAdd];
            Char_Stat add = Char_Stat(enemy[eAdd]);
            initiative[i] = add;
            eAdd++; 
        }
    }

}


//the function that starts the combat enconunter

Combat::Combat() 
{
    menuState = ENEMY_TURN;

}


// checks the enemy health, if zero the combat is resolved.
bool Combat::combat_resolved() {


    return false;
}

// TODO - add check for game over
// Combat::game_over


// simulates the round being done in game
// might need to be moved to Game.cpp?
void Combat::initiate_round() {

   DirectionalInput input = DirectionalInput();

    // Checks if the current index in the initiative is a player character
    // this will then set things up to where the player is prompted with a menu

    for (int i = 0; i < eSize + pSize; i++) {
        
        std::cout << "\nis player?: " << initiative[i].isPlayer;
        if(initiative[i].isPlayer) {
            menuState = START;
        }
        else {
            menuState = ENEMY_TURN;
        }

        // menu activity is done through here
        // takes in input to move a cursor towards different actions

        // The Starting menu navigates between multiple different menus and actions
        // actions currently listed are
        /*
            Attack - switches to the attack menu where you select which enemy to attack

            Defense - temporarily ups the defense of the current character until the next round

            Items - pulls up the items inventory
        */
       // these meaus can be changed depending on what mechanics we implement
       // since were going off of something akin to darkest dungeon we'll likely have it
       // to where instead of attack you select from multiple different abilities

    
        int selected = 2;

        while (menuState == START) {
                        
            if (rightPressed()) {
                std::cout << "up has been pressed";
                menuState = RESOLVE;
            }            

            if (downPressed() || downHeld()) {
                std::cout << "down has been pressed";
                selected++;
                
            }

            if (upPressed() || upHeld()) {
                selected--;
                std::cout << "up has been pressed";
            }

            if (selected >= 5) {
                selected = 2;
            }

            if (selected <= 1) {
                selected = 4;
            }

            if (input.getDirection() != NONE) {
                std::cout << "\n currently selected is --> " << MenuState(selected);
            }

        }

        while (menuState == ATTACK) {

        }

        while (menuState == DEFEND) {

        }

        while (menuState == ITEMS) {

        }

        // This is where all parts of combat set up are resolved
        // Is only active when its an enemy's turn
        
        // for now enemies will only have one move and that is attacking
        // later, if enemies have abilities, logic for what ability will be used will be handled here

        while (menuState == ENEMY_TURN) {

        }
        std::cout << "it gets to here";
    }
}