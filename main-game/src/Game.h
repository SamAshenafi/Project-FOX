// Game.h
#pragma once
#include "raylib.h"
#include "vector"
#include "Player.h"
#include "Tile.h"
#include "Helper.h"
#include <memory>
#include <string_view>
#include <string>
#include "enums.h"


class Game {
  public:
    Game();

    void run();

  private:
    // resolution
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    const int gridWidth = 96;
    const int gridHeight = 80;
    const int overworldUIHeight = 120;
    // TODO: add some way to change the scaling to and from 0.75
    float scaling = 1.0f;

    int grid[20][12];
    GameState gameState = GameState::start_menu;

    const double moveSpeed = 0.1;
    double lastMoveTime = 0;

    // NOTE: Tile & Player are stored in here
    std::vector<GameObject*> gameObjects;
    // NOTE: a pointer to reach the player easily
    Player* player = nullptr;

    // NOTE: Combat would have multiple characters
    // MAYBE: a vector<string> for id (like player-01)
    // and then load from {id}.json when enter combat
    // it will be loaded from ./src/json/player/ if not found
    // in ./save/player/
    // the json will be write to whenever player change equipments or skill
    // and at the end of combat when the player might earn something like EXP


    // set by loadRoom()
    //// set by roomId
    Texture2D overworldBg;
    Texture2D overworldFg;
    Texture2D combatBg;
    // std::vector<Tile> interactableTiles; // Vector to store interactable tiles
    // std::vector<TransitionTile> transitionTiles;


    // savedata.json contains
    std::string currentRoomId = "05-06";
    std::vector<std::string> completed;
    // std::vector<std::string> tempCompleted;

    // inventory mini-class (don't make a class for this yet)
    int gold = 0;
    std::vector<std::string> items;
    // NOTE: for item, we can just use id instead of making a new class
    // TODO: add more stuffs here like unlocked equipments, consumables, etc.
    // TODO: have a helper parse function for parsing item id
    // TODO: have a helper parse function for item name (get rid of the underscore(_))

    // these will only be used when loadSave() & saveSave() is called
    //// player data
    int playerX = 0;
    int playerY = 0;
    std::string playerFacing = "down";

    void handleUserInputStartMenu();
    void handleUserInputOverworld();
    void handleUserInputCombat();
    void shortestPath(int startX, int startY, int targetX, int targetY);

    // NOTE: save to autosave.json whenever combat-> overworld or move to new room
    void loadSave(const std::string& filename);
    void loadRoom(const std::string& roomId);
    void saveSave(const std::string& filename);
    // trigger when interact with a tile
    void loadTile(const std::string& tileId);
    // NOTE: can have a switch for which type of tile it is
    // if it chest, maybe add the contents to the inventory
    // if it ...

    void renderStartMenu();
    void renderOverworld();
    void renderCombat();

    // Helpers
    void resetGrid(); // set all in grid to 0
    void sortGameObjects();
    std::string inputHelper();
};


// NOTE: some of the variable init is useless since they are set by
// loadSave/loadRoom anyway, but keep it there to prevent error
// and improve readability

