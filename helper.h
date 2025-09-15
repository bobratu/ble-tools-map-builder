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
		std::string uuid; // 1 == arduino 2 == waypoint
		bool arduino = false;
		std::string name;
		POINT_OF_INTREST(int,int,std::string,bool,std::string);


};

class POI_RECTANGLE_UI {
	public:
		Rectangle positionRectangle;
		Rectangle nameRectangle;
		Rectangle toggleArduinoRectangle;
		Rectangle idRectangle;
		Rectangle deleteRectangle;
		POINT_OF_INTREST *poi;
		POI_RECTANGLE_UI(Rectangle,Rectangle, Rectangle, Rectangle, Rectangle, POINT_OF_INTREST *poi );
		void Draw();
};


void DrawMatrix(INT_MATRIX_2D &, int, std::vector<POINT_OF_INTREST> );
void WriteToMatrix(INT_MATRIX_2D &, int, int, int, std::vector<POINT_OF_INTREST> &);
void DrawUI(std::vector<POINT_OF_INTREST> &, int, int);
void WriteBorders(INT_MATRIX_2D &);

bool IsPointOfInterest(int xPosition, int yPosition, std::vector<POINT_OF_INTREST> pois, int &out);
void GetUserInput(std::vector<POI_RECTANGLE_UI> &pois, std::vector<POINT_OF_INTREST> &matrixPOIs);
void GetStringFromUser(std::string &str);