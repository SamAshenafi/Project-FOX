// Game.cpp
#include "Game.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include "StringParser.h"
#include "nlohmann/json.hpp"
#include <raylib.h>

Game::Game()
{
  gameState = START_MENU; // Set the initial state to "start"
  double appStartTime = 0;

  // Initialize grid (adjust size accordingly)
  for (int x = 0; x < screenWidth / gridSize; x++)
  {
    for (int y = 0; y < screenHeight / gridSize; y++)
    {
      // grid[x][y] = (x == 2 && y == 3) ? 1 : 0; // Set an obstacle
      grid[x][y] = 0; // Set all to 0 (walkable)
    }
  }
  // spawnTiles();

  loadSaveJson("savegame");

  // Test out the StringParser class
  // std::string input1 = "1-hp_pot";
  // int intValue;
  // std::string stringValue;
  //
  // StringParser::ParseString(input1, intValue, stringValue);
  //
  // std::cout << "Parsed: int=" << intValue << ", str=" << stringValue << std::endl;
  //
  // std::string input2 = "05-06";
  // int firstInt, secondInt;
  //
  // StringParser::ParseCoordinate(input2, firstInt, secondInt);
  // std::cout << "Parsed ID: int1=" << firstInt << ", int2=" << secondInt << std::endl;
}

void Game::loadSaveJson(const std::string &filename)
{
  const std::string saveFilePath = "./save/";
  const std::string jsonFileType = ".json";
  const std::string fullFilePath = saveFilePath + filename + jsonFileType;
  nlohmann::json root;

  // Read the JSON data from the file
  std::ifstream inputFile(fullFilePath);

  if (inputFile.is_open())
  {
    // Parse the JSON data
    try
    {
      inputFile >> root;

      // Deserialize the JSON data into member variables
      // gameState = static_cast<GameState>(root.value("gameState", START_MENU));
      currentRoomId = root.value("currentRoomId", "");
      std::cout << "currentRoomId parsed from JSON is: " << currentRoomId << std::endl;

      completed.clear();
      for (const auto &item : root["completed"])
      {
        completed.push_back(item.get<std::string>());
      }

      // You can add more deserialization logic for other members here
      inputFile.close();
    }
    catch (const std::exception &e)
    {
      fprintf(stderr, "JSON parsing failed: %s\n", e.what());
      inputFile.close();
      // return false; // Loading failed
    }
  }
  else
  {
    fprintf(stderr, "Unable to open file for reading\n");
  }
}

void Game::saveToJson(const std::string &filename)
{
  const std::string saveFilePath = "./save/";
  const std::string jsonFileType = ".json";
  const std::string fullFilePath = saveFilePath + filename + jsonFileType;
  nlohmann::json root;

  // Serialize member data to JSON
  // root["gameState"] = gameState;
  root["currentRoomId"] = currentRoomId;
  root["completed"] = nlohmann::json::array();

  for (const std::string &item : completed)
  {
    root["completed"].push_back(item);
  }

  // Create a JSON writer
  std::ofstream outputFile(fullFilePath);

  if (outputFile.is_open())
  {
    // Write JSON to the output file
    outputFile << root.dump(4); // Pretty print with 4 spaces
    outputFile.close();
  }
  else
  {
    fprintf(stderr, "Unable to open the file for writing\n");
  }
}

void Game::loadRoom(std::string roomId)
{
  const std::string saveFilePath = "./src/json/room/";
  const std::string jsonFileType = ".json";
  const std::string fullFilePath = saveFilePath + roomId + jsonFileType;
  nlohmann::json root;
  std::ifstream jsonFile(fullFilePath);

  if (jsonFile.is_open())
  {
    try
    {
      jsonFile >> root;
      // Parse transition tiles
      for (const auto &transitionData : root["transitionTiles"])
      {
        int tileX = transitionData["x"];
        int tileY = transitionData["y"];
        std::string destinationRoomId = transitionData["destinationRoomId"];
        TransitionTile transitionTile(tileX, tileY, destinationRoomId);
        transitionTiles.push_back(transitionTile);
      }
    }
    catch (const std::exception &e)
    {
      fprintf(stderr, "JSON parsing failed: %s\n", e.what());
    }
  }
}

