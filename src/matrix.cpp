#include "matrix.h"
#include <cstdlib>
#include <iostream>

INT_MATRIX_2D::INT_MATRIX_2D(int rows, int columns) {
	this->rows = rows;
	this->columns = columns;

	std::vector<std::vector<int>> array = {};

	for (int i = 0; i < rows; i++) {
		std::vector<int> new_vec = {};
		array.push_back(new_vec);

		for (int x = 0; x < columns; x++ ) {
			array[i].push_back(0);
		}
	}
    

	this->array = array;
}

INT_MATRIX_2D::INT_MATRIX_2D() : INT_MATRIX_2D(1,1) {
	
}

std::vector<int> INT_MATRIX_2D::operator[](int i) {
	if (i > this->rows) {
		std::cout << i <<" is out of bountsds";
		exit(-1);
	}
	

	return this->array[i];
}

