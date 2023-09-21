#include "raylib.h"

// So, here, we declare variables in C not in C++ !!!!
// 

class Square {
    public : 
        // variables for the dimensions of the square
        int height = 100;
        int width = 100;
        // variables for the coordinates of the top-left of the square
        int x = 350;
        int y = 175;
        // variables for the color of the square and for tracking its changes
            // Color is a struct in raylib
        // I used a bool to track whether it is RED because Colors cannot use "==".
        // There's obviously a more elegant solution that would allow us to use more colors, but I just wanted this to work.
        Color color = RED;
        bool isRed = true;

        // Declare all functions. If our functions had parameters, they would go here too.
        void draw();
        void changeColorOnSpace();
};