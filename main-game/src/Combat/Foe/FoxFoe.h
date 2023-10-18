#pragma once
#include "./Foe.h"

class FoxFoe : public Foe {
  public:
    FoxFoe() {
      id = "FoxFoe";
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


    // std::vector<Action*> actions = {};
    void takeTurn(Game& game) override;
};
