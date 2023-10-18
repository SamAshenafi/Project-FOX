#pragma once
#include <string>
#include "../Unit.h"
#include "../../Game.h"
// #include "../Combat.h"

class Action {
  public:
    Action() {};
    virtual ~Action() = default;
    // Possile targetType
    // "self"
    // "ally"
    // "allies"
    // "team"
    // "enemy"
    // "enemies"
    // "all"
    // "ALL"
    std::string targetType;
    int energyCost = 1;
    int animationDuration = 12;

    virtual int perform(Unit* user, Unit* target, Game& game) = 0;
};

