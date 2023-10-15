// Game.cpp
#include "Game.h"
#include "Combat.h"
#include <cstdio>

Game::Game() {
  InitWindow(settings.screenWidth, settings.screenHeight, "Project: Fox");
  // SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
  SetTargetFPS(60);

<<<<<<< HEAD
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
        gameState = combat;
        break;
      case combat:
        handleUserInputCombat();
        renderCombat();
        break;
    }
  }
=======
  // IMPORTANT: Any texture loading have to go after InitWindow
>>>>>>> ca4a2d8278ac5c8c41104669300cff9cec22798c

  // settings.settings.screenWidth = 1920 / 2;
  // settings.settings.screenHeight = 1080 / 2;
  world = new World(currentRoomId);

  // set initinal game state
  GameState* newState = new MainMenu();
  // GameState* newState = world;
  // GameState* newState = new Combat();
  currentState = newState;
}

Game::~Game() {
  delete currentState;
  delete world;

  CloseWindow();
}


void Game::run() {
  while (!WindowShouldClose()) {
    if (currentState != nullptr) {
      currentState->processInput(*this);
      currentState->update(*this);
      currentState->render(*this);
    }
  }
}

// TODO: FIX THIS!!!!!!
// NOTE: This is very very bad code (it work tho lol), pls fix !!!
void Game::changeState(std::string state) {
  GameState* newState = nullptr;

  if (state == "mainMenu") {
    fprintf(stderr, "gameState is now MainMenu!\n");
    newState = new MainMenu();
  }
  else if (state == "world") {
    if (currentState == world) {
      fprintf(stderr, "gameState is already world!!!\n");
      return;
    }
    else {
      fprintf(stderr, "gameState is now world!\n");
      // loadSave("savedata-01");
      delete currentState;
      currentState = world;
      return;
      // newState = new World(currentRoomId);

    }
  }
  else if (state == "combat") {
    fprintf(stderr, "gameState is now Combat!\n");
    newState = new Combat();
  }

  if (currentState != newState) {
    if (currentState != world) {
      delete currentState;
    }
    currentState = newState;
  }
}

void Game::renderDialog() {
  bool isHover = (GetMousePosition().y / settings.gridHeight) >= 12;
  if (!dialogQueue.empty()) {
    // Draw a dialogue box
    DrawRectangle(
        0,
        settings.screenHeight - settings.overworldUIHeight,
        settings.screenWidth,
        settings.overworldUIHeight,
        DARKGRAY
        );
    if (isHover) {
      Color highlightColor = {255, 255, 255, 75}; // Adjust the alpha value as needed
      DrawRectangle(
          0,
          settings.screenHeight - settings.overworldUIHeight,
          settings.screenWidth,
          settings.overworldUIHeight,
          highlightColor
          );
    }
    else {
    }
    // Draw the current dialog text
    DrawText(
        dialogQueue.front().c_str(),
        10,  // X position of the text
        settings.screenHeight - settings.overworldUIHeight + 10,  // Y position of the text
        20,  // Font size
        WHITE
        );
  }
}

<<<<<<< HEAD
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
    case KEY_P:
      fprintf(stderr, "%s\n", "p was pressed");
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
  // UserInputCombat should follow these controls
  /*
      Down - changes selection down 1
      Up - changes selection up 1
      Right and/or Space - selects whatever is being hovered over

      Mousing over selection boxes - sets the selection to whats being hovered over
      clicking whats being selected - selects whatever is being hovered over
  */

  return;
};

// ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
// ░█░░░█▀█░█▀█░█▀▄
// ░█░░░█░█░█▀█░█░█
// ░▀▀▀░▀▀▀░▀░▀░▀▀░
// LOAD

=======
>>>>>>> ca4a2d8278ac5c8c41104669300cff9cec22798c
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
      // loadRoom(currentRoomId);
      // const std::string roomFilePath = "./assets/room/";
      std::string roomFilePath = "./assets/room/" + currentRoomId;
      // overworldBg = LoadTexture((roomFilePath + "-bg.png").c_str());
      // TODO: also load overworldFg

      completed.clear();
      for (const auto& item : root["completed"]) {
        completed.push_back(item.get<std::string>());
      }

      // playerX = root.value("playerX", 0);
      // playerY = root.value("playerY", 0);
      // playerFacing = root.value("playerFacing", "down");
      //
      // player = new Player(
      //     "player-01",
      //     playerX,
      //     playerY,
      //     playerFacing
      //     );
      // entities.push_back(player);

      // TODO: Add inventory parsing logic here
      // TODO: Add more deserialization logic for other members here

      // parses data for party size, party data is handled in a seperate file 
      //(might be changed for it to be handled for only the save file?)
      //stats for each party member are altered seperately
      //json for party member stats are changed only when the game is saved
      party = {};
      for (const auto& partyData : root["party"])
       {
          Char_Stat add;
          add.id = enemyData["id"];
          add.currentHp = enemyData["currentHp"];
          add.maxHp = enemyData["maxHp"];
          add.atkDmg = enemyData["atkDmg"];
          add.armor = enemyData["armor"];
          party.insert(add);

          // TODO: add abilities 
       }

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

