// Combat.h
#pragma once

#include <string.h>
#include <string>
#include "../GameState.h"
#include <queue>
#include "./Hero/Heroes.h"
#include "Foe/Foe.h"

#include "../Game.h"
// #include "./Action/Actions.h"
#include "./Action/Action.h"

// class Game;

class Combat : public GameState {

  public:
    Combat(); // constructor
    ~Combat() override; // destructor

    void processInput(Game& game) override;
    void update(Game& game) override;
    void render(Game& game) override;

    Room currentRoom;

    Texture2D bg;

    // std::vector<Unit> units;
    std::queue<Unit*> turnQueue = {};
    std::vector<Hero*> heroes = {};
    std::vector<Foe*> foes = {};

    // int currentUnitIndex;
    // bool isRoundOver;
    int currentRound = 0;
    Unit* currentUnit = nullptr;
    // void startRound();

    bool isRoundOver = false;;

    std::unordered_map<std::string, std::function<Action*()>> abilityMap;

    // Helpers
    bool isHero(Unit* unit);
    bool isFoe(Unit* unit);

};
