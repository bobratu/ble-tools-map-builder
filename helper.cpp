#include "helper.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include "raylib.h"


INT_MATRIX_2D::INT_MATRIX_2D(int rows, int columns) {
	this->rows = rows;
	this->columns = columns;

	int **array = (int **)(malloc(sizeof(int *) * rows));

	for (int i = 0; i < rows; i++) {
		array[i] = (int *)malloc(sizeof(int) * columns);

		for (int x = 0; x < columns; x++ ) {
			array[i][x] = 0;

		}
	}
    

	this->array = array;
}

int* INT_MATRIX_2D::operator[](int i) {
	if (i > this->rows) {
		std::cout << i <<" is out of bountsds";
		exit(-1);
	}
	int *bruh = this->array[i];

	return bruh;
}

INT_MATRIX_2D::~INT_MATRIX_2D() {
	for (int i = 0; i < this->rows; i++) {
		free(this->array[i]);
	}
	free(this->array);
}




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
            pois.push_back(POINT_OF_INTREST(xMousePosition,yMousePosition,std::string("ID"),false,"NAME"));
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

POINT_OF_INTREST::POINT_OF_INTREST(int xPosition, int yPosition, std::string uuid,bool arduino, std::string name) {
	this->xPosition = xPosition;
	this->yPosition = yPosition;
	this->uuid = uuid;
    this->arduino = arduino;
	this->name = name;
}

POI_RECTANGLE_UI::POI_RECTANGLE_UI(Rectangle positionRectangle, Rectangle idRectangle, Rectangle nameRectangle,Rectangle toggleArduinoRectangle, Rectangle deleteRectangle, POINT_OF_INTREST *poi) {
    this->positionRectangle = positionRectangle;
    this->nameRectangle = nameRectangle;
    this->idRectangle = idRectangle;
    this->toggleArduinoRectangle = toggleArduinoRectangle;
    this->deleteRectangle = deleteRectangle;
    this->poi = poi;
}
void POI_RECTANGLE_UI::Draw() {
    Rectangle idRectangle = this->idRectangle;
    Rectangle nameRectangle = this->nameRectangle;
    Rectangle positionRectangle = this->positionRectangle;
    Rectangle arduinoToggleRectangle = this->toggleArduinoRectangle;
    Rectangle deleteRectangle = this->deleteRectangle;
    DrawRectangleRec(positionRectangle,GREEN);
    DrawRectangleRec(nameRectangle,GREEN);
    DrawRectangleRec(idRectangle,GREEN);
    DrawRectangleRec(deleteRectangle, RED);
    

    char xPositionStr[16];
    char yPositionStr[16];
    char idStr[16];
    itoa(poi->xPosition,xPositionStr,10);
    itoa(poi->yPosition,yPositionStr,10); //im sure this wont cause any problems in the future..
    

    std::string combined = "";
    combined.append(xPositionStr);
    combined += "/";
    combined.append(yPositionStr);

    DrawText(combined.c_str(),positionRectangle.x+3,positionRectangle.y+2,13,WHITE);
    DrawText(poi->name.c_str(),nameRectangle.x+3,nameRectangle.y+2,13,WHITE);
    DrawText(poi->uuid.c_str(),idRectangle.x+3,idRectangle.y+2,13,WHITE);
    DrawText("X",deleteRectangle.x+7, deleteRectangle.y+2,13,WHITE);

    if (poi->arduino) {
        DrawRectangleRec(arduinoToggleRectangle,ORANGE);
        DrawText("ARD",arduinoToggleRectangle.x, arduinoToggleRectangle.y +2, 13 ,WHITE);
    } else {
        DrawRectangleRec(arduinoToggleRectangle,GREEN);
        DrawText("POI",arduinoToggleRectangle.x, arduinoToggleRectangle.y +2, 13 ,WHITE);
    }
    
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
        Rectangle idRectangle = {startingX + 50, yPosition,100,15};
        Rectangle toggleArduinoRectangle = {startingX + 50 + 100 + 5,yPosition, 25, 15};
        Rectangle nameRectangle = {startingX + 50 + 100 + 5 + 25 +5 , yPosition, 75, 15};
        Rectangle deleteRectangle = {startingX + 50 + 100 + 5 + 25 + 5 + 75 + 5, yPosition, 25, 15};
        POINT_OF_INTREST *poi = &pois[i];

        POI_RECTANGLE_UI poiRectangle(positionRectangle,idRectangle,nameRectangle,toggleArduinoRectangle,deleteRectangle,poi);
        poiRectangle.Draw();
        uiRectangles.push_back(poiRectangle);
    }
    GetUserInput(uiRectangles, pois);
}

void GetUserInput(std::vector<POI_RECTANGLE_UI> &pois, std::vector<POINT_OF_INTREST> &matrixPOIs) {
    for (int i = 0; i < pois.size();i++) {
        POI_RECTANGLE_UI poi = pois[i];
        
        Rectangle arduinoToggleRec = poi.toggleArduinoRectangle;
        Rectangle nameRectangle = poi.nameRectangle;
        Rectangle uuidRectangle = poi.idRectangle;
        Rectangle deleteRectangle = poi.deleteRectangle;
        if (CheckCollisionPointRec(GetMousePosition(),arduinoToggleRec) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            poi.poi->arduino = !poi.poi->arduino;
        }

        if (CheckCollisionPointRec(GetMousePosition(),nameRectangle)) {
            GetStringFromUser(poi.poi->name);            
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
