#include "point_of_interest.h"
POINT_OF_INTREST::POINT_OF_INTREST(int xPosition, int yPosition, std::string uuid,bool arduino) {
	this->xPosition = xPosition;
	this->yPosition = yPosition;
	this->uuid = uuid;
    this->arduino = arduino;
}