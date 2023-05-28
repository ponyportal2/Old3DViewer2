
#include <string.h>
#include <time.h>

#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <vector>

// #include "extras/gui_textbox_extended.h"
#include "raygui.h"
#include "style_dark.h"

#define LINESIZE 16384

typedef struct dot_t {
  float x;
  float y;
  float z;
} dot;

typedef struct vector_t {
  int x;
  int y;
  int z;
} huector;

typedef struct line_t {
  dot a;
  dot b;
} line;

typedef struct vec_line_t {
  Vector3 a;
  Vector3 b;
} vec_line;

void myMain();

int main() {
  FILE* obj_file = fopen("lines.txt", "rb");

  int rows_lines = 4000000;

  std::vector<vec_line> lines;
  lines.reserve(rows_lines);

  char current_line[LINESIZE] = {0};

  while (fgets(current_line, LINESIZE, obj_file)) {
    vec_line temp_line = {{0, 0, 0}, {0, 0, 0}};
    sscanf(current_line, "%f %f %f %f %f %f", &temp_line.a.x, &temp_line.a.y,
           &temp_line.a.z, &temp_line.b.x, &temp_line.b.y, &temp_line.b.z);
    temp_line.a.x *= 9;
    temp_line.a.x += 1;

    temp_line.a.y *= 9;
    temp_line.a.y += 1;

    temp_line.a.z *= 9;
    temp_line.a.z += 1;

    temp_line.b.x *= 9;
    temp_line.b.x += 1;

    temp_line.b.y *= 9;
    temp_line.b.y += 1;

    temp_line.b.z *= 9;
    temp_line.b.z += 1;
    lines.push_back(temp_line);
  }

  const int screenWidth = 1080;
  const int screenHeight = 610;
  InitWindow(screenWidth, screenHeight, "SmartCalc");
  Camera camera = {0};
  camera.position = (Vector3){0.0f, 10.0f, 10.0f};
  camera.target = (Vector3){0.0f, 0.0f, 0.0f};
  camera.up = (Vector3){0.0f, 1.0f, 0.0f};
  camera.fovy = 45.0f;
  //   camera.type = CAMERA_PERSPECTIVE;

  SetCameraMode(camera, CAMERA_FREE);
  SetExitKey(0);
  bool exitWindow = false;
  bool showMessageBox = false;
  // ---------
  // My logic:
  // ---------
  SetTargetFPS(60);
  GuiLoadStyleDark();
  GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
  InitAudioDevice();
  //----------------------------- My logic end
  //  MAIN PROGRAM LOOP:
  //-----------------------------
  float mult = 1.0;
  float plus = 0;
  int aboba = 33;
  while (!exitWindow) {  // Will detect window close button or ESC
    Color backgroundColorValue =
        CLITERAL(Color){aboba * 1.4234, aboba * 0.4324, 33, 33};
    exitWindow = WindowShouldClose();
    // UpdateCamera(&camera);
    if (IsKeyPressed(KEY_ESCAPE)) showMessageBox = !showMessageBox;
    UpdateCamera(&camera);
    BeginDrawing();
    ClearBackground(backgroundColorValue);
    BeginMode3D(camera);
    DrawGrid(10, 1.0f);  // ??
    for (size_t i = 0; i < lines.size(); i++) {
      vec_line ma_line = lines[i];
      //   ma_line.a.x *= mult;
      //   ma_line.a.x += plus;

      //   ma_line.a.y *= mult;
      //   ma_line.a.y += plus;

      //   ma_line.a.z *= mult;
      //   ma_line.a.z += plus;

      //   ma_line.b.x *= mult;
      //   ma_line.b.x += plus;

      //   ma_line.b.y *= mult;
      //   ma_line.b.y += plus;

      //   ma_line.b.z *= mult;
      //   ma_line.b.z += plus;
      DrawLine3D(ma_line.a, ma_line.b, RED);
      DrawCubeV(ma_line.a, {aboba % 35, aboba % 35, aboba % 35}, GREEN);
      //   DrawCubeV(ma_line.b, {3, 3, 3}, BLUE);
    }
    mult *= 1.001;
    plus += 1.0;
    aboba += 1;

    // SetCameraPerspective(
    //     camera, 60.0f, (float)screenWidth / (float)screenHeight, 0.01f,
    //     100.0f);
    // Exit logic:
    // -----------
    if (showMessageBox) {
      DrawRectangle(0, 0, screenWidth, screenHeight, Fade(RAYWHITE, 0.8f));
      int result =
          GuiMessageBox((Rectangle){(float)screenWidth / 2 - 125,
                                    (float)screenHeight / 2 - 50, 250, 100},
                        GuiIconText(ICON_EXIT, "Close Window"),
                        "Do you really want to exit?", "Yes;No");
      if ((result == 0) || (result == 2))
        showMessageBox = false;
      else if (result == 1)
        exitWindow = true;
    }
    // ----------
    EndMode3D();
    EndDrawing();
  }
  CloseAudioDevice();
  CloseWindow();  // Close window and OpenGL context
  return 0;
}

// void myMain() { DrawLine3D(Vector3 startPos, Vector3 endPos, Color color); }