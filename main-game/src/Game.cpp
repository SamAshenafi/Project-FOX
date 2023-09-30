// Game.cpp
#include "Game.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <queue>
#include <raylib.h>
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
        // NOTE: when the player select or start new save, loadSave() -> loadRoom()
        // the player is in the overworld after (cannot save in combat, save exclusively happen when overworld )
        loadSave("savedata-01");
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
  // ClearBackground(RAYWHITE);
  ClearBackground(DARKGRAY);
  DrawTexture(overworldBg, 0, 0, WHITE);

  // Draw the grid (debug only)
  for (int x = 0; x < screenWidth; x += gridWidth) {
    for (int y = 0; y < (screenHeight - overworldUIHeight); y += gridHeight) {
      if (grid[x / gridWidth][y / gridHeight] == 1) {
        DrawRectangle(x, y, gridWidth, gridHeight, DARKGRAY);
      }
      else {
        // DrawRectangleLines(x, y, gridSize, gridSize, DARKGRAY);
        DrawRectangleLines(x, y, gridWidth, gridHeight, BLACK);
      }


    }
  }

  for (GameObject* gameObject : gameObjects) {
    // Call the render method for each object through the pointer
    gameObject->render(gridWidth, gridHeight);
  }

  // TODO: draw currentRoomId-fg.png here

  Vector2 mousePosition = GetMousePosition();
  int gridX = mousePosition.x / gridWidth;
  int gridY = mousePosition.y / gridHeight;
  for (int x = 0; x < screenWidth; x += gridWidth) {
    for (int y = 0; y < (screenHeight - overworldUIHeight); y += gridHeight) {
      // Check if mouse is over this grid tile
      if (x / gridWidth == gridX && y / gridHeight == gridY) {
        // DrawRectangle(x, y, gridWidth, gridHeight, ColorAlpha(WHITE, 30));
        Color highlightColor = {255, 255, 255, 75}; // Adjust the alpha value as needed
        DrawRectangle(x, y, gridWidth, gridHeight, highlightColor);
      }
    }
  }
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

  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    std::queue<Vector2>().swap(pathQueue); // empty the queue
    Vector2 mousePosition = GetMousePosition();
    int targetX = mousePosition.x / gridWidth;
    int targetY = mousePosition.y / gridHeight;
    fprintf(stderr, "mousePosition: %d, %d\n", targetX, targetY);

    std::vector<Vector2> path = findShortestPath(player->x, player->y, targetX, targetY);
    if (!path.empty()) {
      for (const Vector2& position : path) {
        // debug
        std::cout << "X: " << position.x << ", Y: " << position.y << std::endl;
        pathQueue.push(position);
      }

      // Debug: Print the contents of pathQueue
      // std::cout << "Contents of pathQueue:" << std::endl;
      // std::queue<Vector2> tempQueue = pathQueue; // Copy pathQueue for debugging
      // while (!tempQueue.empty()) {
      //   Vector2 pos = tempQueue.front();
      //   tempQueue.pop();
      //   std::cout << "X: " << pos.x << ", Y: " << pos.y << std::endl;
      // }
    }
    else {
      std::cout << "No path found!" << std::endl;
    }
  }

  int keyPressed = GetKeyPressed();
  switch (keyPressed) {
    case KEY_S:
      // TODO: This is place holder
      // plan is to have a button/UI to select different save
      // like savedata-02 -> savedata-08
      fprintf(stderr, "%s\n", "saved to savedata-01.json");
      saveSave("savedata-01");
      break;
    case KEY_SPACE:
      fprintf(stderr, "%s\n", "space was pressed");
      int targetX = player->x;
      int targetY = player->y;

      if (player->facing == "up") {
        targetY--;
      }
      else if (player->facing == "down") {
        targetY++;
      }
      else if (player->facing == "left") {
        targetX--;
      }
      else if (player->facing == "right") {
        targetX++;
      }
      else {
        fprintf(stderr, "invalid player->facing direction");
        return;
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

  int newX = player->x;
  int newY = player->y;
  std::string direction = inputHelper();

  if (direction == "none") {
    // Continue moving along the path until the queue is empty
    while (!pathQueue.empty()) {
      if (deltaTimeSinceLastMove < moveSpeed) {
        break; // Too soon for another move
      }
      Vector2 nextPos = pathQueue.front();
      pathQueue.pop();
      player->move(nextPos.x, nextPos.y);
      lastMoveTime = currentTime;
      break;
    }
    return;
  }
  else if (direction == "right") {
    player->facing = "right";
    newX++;
  }
  else if (direction == "left") {
    player->facing = "left";
    newX--;
  }
  else if (direction == "down") {
    player->facing = "down";
    newY++;
  }
  else if (direction == "up") {
    player->facing = "up";
    newY--;
  }
  else {
    fprintf(stderr, "error direction\n");
  }

  std::queue<Vector2>().swap(pathQueue); // empty the queue

  if (deltaTimeSinceLastMove < moveSpeed) {
    return; // Too soon for another move
  }

  // NOTE: this might be uneccessary, add back if break
  // no movement
  // if (newX == player->x && newY == player->y) {
  // }

  // Check if the new position is out of bounds
  bool isOutOfBound = newX < 0 ||
    newX >= (screenWidth / gridWidth) ||
    newY < 0 ||
    newY >= ((screenHeight - overworldUIHeight) / gridHeight);
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
  else if (newY != 0){
    // NOTE: player's depth/y changed, so we need to sort the GameObjects vector
    sortGameObjects();
    player->move(newX, newY);
    lastMoveTime = currentTime;
  }
  else {
    player->move(newX, newY);
    lastMoveTime = currentTime;
  }
}

void Game::handleUserInputCombat() {
  // TODO:
  return;
};

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
      // const std::string roomFilePath = "./assets/room/";
      std::string roomFilePath = "./assets/room/" + currentRoomId;
      overworldBg = LoadTexture((roomFilePath + "-bg.png").c_str());
      // TODO: also load overworldFg

      completed.clear();
      for (const auto& item : root["completed"]) {
        completed.push_back(item.get<std::string>());
      }

      playerX = root.value("playerX", 0);
      playerY = root.value("playerY", 0);
      playerFacing = root.value("playerFacing", "down");

      player = new Player(
          "player-01",
          playerX,
          playerY,
          playerFacing
          );
      gameObjects.push_back(player);

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
  const std::string saveFilePath = "./json/room/";
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
    const std::string chestFilePath = "./json/chest/";
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
    const std::string combatFilePath = "./json/combat/";
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
    for (int y = 0; y < (screenHeight - overworldUIHeight) / gridHeight; y++) {
      grid[x][y] = 0; // Set all to 0 (walkable)
    }
  }
}

