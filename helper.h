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
		int uuid; // 1 == arduino 2 == waypoint
		bool arduino = false;
		std::string name;
		POINT_OF_INTREST(int,int,int,bool,std::string);


};

class POI_RECTANGLE_UI {
	public:
		Rectangle positionRectangle;
		Rectangle nameRectangle;
		Rectangle toggleArduinoRectangle;
		Rectangle idRectangle;
		POINT_OF_INTREST *poi;
		POI_RECTANGLE_UI(Rectangle,Rectangle, Rectangle, Rectangle, POINT_OF_INTREST *poi );
		void Draw();
};


void DrawMatrix(INT_MATRIX_2D &, int, std::vector<POINT_OF_INTREST> );
void WriteToMatrix(INT_MATRIX_2D &, int, int, int, std::vector<POINT_OF_INTREST> &);
void DrawUI(std::vector<POINT_OF_INTREST> &, int, int);
void WriteBorders(INT_MATRIX_2D &);

bool IsPointOfInterest(int xPosition, int yPosition, std::vector<POINT_OF_INTREST> pois);
