#include "raylib.h"
#include "raymath.h"

#define SCREEN_WIDTH 300
#define SCREEN_HEIGHT 300
#define FPS 60
#define RADIUS 25.f


int main(void)
{
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "BALLS");

  Vector2 PosA = {100, 200};
  Vector2 PosB = {200, 200};

  Vector2 VelA = {5.f, 4.f};
  Vector2 VelB = {-3.f, -7.f};
  

  SetTargetFPS(FPS);
  while(!WindowShouldClose())
  {
    PosA = Vector2Add(PosA, VelA);
    PosB = Vector2Add(PosB, VelB);

    if(PosA.x >= SCREEN_WIDTH - RADIUS)
    {
      PosA.x = SCREEN_WIDTH - RADIUS;
      VelA.x *= -1;
    }
    else if(PosA.x <= RADIUS)
    {
      PosA.x = RADIUS;
      VelA.x *= -1;
    }
    if(PosB.x >= SCREEN_WIDTH - RADIUS)
    {
      PosB.x = SCREEN_WIDTH - RADIUS;
      VelB.x *= -1;
    }
    else if(PosB.x <= RADIUS)
    {
      PosB.x = RADIUS;
      VelB.x *= -1;
    }
    if(PosA.y >= SCREEN_HEIGHT - RADIUS)
    {
      PosA.y = SCREEN_HEIGHT - RADIUS;
      VelA.y *= -1;
    }
    else if(PosA.y <= RADIUS)
    {
      PosA.y = RADIUS;
      VelA.y *= -1;
    }
    if(PosB.y >= SCREEN_HEIGHT - RADIUS)
    {
      PosB.y = SCREEN_HEIGHT - RADIUS;
      VelB.y *= -1;
    }
    else if(PosB.y <= RADIUS)
    {
      PosB.y = RADIUS;
      VelB.y *= -1;
    }
    
    float Distance = Vector2Distance(PosA, PosB);
    if(Distance < 2.f * RADIUS)
    { 
      /*seperate em*/
      Vector2 normalized = Vector2Normalize(Vector2Subtract(PosA, PosB));
      float displacement = (2.f * RADIUS - Distance) / 2.f;
      Vector2 displacementVector = Vector2Scale(normalized, displacement);

      PosA = Vector2Add(PosA, displacementVector);
      PosB = Vector2Subtract(PosB, displacementVector);
      
      /*v1' */ 
      Vector2 PosDiffVectA = Vector2Subtract(PosA, PosB);
      Vector2 VelDifVectA = Vector2Subtract(VelA, VelB);
      float UpperDotProductA = Vector2DotProduct(VelDiffVectA, PosDiffVectA);
      float magnitudeSqrA = Vector2DistanceSqr(PosA, PosB);
      float fractionA = UpperDotProductA / magnitudeSqrA;
      
      /*v2' */
      Vector2 PosDiffVectB = Vector2Subtract(PosB, PosA);
      Vector2 VelDiffVectB = Vector2Subtract(VelB, VelA);
      float UpperDotProductB = Vector2DotProduct(VelDiffVectB, PosDiffVectB);
      float magnitudeSqrB = Vector2DistanceSqr(PosB, PosA);
      float fractionB = UpperDotProductB / magnitudeSqrB;
      
      VelA = Vector2Subtract(VelA, Vector2Scale(PosDiffVectA, fractionA));
      VelB = Vector2Subtract(VelB, Vector2Scale(PosDiffVectB, fractionB));

    }


    BeginDrawing();
    ClearBackground(BLACK);
    DrawCircleV(PosA, RADIUS, RED);
    DrawCircleV(PosB, RADIUS, BLUE);
    EndDrawing();
  }


  CloseWindow();
  return 0;
}
