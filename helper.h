#pragma once
#include "raylib.h"
#include <string>
#include <vector>
class INT_MATRIX_2D {
	public:
		int rows;
		int columns;
		int** array;
		INT_MATRIX_2D(int,int);
		~INT_MATRIX_2D();
		int* operator[](int);


};

class POINT_OF_INTREST {
	public:
		int xPosition;
		int yPosition;
		int id; // 1 == arduino 2 == waypoint
		std::string name;
		POINT_OF_INTREST(int,int,int,std::string);


};

class POI_RECTANGLE_UI {
	public:
		Rectangle positionRectangle;
		Rectangle nameRectangle;
		Rectangle idRectangle;
		POINT_OF_INTREST *poi;
		POI_RECTANGLE_UI(Rectangle, Rectangle, Rectangle, POINT_OF_INTREST *poi );
		void Draw();
};


void DrawMatrix(INT_MATRIX_2D &, int, std::vector<POINT_OF_INTREST> );
void WriteToMatrix(INT_MATRIX_2D &, int, int, int, std::vector<POINT_OF_INTREST> &);
void DrawUI(std::vector<POINT_OF_INTREST> &, int, int);
void WriteBorders(INT_MATRIX_2D &);

bool IsPointOfInterest(int xPosition, int yPosition, std::vector<POINT_OF_INTREST> pois);
