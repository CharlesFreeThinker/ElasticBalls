#include "raylib.h"
#include "raymath.h"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000
#define FPS 60
#define RADIUS 25.f
#define MAX_BALLS 20

int main(void)
{
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "BALLS");

  Vector2 Pos[MAX_BALLS];
  Vector2 Vel[MAX_BALLS];
  Color Colour[MAX_BALLS];

  for (int i = 0; i < MAX_BALLS; i++)
  {
    Pos[i].x = GetRandomValue(RADIUS, SCREEN_WIDTH - RADIUS);
    Pos[i].y = GetRandomValue(RADIUS, SCREEN_HEIGHT - RADIUS);

    Vel[i].x = GetRandomValue(-5, 5);
    Vel[i].y = GetRandomValue(-5, 5);
  
    Colour[i].r = GetRandomValue(0,255);
    Colour[i].g = GetRandomValue(0,255);
    Colour[i].b = GetRandomValue(0,255);
    Colour[i].a = 255;
  }
  
  SetTargetFPS(FPS);
  while(!WindowShouldClose())
  {
    for (int i = 0; i < MAX_BALLS; i++)
    {
      Pos[i] = Vector2Add(Pos[i], Vel[i]);
        
      //Border Collision
      if(Pos[i].x < RADIUS)
      {
        Pos[i].x = RADIUS;
        Vel[i].x *= -1;
      }
      else if(Pos[i].x > SCREEN_WIDTH - RADIUS)
      {
        Pos[i].x = SCREEN_WIDTH - RADIUS;
        Vel[i].x *= -1;
      }
      if(Pos[i].y < RADIUS)
      {
        Pos[i].y = RADIUS;
        Vel[i].y *= -1;
      }
      else if(Pos[i].y > SCREEN_HEIGHT - RADIUS)
      {
        Pos[i].y = SCREEN_HEIGHT - RADIUS;
        Vel[i].y *= -1;
      }

      for(int j = i + 1; j < MAX_BALLS; j++)
      {
        //its quite unrealistic if a ball is inside another ball...
        if(Vector2Distance(Pos[i], Pos[j]) < 2.f * RADIUS)
        {
          //Seperation
          Vector2 normalized = Vector2Normalize(Vector2Subtract(Pos[i], Pos[j]));
          float displacement = (2.f * RADIUS - Vector2Distance(Pos[i], Pos[j])) / 2.f;
          Vector2 displacementVector = Vector2Scale(normalized, displacement);

          Pos[i] = Vector2Add(Pos[i], displacementVector);
          Pos[j] = Vector2Subtract(Pos[j], displacementVector);

          //Stupid freaking wikipedia math
          //v1'
          Vector2 PosDiffVectI = Vector2Subtract(Pos[i], Pos[j]);
          Vector2 VelDiffVectI = Vector2Subtract(Vel[i], Vel[j]);
          float UpperDotProductI = Vector2DotProduct(VelDiffVectI, PosDiffVectI);
          float magnitudeSqrI = Vector2DistanceSqr(Pos[i], Pos[j]);
          float fractionI = UpperDotProductI / magnitudeSqrI;

          //v2'
          Vector2 PosDiffVectJ = Vector2Subtract(Pos[j], Pos[i]);
          Vector2 VelDiffVectJ = Vector2Subtract(Vel[j], Vel[i]);
          float UpperDotProductJ = Vector2DotProduct(VelDiffVectJ, PosDiffVectJ);
          float magnitudeSqrJ = Vector2DistanceSqr(Pos[j], Pos[i]);
          float fractionJ = UpperDotProductJ / magnitudeSqrJ;

          Vel[i] = Vector2Subtract(Vel[i], Vector2Scale(PosDiffVectI, fractionI));
          Vel[j] = Vector2Subtract(Vel[j], Vector2Scale(PosDiffVectJ, fractionJ));


        }
      }

    }

    BeginDrawing();
    for (int i = 0; i < MAX_BALLS; i++)
    {
      ClearBackground(BLACK);
      DrawCircleV(Pos[i], RADIUS, Colour[i]);
    }
    EndDrawing();
  }


  CloseWindow();
  return 0;
}
