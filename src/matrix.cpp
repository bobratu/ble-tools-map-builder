#include "matrix.h"
#include <cstdlib>
#include <iostream>

INT_MATRIX_2D::INT_MATRIX_2D(int rows, int columns) {
	this->rows = rows;
	this->columns = columns;

	int **array = (int **)(malloc(sizeof(int *) * rows));

	for (int i = 0; i < rows; i++) {
		array[i] = (int *)malloc(sizeof(int) * columns);

		for (int x = 0; x < columns; x++ ) {
			array[i][x] = 0;

		}
	}
    

	this->array = array;
}

int* INT_MATRIX_2D::operator[](int i) {
	if (i > this->rows) {
		std::cout << i <<" is out of bountsds";
		exit(-1);
	}
	int *bruh = this->array[i];

	return bruh;
}

INT_MATRIX_2D::~INT_MATRIX_2D() {
	for (int i = 0; i < this->rows; i++) {
		free(this->array[i]);
	}
	free(this->array);
}