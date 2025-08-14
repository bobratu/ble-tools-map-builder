#include "raylib.h"
#include "rlgl.h"
#include <stdio.h>
#include "helper.h"

void UpdateDrawFrame();     
void CreateWindow(int,int);

const int X_PANEL_SIZE = 150;

int main()
{ 
    int xResolution;
    int yResolution;

    printf("enter x resolution \n");
    scanf_s("%d",&xResolution);
    printf("enter y resolutoin \n");
    scanf_s("%d",&yResolution);

    CreateWindow(xResolution+X_PANEL_SIZE,yResolution);
    
    return 0;
}

void CreateWindow(int xResolution, int yResolution) {
    InitWindow(xResolution,yResolution, "Map builder");

    SetTargetFPS(60);   

    while (!WindowShouldClose())    
    {
        UpdateDrawFrame();
    }

    CloseWindow();        
}

void UpdateDrawFrame()
{
    BeginDrawing();

    EndDrawing();
}