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



POINT_OF_INTREST::POINT_OF_INTREST(int xPosition, int yPosition, int id, std::string name) {
	this->xPosition = xPosition;
	this->yPosition = yPosition;
	this->id = id;
	this->name = name;
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
            pois.push_back(POINT_OF_INTREST(xMousePosition,yMousePosition,-1,"UNLABELED"));
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


void DrawUI(INT_MATRIX_2D &matrix, int xResolution, int yResolution) {
    

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
                    DrawRectangle(xPosition,yPosition,downscale_amt,downscale_amt,BLACK); // ARDUINO POSITIONS
                } else if (value == 2) {
                    DrawRectangle(xPosition,yPosition,downscale_amt,downscale_amt,ORANGE); // ARDUINO POSITIONS
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