void Game::sortGameObjects() {
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

}

std::string Game::inputHelper() {
  std::string lastDirection = player->facing;

  if (IsKeyPressed(KEY_RIGHT)) return "right";
  if (IsKeyPressed(KEY_LEFT)) return "left";
  if (IsKeyPressed(KEY_UP)) return "up";
  if (IsKeyPressed(KEY_DOWN)) return "down";

  bool isNoMovementKeyHeld = !(
      IsKeyDown(KEY_RIGHT) ||
      IsKeyDown(KEY_LEFT) ||
      IsKeyDown(KEY_DOWN) ||
      IsKeyDown(KEY_UP)
      );

  if (isNoMovementKeyHeld) {
    return "none";
  }

  bool isNoChange =
    IsKeyDown(KEY_RIGHT) && lastDirection == "right" ||
    IsKeyDown(KEY_LEFT) && lastDirection == "left" ||
    IsKeyDown(KEY_DOWN) && lastDirection == "down" ||
    IsKeyDown(KEY_UP) && lastDirection == "up";

  if (isNoChange) {
    return lastDirection;
  }
  else {
    if (IsKeyDown(KEY_RIGHT)) {
      return "right";
    }
    else if (IsKeyDown(KEY_LEFT)) {
      return "left";
    }
    else if (IsKeyDown(KEY_DOWN)) {
      return "down";
    }
    else if (IsKeyDown(KEY_UP)) {
      return "up";
    }
  }

  return "error";
}

std::vector<Vector2> Game::findShortestPath(int startX, int startY, int targetX, int targetY) {
  Vector2 start = {(float)startX, (float)startY};
  Vector2 target = {(float)targetX, (float)targetY};
  int dx[] = {1, -1, 0, 0};  // Possible movements in x-direction
  int dy[] = {0, 0, 1, -1};  // Possible movements in y-direction
  std::vector<std::vector<Vector2>> parent(20, std::vector<Vector2>(12, {-1, -1}));
  std::queue<Vector2> q;
  q.push(start);

  while (!q.empty()) {
    Vector2 curr = q.front();
    q.pop();

    if (curr.x == target.x && curr.y == target.y) {
      // Reconstruct the path from target to start
      std::vector<Vector2> path;
      while (curr.x != start.x || curr.y != start.y) {
        path.push_back(curr);
        curr = parent[(int)curr.x][(int)curr.y];
      }
      path.push_back(start);
      std::reverse(path.begin(), path.end());
      return path;
    }

    for (int i = 0; i < 4; ++i) {
      int newX = (int)curr.x + dx[i];
      int newY = (int)curr.y + dy[i];
      bool isValid =
        newX >= 0 &&
        newX < 20 &&
        newY >= 0 &&
        newY < 12 &&
        grid[newX][newY] == 0;

      if (isValid && parent[newX][newY].x == -1) {
        q.push({(float)newX, (float)newY});
        parent[newX][newY] = curr;
      }
    }
  }

  // No path found
  return {};
}
