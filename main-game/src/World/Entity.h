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
    // TODO: use this to render
    float offsetX = 0;
    float offsetY = 0;
    Texture2D sprite;

    // virtual void interact() = 0;
    virtual void render(int gridWidth, int gridHeight) = 0;
};
