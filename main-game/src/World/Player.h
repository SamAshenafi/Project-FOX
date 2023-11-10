#pragma once
#include "Entity.h"
// #include "Combat/Unit.h"
// #include "enums.h"
#include <string>
#include "World.h"
#include <queue>

class World;

class Player : public Entity {
  public:
    std::string facing;

    // For stopping movement during dialogue
    bool movable;

    Player(
        const std::string& playerId,
        int playerX,
        int playerY,
        std::string facing,
        Inventory playerInventory
        );

    std::queue<std::pair<int, int>> pathQueue = {};

    void processInput(Game&);
    void move(int newX, int newY);

    //stats specific
    // int exp;
    // int level = (level * 100 * 1.25) * exp;
    // std::vector<equipment*> equipments;

    // Shared
    void render(int gridWidth, int gridHeight);
    void update();

  private:
    // Animation duration
    int animationDuration = 0;

    // Private Helpers to reduce redundancy
    std::string inputHelper(std::string facing);
    void resetAnimationDuration();
    void findShortestPath(World& world, int startX, int startY, int targetX, int targetY);
};