#include "stdlib.h"
#include "stdio.h"
#include "raylib.h"
#include "raymath.h"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000
#define FPS 60
#define RADIUS 25.f
#define MAX_BALLS 50

typedef struct {
        Vector2 Pos;
        Vector2 Vel;
        Color Color;
}Circle;

void borderCollision(Circle *Circles, int i);
void seperateAndBounce(Circle *Circles, int i, int j);

int main(void)
{
        InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "BALLS");
 
        Circle *Circles = malloc(MAX_BALLS * sizeof(Circle));
        if(Circles == NULL)
        {
                printf("Malloc failed.\n");
                return 1;
        }


        for (int i = 0; i < MAX_BALLS; i++)
        {
                Circles[i].Pos.x = GetRandomValue(RADIUS, SCREEN_WIDTH - RADIUS);
                Circles[i].Pos.y = GetRandomValue(RADIUS, SCREEN_HEIGHT - RADIUS);

                Circles[i].Vel.x = GetRandomValue(-5, 5);
                Circles[i].Vel.y = GetRandomValue(-5, 5);
  
                Circles[i].Color.r = GetRandomValue(0,255);
                Circles[i].Color.g = GetRandomValue(0,255);
                Circles[i].Color.b = GetRandomValue(0,255);
                Circles[i].Color.a = 255;
        }
  
        SetTargetFPS(FPS);
        while(!WindowShouldClose())
        {
                for (int i = 0; i < MAX_BALLS; i++)
                {

                        Circles[i].Pos = Vector2Add(Circles[i].Pos, Circles[i].Vel);
                        borderCollision(Circles, i);

                        for(int j = i + 1; j < MAX_BALLS; j++)
                        {
                                if(Vector2Distance(Circles[i].Pos, Circles[j].Pos) <= 2.f * RADIUS)
                                {
                                        seperateAndBounce(Circles, i, j);
                                }
        
                        }
                }
  
                BeginDrawing();
                for (int i = 0; i < MAX_BALLS; i++)
                {
                        const char *fpsText = TextFormat("FPS: %d", GetFPS());
                        DrawText(fpsText, 10, 10, 20, RED);
                        ClearBackground(BLACK);
                        DrawCircleV(Circles[i].Pos, RADIUS, Circles[i].Color);
                }
                EndDrawing();
        }
        CloseWindow();
        free(Circles);
        return 0;
}

void borderCollision(Circle *Circles, int i)
{
        if(Circles[i].Pos.x < RADIUS)
                        {
                                Circles[i].Pos.x = RADIUS;
                                Circles[i].Vel.x *= -1;
                        }
                        else if(Circles[i].Pos.x > SCREEN_WIDTH - RADIUS)
                        {
                                Circles[i].Pos.x = SCREEN_WIDTH - RADIUS;
                                Circles[i].Vel.x *= -1;
                        }
                        if(Circles[i].Pos.y < RADIUS)
                        {
                                Circles[i].Pos.y = RADIUS;
                                Circles[i].Vel.y *= -1;
                        }
                        else if(Circles[i].Pos.y > SCREEN_HEIGHT - RADIUS)
                        {
                                Circles[i].Pos.y = SCREEN_HEIGHT - RADIUS;
                                Circles[i].Vel.y *= -1;
                        }
}
void seperateAndBounce(Circle *Circles, int i, int j)
{
        Vector2 displacementDirection= Vector2Normalize(Vector2Subtract(Circles[i].Pos, Circles[j].Pos));
        float displacementDistance = (2.f * RADIUS - Vector2Distance(Circles[i].Pos, Circles[j].Pos)) / 2.f;
        Vector2 displacementVector = Vector2Scale(displacementDirection, displacementDistance);

        Circles[i].Pos = Vector2Add(Circles[i].Pos, displacementVector);
        Circles[j].Pos = Vector2Subtract(Circles[j].Pos, displacementVector);
        
        //v1'
        Vector2 PosDiffVect = Vector2Subtract(Circles[i].Pos, Circles[j].Pos);
        Vector2 VelDiffVect = Vector2Subtract(Circles[i].Vel, Circles[j].Vel);
        float magnitudeSqr = Vector2DistanceSqr(Circles[i].Pos, Circles[j].Pos);
        float UpperDotProduct = Vector2DotProduct(VelDiffVect, PosDiffVect);
        float fractionI = UpperDotProduct / magnitudeSqr;
                                
        Circles[i].Vel = Vector2Subtract(Circles[i].Vel, Vector2Scale(PosDiffVect, fractionI));

        //v2'
        PosDiffVect = Vector2Scale(PosDiffVect, -1);
        VelDiffVect = Vector2Scale(VelDiffVect, -1);
        float fractionJ = UpperDotProduct / magnitudeSqr;
 
        Circles[j].Vel = Vector2Subtract(Circles[j].Vel, Vector2Scale(PosDiffVect, fractionJ));
}
