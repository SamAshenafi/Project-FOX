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
  exitButtonTexture = LoadTexture("assets/ExitButton.png");

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
  popupWidth = 300;
  popupHeight = 200;
  // Exit Button
  float buttonScale = 0.2f;
  float buttonWidth = exitButtonTexture.width * buttonScale;
  float buttonHeight = exitButtonTexture.height * buttonScale;
  float marginRight = 3.0f;
  float marginTop = 3.0f;
  exitButton = {screenWidth - buttonWidth - marginRight, marginTop, buttonWidth, buttonHeight};
  yesButton = {(screenWidth - popupWidth) / 2 + 50, (screenHeight - popupHeight) / 2 + 100, 80, 50};
  noButton = {(screenWidth + popupWidth) / 2 - 150, (screenHeight - popupHeight) / 2 + 100, 80, 50};
  // Initializing texts for render
  projectText = "PROJECT:";
  foxText = "FOX";
  startText = "PRESS SPACE TO BEGIN!";
  // For animation
  framesCounter = 0;
  appStartTime = GetTime();
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
  UnloadTexture(exitButtonTexture);
}

void MainMenu::render(Game &game)
{
  BeginDrawing();

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
  sourceRec.x = 0.0f;
  sourceRec.y = 0.0f;
  sourceRec.width = (float)exitButtonTexture.width;
  sourceRec.height = (float)exitButtonTexture.height;

  // Draw the exit button texture
  DrawTexturePro(exitButtonTexture, sourceRec, exitButton, (Vector2){0, 0}, 0.0f, WHITE);
  // confirmation screen
  if (showConfirmationScreen)
  {
    // background
    DrawRectangle((screenWidth - popupWidth) / 2, (screenHeight - popupHeight) / 2, popupWidth, popupHeight, LIGHTGRAY);

    int textWidth = MeasureText(confirmationText.c_str(), 20);
    DrawText(confirmationText.c_str(), (screenWidth - textWidth) / 2, (screenHeight - popupHeight) / 2 + 40, 20, BLACK);

    // Yes button popup
    DrawRectangleRec(yesButton, DARKGRAY);
    DrawText(yesButtonText, yesButton.x + (yesButton.width - MeasureText(yesButtonText, 20)) / 2, yesButton.y + (yesButton.height - 20) / 2, 20, WHITE);

    // No button popup
    DrawRectangleRec(noButton, DARKGRAY);
    DrawText(noButtonText, noButton.x + (noButton.width - MeasureText(noButtonText, 20)) / 2, noButton.y + (noButton.height - 20) / 2, 20, WHITE);
  }

  ClearBackground(DARKGRAY);
  if (game.gameOver)
  {
    DrawText(
        "GAME OVER!\n press Space to return to main menu.",
        game.settings.screenWidth / 2 - 50,
        game.settings.screenHeight / 2, 20,
        RAYWHITE);
  }
  EndDrawing();
}

void MainMenu::processInput(Game &game)
{
  if (IsKeyPressed(KEY_SPACE))
  {
    if (game.gameOver)
      game.gameOver = false;
    else
    {
      game.startNewGame();
    }
  }
  else if (IsKeyPressed(KEY_LEFT_BRACKET))
  {
    fprintf(stderr, "%s\n", "[ was pressed");
    fprintf(stderr, "%s\n", "loaded from savedata-01.json");
    game.gameOver = false;
    game.loadSave("savedata-01");
    game.changeState(game.world);
  }

  if (showConfirmationScreen)
  {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
      Vector2 mousePosition = GetMousePosition();

      // Handle "Yes" button click
      if (CheckCollisionPointRec(mousePosition, yesButton))
      {
        CloseWindow(); // Close the application
      }

      // Handle "No" button click
      if (CheckCollisionPointRec(mousePosition, noButton))
      {
        showConfirmationScreen = false; // Close the popup
      }
    }
  }
  else
  {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
      Vector2 mousePosition = GetMousePosition();
      if (CheckCollisionPointRec(mousePosition, exitButton))
      {
        // If the exit button is clicked
        showConfirmationScreen = true;
      }
    }
  }
}

void MainMenu::update(Game &game)
{
  framesCounter++;

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
  double elapsedTime = GetTime() - appStartTime;
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
