#include "raylib.h"
#include "input.h"
#include <iostream>

// Testing setup that directly tests the output of DirectionalInput.getDirection()

int main() {
    InitWindow(800, 450, "Testing");
    SetTargetFPS(60);

    DirectionalInput input;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKGRAY);
        std::cout << "directional output: " << input.getDirection() << std::endl;
        EndDrawing();
    }
    return 0;
}