void Game::saveSave(const std::string& filename) {
  const std::string saveFilePath = "./save/";
  const std::string jsonFileType = ".json";
  const std::string fullFilePath = saveFilePath + filename + jsonFileType;
  nlohmann::json root;
  // TODO: this part is also WIP, more work need to be done here
  // Mostly,
  // - Player x, y, and other data members also need to be saved
  // - Room does not need to be saved since we load it when we load the save

  //TODO: add portion that saves the stats for each party member

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
        
        // Part of placeholder below
        fprintf(stderr, "Chest contains:\n");

        // Parse Chest
        for (const auto& itemData : root["items"]) {
            std::string itemID = itemData["id"].get<std::string>();
            int quantity = itemData["quantity"].get<int>();
            // TODO: Menu and implementation for taking things in and out of chests
            // Placeholder
            fprintf(stderr, "%i %s\n", quantity, itemID.c_str());
            }

      }
      catch (const std::exception& e) {
        fprintf(stderr, "JSON parsing failed: %s\n", e.what());
      }
    }
  }
  else if (tileType == "combat") {
    // TODO: load combat encounter, blah blah blah
    // first grabs enemy data from the tileType
    // then grabs player data from file
    // initiates combat right after

    const std::string combatFilePath = "./json/combat/";
    const std::string jsonFileType = ".json";
    const std::string fullFilePath = combatFilePath + tileId + jsonFileType;
    nlohmann::json root;
    std::ifstream jsonFile(fullFilePath);
    if (jsonFile.is_open()) {
      try {
        jsonFile >> root;
<<<<<<< HEAD
        // TODO: parse combat json data here
        /*
          Combat data includes (and this will be updated as combat is developed)

          id - used for displaying the enemy name as well as grabbing its texture path
          currentHp - the current amount of health points a character has 
          maxHp - the maximum amount of health points a character has 
          atkDmg - the strength of a characters attack
          armor - what damage is reduced depending on a attack

          player party should already have been set before hand
          maybe have it kept in the save file?
        */
       encounter = party;
       for (const auto& enemyData : root["enemies"])
       {
          Char_Stat add;
          add.id = enemyData["id"];
          add.currentHp = enemyData["currentHp"];
          add.maxHp = enemyData["maxHp"];
          add.atkDmg = enemyData["atkDmg"];
          add.armor = enemyData["armor"];
          encounter.insert(add);

          // TODO: add abilities 

       }
=======

        // Part of placeholder below
        fprintf(stderr, "------Battle------\n");

        fprintf(stderr, "--Conditions\n");
        // Parse conditions
        for (const auto& conditionData : root["conditions"]) {
            std::string condition = conditionData.get<std::string>();
            // Placeholder
            fprintf(stderr, "%s\n", condition.c_str());
        }

        // Parse enemies
        fprintf(stderr, "--Enemies\n");
        for (const auto& enemyData : root["enemies"]) {
            std::string enemy = enemyData["id"].get<std::string>();
            int ATK = enemyData["ATK"].get<int>();
            int DEF = enemyData["DEF"].get<int>();
            int SPD = enemyData["SPD"].get<int>();
            // Placeholder
            fprintf(stderr, "%s:\n   ATK: %i\n   DEF: %i\n   SPD: %i\n",
                enemy.c_str(),
                ATK, DEF, SPD);
        }

      }
      catch (const std::exception& e) {
        fprintf(stderr, "JSON parsing failed: %s\n", e.what());
      }
    }
  }
  else if (tileType == "npc") {
    // TODO: Call dialogue
    const std::string npcFilePath = "./json/npc/";
    const std::string jsonFileType = ".json";
    const std::string fullFilePath = npcFilePath + tileId + jsonFileType;
    nlohmann::json root;
    std::ifstream jsonFile(fullFilePath);
    if (jsonFile.is_open()) {
      try {
        jsonFile >> root;

        // Part of placeholder below
        fprintf(stderr, "------NPC------\n");

        // Parse NPC data
        std::string name = root["name"].get<std::string>();
        std::string text = root["text"].get<std::string>();
        fprintf(stderr, "%s: %s\n", name.c_str(), text.c_str());

>>>>>>> ca4a2d8278ac5c8c41104669300cff9cec22798c
      }
      catch (const std::exception& e) {
        fprintf(stderr, "JSON parsing failed: %s\n", e.what());
      }
    }
    gameState = loading_combat;
  }
  // TODO: add more parsing for other tile type here
  else if (true) {
  }
}
