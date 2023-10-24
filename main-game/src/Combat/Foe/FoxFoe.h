#pragma once
#include "./Foe.h"

class FoxFoe : public Foe {
  public:
    FoxFoe() {
      id = "FoxFoe";
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

      // possible later implementation
      // expGain
      // loot

      actionList.push_back("DoNothing");
      actionList.push_back("Strike");
    };


    // std::vector<Action*> actions = {};
    // Action* decideAction() override;
    void decideAction() override;
    std::vector<Unit*> decideTarget(std::vector<Unit*> targets) override;
};
