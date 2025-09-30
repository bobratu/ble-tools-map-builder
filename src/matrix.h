#pragma once
class INT_MATRIX_2D {
	public:
		int rows;
		int columns;
		int** array;
		
		INT_MATRIX_2D(int,int);
		~INT_MATRIX_2D();
		int* operator[](int);


};