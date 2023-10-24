#include "Combat.h"
#include <raylib.h>

void Combat::processInput(Game& game) {
  if (animationDuration != 0) return;
  // TODO:
  int keyPressed = GetKeyPressed();
  switch (keyPressed) {
    case KEY_C:
      fprintf(stderr, "%s\n", "c was pressed");
      // game.changeState("world");
      game.changeState(game.world);
      break;
    // delete this section?
    // case KEY_N:
    //   fprintf(stderr, "%s\n", "n was pressed");
    //   // if (currentUnit != nullptr) {
    //   //   if (isHero(currentUnit)) {
    //   //     if (highlightedAction != nullptr) {
    //   //       fprintf(stderr, "%s\n", "do nothing action is executed");
    //   //       currentUnit->selectedAction = highlightedAction;
    //   //       highlightedAction = nullptr;
    //   //     }
    //   //     else {
    //   //       fprintf(stderr, "%s\n", "no action is selected. Please select one by pressing p for now.");
    //   //     }
    //   //   }
    //   // }
    //   break;
    case KEY_P:
      fprintf(stderr, "%s\n", "p was pressed");
      if (isHero(currentUnit)) {
        selected = (selected + 1) % (currentUnit->actions.size());
        fprintf(stderr, "%s%i\n", "selection size: ",currentUnit->actions.size());
        fprintf(stderr, "%s%s\n", "action selected: ",currentUnit->actionList[selected].c_str());
        highlightedAction = currentUnit->actions[selected];
      }
      else {
        fprintf(stderr, "Unit w/ id: %s is not a hero\n", currentUnit->id.c_str());
      }
      break;
    case KEY_SEVEN:
      fprintf(stderr, "%s\n", "7 was pressed");
      if (highlightedAction != nullptr) {
        if (highlightedAction->targetType == "enemy") {
          targets = {};
          targets.push_back(foes[0]);
          fprintf(stderr, "%s\n", "do nothing action is executed on enemy at rank 1");
          currentUnit->selectedAction = highlightedAction;
        }
      }
      else {
        fprintf(
            stderr,
            "%s\n",
            "no action is selected. Please select one by pressing p for now."
            );
      }
      break;
    case KEY_SPACE:
      fprintf(stderr, "%s\n", "space was pressed");
      if (!game.dialogQueue.empty()) {
        game.dialogQueue.pop();
        break;
      }
      break;
  }
  return;
}
