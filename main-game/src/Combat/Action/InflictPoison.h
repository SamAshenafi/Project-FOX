#pragma once
#include "Action.h"
#include "../Token/Poison.h"

class InflictPoison : public Action {
  public:
    // InflictPoison() {
    //   energyCost = 1;
    // }
    InflictPoison();
    ~InflictPoison();
    
    // TODO: add target type functionality (should be simple)
    // std::string targetType = "enemy";

    int perform(Unit* user, std::vector<Unit*> targets, Game& game) override;
};