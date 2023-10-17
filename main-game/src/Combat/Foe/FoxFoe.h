#pragma once
#include "./Foe.h"

class FoxHero : public Foe {
  FoxHero();

    int hp = 100;
    int maxHp = 100;
    int bonusMaxHp;

    int baseAtk = 10;
    int bonusAtk;
    int baseDef = 4;
    int bonusDef;

    int baseEnergy = 1;
    int energy;
};
