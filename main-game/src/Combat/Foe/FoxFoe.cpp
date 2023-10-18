#include "FoxFoe.h"
#include "../Action/Actions.h"
#include <raylib.h>

void FoxFoe::takeTurn(Game& game) {
  if (actions.empty()) {
    fprintf(stderr, "no actions\n");
    return;
  }
  selectedAction = actions[0];
  if (selectedAction != nullptr) {
    // game.dialogQueue.push("Foe did nothing!");
    selectedAction->perform(this, this, game);
    // startAnimationTime = GetTime();
    // animationTimer = 2.0;
    selectedAction = nullptr;
  }
};
