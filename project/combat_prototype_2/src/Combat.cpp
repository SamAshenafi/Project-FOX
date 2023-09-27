//Combat.cpp

#include <raylib.h>
#include "Combat.h"
#include "stats.h"
#include "inventory.h"
#include "vector"
#include "nlohmann/json.hpp"

/*
    This code is used to simulate and draw combat onto the screen
    
    Combat is split into multiple parts
*/

// this function takes the given stat array of both party members and enemies and 
// puts them into an initiative array that determines whos turn it is
Combat::initialize_combat(Stat[] party, Stat[] enemies) {

    pSize = sizeof(party);
    eSize = sizeof(enemy);
    int pAdd = 0;
    int eAdd = 0;

    // some additional likes may be added to sort this array if we ever
    // determine turn order based on a speed stat
    for (int i = 0, i < sizeof(party) + sizeof(enemy); i++) {
        if (pAdd < pSize) {
            initiative[i] = party[pAdd]
            pAdd++; 
        }
        else if (eAdd < eSize) {
            initiative[i] = party[eAdd]
            eAdd++; 
        }
    }
}

Combat::Combat() {
    initialize_combat(party,enemy);    

    
    
    CombatState = MENU; //sets state to menu
}


// checks the enemy health, if zero the combat is resolved.
Combat::combat_resolved() {


    return false
}

// TODO - add check for game over
// Combat::game_over

Combat::initiate_round() {
    for (int i = 0; i < sizeof(initiative); i++)
        if()
}