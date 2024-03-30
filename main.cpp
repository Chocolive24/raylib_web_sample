#include <raylib.h>

#ifdef PLATFORM_WEB
#include <emscripten/emscripten.h>
#else
#endif

#include <iostream>

void UpdateDrawFrame(void); // Update and Draw one frame

static constexpr int screenWidth = 800;
static constexpr int screenHeight = 650;

static Texture2D penguin;
static Vector2 position;

int main() {
  InitWindow(screenWidth, screenHeight, "Raylib sample");

  penguin = LoadTexture("data/Penguin.png");
  position = {screenWidth * 0.5f - penguin.width,
                      screenHeight * 0.5f - penguin.height};

  InitAudioDevice();

  // Load explosion sound
  Sound music = LoadSound("data/music.wav");

  PlaySound(music);

#ifdef PLATFORM_WEB
  emscripten_set_main_loop(UpdateDrawFrame, 0, 1);

#else
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    UpdateDrawFrame();
  }

#endif

  UnloadTexture(penguin);
  UnloadSound(music);  // Unload sound

  CloseAudioDevice();
  CloseWindow();

  return EXIT_SUCCESS;
}

void UpdateDrawFrame(void) {
  BeginDrawing();
  {
    ClearBackground(BLACK);

    DrawTextureEx(penguin, position, 0.f, 4.f, WHITE);

    DrawText("Raylib sample !!!", 290, 240, 30, WHITE);
  }
  EndDrawing();
}