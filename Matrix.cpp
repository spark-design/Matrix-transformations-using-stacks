#include "Matrix.h"
#include <iostream>
#include <iomanip>

using namespace::std;

void Matrix::setValue(int x, int y, double val)
{
	matrix[x][y] = val;
}

Matrix Matrix::multiply(Matrix input)
{
	Matrix result;

	for(int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			for (int k = 0; k < 4; k++)
			{
				result.matrix[i][j] += input.matrix[i][k] * matrix[k][j];
			}
	return result;

}