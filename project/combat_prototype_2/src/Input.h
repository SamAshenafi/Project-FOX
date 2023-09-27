#include "raylib.h"

// These functions and classes are for handling inputs.
// Currently, the boolean functions are only set up for directional buttons,
// but more bools can be added.

// When testing, change the last line of DirectionalInput::getDirection()
// to "return 5;". This way you can see if something slipped through.

// Class that handles directional input
// Use function getDirection() to receive the current input info
class DirectionalInput {
    private :
        int  direction, prevDirection;
        bool currRight, currUp, currLeft, currDown,
             lastRight, lastUp, lastLeft, lastDown,
             currRightPress, currUpPress, currLeftPress, currDownPress;
        void updateDirection();

    public :
        // Declare this when initializing
        DirectionalInput();
        // Call this whenever you need to get input to move a character or cursor or the like
        int getDirection();
};

// Stand-alone functions for getting keyboard input
// raylib's built-in functions work fine, but these are shorter to call
bool    rightPressed(), rightHeld(),
        upPressed(), upHeld(),
        leftPressed(), leftHeld(),
        downPressed(), downHeld();

// These enums correspond to the meaning of the outputs.
// Set up your code accordingly
// The choice of values for each direction comes from the unit circle.
enum direction {
    RIGHT = 0,
    UP = 1,
    LEFT = 2,
    DOWN = 3,
    NONE = 4,
};