void Game::handleUserInput()
{
  double currentTime = GetTime();
  double deltaTimeSinceLastMove = currentTime - lastMoveTime;
  if (deltaTimeSinceLastMove < moveSpeed)
  {
    // fprintf(stderr,"too soon\n");
    return; // Too soon for another move
  }

  int keyPressed = GetKeyPressed();
  switch (keyPressed)
  {
  // Detect when movement key is pushed to smooth out the movement
  case KEY_LEFT:
    player->move(player->x - 1, player->y);
    player->facing = Direction::LEFT;
    break;
  case KEY_DOWN:
    player->move(player->x, player->y + 1);
    player->facing = Direction::DOWN;
    break;
  case KEY_UP:
    player->move(player->x, player->y - 1);
    player->facing = Direction::UP;
    break;
  case KEY_RIGHT:
    player->move(player->x + 1, player->y);
    player->facing = Direction::RIGHT;
    break;
  case KEY_S:
    fprintf(stderr, "%s\n", "saved to savegame.json");
    saveToJson("savegame");
    break;
  case KEY_SPACE:
    fprintf(stderr, "%s\n", "space was pressed");
    int targetX = player->x;
    int targetY = player->y;

    switch (player->facing)
    {
    case Direction::UP:
      targetY--;
      break;
    case Direction::DOWN:
      targetY++;
      break;
    case Direction::LEFT:
      targetX--;
      break;
    case Direction::RIGHT:
      targetX++;
      break;
    }
    // Check if the target position is within bounds and if there's an interactable tile at the target position
    for (Tile tile : interactableTiles)
    {
      if (tile.x == targetX && tile.y == targetY)
      {
        tile.interact(); // Call the interact method of the tile
        break;           // Exit the loop once an interactable tile is found
      }
    }
    break;
  }

  // player->updateAnimation();

  int newX = player->x;
  int newY = player->y;

  if (IsKeyDown(KEY_RIGHT))
  {
    player->facing = Direction::RIGHT;
    newX++;
  }
  else if (IsKeyDown(KEY_LEFT))
  {
    player->facing = Direction::LEFT;
    newX--;
  }
  else if (IsKeyDown(KEY_DOWN))
  {
    player->facing = Direction::DOWN;
    newY++;
  }
  else if (IsKeyDown(KEY_UP))
  {
    player->facing = Direction::UP;
    newY--;
  }

  // no movement
  if (newX == player->x && newY == player->y)
    return;

  // Check if the new position is out of bounds
  if (
      newX < 0 ||
      newX >= (screenWidth / gridSize) ||
      newY < 0 ||
      newY >= (gameHeight / gridSize))
  {
    fprintf(stderr, "out of bound: %d, %d\n", newX, newY);
    // Check if there's a transition tile in the direction the player is moving
    // for (const TransitionTile& tile : transitionTiles) {
    //   if ((tile.x == newX && tile.y == newY) && tile.destinationRoomId != "") {
    //     // Load the destination room based on the transition tile's destinationRoomId
    //     loadRoom(tile.destinationRoomId);
    //     break;
    //   }
    // }
    return; // Player moved to a new room, no need to continue with the current input
  }
  else
  {
    player->move(newX, newY);
    lastMoveTime = currentTime;
    // fprintf(stderr, "lastMoveTime is %f\n", lastMoveTime);
  }
}

bool Game::isValidMove(int newX, int newY)
{
  return (newX >= 0 && newX < (screenWidth / gridSize) && newY >= 0 && newY < (screenHeight / gridSize) && grid[newX][newY] == 0);
}

void Game::spawnTiles()
{
  // TODO: Spawn your tiles here
  // ChestTile* chestTile = new ChestTile("chest_1", 3, 3);
  // interactableTiles.push_back(chestTile);
}










void Game::run()
{
  int framesCounter = 0;

InitWindow(screenWidth, screenHeight, "Project:Fox");
appStartTime = GetTime();

player = std::make_unique<Character>(1, 1);

SetTargetFPS(60);

Texture2D start_img = LoadTexture("assets/MainMenuBackground.png");

Font font = LoadFontEx("assets/font.ttf", 55, 0, 0);
Font titlefont = LoadFontEx("assets/TitleFont.ttf", 110, 0, 0);
float bounceHeight = 10.0f; // The maximum height of the bounce
float bounceSpeed = 5.0f;   // How fast the title bounces
float bounceTime = 0.0f;    // A timer to control the bounce effect

Texture2D treeTexture = LoadTexture("assets/trees.png");
int frameWidth = treeTexture.width / 2; // 2 for the number of frames
int frameHeight = treeTexture.height; // The height is the same for each frame
Rectangle frameRec = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight };
Vector2 treePosition = { -20, 470 }; // Change to where you want the tree to be drawn
Vector2 treePosition2 = { 1300, 470};
float scaleFactor = 8.0f; //Sizing of Image

