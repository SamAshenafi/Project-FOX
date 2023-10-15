// GameObject.h
#pragma once

#include <raylib.h>
#include <string>

class Entity {
  public:
    std::string id;
    int x;
    int y;

    // TODO: use this to render
    float offsetX = 0;
    float offsetY = 0;
    Texture2D sprite;

    // TODO: maybe add parameter such as scaling because
    // that is necessary for rendering correctly when resizing
    virtual void render(int gridWidth, int gridHeight) = 0;
};