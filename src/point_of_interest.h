#pragma once
#include <string>
class POINT_OF_INTREST {
	public:
		int xPosition;
		int yPosition;
		std::string uuid;
		bool arduino = false;
		POINT_OF_INTREST(int,int,std::string,bool);
};
