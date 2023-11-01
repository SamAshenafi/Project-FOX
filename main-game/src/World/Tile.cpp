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

std::pair<std::string, std::string> Tile::interact() {
  std::string tileType = Helper::parseGameObjectType(id);
  std::string tileText = "";
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
        // Parse NPC data
        std::string name = root["name"].get<std::string>();
        std::string text = root["text"].get<std::string>();
        // Add to second output string
        tileText = name + ": " + text;
      }
      catch (const std::exception& e) {
        fprintf(stderr, "JSON parsing failed: %s\n", e.what());
      }
    }
  }
  // TODO: add more parsing for other tile type here
  else if (true) {
  }
  return std::make_pair(tileType, tileText);
}

void Tile::render(int gridWidth, int gridHeight) {
  // PLACEHOLDER:
  Color color = BLUE;
  std::string tileType = Helper::parseGameObjectType(id);
  if (tileType == "chest") color = YELLOW;
  else if (tileType == "npc") color = GREEN;
  else if (tileType == "battle") color = RED;
  DrawRectangle(
      x * gridWidth,
      y * gridHeight,
      gridWidth,
      gridHeight,
      color);
  return;
}
