#include "MainMenu.h"
#include <cstdio>
#include <raylib.h>

MainMenu::MainMenu()
{
  start_img = LoadTexture("assets/MainMenuBackground.png");
  font = LoadFontEx("assets/font.ttf", 80, 0, 0);  
  titlefont = LoadFontEx("assets/TitleFont.ttf", 130, 0, 0);  
  treeTexture = LoadTexture("assets/trees.png");
  foxTexture = LoadTexture("assets/fox(Title).png");

  bounceHeight = 10.0f;
  bounceSpeed = 5.0f;
  bounceTime = 0.0f;
  frameWidth = treeTexture.width / 2;
  frameHeight = treeTexture.height;
  frameRec = {0.0f, 0.0f, static_cast<float>(frameWidth), static_cast<float>(frameHeight)};
  treePosition = {-20 * 0.6, 230 * 0.6};
  treePosition2 = {1100 * 0.6, 300 * 0.6};
  scaleFactor = 8.0f;
  int totalFoxFrames = 6; 
  foxFrameWidth = foxTexture.width / totalFoxFrames;
  foxFrameHeight = foxTexture.height;
  foxFrameRec = {0.0f, 0.0f, static_cast<float>(foxFrameWidth), static_cast<float>(foxFrameHeight)};
  foxPosition = {static_cast<float>(-foxFrameWidth), static_cast<float>(screenHeight) / 2.0f - 100};
  foxSpeed = 80.0f;
  foxReachedCenter = false;
  exitButton = {static_cast<float>(screenWidth - 120), 20.0f, 100.0f, 40.0f};
  exitButtonText = "Exit";
  // Initializing texts for render
  projectText = "PROJECT:";
  foxText = "FOX";
  startText = "PRESS SPACE TO BEGIN!";
  // For animation
  framesCounter = 0;
  menuStartTime = GetTime();
  foxReachedCenter = false;
  titlePosY = -50; 
}

MainMenu::~MainMenu()
{
  UnloadTexture(start_img);
  UnloadFont(font);
  UnloadFont(titlefont);
  UnloadTexture(treeTexture);
  UnloadTexture(foxTexture);
}

void MainMenu::render(Game &game)
{
  BeginDrawing();

  if (game.gameOver) renderGameOver(game);
  else renderMain(game);

  EndDrawing();
}

void MainMenu::renderMain(Game& game) {
  // Background image
  Rectangle sourceRec = {0.0f, 0.0f, static_cast<float>(start_img.width), static_cast<float>(start_img.height)};
  Rectangle destRecBG = {0.0f, 0.0f, static_cast<float>(screenWidth), static_cast<float>(screenHeight)};
  Vector2 origin = {0.0f, 0.0f};
  DrawTexturePro(start_img, sourceRec, destRecBG, origin, 0.0f, WHITE);

  // Trees
  destRec = {treePosition.x, treePosition.y, frameWidth * scaleFactor, frameHeight * scaleFactor};
  destRec2 = {treePosition2.x, treePosition2.y, frameWidth * scaleFactor, frameHeight * scaleFactor};
  DrawTexturePro(treeTexture, frameRec, destRec, (Vector2){0, 0}, 0.0f, WHITE);
  DrawTexturePro(treeTexture, frameRec, destRec2, (Vector2){0, 0}, 0.0f, WHITE);

  // Fox
  DrawTexturePro(foxTexture, foxFrameRec, (Rectangle){foxPosition.x, foxPosition.y, foxFrameWidth, foxFrameHeight}, (Vector2){0, 0}, 0.0f, WHITE);

  // Text elements
  // Title text
  Vector2 projectTextSize = MeasureTextEx(titlefont, projectText.c_str(), titlefont.baseSize, 0);
  Vector2 foxTextSize = MeasureTextEx(titlefont, foxText.c_str(), titlefont.baseSize, 0);
  float titlePosX = (screenWidth - (projectTextSize.x + foxTextSize.x + 10)) / 2;  
  DrawTextEx(titlefont, projectText.c_str(), {titlePosX, titlePosY}, titlefont.baseSize, 0, WHITE);
  DrawTextEx(titlefont, foxText.c_str(), {titlePosX + projectTextSize.x + 10, titlePosY}, titlefont.baseSize, 0, ORANGE);

  // Start text
  Vector2 startTextSize = MeasureTextEx(font, startText.c_str(), font.baseSize, 0);
  float startTextPosX = (screenWidth - startTextSize.x) / 2;
  float startTextPosY = screenHeight / 2 + 180; 
  if (foxReachedCenter && (framesCounter / 30) % 2)
  { // Blinking effect
    DrawTextEx(font, startText.c_str(), {startTextPosX, startTextPosY}, font.baseSize, 0, WHITE);
  }

  // "Press Space to Start Your Adventure" Text
  if (foxReachedCenter && (framesCounter / 30) % 2)
  { // Blinking effect
    DrawTextEx(font, startText.c_str(), {startTextPosX, startTextPosY}, font.baseSize, 0, WHITE);
  }

  // Exit button
  DrawRectangleRec(exitButton, GRAY);
  Vector2 buttonTextSize = MeasureTextEx(font, exitButtonText, font.baseSize, 1);
  Vector2 buttonTextPosition = {exitButton.x + (exitButton.width - buttonTextSize.x) / 2, exitButton.y + (exitButton.height - buttonTextSize.y) / 2};
  DrawTextEx(font, exitButtonText, buttonTextPosition, font.baseSize, 1, WHITE);
}

