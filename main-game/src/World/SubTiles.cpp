#include "Tile.h"
#include "../../external-libs/nlohmann/json.hpp"

// ---------------------------------------------- Combat Tile
CombatTile::CombatTile(
    const std::string& tileId,
    int tileX,
    int tileY,
    bool isBlockMovement
) : Tile(tileId, tileX, tileY, isBlockMovement)
{
  // Additional constructor functionality to add to base constructor

  // sprite = Helper::loadTexture("path_to_your_tile_texture.png");
}

std::pair<std::string, std::string> CombatTile::interact() {

  return Tile::interact();
}

// ---------------------------------------------- NPC Tile
NpcTile::NpcTile(
    const std::string& tileId,
    int tileX,
    int tileY,
    bool isBlockMovement
) : Tile(tileId, tileX, tileY, isBlockMovement)
{
  // Additional constructor functionality to add to base constructor
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
      fprintf(stderr, "%s JSON parsing failed: %s\n", id, e.what());
    }
  }
}

std::pair<std::string, std::string> NpcTile::interact() {
  return Tile::interact();
}

// ---------------------------------------------- Chest Tile
ChestTile::ChestTile(
    const std::string& tileId,
    int tileX,
    int tileY,
    bool isBlockMovement
) : Tile(tileId, tileX, tileY, isBlockMovement)
{
  const std::string chestFilePath = "./json/chest/";
  const std::string jsonFileType = ".json";
  const std::string fullFilePath = chestFilePath + id + jsonFileType;
  nlohmann::json root;
  std::ifstream jsonFile(fullFilePath);
  if (jsonFile.is_open()) {
    try {
      jsonFile >> root;

      tileText = "Obtained:";

      int chestKeys = root["keys"];
      inventory.setKeys(chestKeys);
      if (inventory.hasKey()) tileText = tileText + " " + std::to_string(chestKeys) + " key \\\\";

      // Parse Chest
      for (const auto& itemData : root["items"]) {
        std::string itemID = itemData["id"].get<std::string>();
        int quantity = itemData["quantity"].get<int>();
        tileText = tileText + " " + std::to_string(quantity) + " " + itemID.c_str() + " \\\\";

        // TODO: Fill chest inventory here:




      }
    }
    catch (const std::exception& e) {
      fprintf(stderr, "JSON parsing failed: %s\n", e.what());
    }
  }

  // sprite = Helper::loadTexture("path_to_your_tile_texture.png");
}

// ---------------------------------------------- Door Tile
DoorTile::DoorTile(
    const std::string& tileId,
    int tileX,
    int tileY,
    bool isBlockMovement
) : Tile(tileId, tileX, tileY, isBlockMovement)
{
  // Additional constructor functionality to add to base constructor

  // sprite = Helper::loadTexture("path_to_your_tile_texture.png");
}

void DoorTile::open() {
  isBlockMovement = false;
  // TODO: Change sprite to sprite for open door
}