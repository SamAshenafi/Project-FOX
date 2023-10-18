#pragma once
#include "./Hero.h"

class FoxHero : public Hero {
  public:
    FoxHero() {
      id = "FoxHero";
    };

    int hp = 100;
    int maxHp = 100;
    int bonusMaxHp;

    int baseAtk = 10;
    int bonusAtk;
    int baseDef = 4;
    int bonusDef;

    int speed = 6;

    int baseEnergy = 1;
    int energy;

};
