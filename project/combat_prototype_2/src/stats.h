// stats.h

// used to pull and modify stats when call for
// used as well to help determine win/loss states in the game

// extra classes will be initialized for more complex stats here

#pragma once
#include "raylib.h"
#include <iostream>

Class Char_Stat{
    public:
        int currentHp;
        int maxHp;
        int atkDmg;
        int armor;
        bool isPlayer;
        std::string combat_texture_path; //path towards texture file that will hold the sprites used in combat

        //could probably be replaced with just including 
        //Char_Stat.maxHp -= Char_Stat.atkDam + Char_Stat.armor

        //void changeStat(); 

}