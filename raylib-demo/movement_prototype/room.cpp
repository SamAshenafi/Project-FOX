#include "raylib.h"

int main()
{
  const int screenWidth = 800;
  const int screenHeight = 600;
  const int gridSize = 50;
  int playerX = 1;
  int playerY = 1;
  int playerFacing = 1; // 0: Up, 1: Right, 2: Down, 3: Left

  // Define a grid where 0 represents walkable cells and 1 represents non-walkable cells
  int grid[screenWidth / gridSize][screenHeight / gridSize] = {
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0}
  };

  bool objectExists = false;
  int objectX = 2;
  int objectY = 2;

  InitWindow(screenWidth, screenHeight, "Grid-Based Movement with Interactive Objects");

  SetTargetFPS(60);

  while (!WindowShouldClose())
  {
    // Input handling
    if (IsKeyDown(KEY_RIGHT) && (playerX < (screenWidth / gridSize) - 1) && grid[playerX + 1][playerY] == 0)
    {
      playerX++;
      playerFacing = 1;
    }
    else if (IsKeyDown(KEY_LEFT) && (playerX > 0) && grid[playerX - 1][playerY] == 0)
    {
      playerX--;
      playerFacing = 3;
    }
    else if (IsKeyDown(KEY_DOWN) && (playerY < (screenHeight / gridSize) - 1) && grid[playerX][playerY + 1] == 0)
    {
      playerY++;
      playerFacing = 2;
    }
    else if (IsKeyDown(KEY_UP) && (playerY > 0) && grid[playerX][playerY - 1] == 0)
    {
      playerY--;
      playerFacing = 0;
    }
    else if (IsKeyPressed(KEY_SPACE))
    {
      // Check if there's an object in front of the player
      if (playerFacing == 0 && objectX == playerX && objectY == playerY - 1)
      {
        // Remove the object
        objectExists = false;
      }
      else if (playerFacing == 1 && objectX == playerX + 1 && objectY == playerY)
      {
        // Remove the object
        objectExists = false;
      }
      else if (playerFacing == 2 && objectX == playerX && objectY == playerY + 1)
      {
        // Remove the object
        objectExists = false;
      }
      else if (playerFacing == 3 && objectX == playerX - 1 && objectY == playerY)
      {
        // Remove the object
        objectExists = false;
      }
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Draw the grid
    for (int x = 0; x < screenWidth; x += gridSize)
    {
      for (int y = 0; y < screenHeight; y += gridSize)
      {
        if (grid[x / gridSize][y / gridSize] == 1)
        {
          DrawRectangle(x, y, gridSize, gridSize, DARKGRAY);
        }
        else
        {
          DrawRectangleLines(x, y, gridSize, gridSize, DARKGRAY);
        }
      }
    }

    // Draw the interactive object (pot or chest)
    if (objectExists)
    {
      DrawRectangle(objectX * gridSize, objectY * gridSize, gridSize, gridSize, BLUE);
    }

    // Draw the player character
    DrawRectangle(playerX * gridSize, playerY * gridSize, gridSize, gridSize, RED);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}

