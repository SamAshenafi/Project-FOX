#pragma once
#include "./Hero.h"
#include <vector>

class Action;

class FoxHero : public Hero {
  public:
    FoxHero() {
      //int heroLevel = ;
      id = "FoxHero";
      hp = 100;
      maxHp = 100;
      bonusMaxHp;

      baseAtk = 10;
      bonusAtk;
      baseDef = 4;
      bonusDef;

      baseSpeed = 6;

      baseEnergy = 1;
      energy;

      actionList.push_back("DoNothing");
      actionList.push_back("Strike");
      // actionList.push_back("InflictPoison");
    };
};
