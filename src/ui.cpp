#include "ui.h"
#include <iostream>
#include <cstdlib>
#include <vector>


POI_RECTANGLE_UI::POI_RECTANGLE_UI(Rectangle positionRectangle, Rectangle idRectangle,Rectangle toggleArduinoRectangle, Rectangle deleteRectangle, POINT_OF_INTREST *poi) {
    this->positionRectangle = positionRectangle;
    this->idRectangle = idRectangle;
    this->toggleArduinoRectangle = toggleArduinoRectangle;
    this->deleteRectangle = deleteRectangle;
    this->poi = poi;
}


void POI_RECTANGLE_UI::Draw() {
    Rectangle idRectangle = this->idRectangle;

    Rectangle positionRectangle = this->positionRectangle;
    Rectangle arduinoToggleRectangle = this->toggleArduinoRectangle;
    Rectangle deleteRectangle = this->deleteRectangle;
    DrawRectangleRec(positionRectangle,GREEN);
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


