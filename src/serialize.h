#pragma once
#include "matrix.h"
#include "point_of_interest.h"
#include <vector>
#include <memory>

struct MapHeader {
    int rows;
    int columns;
    int points_of_interest;
    int data_offset = 10; // this means the matrix is 10 bytes away from the header and that the point of interest are 10 bytes away from the matrix
};

struct MapData {
    INT_MATRIX_2D matrix;
    std::vector<POINT_OF_INTREST> pois;
};

class SERIALIZE {
    public:
    static bool Serialize_Map_Data(INT_MATRIX_2D,std::vector<POINT_OF_INTREST>);
};

class DESERIALIZE { // new class because i think its more readable
    public:
    static bool Deserialize_Map_Data(std::string filename,MapData &data);
};


