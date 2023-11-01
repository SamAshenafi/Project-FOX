// Game.cpp
#include "Game.h"
#include <cstdio>

Game::Game() {
  InitWindow(settings.screenWidth, settings.screenHeight, "Project: Fox");
  // SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
  SetTargetFPS(60);

  // IMPORTANT: Any texture loading have to go after InitWindow

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
// void Game::changeStateByString(std::string state) {
//   GameState* newState = nullptr;
//
//   if (state == "mainMenu") {
//     fprintf(stderr, "gameState is now MainMenu!\n");
//     newState = new MainMenu();
//   }
//   else if (state == "world") {
//     if (currentState == world) {
//       fprintf(stderr, "gameState is already world!!!\n");
//       return;
//     }
//     else {
//       fprintf(stderr, "gameState is now world!\n");
//       // loadSave("savedata-01");
//       delete currentState;
//       currentState = world;
//       return;
//       // newState = new World(currentRoomId);
//
//     }
//   }
//   else if (state == "combat") {
//     fprintf(stderr, "gameState is now Combat!\n");
//     newState = new Combat();
//   }
//
//   if (currentState != newState) {
//     if (currentState != world) {
//       delete currentState;
//     }
//     currentState = newState;
//   }
// }

void Game::changeState(GameState* newGameState) {
  if (newGameState == currentState) return;
  if (currentState != world) {
    delete currentState;
  }
  currentState = newGameState;
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


// TODO: Remember to construct room background filepaths when loading room vector from save
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

      // World Data
      nlohmann::json worldData = root["WorldData"];
      world->players.clear();
      for (const auto& pc : worldData["Players"]) {
        Player* PC = new Player(
          pc["id"], pc["x"], pc["y"], pc["facing"]
        );
        world->players.push_back(PC);
      }
      world->rooms.clear();
      for (const auto& room : worldData["Rooms"]) {
        Room* newRoom = world->buildRoom(room["room"], room);
        world->rooms.push_back(newRoom);
      }
      Room* roomToSet = world->findRoom(worldData["currentRoomId"]);
      world->setRoom(roomToSet);

      // Completed
      completed.clear();
      for (const auto& item : root["completed"]) {
        completed.push_back(item.get<std::string>());
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

  // Serialize member data to JSON
  root["completed"] = nlohmann::json::array();
  root["WorldData"] = nlohmann::json::object();
  root["WorldData"]["currentRoomId"] = currentRoomId;

  for (const std::string& item : completed) {
    root["completed"].push_back(item);
  }

  // -------- WorldData members
  root["WorldData"]["Players"] = nlohmann::json::array();
  root["WorldData"]["Rooms"] = nlohmann::json::array();

  for (Player* player : world->players) {
    nlohmann::json playerInfo = nlohmann::json::object( {
      {"id", player->id},
      {"x", player->x},
      {"y", player->y},
      {"facing", player->facing}
    });
    root["WorldData"]["Players"].push_back(playerInfo);
  }

  // Fill room data
  for (Room* room : world->rooms) {
    nlohmann::json roomData = nlohmann::json::object({
      {"room", room->roomId}, {"roomInfo", room->roomInfo}
    });

    roomData["specialTiles"] = nlohmann::json::array();
    for (Tile* tile : room->tiles) {
      roomData["specialTiles"].push_back(nlohmann::json::array({
        tile->id, tile->isBlockMovement, tile->x, tile->y
      }));
    }
    roomData["transitionTiles"] = nlohmann::json::array();
    for (TransitionTile* transitionTile : room->transitionTiles) {
      roomData["transitionTiles"].push_back(nlohmann::json::array({
        transitionTile->destinationRoomId,
        transitionTile->x, transitionTile->y,
        transitionTile->enterX, transitionTile->enterY
      }));
    }
    root["WorldData"]["Rooms"].push_back(roomData);
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