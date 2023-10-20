#include "World.h"

void World::processInput(Game& game) {
  player->processInput(game);

  int keyPressed = GetKeyPressed();
  switch (keyPressed) {
    case KEY_C:
      fprintf(stderr, "%s\n", "c was pressed");
      // game.changeState("combat");
      // Transfer data from World to Combat here
      enterCombat(game, "battle-aaa");
      break;
    case KEY_O:
      {
        fprintf(stderr, "%s\n", "o was pressed");
        std::string placeholderDialog = "Lorem ipsum...";
        int d4Result = GetRandomValue(1, 4);
        switch (d4Result) {
          case 1:
            game.dialogQueue.push("That's a lotta Damage!!!!!");
            break;
          case 2:
            game.dialogQueue.push("Hi, this is dialog.");
            break;
          case 3:
            game.dialogQueue.push("Almost!");
            break;
          case 4:
            game.dialogQueue.push(placeholderDialog);
            break;
        }
        break;
      }
    case KEY_P:
      fprintf(stderr, "%s\n", "p was pressed");
      // TODO: This is place holder
      // plan is to have a button/UI to select different save
      // like savedata-02 -> savedata-08
      fprintf(stderr, "%s\n", "saved to savedata-01.json");
      game.saveSave("savedata-01");
      break;
  }
}


