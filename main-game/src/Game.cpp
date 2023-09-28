// Game.cpp
#include "Game.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"

Game::Game() {
  // Initialize grid (adjust size accordingly)
  resetGrid();
}


void Game::run() {
  // SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
  InitWindow(screenWidth, screenHeight, "Game Title");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    switch (gameState) {
      case start_menu:
        // NOTE: temporary placeholder for start menu.
        if (IsKeyPressed(KEY_SPACE)) {
          gameState = loading_overworld;
        }
        renderStartMenu();
        break;
      case loading_overworld:
        // TODO: when the player select or start new save, loadSave() -> loadRoom()
        // the player is in the overworld after (cannot save in combat, save exclusively happen when overworld )
        gameState = overworld;
        break;
      case overworld:
        handleUserInputOverworld();
        renderOverworld();
        break;
      case loading_combat:
        // TODO: load combat encounter/enemy info
        // TODO: do transition animation
        break;
      case combat:
        handleUserInputCombat();
        renderCombat();
        break;
    }
  }

  // TODO: unload stuffs when game about to close to prevent memory leak
  // UnloadTexture(player->texture);

  CloseWindow();
}

// ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
// ░█▀▄░█▀▀░█▀█░█▀▄░█▀▀░█▀▄
// ░█▀▄░█▀▀░█░█░█░█░█▀▀░█▀▄
// ░▀░▀░▀▀▀░▀░▀░▀▀░░▀▀▀░▀░▀
// RENDER
// NOTE + TODO: use scaling * ... for all your render so that it
// look correct when resized

void Game::renderStartMenu() {
  BeginDrawing();
  // TODO: put your render for start menu/screen here

  // placeholder, to be replaced
  DrawText(
      "Press Space to Continue or something idk",
      scaling * screenWidth / 2 - 50,
      scaling * screenHeight / 2, 20,
      RAYWHITE
      );
  EndDrawing();
}

void Game::renderOverworld() {
  BeginDrawing();
  ClearBackground(RAYWHITE);
  // ClearBackground(DARKGRAY);
  // TODO: draw currentRoomId-bg.png here

  // Draw the grid (debug only)
  // for (int x = 0; x < ScreenWidth; x += GridWidth) {
  //   for (int y = 0; y < ScreenHeight; y += GridHeight) {
  //     if (grid[x / GridWidth][y / GridHeight] == 1) {
  //       DrawRectangle(x, y, GridWidth, GridHeight, DARKGRAY);
  //     }
  //     else {
  //       // DrawRectangleLines(x, y, gridSize, gridSize, DARKGRAY);
  //       DrawRectangleLines(x, y, GridWidth, GridHeight, BLACK);
  //     }
  //   }
  // }

  // NOTE: Sort player and tile/object based on their y (depth)
  // THEN: Iterate & call render for player and object
  // NOTE: This is necessary because the sprite of whatever would not
  // fit the 96x80 grid, so the object with lower y (farther away) will
  // render before object closer
  // basically, if player is in front of the chest, the chest sprite would not
  // appear over the player
  // and vice versa,
  // if player is behind, the player sprite would not appear over the chest
  std::sort(
      gameObjects.begin(),
      gameObjects.end(),
      [](const GameObject* a, const GameObject* b) {
      return a->y < b->y;
      });
  for (GameObject* gameObject : gameObjects) {
    // Call the render method for each object through the pointer
    gameObject->render();
  }

  // TODO: draw currentRoomId-fg.png here
  EndDrawing();
}

void Game::renderCombat() {
  // TODO:
}

// ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
// ░▀█▀░█▀█░█▀█░█░█░▀█▀
// ░░█░░█░█░█▀▀░█░█░░█░
// ░▀▀▀░▀░▀░▀░░░▀▀▀░░▀░
// INPUT

