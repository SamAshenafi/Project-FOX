#include "FoxFoe.h"
#include "../Action/Actions.h"
#include <raylib.h>

Action* FoxFoe::decideAction() {
  if (actions.empty()) {
    fprintf(stderr, "no actions\n");
    return nullptr;
  }
  selectedAction = actions[0];
  // if (selectedAction == nullptr) {
    // return nullptr;
    // game.dialogQueue.push("Foe did nothing!");
    // selectedAction->perform(this, this, game);
    // startAnimationTime = GetTime();
    // animationTimer = 2.0;
    // selectedAction = nullptr;
  // }
  return selectedAction;
};
