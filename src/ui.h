#pragma once
#include "point_of_interest.h"
#include "raylib.h"
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

