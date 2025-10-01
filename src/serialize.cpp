#include "serialize.h"
#include "matrix.h"
#include <fstream>
#include <iostream>
#include <algorithm>

bool SERIALIZE::Serialize_Map_Data(INT_MATRIX_2D matrix, std::vector<POINT_OF_INTREST> pois) {
    //std::ofstream outfile("output.map", std::ios::binary);

    //if (!outfile.is_open()) return false;

    ////MapHeader header = {};
    ////header.columns = matrix.columns;
    ////header.rows = matrix.rows;
    ////header.points_of_interest = pois.size();

    ////outfile.write(reinterpret_cast<char*>("woah"), sizeof(std::string));


    //outfile.close();

    return true;
}


bool DESERIALIZE::Deserialize_Map_Data(std::string filename ,MapData &data) {
    return true;
}