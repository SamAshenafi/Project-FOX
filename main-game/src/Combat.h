// Combat.h
#pragma once
#include "raylib.h"
#include "vector"
#include <string>

// this class will hold the data for the stats a player character or enemy has
// this class also includes whatever abilities the player/enemy has
class Char_Stat{
    public:
        std::string id;
        int currentHp;
        int maxHp;
        int atkDmg;
        int armor;
        bool isPlayer;
};

class Combat{
    public:
        int pSize;
        int eSize;

        void initialize_combat(std::vector<std::string> party, std::vector<std::string> enemy);
        bool combat_resolved();
        bool game_over();
        void initiate_round();

        void initialize_stats(std::string path);

        // initialize pulls the stats from the 
        void initialize_stats();
        void update_stats();
        int grab_int_stat(std::string path, std::string variable);

        Combat();

        MenuState menuState;

        std::vector<Char_Stat> initiative;
};