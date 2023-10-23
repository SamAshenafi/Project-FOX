#pragma once
#include "./Hero.h"
#include <vector>

class Action;

class FoxHero : public Hero {
  public:
    FoxHero() {
      //int heroLevel = ;
      id = "FoxHero";
      actionList.push_back("DoNothing");
      actionList.push_back("Strike");
    };

    int hp = 100;
    int maxHp = 100;
    int bonusMaxHp;

    int baseAtk = 10;
    int bonusAtk;
    int baseDef = 4;
    int bonusDef;

    int baseSpeed = 6;

    int baseEnergy = 1;
    int energy;
};
