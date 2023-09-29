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
Char_Stat::Char_Stat(std::string path) {
    
    const std::string statFilePath = "./json/";
    const std::string jsonFileType = ".json";
    const std::string fullFilePath = statFilePath + path + jsonFileType;
    nlohmann::json root;

    std::ifstream inputFile(fullFilePath);

    if (inputFile.is_open()) {
    // Parse the JSON data
    try {
      inputFile >> root;

      // Deserialize the JSON data into member variables
      // gameState = static_cast<GameState>(root.value("gameState", START_MENU));
      currentHp = root.value("currentHp");
      std::cout << "\ncurrentHP parsed from JSON is: " << currentHp << std::endl;

      maxHp = root.value("maxHp");
      std::cout << "\nmaxHp parsed from JSON is: " << maxHp << std::endl;

      atkDmg = root.value("atkDmg");
      std::cout << "\natkDmg parsed from JSON is: " << atkDmg << std::endl;

      armor = root.value("armor");
      std::cout << "\narmor parsed from JSON is: " << armor << std::endl;

      isPlayer = root.value("isPlayer");
      std::cout << "\nisPlayer parsed from JSON is: " << isPlayer << std::endl;

      combat_texture_path = root.value("texture_path", "");
      std::cout << "\ncombat_texture_path parsed from JSON is: " << combat_texture_path << std::endl;

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
Combat::initialize_combat(std::string party[], std::string enemy[]) {

    pSize = sizeof(party);
    eSize = sizeof(enemy);
    int pAdd = 0;
    int eAdd = 0;

    // some additional likes may be added to sort this array if we ever
    // determine turn order based on a speed stat
    for (int i = 0, i < sizeof(party) + sizeof(enemy); i++) {
        if (pAdd < pSize) {
            Char_Stat add = new Char_Stat(party[pAdd]);
            initiative[i] = add;
            pAdd++; 
        }
        else if (eAdd < eSize) {
            Char_Stat add = new Char_Stat(party[eAdd]);
            initiative[i] = add;
            eAdd++; 
        }
    }

}


//the function that starts the combat enconunter, it is given the files names to be used in the .json pathing

Combat::Combat(std::string[] party, std::string[] enemy) {
    initialize_combat(party,enemy);    
    MenuState = ENEMY_TURN;

}


// checks the enemy health, if zero the combat is resolved.
Combat::combat_resolved() {


    return false
}

// TODO - add check for game over
// Combat::game_over


// simulates the round being done in game
// might need to be moved to Game.cpp?
Combat::initiate_round() {

    DirectionalInput();

    // Checks if the current index in the initiative is a player character
    // this will then set things up to where the player is prompted with a menu

    for (int i = 0; i < sizeof(initiative); i++) {
        

        if(initiative[i].isPlayer()) {
            MenuState = START;
        }
        else {
            MenuState = ENEMY_TURN;
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

        enum StartMenu = {ATTACK, DEFEND, ITEMS};
        int selected = 0;

        while (MenuState == START) {
            
            if (rightPressed()) {
                
            }

            if (downPressed() || downHeld()) {
                selected++;
                
            }

            if (upPressed() || upHeld()) {
                selected--;
            }

            if (selected >= 3) {
                selected = 0;
            }

            if (selected <= -1) {
                selected = 2;
            }

            if (getDirection() != NONE) {
                std::cout << "\n currently selected is --> " << Startmenu[selected];
            }

        }

        while (MenuState == ATTACK) {

        }

        while (MenuState == Defend) {

        }

        while (MenuState == ITEMS) {

        }

        // This is where all parts of combat set up are resolved
        // Is only active when its an enemy's turn
        
        // for now enemies will only have one move and that is attacking
        // later, if enemies have abilities, logic for what ability will be used will be handled here

        while (MenuState == ENEMY_TURN) {

        }
    }
}