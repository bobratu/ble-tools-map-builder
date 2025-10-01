#include "raylib.h"
#include "rlgl.h"
#include <cstdlib>
#include <iostream>
#include "matrix.h"
#include "ui.h"
#include "point_of_interest.h"
#include <vector>
#include "helper.h"
#include "serialize.h"

void CreateWindow(int,int,int);
int main()
{ 
    CreateWindow(500, 500, 10);    

    
    return 0;
}

void CreateWindow(int xResolution, int yResolution, int downscale_amt) {
    InitWindow(xResolution+300,yResolution, "Map builder");
    SetTargetFPS(200);   
   
    INT_MATRIX_2D matrix(xResolution/downscale_amt,yResolution/downscale_amt); // you should prolly make sure this divides into an even number 
    std::vector<POINT_OF_INTREST> pois{};

    WriteBorders(matrix);
    int counter = 0;
    while (!WindowShouldClose())    
    {
        BeginDrawing();
        WriteToMatrix(matrix, downscale_amt, xResolution, yResolution, pois);
        DrawMatrix(matrix,downscale_amt, pois);
        DrawUI(pois,xResolution,yResolution);
        if (counter == 1500) {
            SERIALIZE::Serialize_Map_Data(matrix,pois);
            std::cout << "\n SERIALIZED SERILAIZED";
        }
        counter++;
        EndDrawing();
    }

    CloseWindow();        
}



