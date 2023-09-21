#include "raylib.h"
#include "middlesquare.h"

void Square::draw() {
    // Draws the square using the class variables
    DrawRectangle(x, y, width, height, color);
}

void Square::changeColorOnSpace() {
    // Checks if the spacebar has been pressed.
    // Only returns true on the frame that the key is pressed, not in frames that it continues to be down
    // IsKeyDown() would return true on any frame that the key is down
    if (IsKeyPressed(KEY_SPACE)) {
        if (isRed) {
            color = BLUE;
        }
        else color = RED;
        isRed = !isRed;
    }
}