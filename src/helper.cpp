#include "ui.h"
#include "helper.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include "raylib.h"

void WriteToMatrix(INT_MATRIX_2D &matrix, int downscale_amt, int xResolution, int yResolution, std::vector<POINT_OF_INTREST> &pois) {
    Vector2 mousePosition = GetMousePosition();

    if (mousePosition.x > 0 && mousePosition.y > 0 && mousePosition.x < xResolution && mousePosition.y < yResolution) {
        int xMousePosition = ((int)mousePosition.x)/downscale_amt;
        int yMousePosition = ((int)mousePosition.y)/downscale_amt;

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            matrix[xMousePosition][yMousePosition] = 1;
        } else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            matrix[xMousePosition][yMousePosition] = 0;

        } else if (IsKeyPressed(KEY_H)) {
            pois.push_back(POINT_OF_INTREST(xMousePosition,yMousePosition,std::string("ID"),false));
            matrix[xMousePosition][yMousePosition] = 2;
        }

    }
}


bool IsPointOfInterest(int xPosition, int yPosition, std::vector<POINT_OF_INTREST> pois, int &index) {
    for (int i = 0; i < pois.size(); i++) {
        POINT_OF_INTREST poi = pois[i];

        if (poi.xPosition == xPosition && poi.yPosition == yPosition) {
            index = i;
            return true;
        }
    }

    return false;
}


void DrawUI(std::vector<POINT_OF_INTREST> &pois, int xResolution, int yResolution) {
    int startingX = xResolution+5;
    int startingY = 5;
    DrawRectangle(xResolution,0,300,900,BLACK);

    std::vector<POI_RECTANGLE_UI> uiRectangles{};
    uiRectangles.reserve(pois.size());
    
    for (int i = 0; i < pois.size(); i++) {
        int yPosition = startingY+(20*i);
        Rectangle positionRectangle = {startingX,yPosition,45,15};
        Rectangle idRectangle = {startingX + 50, yPosition,175,15};
        Rectangle toggleArduinoRectangle = {startingX + 50 + 175 + 5,yPosition, 25, 15};
        Rectangle deleteRectangle = {startingX + 50 + 175 + 5 + 25 + 5, yPosition, 25, 15};
        POINT_OF_INTREST *poi = &pois[i];

        POI_RECTANGLE_UI poiRectangle(positionRectangle,idRectangle,toggleArduinoRectangle,deleteRectangle,poi);
        poiRectangle.Draw();
        uiRectangles.push_back(poiRectangle);
    }
    GetUserInput(uiRectangles, pois);
}

void GetUserInput(std::vector<POI_RECTANGLE_UI> &pois, std::vector<POINT_OF_INTREST> &matrixPOIs) {
    for (int i = 0; i < pois.size();i++) {
        POI_RECTANGLE_UI poi = pois[i];
        
        Rectangle arduinoToggleRec = poi.toggleArduinoRectangle;
        Rectangle uuidRectangle = poi.idRectangle;
        Rectangle deleteRectangle = poi.deleteRectangle;
        if (CheckCollisionPointRec(GetMousePosition(),arduinoToggleRec) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            poi.poi->arduino = !poi.poi->arduino;
        }


        if (CheckCollisionPointRec(GetMousePosition(),uuidRectangle)) {
            GetStringFromUser(poi.poi->uuid);
        }

        if (CheckCollisionPointRec(GetMousePosition(),deleteRectangle) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            
            for (int i = 0; i < matrixPOIs.size();i++) {
                if (&matrixPOIs[i] == poi.poi) {
                    matrixPOIs.erase(matrixPOIs.begin()+i);
                    break;
                }
            }
            
        }

    }
}

void GetStringFromUser(std::string &str) {
    int key = GetCharPressed();

    while (key > 0 && str.length() < 9) {
        if (key >= 32 && key <= 125) {
            str.push_back(char(key));
        }
        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE) && str.length() > 0) {
        str.pop_back();
    }
}

void DrawMatrix(INT_MATRIX_2D &matrix, int downscale_amt, std::vector<POINT_OF_INTREST> pois) {
        for (int x = 0; x < matrix.rows; x++) {
            for (int y = 0; y < matrix.columns; y++) {
                int xPosition = x*downscale_amt;
                int yPosition = y*downscale_amt;
                int value = matrix[x][y];

                int poiIndex = -1;
                bool isPoi = IsPointOfInterest(x,y,pois,poiIndex);

                if (isPoi) {
                    POINT_OF_INTREST poi = pois[poiIndex];
                    if (poi.arduino) {
                        DrawRectangle(xPosition, yPosition, downscale_amt, downscale_amt, ORANGE);
                    } else {
                        DrawRectangle(xPosition, yPosition, downscale_amt, downscale_amt, GREEN);
                    }
                
                } else {
                    DrawRectangle(xPosition,yPosition,downscale_amt,downscale_amt,BLACK);
                }

                if (value == 1 && !isPoi) {
                    DrawRectangle(xPosition,yPosition,downscale_amt,downscale_amt,WHITE); // WALLS
                } else if (value == 0 && !isPoi) {
                    DrawRectangle(xPosition,yPosition,downscale_amt,downscale_amt,BLACK); // EMPTY
                }

            }
        }
        
        
}

void WriteBorders(INT_MATRIX_2D &matrix) {

    for (int x = 0; x < matrix.rows; x++) {
        for (int y =0; y < matrix.columns; y++) {
            if (x == 0 || y == 0 || x == matrix.rows - 1 || y == matrix.columns -1) {
                matrix[x][y] = 1;
            }
        }
    }


}