void Game::handleUserInputOverworld() {
  double currentTime = GetTime();
  double deltaTimeSinceLastMove = currentTime - lastMoveTime;
  if (deltaTimeSinceLastMove < moveSpeed) {
    // fprintf(stderr,"too soon\n");
    return; // Too soon for another move
  }

  Player* player = nullptr;

  for (GameObject* gameObject : gameObjects) {
    bool isPlayer = Helper::parseGameObjectType(gameObject->id) == "player";
    if (isPlayer) {
      player = dynamic_cast<Player*>(gameObject);
      break;
    }
  }

  int keyPressed = GetKeyPressed();
  switch (keyPressed) {
    // Detect when movement key is pushed to smooth out the movement
    case KEY_LEFT:
      player->move(player->x-1, player->y);
      player->facing = Direction::left;
      break;
    case KEY_DOWN:
      player->move(player->x, player->y+1);
      player->facing = Direction::down;
      break;
    case KEY_UP:
      player->move(player->x, player->y-1);
      player->facing = Direction::up;
      break;
    case KEY_RIGHT:
      player->move(player->x+1, player->y);
      player->facing = Direction::right;
      break;
    case KEY_S:
      // TODO: This is place holder
      // plan is to have a button/UI to select different save
      // like savedata-02 -> savedata-08
      fprintf(stderr, "%s\n", "saved to savegame.json");
      saveSave("savedata-01");
      break;
    case KEY_SPACE:
      fprintf(stderr, "%s\n", "space was pressed");
      int targetX = player->x;
      int targetY = player->y;

      switch (player->facing) {
        case Direction::up:
          targetY--;
          break;
        case Direction::down:
          targetY++;
          break;
        case Direction::left:
          targetX--;
          break;
        case Direction::right:
          targetX++;
          break;
      }

      for (GameObject* gameObject : gameObjects) {
        bool isInterableObject =
          Helper::parseGameObjectType(gameObject->id) != "player" &&
          gameObject->x == targetX &&
          gameObject->y == targetY
          ;
        if (isInterableObject) {
          loadTile(gameObject->id);
        }
      }
      break;
  }


  // player->updateAnimation();

  int newX = player->x;
  int newY = player->y;

  if (IsKeyDown(KEY_RIGHT)) {
    player->facing = Direction::right;
    newX++;
  }
  else if (IsKeyDown(KEY_LEFT)) {
    player->facing = Direction::left;
    newX--;
  }
  else if (IsKeyDown(KEY_DOWN)) {
    player->facing = Direction::down;
    newY++;
  }
  else if (IsKeyDown(KEY_UP)) {
    player->facing = Direction::up;
    newY--;
  }

  // no movement
  if (newX == player->x && newY == player->y) return;

  // Check if the new position is out of bounds
  bool isOutOfBound = newX < 0 ||
    newX >= (screenWidth / gridWidth) ||
    newY < 0 ||
    newY >= (screenHeight / gridHeight);
  if (isOutOfBound) {
    fprintf(stderr, "out of bound: %d, %d\n", newX, newY);
    // TODO: if current tile is transition tile
    if (true) {
      // TODO: move player to transitionTile.enterX and enterY
      // player->move(0, 0);
      return;
    }
    return; // Player moved to a new room, no need to continue with the current input
  }
  else if (grid[newX][newY] == 1) {
    // no movement, terrain or tile block
    return;
  }
  else {
    player->move(newX, newY);
    lastMoveTime = currentTime;
  }
}

// ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
// ░█░░░█▀█░█▀█░█▀▄
// ░█░░░█░█░█▀█░█░█
// ░▀▀▀░▀▀▀░▀░▀░▀▀░
// LOAD

void Game::loadSave(const std::string& filename) {
  const std::string saveFilePath = "./save/";
  const std::string jsonFileType = ".json";
  const std::string fullFilePath = saveFilePath + filename + jsonFileType;
  nlohmann::json root;

  // Read the JSON data from the file
  std::ifstream inputFile(fullFilePath);

  if (inputFile.is_open()) {
    // Parse the JSON data
    try {
      inputFile >> root;
      // TODO: this part is WIP, more work need to be done here
      // Deserialize the JSON data into member variables
      currentRoomId = root.value("currentRoomId", "");
      loadRoom(currentRoomId);

      completed.clear();
      for (const auto& item : root["completed"]) {
        completed.push_back(item.get<std::string>());
      }

      // TODO: Add inventory parsing logic here
      // TODO: Add more deserialization logic for other members here

      inputFile.close();
    }
    catch (const std::exception& e) {
      fprintf(stderr, "JSON parsing failed: %s\n", e.what());
      inputFile.close();
    }
  }
  else {
    fprintf(stderr, "Unable to open file for reading\n");
  }
}

