#pragma once
#include "raylib.h"
#include <string>
#include <vector>
#include "matrix.h"
#include "point_of_interest.h"



class POI_RECTANGLE_UI {
	public:
		Rectangle positionRectangle;
		
		Rectangle toggleArduinoRectangle;
		Rectangle idRectangle;
		Rectangle deleteRectangle;
		POINT_OF_INTREST *poi;
		POI_RECTANGLE_UI(Rectangle,Rectangle, Rectangle, Rectangle, POINT_OF_INTREST *poi );
		void Draw();
};


void DrawMatrix(INT_MATRIX_2D &, int, std::vector<POINT_OF_INTREST> );
void WriteToMatrix(INT_MATRIX_2D &, int, int, int, std::vector<POINT_OF_INTREST> &);
void DrawUI(std::vector<POINT_OF_INTREST> &, int, int);
void WriteBorders(INT_MATRIX_2D &);

bool IsPointOfInterest(int xPosition, int yPosition, std::vector<POINT_OF_INTREST> pois, int &out);
void GetUserInput(std::vector<POI_RECTANGLE_UI> &pois, std::vector<POINT_OF_INTREST> &matrixPOIs);
void GetStringFromUser(std::string &str);