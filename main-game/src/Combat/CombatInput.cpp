#include "Combat.h"

void Combat::processInput(Game& game) {
  // TODO:
  int keyPressed = GetKeyPressed();
  switch (keyPressed) {
    case KEY_C:
      fprintf(stderr, "%s\n", "c was pressed");
      // game.changeState("world");
      game.changeState(game.world);
      break;
    case KEY_N:
      fprintf(stderr, "%s\n", "n was pressed");
      if (currentUnit != nullptr) {
        if (isHero(currentUnit)) {
          // PLACEHOLDER //
          if (hovered != nullptr) {
            fprintf(stderr, "%s\n", "do nothing action is executed");
            currentUnit->selectedAction = hovered;
            hovered = nullptr;
          }
          else {
            fprintf(stderr, "%s\n", "no action is selected. Please select one by pressing p for now.");
          }
          // PLACEHOLDER //
        }
      }
      break;
    case KEY_P:
      fprintf(stderr, "%s\n", "p was pressed");
      if (isHero(currentUnit)) {
        fprintf(stderr, "%s\n", "do nothing action is selected");
        hovered = currentUnit->actions[0];
      }
      // PLACEHOLDER //
      // if (currentUnit != nullptr) {
      //   if (isHero(currentUnit)) {
      //     if (currentUnit->selectedAction != nullptr) {
      //       currentUnit->selectedAction->perform(currentUnit, currentUnit, game);
      //       // currentUnit->startAnimationTime = GetTime();
      //       // game.dialogQueue.push("Player did nothing!");
      //       // currentUnit->animationTimer = 2.0;
      //       currentUnit->selectedAction = nullptr;
      //     }
      //     else {
      //       fprintf(stderr, "no action is selecter. Use n to select DoNothing\n");
      //     }
      //   }
      //   else {
      //   }
      // }
      // else {
      //   fprintf(stderr, "sigsegv\n");
      // }
      // PLACEHOLDER //

      // if (currentUnitIndex < units.size()) {
      //   Unit& currentPlayer = units[currentUnitIndex];
      //   if (!currentPlayer.hasTakenTurn) {
      //     // Handle player's turn (e.g., wait for user input like Space key press)
      //     currentPlayer.passTurn();
      //     currentUnitIndex++;
      //   }
      // }
      // else {
      //   startRound();
      // }
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
