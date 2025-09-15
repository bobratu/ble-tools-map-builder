#include "raylib.h"
#include "rlgl.h"
#include <cstdlib>
#include <iostream>
#include "helper.h"
#include <vector>

void CreateWindow(int,int,int);
int main()
{ 
    CreateWindow(500, 500, 10);    
    
    return 0;
}

void CreateWindow(int xResolution, int yResolution, int downscale_amt) {
    InitWindow(xResolution+300,yResolution, "Map builder");
    SetTargetFPS(60);   
   
    INT_MATRIX_2D matrix(xResolution/downscale_amt,yResolution/downscale_amt); // you should prolly make sure this divides into an even number 
    std::vector<POINT_OF_INTREST> pois{};

    WriteBorders(matrix);



    while (!WindowShouldClose())    
    {

        BeginDrawing();




        WriteToMatrix(matrix, downscale_amt, xResolution, yResolution, pois);
        DrawMatrix(matrix,downscale_amt, pois);
        DrawUI(pois,xResolution,yResolution);
        EndDrawing();

    }

    CloseWindow();        
}



