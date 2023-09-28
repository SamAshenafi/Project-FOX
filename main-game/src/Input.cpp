#include "raylib.h"
#include "Input.h"

DirectionalInput::DirectionalInput() {
    currRight = false; currUp = false; currLeft = false; currDown = false;
    lastRight = false; lastUp = false; lastLeft = false; lastDown = false;
    currRightPress = false; currUpPress = false; currLeftPress = false; currDownPress = false;
    prevDirection = NONE;
}

// Helper function for getDirection(). Just cleans things up a bit
void DirectionalInput::updateDirection() {
    lastRight = currRight;
    lastUp = currUp;
    lastLeft = currLeft;
    lastDown = currDown;
    currRight = rightHeld();
    currUp = upHeld();
    currLeft = leftHeld();
    currDown = downHeld();
    currRightPress = rightPressed();
    currUpPress = upPressed();
    currLeftPress = leftPressed();
    currDownPress = downPressed();
}

int DirectionalInput::getDirection() {
    updateDirection();
    // If the player is not pressing/holding any directional buttons, output NONE
    if (!(currRight || currUp || currLeft || currDown)) {
        prevDirection = NONE;
        return NONE;
    }
    // Return the last output if the input has not changed
    if (currRight == lastRight && currUp == lastUp && currLeft == lastLeft && currDown == lastDown) {
        return prevDirection;
    }

    // If a directional key was pressed on this frame, that's the output
    // Will exhibit priority if the user starts pressing buttons on the same frame,
    // but that is something that I do not expect someone to do on accident
    // **** Need to account for starting pressing a direction while the opposite is already pressed
            // ^^ Bug fixing later
    if (currRightPress) {
        prevDirection = RIGHT;
        return RIGHT;
    }
    if (currUpPress) {
        prevDirection = UP;
        return UP;
    }
    if (currLeftPress) {
        prevDirection = LEFT;
        return LEFT;
    }
    if (currDownPress) {
        prevDirection = DOWN;
        return DOWN;
    }

    switch (prevDirection) {
        case RIGHT :
            // If the previous direction is still being pressed, return it
            if (currRight) {
                return RIGHT;
            }
            // If not, and the opposite direction is being pressed, return that
            if (currLeft) {
                prevDirection = LEFT;
                return LEFT;
            }
            // If these aren't the case, check the remaining two
            if (currUp) {
                if (currDown) {
                    prevDirection = NONE;
                    return NONE;
                }
                else {
                    prevDirection = UP;
                    return UP;
                }
            }
            else {
                prevDirection = DOWN;
                return DOWN;
            }
        case UP :
            // If the previous direction is still being pressed, return it
            if (currUp) {
                return UP;
            }
            // If not, and the opposite direction is being pressed, return that
            if (currDown) {
                prevDirection = DOWN;
                return DOWN;
            }
            // If these aren't the case, check the remaining two
            if (currRight) {
                if (currLeft) {
                    prevDirection = NONE;
                    return NONE;
                }
                else {
                    prevDirection = RIGHT;
                    return RIGHT;
                }
            }
            else {
                prevDirection = LEFT;
                return LEFT;
            }
        case LEFT :
            // If the previous direction is still being pressed, return it
            if (currLeft) {
                return LEFT;
            }
            // If not, and the opposite direction is being pressed, return that
            if (currRight) {
                prevDirection = RIGHT;
                return RIGHT;
            }
            // If these aren't the case, check the remaining two
            if (currUp) {
                if (currDown) {
                    prevDirection = NONE;
                    return NONE;
                }
                else {
                    prevDirection = UP;
                    return UP;
                }
            }
            else {
                prevDirection = DOWN;
                return DOWN;
            }
        case DOWN :
            // If the previous direction is still being pressed, return it
            if (currDown) {
                return DOWN;
            }
            // If not, and the opposite direction is being pressed, return that
            if (currUp) {
                prevDirection = UP;
                return UP;
            }
            // If these aren't the case, check the remaining two
            if (currRight) {
                if (currLeft) {
                    prevDirection = NONE;
                    return NONE;
                }
                else {
                    prevDirection = RIGHT;
                    return RIGHT;
                }
            }
            else {
                prevDirection = LEFT;
                return LEFT;
            }
        default : break; // This line should not be called. This is just to prevent errors in case of bugs
    }
    return 4; // This line should not be called. This is just to prevent errors in case of bugs
}

bool rightPressed() {
    return IsKeyPressed(KEY_RIGHT);
}
bool rightHeld() {
    return IsKeyDown(KEY_RIGHT);
}
bool upPressed() {
    return IsKeyPressed(KEY_UP);
}
bool upHeld() {
    return IsKeyDown(KEY_UP);
}
bool leftPressed() {
    return IsKeyPressed(KEY_LEFT);
}
bool leftHeld() {
    return IsKeyDown(KEY_LEFT);
}
bool downPressed() {
    return IsKeyPressed(KEY_DOWN);
}
bool downHeld() {
    return IsKeyDown(KEY_DOWN);
}
