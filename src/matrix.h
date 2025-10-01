#pragma once
#include <vector>
class INT_MATRIX_2D {
	public:
		int rows;
		int columns;
		std::vector<std::vector<int>> array;
		
		INT_MATRIX_2D(int,int);
		INT_MATRIX_2D();
		std::vector<int> operator[](int);
};