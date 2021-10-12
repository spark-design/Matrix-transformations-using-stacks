#define _USE_MATH_DEFINES
#include "Stack.h"
#include <iomanip>
#include <iostream>
#include <cmath>

using namespace::std;

Stack::~Stack()
{
	Node* tmp = top;

	while (tmp != nullptr)
	{
		top = top->next;
		delete tmp;
		tmp = top;
	}
}

void Stack::push(Matrix data)
{
	Node *tmp = new Node(data);

	tmp->next = top;
	top = tmp;
}

bool Stack::pop()
{
	Node* tmp = top;

	if (top == nullptr)
	{
		return false;
	}

	top = top->next;

	delete tmp;

	return true;
}

bool Stack::peek(Matrix& data)
{
	if (top == nullptr)
	{
		return false;
	}

	data = top->mat;

	return true;
}

void Stack::display()
{
	Node* tmp = top;
	
	while (tmp != nullptr)
	{
		for(int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				cout << "[ " << fixed << setprecision(6) << tmp->mat.matrix[x][y] << " ]" << "\t";// Using 6 decimal places to help fix a glitch with sin in visual studio
			}
			cout << endl;
		}
		tmp = tmp->next;
		cout << endl;
	}
}

double Stack::cosConvert(double angle) // Utilizes cos because sin has glitches in Visual so I needed a convert for sin so I made these 2 functions
{
	double result;
	result = cos(angle * M_PI / 180.0);
	return result;
}

double Stack::sinConvert(double angle) // Utilizes sin successfully, given glitches with sin in visual
{
	double result;
	result = sin(angle * M_PI / 180.0);
	return result;
}

void Stack::transformVertex(double x, double y, double z)
{
	double vector4 [4] = {x, y, z, 1.0};

	Matrix transform;
	Matrix result;

	// Create an identity matrix for result
	result.setValue(0, 0, 1.0);
	result.setValue(1, 0, 0.0);
	result.setValue(2, 0, 0.0);
	result.setValue(3, 0, 0.0);
	
	result.setValue(0, 1, 0.0);
	result.setValue(1, 1, 1.0);
	result.setValue(2, 1, 0.0);
	result.setValue(3, 1, 0.0);

	result.setValue(0, 2, 0.0);
	result.setValue(1, 2, 0.0);
	result.setValue(2, 2, 1.0);
	result.setValue(3, 2, 0.0);

	result.setValue(0, 3, 0.0);
	result.setValue(1, 3, 0.0);
	result.setValue(2, 3, 0.0);
	result.setValue(3, 3, 1.0);

	while (peek(transform))
	{
		result = result.multiply(transform);

		pop();
	}

	cout << "transformation matrix: \n";

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			cout << std::setprecision(6) << fixed << result.matrix[x][y] << "\t";
		}
		cout << endl;
	}

	cout << "transformation vertex: \n";
	for (int j = 0; j < 4; ++j)
	{
		double product = 0.0;
		for (int k = 0; k < 4; ++k)
		{
			product += vector4[k] * result.matrix[j][k];
		}
		cout << product << " ";
	}
	cout << endl;

}

void Stack::pitch(double angle) // Rotate X
{
	Matrix *tmp = new Matrix();

	tmp->setValue(0,0, 1.0);
	tmp->setValue(1,0, 0.0);
	tmp->setValue(2,0, 0.0);
	tmp->setValue(3,0, 0.0);

	tmp->setValue(0,2, 0.0);
	tmp->setValue(1,2, sinConvert(angle));
	tmp->setValue(2,2, cosConvert(angle));
	tmp->setValue(3,2, 0.0);

	tmp->setValue(0,1, 0.0);
	tmp->setValue(1,1, cosConvert(angle)); // -
	tmp->setValue(2,1, -sinConvert(angle));
	tmp->setValue(3,1, 0.0);

	tmp->setValue(0,3, 0.0);
	tmp->setValue(1,3, 0.0);
	tmp->setValue(2,3, 0.0);
	tmp->setValue(3,3, 1.0);

	push(*tmp);
}

void Stack::yaw(double angle) // Rotate Y
{
	Matrix *tmp = new Matrix();

	tmp->setValue(0,0, cosConvert(angle));
	tmp->setValue(1,0, 0.0);
	tmp->setValue(2,0, sinConvert(angle));
	tmp->setValue(3,0, 0.0);

	tmp->setValue(0,1, 0.0);
	tmp->setValue(1,1, 1.0);
	tmp->setValue(2,1, 0.0);
	tmp->setValue(3,1, 0.0);

	tmp->setValue(0,2, -sinConvert(angle)); //-
	tmp->setValue(1,2, 0.0);
	tmp->setValue(2,2, cosConvert(angle));
	tmp->setValue(3,2, 0.0);

	tmp->setValue(0,3, 0.0);
	tmp->setValue(1,3, 0.0);
	tmp->setValue(2,3, 0.0);
	tmp->setValue(3,3, 1.0);

	push(*tmp);
}

void Stack::roll(double angle) // Rotate Z
{
	Matrix* tmp = new Matrix();

	tmp->setValue(0,0, cosConvert(angle));
	tmp->setValue(1,0, -sinConvert(angle));
	tmp->setValue(2,0, 0.0);
	tmp->setValue(3,0, 0.0);

	tmp->setValue(0,1, sinConvert(angle));
	tmp->setValue(1,1, cosConvert(angle));
	tmp->setValue(2,1, 0.0);
	tmp->setValue(3,1, 0.0);

	tmp->setValue(0,2, 0.0);
	tmp->setValue(1,2, 0.0);
	tmp->setValue(2,2, 1.0);
	tmp->setValue(3,2, 0.0);

	tmp->setValue(0,3, 0.0);
	tmp->setValue(1,3, 0.0);
	tmp->setValue(2,3, 0.0);
	tmp->setValue(3,3, 1.0);

	push(*tmp);
}

void Stack::translate(double x, double y, double z)
{
	Matrix* tmp = new Matrix();

	tmp->setValue(0,0, 1.0);
	tmp->setValue(1,0, 0.0);
	tmp->setValue(2,0, 0.0);
	tmp->setValue(3,0, 0.0);

	tmp->setValue(0,1, 0.0);
	tmp->setValue(1,1, 1.0);
	tmp->setValue(2,1, 0.0);
	tmp->setValue(3,1, 0.0);

	tmp->setValue(0,2, 0.0);
	tmp->setValue(1,2, 0.0);
	tmp->setValue(2,2, 1.0);
	tmp->setValue(3,2, 0.0);

	tmp->setValue(0,3, x);
	tmp->setValue(1,3, y);
	tmp->setValue(2,3, z);
	tmp->setValue(3,3, 1.0);

	push(*tmp);
}