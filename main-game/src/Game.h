// Game.h
#pragma once
// #include "GameStates.h"

#include "Combat/Unit.h"
#include "raylib.h"
#include "vector"
#include "Combat.h"
#include "Helper.h"
#include <algorithm>
#include <memory>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <queue>
#include <random>
#include <string_view>
#include <string>
// #include "enums.h"
#include "../external-libs/nlohmann/json.hpp"

#include "GameState.h"

#include "World/World.h"
#include "World/Entity.h"
#include "World/Player.h"
#include "World/Tile.h"

#include "Combat/Combat.h"
#include "MainMenu/MainMenu.h"

class GameState;

class GameSettings {
  public:
    int screenWidth = 1920 / 2;
    int screenHeight = 1080 / 2;
    int gridWidth = 96 / 2;
    int gridHeight = 80 / 2;
    int overworldUIHeight = 120 / 2;
};

class Game {
  public:
    Game();
    ~Game();

    void run();

    // resolution
    GameSettings settings;
    // TODO: add some way to change the resolution variables back and forth

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
    // it will be loaded from ./json/player/ if not found
    // in ./save/player/
    // the json will be write to whenever player change equipments or skill
    // and at the end of combat when the player might earn something like EXP

    // the vector used to store the stats for a combat encounter
    std::vector<Char_Stat> encounter;
    std::vector<Char_Stat> party;

    std::queue<std::pair<int, int>> pathQueue;

    // DialogQueue dialogueQueue;
    std::queue<std::string> dialogQueue;

    // savedata.json contains
    std::string currentRoomId = "05-06";
    std::vector<std::string> completed;
    // std::vector<std::string> tempCompleted;

    // inventory mini-class (don't make a class for this yet)
    int gold = 0;
    std::vector<std::string> items;


    // Exploration* exploration;
    // MainMenu* mainMenu;

    GameState* world;

    GameState* currentState;
    // void processInput();
    // void update();
    // void render();

    void changeState(std::string state);

    void renderDialog();

    // NOTE: save to autosave.json whenever combat-> overworld or move to new room
    void loadSave(const std::string& filename);
    // void loadRoom(const std::string& roomId);
    void saveSave(const std::string& filename);
    // trigger when interact with a tile
    void loadTile(const std::string& tileId);

    // Helpers
};

