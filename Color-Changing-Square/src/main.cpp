#include "raylib.h"
#include "middlesquare.h"

int main() {
    // Creates a window
    InitWindow(800, 450, "Testing");
    // Sets the FPS target to 60. I'm not sure whether this is necessary here.
    SetTargetFPS(60);

    // Creates the square in the middle
    // Square is a class declared in "middlesquare.h" with its class variables
    // And its functions are defined in "middlesquare.cpp"
    Square newSquare;

    // Runs in a loop until the window is closed
    while (!WindowShouldClose()) {
        // When the spacebar is pressed, the color of newSquare changes
        newSquare.changeColorOnSpace();
        // creates the canvas for drawing.
        BeginDrawing();
        // Draws a background. Raylib has macros defined for a number of colors
        // You can find them on the raylib website.
        ClearBackground(DARKGRAY);
        // Draws the square
        newSquare.draw();
        // Closes the drawing canvas
        EndDrawing();
    }
    return 0;
}