// Combat.h

#pragma once
#include "raylib.h"
#include <string>


// Different states of combat
enum MenuState { ENEMY_TURN, START, ATTACK, DEFEND, ITEMS };

class Char_Stat{
    public:
        int currentHp;
        int maxHp;
        int atkDmg;
        int armor;
        bool isPlayer;
        std::string combat_texture_path; //path towards texture file that will hold the sprites used in combat
    

        Char_Stat(std::string path);

        //could probably be replaced with just including 
        //Char_Stat.maxHp -= Char_Stat.atkDam + Char_Stat.armor

};

class Combat {
    private:

    public:
        //stats need to be initialized for these arrays  

        // TODO for Alton - get a better idea of json files and pulling infor from them
        // this will allow you to better optimise thhe classes for stats and inventory

        const int pSize;
        const int eSize;

        void initialize_combat(std::string party[], std::string enemy[]);
        bool combat_resolved();
        bool game_over();
        void initiate_round();

        void initialize_stats(std::string path);

        // initialize pulls the stats from the 
        void initialize_stats();
        void update_stats();
        int grab_int_stat(std::string path, std::string variable);


        Combat(std::string party[], std::string enemy[]);  

        Char_Stat initiative[];
};