void Game::loadRoom(const std::string& roomId) {
  const std::string saveFilePath = "./src/json/room/";
  const std::string jsonFileType = ".json";
  const std::string fullFilePath = saveFilePath + roomId + jsonFileType;
  nlohmann::json root;
  std::ifstream jsonFile(fullFilePath);

  if (jsonFile.is_open()) {
    try {
      jsonFile >> root;
      // TODO: this part is also WIP, more work need to be done here
      // TODO: when parsing room Tile,
      // if Tile.isBlockMovement == true then set grid[tileX][tileY] = 1

      // Parse transition tiles
      for (const auto& transitionData : root["transitionTiles"]) {
        int tileX = transitionData["x"];
        int tileY = transitionData["y"];
        int enterX = transitionData["enterX"];
        int enterY = transitionData["enterY"];
        std::string destinationRoomId = transitionData["destinationRoomId"];
        // TODO: create new TransitionTile & push into the transitionTiles vector
        // TransitionTile transitionTile(tileX, tileY, destinationRoomId);
        // transitionTiles.push_back(transitionTile);
      }
    }
    catch (const std::exception& e) {
      fprintf(stderr, "JSON parsing failed: %s\n", e.what());
    }
  }
}

void Game::saveSave(const std::string& filename) {
  const std::string saveFilePath = "./save/";
  const std::string jsonFileType = ".json";
  const std::string fullFilePath = saveFilePath + filename + jsonFileType;
  nlohmann::json root;
  // TODO: this part is also WIP, more work need to be done here
  // Mostly,
  // - Player x, y, and other data members also need to be saved
  // - Room does not need to be saved since we load it when we load the save

  // Serialize member data to JSON
  root["currentRoomId"] = currentRoomId;
  root["completed"] = nlohmann::json::array();

  for (const std::string& item : completed) {
    root["completed"].push_back(item);
  }

  // Create a JSON writer
  std::ofstream outputFile(fullFilePath);

  if (outputFile.is_open()) {
    // Write JSON to the output file
    outputFile << root.dump(2); // Pretty print with 2 spaces
    outputFile.close();
  }
  else {
    fprintf(stderr, "Unable to open the file for writing\n");
  }
}

void Game::loadTile(const std::string& tileId) {
  std::string tileType = Helper::parseGameObjectType(tileId);
  if (tileType == "chest") {
    const std::string chestFilePath = "./src/json/chest/";
    const std::string jsonFileType = ".json";
    const std::string fullFilePath = chestFilePath + tileId + jsonFileType;
    nlohmann::json root;
    std::ifstream jsonFile(fullFilePath);
    if (jsonFile.is_open()) {
      try {
        jsonFile >> root;
        // TODO: parse chest json data here
      }
      catch (const std::exception& e) {
        fprintf(stderr, "JSON parsing failed: %s\n", e.what());
      }
    }
  }
  else if (tileType == "combat") {
    // TODO: load combat encounter, blah blah blah
    const std::string combatFilePath = "./src/json/combat/";
    const std::string jsonFileType = ".json";
    const std::string fullFilePath = combatFilePath + tileId + jsonFileType;
    nlohmann::json root;
    std::ifstream jsonFile(fullFilePath);
    if (jsonFile.is_open()) {
      try {
        jsonFile >> root;
        // TODO: parse combat json data here
      }
      catch (const std::exception& e) {
        fprintf(stderr, "JSON parsing failed: %s\n", e.what());
      }
    }
  }
  // TODO: add more parsing for other tile type here
  else if (true) {
  }
}


// ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
// ░█░█░█▀▀░█░░░█▀█░█▀▀░█▀▄░█▀▀
// ░█▀█░█▀▀░█░░░█▀▀░█▀▀░█▀▄░▀▀█
// ░▀░▀░▀▀▀░▀▀▀░▀░░░▀▀▀░▀░▀░▀▀▀
// HELPERS

void Game::resetGrid() {
  for (int x = 0; x < screenWidth / gridWidth; x++) {
    for (int y = 0; y < gridHeight / gridHeight; y++) {
      grid[x][y] = 0; // Set all to 0 (walkable)
    }
  }
}
