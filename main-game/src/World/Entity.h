// GameObject.h
#pragma once

#include <raylib.h>
#include <string>
#include "Inventory.h"
class Entity {
  public:
    std::string id;
    int x;
    int y;
    Inventory inventory;
    // Use this to render
    int animationFrame = 0;
    int animationRow = 0;
    int spriteWidth = 200; // Default value for preventing problems
    int spriteHeight = 250; // Default value for preventing problems
    float offsetX = 0;
    float offsetY = 0;
    Texture2D sprite;

    // virtual void interact() = 0;
    virtual void render(int gridWidth, int gridHeight) = 0;
  protected:
    void renderHelper(int gridWidth, int gridHeight, bool flipped);
};
