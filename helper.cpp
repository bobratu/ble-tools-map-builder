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
            pois.push_back(POINT_OF_INTREST(xMousePosition,yMousePosition,-1,false,"UNLABELED"));
            matrix[xMousePosition][yMousePosition] = 2;
        }

    }
}


bool IsPointOfInterest(int xPosition, int yPosition, std::vector<POINT_OF_INTREST> pois) {
    for (int i = 0; i < pois.size(); i++) {
        POINT_OF_INTREST poi = pois[i];

        if (poi.xPosition == xPosition && poi.yPosition == yPosition) {
            return true;
        }
    }

    return false;
}

POINT_OF_INTREST::POINT_OF_INTREST(int xPosition, int yPosition, int uuid,bool arduino, std::string name) {
	this->xPosition = xPosition;
	this->yPosition = yPosition;
	this->uuid = uuid;
    this->arduino = arduino;
	this->name = name;
}

POI_RECTANGLE_UI::POI_RECTANGLE_UI(Rectangle positionRectangle, Rectangle idRectangle, Rectangle nameRectangle,Rectangle toggleArduinoRectangle, POINT_OF_INTREST *poi) {
    this->positionRectangle = positionRectangle;
    this->nameRectangle = nameRectangle;
    this->idRectangle = idRectangle;
    this->toggleArduinoRectangle = toggleArduinoRectangle;
    this->poi = poi;
}
void POI_RECTANGLE_UI::Draw() {
    Rectangle idRectangle = this->idRectangle;
    Rectangle nameRectangle = this->nameRectangle;
    Rectangle positionRectangle = this->positionRectangle;
    Rectangle arduinoToggleRectangle = this->toggleArduinoRectangle;
    DrawRectangleRec(positionRectangle,GREEN);
    DrawRectangleRec(nameRectangle,GREEN);
    DrawRectangleRec(idRectangle,GREEN);
    DrawRectangleRec(arduinoToggleRectangle,GREEN);

    char xPositionStr[16];
    char yPositionStr[16];
    char idStr[16];
    itoa(poi->xPosition,xPositionStr,10);
    itoa(poi->yPosition,yPositionStr,10); //im sure this wont cause any problems in the future..
    itoa(poi->uuid,idStr,10);

    std::string combined = "";
    combined.append(xPositionStr);
    combined += "/";
    combined.append(yPositionStr);

    DrawText(combined.c_str(),positionRectangle.x+3,positionRectangle.y+2,13,WHITE);
    DrawText(poi->name.c_str(),nameRectangle.x+3,nameRectangle.y+2,13,WHITE);
    DrawText(idStr,idRectangle.x+3,idRectangle.y+2,13,WHITE);

}



void DrawUI(std::vector<POINT_OF_INTREST> &pois, int xResolution, int yResolution) {
    int startingX = xResolution+5;
    int startingY = 5;

    std::vector<POI_RECTANGLE_UI> uiRectangles{};
    uiRectangles.reserve(pois.size());
    
    for (int i = 0; i < pois.size(); i++) {
        int yPosition = startingY+(20*i);
        Rectangle positionRectangle = {startingX,yPosition,45,15};
        Rectangle idRectangle = {startingX + 50, yPosition,25,15};
        Rectangle toggleArduinoRectangle = {startingX + 50 + 25 + 5,yPosition, 25, 15};
        Rectangle nameRectangle = {startingX + 50 + 25 + 25+ 5 +5 , yPosition, 100, 15};
        POINT_OF_INTREST *poi = &pois[i];

        POI_RECTANGLE_UI poiRectangle(positionRectangle,idRectangle,nameRectangle,toggleArduinoRectangle,poi);
        poiRectangle.Draw();
        uiRectangles.push_back(poiRectangle);
    
    }
}
void DrawMatrix(INT_MATRIX_2D &matrix, int downscale_amt, std::vector<POINT_OF_INTREST> pois) {
        for (int x = 0; x < matrix.rows; x++) {

            for (int y = 0; y < matrix.columns; y++) {
                int xPosition = x*downscale_amt;
                int yPosition = y*downscale_amt;

                int value = matrix[x][y];

                bool isPoi = IsPointOfInterest(x,y,pois);

                if (value == 1) {
                    DrawRectangle(xPosition,yPosition,downscale_amt,downscale_amt,WHITE); // WALLS
                } else if (value == 0) {
                    DrawRectangle(xPosition,yPosition,downscale_amt,downscale_amt,BLACK); // EMPTY
                }


                if (isPoi) {
                    DrawRectangle(xPosition, yPosition, downscale_amt, downscale_amt, GREEN);

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
