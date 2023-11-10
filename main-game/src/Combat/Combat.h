// Combat.h
#pragma once

#include <string.h>
#include <string>
#include "../GameState.h"
#include <queue>
#include "./Hero/Heroes.h"
#include "Foe/Foes.h"
#include "../Game.h"
#include "./Action/Action.h"
// #include "./Action/Actions.h" // Error, use this in cpp instead

// class Game;
class Unit;

class Combat : public GameState {

  public:
    Combat(std::string combatId); // constructor
    ~Combat() override; // destructor

    void processInput(Game& game) override;
    void update(Game& game) override;
    void render(Game& game) override;

    Room currentRoom;

    Texture2D bg;

    // Placeholder for making loadBattle()
    std::vector<Unit*> unitsFromJSON = {};
    void loadBattle(const std::string& battleId);

    // std::vector<Unit> units;
    // std::vector<Unit*> turnQueue = {};
    std::queue<Unit*> turnQueue = {};
    std::vector<Unit*> heroes = {};
    std::vector<Unit*> foes = {};

    // int currentUnitIndex;
    // bool isRoundOver;
    int currentRound = 0;
    Unit* currentUnit = nullptr;
    // int currentUnitIndex = 0;
    // void startRound();
    
    int selected = 0;
    int numberOfTargets;
    Action* highlightedAction = nullptr;
    std::vector<Unit*> targets = {};
    Unit* highlightedTarget = nullptr;
    std::vector<Unit*> availableTargets = {};
    std::vector<Unit*> previousAvailable = {};

    bool isRoundOver = false;;
    bool combatConcluded = false;

    int animationDuration = 0;



    // std::unordered_map<std::string, std::function<Action*()>> abilityMap = {
    //   {"DoNothing", []() { return new DoNothing(); }},
    // };
    // std::unordered_map<std::string, std::function<Foe*()>> foeMap;
    // std::unordered_map<std::string, std::function<Foe*()>> foeMap = {
    //   {"FoxFoe", []() { return new FoxFoe(); }},
    //   // {"AnotherEnemyType", []() { return new AnotherEnemyType(); }},
    //   // Add more enemy types as needed
    // };

    // Helpers
    bool isHero(Unit* unit);
    bool isFoe(Unit* unit);
    std::vector<Unit*> unitsVanquished (std::vector<Unit*> units);
    Foe* createFoe(const std::string& foeId);
    Action* createAction(const std::string& actionId, int amount);
    
    void RenderUI(int screenWidth,int screenHeight);
    void RenderUnits(
      std::vector<Unit*> heroes,
      std::vector<Unit*> foes,
      int screenWidth,
      int screenHeight
    );
    Texture2D loadTexture(std::string filePath);
    void loadTokenTextures();
};