Texture2D foxTexture = LoadTexture("assets/fox(Title).png");
const int foxFrames = 6; // Total number of frames in the fox animation
const int foxFrameWidth = foxTexture.width / foxFrames;
const int foxFrameHeight = foxTexture.height;
Rectangle foxFrameRec = { 0.0f, 0.0f, (float)foxFrameWidth, (float)foxFrameHeight };
Vector2 foxPosition = { static_cast<float>(-foxFrameWidth), screenHeight / 2.0f }; // Starting off-screen to the left
const float foxSpeed = 80.0f; // Adjust as necessary for speed
bool foxReachedCenter = false;

//Exit Button
Rectangle exitButton = { static_cast<float>(screenWidth - 120), 20.0f, 100.0f, 40.0f }; // x, y, width, height
const char* exitButtonText = "Exit";



while (!WindowShouldClose())
{
    if (gameState == START_MENU)
    {
        framesCounter++;
        

        int imgWidth = start_img.width;
        int imgHeight = start_img.height;
        int imgPosX = (screenWidth - imgWidth) / 2;
        int imgPosY = (screenHeight - imgHeight) / 2;

        const char* text = "PRESS SPACE TO START YOUR ADVENTURE!";
        Vector2 textSize = MeasureTextEx(font, text, font.baseSize * 2, 0);
        float textPosX = (screenWidth - textSize.x) / 2;
        float textPosY = screenHeight / 2 + 350; 

        const char* projectText = "PROJECT:";
        Vector2 projectSize = MeasureTextEx(titlefont, projectText, titlefont.baseSize * 4, 0);
        
        const char* foxText = "FOX";
        Vector2 foxSize = MeasureTextEx(titlefont, foxText, titlefont.baseSize * 4, 0);
        

        float entireTitleWidth = projectSize.x + foxSize.x; 
        float titlePosX = (screenWidth - entireTitleWidth) / 2;
        float foxPosX = titlePosX + projectSize.x;

        double elapsedTime = GetTime() - appStartTime;
        float titlePosY;
if (elapsedTime < 3)
{
    titlePosY = -190; // Before 3 seconds, the title is off-screen
}
else if (elapsedTime >= 3 && elapsedTime < 4)
{
    // Between 3 and 4 seconds, we animate the title to its position
    float animationTime = elapsedTime - 3;
    titlePosY = animationTime * (screenHeight / 2 - 400); 
    if (titlePosY > screenHeight / 2 - 400)
    {
        titlePosY = screenHeight / 2 - 400;
        bounceTime = 0.0f; 
    }
}
else
{
    // After 4 seconds, the title bounces around its position
    titlePosY = screenHeight / 2 - 400;

    bounceTime += GetFrameTime();
    float bounceOffset = sinf(bounceTime * bounceSpeed) * bounceHeight;
    titlePosY += bounceOffset;
}
        //Tree animation
        int currentFrame = (framesCounter / 30) % 2; // Adjust the speed if necessary
        frameRec.x = (float)currentFrame * (float)frameWidth;
        

        // Create a destination rectangle for drawing the scaled tree
        Rectangle destRec = {
            treePosition.x,
            treePosition.y,
            frameWidth * scaleFactor, // Scale the frame width
            frameHeight * scaleFactor // Scale the frame height
        };
        Rectangle destRec2 = {
    treePosition2.x,
    treePosition2.y,
    frameWidth * scaleFactor, // Scale the frame width
    frameHeight * scaleFactor // Scale the frame height
};
      if (!foxReachedCenter)
        {
            // Repeat first three frames until the fox reaches the screen center
            int frame = (framesCounter / 15) % 3; 
            foxFrameRec.x = frame * foxFrameWidth;
        }
        else
        {
            // Play frames 4, 5, 6 once when the fox reaches the center
            int frame = 3 + ((framesCounter / 15) % 3);
            foxFrameRec.x = frame * foxFrameWidth;
        }

        // Move fox to the center
        if (foxPosition.x < screenWidth / 2 - foxFrameWidth / 2)
        {
            foxPosition.x += foxSpeed * GetFrameTime();
        }
        else
        {
            foxReachedCenter = true;
        }


        BeginDrawing();

ClearBackground(RAYWHITE);
DrawTexture(start_img, imgPosX, imgPosY, WHITE);

// Trees
DrawTexturePro(treeTexture, frameRec, destRec, (Vector2){ 0, 0 }, 0.0f, WHITE);
DrawTexturePro(treeTexture, frameRec, destRec2, (Vector2){ 0, 0 }, 0.0f, WHITE);

//Fox
DrawTexturePro(foxTexture, foxFrameRec, (Rectangle){ foxPosition.x, foxPosition.y, foxFrameWidth, foxFrameHeight }, (Vector2){ 0, 0 }, 0.0f, WHITE);

// Title
std::string fullTitle = std::string(projectText) + foxText;
Vector2 fullTitleSize = MeasureTextEx(titlefont, fullTitle.c_str(), titlefont.baseSize * 2, 0);
Vector2 fullTitlePosition = { (screenWidth - fullTitleSize.x) / 2, titlePosY };
DrawTextEx(titlefont, fullTitle.c_str(), fullTitlePosition, titlefont.baseSize * 2, 0, WHITE);
Vector2 projectPartSize = MeasureTextEx(titlefont, projectText, titlefont.baseSize * 2, 0);
Vector2 foxPartPosition = { fullTitlePosition.x + projectPartSize.x, titlePosY };

//Fox
DrawTextEx(titlefont, foxText, foxPartPosition, titlefont.baseSize * 2, 0, ORANGE);

if (foxReachedCenter && (framesCounter / 30) % 2) // blinking effect
{
    DrawTextEx(font, text, (Vector2){textPosX, textPosY}, font.baseSize * 2, 0, WHITE);
}
// Draw the exit button
DrawRectangleRec(exitButton, GRAY); // Draw the button rectangle
Vector2 buttonTextSize = MeasureTextEx(font, exitButtonText, font.baseSize, 1);
Vector2 buttonTextPosition = {
    exitButton.x + (exitButton.width - buttonTextSize.x) / 2,
    exitButton.y + (exitButton.height - buttonTextSize.y) / 2
};
DrawTextEx(font, exitButtonText, buttonTextPosition, font.baseSize, 1, WHITE);

// Check for button clicks
if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    Vector2 mousePosition = GetMousePosition();
    if (CheckCollisionPointRec(mousePosition, exitButton)) {
        // Exit the application
        CloseWindow(); // This will break the loop and can close the window
        return; // If needed, to exit the function or you can use `exit(0);` to terminate the program
    }
}
EndDrawing();

        if (IsKeyPressed(KEY_SPACE))
        {
            gameState = IN_GAME;
            framesCounter = 0;
        }
    }

    else if (gameState == IN_GAME)
    {
      handleUserInput();

      BeginDrawing();
      // ClearBackground(RAYWHITE);
      ClearBackground(DARKGRAY);

      // Draw the grid
      for (int x = 0; x < screenWidth; x += gridSize)
      {
        for (int y = 0; y < gameHeight; y += gridSize)
        {
          if (grid[x / gridSize][y / gridSize] == 1)
          {
            DrawRectangle(x, y, gridSize, gridSize, DARKGRAY);
          }
          else
          {
            // DrawRectangleLines(x, y, gridSize, gridSize, DARKGRAY);
            DrawRectangleLines(x, y, gridSize, gridSize, BLACK);
          }
        }
      }

      // TODO: implement draw for tiles object
      for (Tile tile : interactableTiles)
      {
        tile.draw(gridSize);
      }

      // Draw the player character
      player->draw(gridSize);
      EndDrawing();
    }
  }

  // for (Tile tile : interactableTiles) {
  // delete tile;
  // }

  UnloadTexture(player->texture);
  UnloadFont(font);
  UnloadTexture(treeTexture);
  UnloadTexture(foxTexture);

  CloseWindow();
  framesCounter = 0;
}
