#pragma once

class Matrix
{
public:
	double matrix[4][4] = { 0 };

	void setValue(int x, int y, double val);
	Matrix multiply(Matrix input);
};