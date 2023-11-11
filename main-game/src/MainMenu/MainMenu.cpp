#include "MainMenu.h"
#include <cstdio>
#include <raylib.h>

void MainMenu::render(Game& game) {
  BeginDrawing();
  // TODO: put your render for start menu/screen here
  ClearBackground(DARKGRAY);
  if(game.gameOver) {
    DrawText(
      "GAME OVER!\n press Space to return to main menu.",
      game.settings.screenWidth / 2 - 50,
      game.settings.screenHeight / 2, 20,
      RAYWHITE
      );
  }
  // placeholder, to be replaced
  else {
    DrawText(
      "Press Space to Start A New Game\n or [ to load your saved game",
      game.settings.screenWidth / 2 - 50,
      game.settings.screenHeight / 2, 20,
      RAYWHITE
      );
  }
  EndDrawing();
}

void MainMenu::processInput(Game& game) {
  if (IsKeyPressed(KEY_SPACE)) {
    if (game.gameOver) game.gameOver = false;
    else {
      game.startNewGame();
    }
  }
  else if(IsKeyPressed(KEY_LEFT_BRACKET)) {
    fprintf(stderr, "%s\n", "[ was pressed");
    fprintf(stderr, "%s\n", "loaded from savedata-01.json");
    game.gameOver = false;
    game.loadSave("savedata-01");
    game.changeState(game.world);
  }
}

void MainMenu::update(Game& game) {
}

MainMenu::MainMenu() {
}

MainMenu::~MainMenu() {
  return;
}
