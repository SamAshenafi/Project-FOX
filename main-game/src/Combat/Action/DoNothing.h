#pragma once
#include "Action.h"

class DoNothing : public Action {
  public:
    // DoNothing() {
    //   energyCost = 1;
    // }
    DoNothing();
    ~DoNothing();

    // std::string targetType = 

    int perform(Unit* user, std::vector<Unit*> targets, Game& game) override;
};
