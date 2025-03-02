#include "raylib.h"
#include <iostream>
#include "raymath.h"
#include <random>

std::random_device rd;
std::default_random_engine eng(rd());

#define SCREEN_WIDTH 1920/1.2
#define SCREEN_HEIGHT 1080/1.2


Vector2 surfacePointRot(float radius,float angle){
  float rad = angle * DEG2RAD;
  return Vector2{radius*cos(rad),radius*sin(rad)};
}

struct Line{
  Vector2 start;
  Vector2 end;
  Color color;
};


int main(void)
{

  int divisions = 200;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Cardioid");

    SetTargetFPS(300);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    ClearBackground(BLACK);

    Vector2 centerVec = Vector2{SCREEN_WIDTH/2.0, SCREEN_HEIGHT/2.0};

    int curIndex = 0;
    double multiplier = 4.0;
    Line lines[divisions];

    Color curColor = {0,0,0,255};
    int hue = 0;

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();

        DrawCircleLines(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 400, WHITE);

        float radius = 400;
        Vector2 vals[divisions];
        for(int i = 0; i < divisions; i++){
          Vector2 vec = surfacePointRot(radius, (360.0/divisions)*i);

          vals[i] = vec;
        }


        Vector2 curPos = centerVec+vals[0];

        int connectionIndex = (int(curIndex*multiplier))%divisions;
        Vector2 nextPos = centerVec+vals[connectionIndex];

        hue++;
        if(hue > 360){
          hue = 0;
        }
        curColor = ColorFromHSV(hue, 1.0, 1.0);

        lines[curIndex%divisions] = {centerVec+vals[curIndex%divisions], nextPos, WHITE};

        for(int i = 0; i < divisions; i++){
          DrawLineEx(lines[i].start,lines[i].end, 1.0,lines[i].color);
        }
        curIndex++;
        multiplier += 0.01;
        ClearBackground(BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
