#pragma once
#include "Action.h"

class DoNothing : public Action {
  public:
    // DoNothing() {
    //   energyCost = 1;
    // }
    DoNothing();
    ~DoNothing();
    int perform(Unit *user, Unit *target, Game &game) override;

};
