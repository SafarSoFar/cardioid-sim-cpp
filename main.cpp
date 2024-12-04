#include "raylib.h"
#include <iostream>
#include "raymath.h"
#include <random>


std::random_device rd;
std::default_random_engine eng(rd());

#define SCREEN_WIDTH 1920/1.2
#define SCREEN_HEIGHT 1080/1.2

Vector2 operator+(Vector2 lhs, Vector2 rhs){
  return Vector2{lhs.x+rhs.x, lhs.y+rhs.y};
}

Vector2 operator-(Vector2 lhs, Vector2 rhs){
  return Vector2{lhs.x-rhs.x, lhs.y-rhs.y};
}

Vector2 operator*(Vector2 lhs, float rhs){
  return Vector2{lhs.x*rhs, lhs.y * rhs};
}

Vector2 operator/(Vector2 lhs, float rhs){
  return Vector2{lhs.x/rhs, lhs.y/rhs};
}

Vector2 matMul(Vector2 vec2D, std::vector<std::vector<float>> mat){
  /*if(mat[0].size() != 3 || mat.size() != 3){*/
  /*  return Vector3Zero();*/
  /*}*/
  float x = (vec2D.x*mat[0][0])+(vec2D.y*mat[0][1]);
  float y = (vec2D.x*mat[1][0])+(vec2D.y*mat[1][1]);
  Vector2 vec = Vector2{x,y};
  return vec;
};

Vector2 zAxisRotation(Vector2 vec2, float angle){
  float radians = angle*DEG2RAD;
  float cosine = cos(radians);
  float sine = sin(radians);
  std::vector<std::vector<float>> rotZMat ={
    {cosine,-sine,0},
    {sine,cosine,0}
  };
  Vector2 rotatedVec = matMul(vec2, rotZMat);
  return rotatedVec;
};


int main(void)
{

  int divisions = 200;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Cardioid");

    SetTargetFPS(60);
    ClearBackground(BLACK);


    float radius = 400;
    Vector2 vals[divisions];
    for(int i = 0; i < divisions; i++){
      Vector2 vec = Vector2{radius,0};
      vec = zAxisRotation(vec, (360.0/divisions)*i);
      vals[i] = vec;
    }

    Vector2 centerVec = Vector2{SCREEN_WIDTH/2.0, SCREEN_HEIGHT/2.0};

    Vector2 curPos = centerVec+vals[0];
    int curIndex = 0;
    double multiplier = 1.0;
    std::pair<Vector2,Vector2>lines[divisions];

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();

        DrawCircleLines(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 400, WHITE);

        int connectionIndex = (int(curIndex*multiplier))%divisions;
        Vector2 nextPos = centerVec+vals[connectionIndex];
        lines[curIndex%divisions] = {centerVec+vals[curIndex%divisions], nextPos};

        for(int i = 0; i < divisions; i++){
          DrawLineV(lines[i].first,lines[i].second, WHITE);
        }

        multiplier += 0.1;
        curIndex++;
        ClearBackground(BLACK);

        
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