void MainMenu::renderGameOver(Game& game) {
  ClearBackground(DARKGRAY);
  if(game.gameOver) {
    DrawText(
      "GAME OVER!\n Press Space to return to main menu\n Or Press Shift+Enter to load your last save.",
      game.settings.screenWidth / 2 - 50,
      game.settings.screenHeight / 2, 20,
      RAYWHITE
      );
  }
}

void MainMenu::processInput(Game& game) {
  if (IsKeyPressed(KEY_SPACE)) {
    if (game.gameOver) {
      game.gameOver = false;
      framesCounter = 0;
      menuStartTime = GetTime();
    }
    else {
      game.startNewGame();
    }
  }
  else if ((IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) && IsKeyPressed(KEY_ENTER)) {
    fprintf(stderr, "%s\n", "loaded from savedata-01.json");
    game.gameOver = false;
    game.startNewGame();
    game.loadSave("savedata-01");
  }
}

void MainMenu::update(Game &game)
{
  ++framesCounter;
  if (game.gameOver) updateGameOver(game);
  else updateMain(game);
}

void MainMenu::updateMain(Game& game) {
  // Tree Animation
  int currentFrame = (framesCounter / 30) % 2; // Adjust the speed if necessary
  frameRec.x = (float)currentFrame * (float)frameWidth;

  // Fox Animation
  if (!foxReachedCenter)
  {
    int frame = (framesCounter / 15) % 3;
    foxFrameRec.x = frame * foxFrameWidth;
    if (foxPosition.x < screenWidth / 2 - foxFrameWidth / 2)
    {
      foxPosition.x += foxSpeed * GetFrameTime();
    }
    else
    {
      foxReachedCenter = true;
    }
  }
  else
  {
    int frame = 3 + ((framesCounter / 15) % 3);
    foxFrameRec.x = frame * foxFrameWidth;
  }

  // Title Bounce Animation
  double elapsedTime = GetTime() - menuStartTime;
  float finalYPosition = screenHeight / 2 - 225; // Final Y-position for the title before bouncing

  if (elapsedTime < 3)
  {
    titlePosY = -100; // Start off-screen
  }
  else if (elapsedTime >= 3 && elapsedTime < 4)
  {
    float animationTime = elapsedTime - 3;
    // Smoothly animate title to its final position
    titlePosY = -80 + (animationTime * (finalYPosition + 80));
    if (titlePosY > finalYPosition)
    {
      titlePosY = finalYPosition;
      bounceTime = 0.0f; // Reset bounce time
    }
  }
  else
  {
    // Start bouncing only after title has reached final position
    bounceTime += GetFrameTime();
    float bounceOffset = sinf(bounceTime * bounceSpeed) * bounceHeight;
    titlePosY = finalYPosition + bounceOffset; // Apply bounce effect
  }
}

void MainMenu::updateGameOver(Game& game) {

}