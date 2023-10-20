// Tile.cpp
#include "Tile.h"
#include "../Helper.h"

Tile::Tile(
    const std::string& tileId,
    int tileX,
    int tileY,
    bool isBlockMovement
    ) :
  isBlockMovement(isBlockMovement)
{
  id = tileId;
  x = tileX;
  y = tileY;
  // sprite = Helper::loadTexture("path_to_your_tile_texture.png");
}

std::string Tile::interact() {
  // Copied from Game::loadTile()
  std::string tileType = Helper::parseGameObjectType(id);
  if (tileType == "chest") {
    const std::string chestFilePath = "./json/chest/";
    const std::string jsonFileType = ".json";
    const std::string fullFilePath = chestFilePath + id + jsonFileType;
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
  else if (tileType == "battle") {
    // TODO: load combat encounter, blah blah blah
    const std::string battleFilePath = "./json/battle/";
    const std::string jsonFileType = ".json";
    const std::string fullFilePath = battleFilePath + id + jsonFileType;
    nlohmann::json root;
    std::ifstream jsonFile(fullFilePath);
    
    // Placeholder until we can get combat to start
    fprintf(stderr, "battle tile\n");
    if (jsonFile.is_open()) {
      try {
        jsonFile >> root;
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
    const std::string fullFilePath = npcFilePath + id + jsonFileType;
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

      }
      catch (const std::exception& e) {
        fprintf(stderr, "JSON parsing failed: %s\n", e.what());
      }
    }
  }
  // TODO: add more parsing for other tile type here
  else if (true) {
  }
  return tileType;
}

void Tile::render(int gridWidth, int gridHeight) {
  // PLACEHOLDER:
  DrawRectangle(
      x * gridWidth,
      y * gridHeight,
      gridWidth,
      gridHeight,
      BLUE);
  return;
}
