// Combat.h

#pragma once
#include "raylib.h"
#include "stats.h"


// Different states of combat
enum CombatState {
    MENU
    ACTION
}

enum MenuState{
    START
    ATTACK
    ITEMS
}

class Combat {
    private:

    public:
        //stats need to be initialized for these arrays  

        // TODO for Alton - get a better idea of json files and pulling infor from them
        // this will allow you to better optimise thhe classes for stats and inventory


        Stat[] initiative;

        const int pSize;
        const int eSize;

        void initialize_combat(STAT[] party, STAT[] enemy);
        bool combat_resolved();
        bool game_over();
        void initiate_round();

        // initialize pulls the stats from the 
        void initialize_stats();
        void update_stats();


        Combat(std::string[] party, std::string[] enemy);  

}