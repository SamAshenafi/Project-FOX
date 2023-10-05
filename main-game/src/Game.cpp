// Game.cpp
#include "Game.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <queue>
#include <raylib.h>
#include "nlohmann/json.hpp"

Game::Game() : gen(rd()) {
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

void Game::renderStartMenu() {
  BeginDrawing();
  // TODO: put your render for start menu/screen here

  // placeholder, to be replaced
  DrawText(
      "Press Space to Continue or something idk",
      screenWidth / 2 - 50,
      screenHeight / 2, 20,
      RAYWHITE
      );
  EndDrawing();
}

void Game::renderOverworld() {
  BeginDrawing();
  // ClearBackground(RAYWHITE);
  ClearBackground(DARKGRAY);
  // DrawTexture(overworldBg, 0, 0, WHITE);

  Rectangle srcRect = { 0, 0, static_cast<float>(overworldBg.width), static_cast<float>(overworldBg.height) };
  Rectangle destRect = { 0, 0, static_cast<float>(screenWidth), static_cast<float>((screenHeight - overworldUIHeight)) };
  // DrawTexture(overworldBg, 0, 0, WHITE);
  DrawTexturePro(
      overworldBg,
      srcRect,
      destRect,
      { 0, 0 },
      0.0f,
      WHITE
      );

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
  renderDialog();
  EndDrawing();
}

void Game::renderCombat() {
  // TODO:
}

void Game::renderDialog() {
  bool isHover = (GetMousePosition().y / gridHeight) >= 12;
  if (!dialogQueue.empty()) {
    // Draw a dialogue box
    DrawRectangle(
        0,
        screenHeight - overworldUIHeight,
        screenWidth,
        overworldUIHeight,
        DARKGRAY
        );
    if (isHover) {
      Color highlightColor = {255, 255, 255, 75}; // Adjust the alpha value as needed
      DrawRectangle(
          0,
          screenHeight - overworldUIHeight,
          screenWidth,
          overworldUIHeight,
          highlightColor
          );
    }
    else {
    }
    // Draw the current dialog text
    DrawText(
        dialogQueue.front().c_str(),
        10,  // X position of the text
        screenHeight - overworldUIHeight + 10,  // Y position of the text
        20,  // Font size
        WHITE
        );
  }
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
    Vector2 mousePosition = GetMousePosition();
    int targetX = mousePosition.x / gridWidth;
    int targetY = mousePosition.y / gridHeight;

    fprintf(stderr, "mousePosition: %d, %d\n", targetX, targetY);

    // If player hit the UI/Dialog area
    if (targetY >= 12) {
      if (!dialogQueue.empty()) {
        dialogQueue.pop();
        return;
      }
      // NOTE: UI button interaction should go here
    }

    std::queue<std::pair<int, int>>().swap(pathQueue); // empty the queue
    findShortestPath(player->x, player->y, targetX, targetY);
    if (!pathQueue.empty()) {
      // reset move timer for smoother transition?
      deltaTimeSinceLastMove = 0;
    }
  }

  int keyPressed = GetKeyPressed();
  switch (keyPressed) {
    case KEY_O:
      {
        fprintf(stderr, "%s\n", "o was pressed");
        std::string placeholderDialog = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Suspendisse sed maximus nisl. In condimentum urna ac feugiat gravida. Vestibulum et iaculis arcu. Mauris commodo arcu et sem ornare maximus. Phasellus sit amet imperdiet odio. Duis tincidunt tincidunt faucibus. Donec dapibus, nulla nec fringilla hendrerit, arcu tellus eleifend neque, quis congue magna lacus sed nisi.";
        int d4Result = rollD4();
        switch (d4Result) {
          case 1:
            dialogQueue.push("Failure!");
            break;
          case 2:
            dialogQueue.push("Hi, this is dialog. Ipsum...");
            break;
          case 3:
            dialogQueue.push("Almost!");
            break;
          case 4:
            dialogQueue.push(placeholderDialog);
            break;
        }
        break;
      }
    case KEY_S:
      fprintf(stderr, "%s\n", "s was pressed");
      // TODO: This is place holder
      // plan is to have a button/UI to select different save
      // like savedata-02 -> savedata-08
      fprintf(stderr, "%s\n", "saved to savedata-01.json");
      saveSave("savedata-01");
      break;
    case KEY_SPACE:
      fprintf(stderr, "%s\n", "space was pressed");
      if (!dialogQueue.empty()) {
        dialogQueue.pop();
        break;
      }
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
      std::pair<int, int> nextPos = pathQueue.front();
      pathQueue.pop();
      player->move(nextPos.first, nextPos.second);
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

  std::queue<std::pair<int, int>>().swap(pathQueue); // empty the queue

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


/*
TODO: This can be optimized further by keeping track of the target
the player is walking to then decide if the current path is "good"
if good -> calculate from old target to new target instead
if bad -> same as before
*/
void Game::findShortestPath(int startX, int startY, int targetX, int targetY) {
  std::pair<int, int> start = { startX, startY};
  std::pair<int, int> target = { targetX, targetY};
  int dx[] = {1, -1, 0, 0};  // Possible movements in x-direction
  int dy[] = {0, 0, 1, -1};  // Possible movements in y-direction
  std::vector<std::vector<std::pair<int, int>>> parent(20, std::vector<std::pair<int, int>>(12, {-1, -1}));
  std::queue<std::pair<int, int>> q;
  q.push(start);

  if (grid[targetX][targetY] != 0) {
    std::cout << "Target cell is not reachable!" << std::endl;
    return;
  }

  while (!q.empty()) {
    std::pair<int, int> curr = q.front();
    q.pop();

    if (curr == target) {
      // Reconstruct the path from target to start
      std::vector<std::pair<int, int>> path;
      while (curr.first != start.first || curr.second != start.second) {
        path.push_back(curr);
        curr = parent[curr.first][curr.second];
      }
      path.push_back(start);

      // update the pathQueue
      for (int i = path.size() - 1; i >= 0; --i) {
        pathQueue.push(path[i]);
      }
      return;
    }

    for (int i = 0; i < 4; ++i) {
      int newX = curr.first + dx[i];
      int newY = curr.second + dy[i];
      bool isValid =
        newX >= 0 &&
        newX < 20 &&
        newY >= 0 &&
        newY < 12 &&
        grid[newX][newY] == 0;

      if (isValid && parent[newX][newY].first == -1) {
        q.push({newX, newY});
        parent[newX][newY] = curr;
      }
    }
  }

  std::cout << "No path found!" << std::endl;
}

int Game::rollD4() {
  std::uniform_int_distribution<int> distribution(1, 4);
  return distribution(gen);
}

int Game::rollD20() {
  std::uniform_int_distribution<int> distribution(1, 20);
  return distribution(gen);
}
