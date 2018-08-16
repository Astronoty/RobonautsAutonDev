#include "stdafx.h"
#include "Bezier.h"
#include <iostream>

using namespace std;

Bezier::Bezier(int degree)
	:degree(degree)
{
}

//Constructor for standard bezier that takes N degree and N+1 points for both x and y
Bezier::Bezier(vector<double> &x, vector<double> &y)
{
	degree = x.size() - 1;

		setBernsteinBasis(degree);

		xPoints.reserve(degree);
		yPoints.reserve(degree);

		vector<double> temp;

		for (uint16_t i = 0; i < x.size(); i++)
		{
			temp = { x.at(i) };
			xPoints.push_back(temp);

			temp = { y.at(i) };
			yPoints.push_back(temp);
		}

		temp = {};
		tMatrix.push_back(temp);
}

Bezier::~Bezier()
{
	degree = NULL;
	xPoints.clear();
	yPoints.clear();
	bernsteinBasis.clear();
	tMatrix.clear();
}

void Bezier::setBernsteinBasis(int degree)
{
	//Select the right basis matrix based on degree
	switch (degree)
	{
		case 1: bernsteinBasis = 
			{
			{ 1, 0},
			{-1, 1}
			};
			break;
	
		case 2: bernsteinBasis = 
			{
			{ 1, 0, 0},
			{-2, 2, 0},
			{ 1,-2, 1}
			};
			break;
		case 3: bernsteinBasis = 
			{
			{ 1, 0, 0, 0 },
			{-3, 3, 0, 0 },
			{ 3,-6, 3, 0 },
			{-1, 3,-3, 1 }
			};
			break;
		case 4: bernsteinBasis = 
			{
			{ 1, 0,  0,  0, 0},
			{-4, 4,  0,  0, 0},
			{ 6,-12, 6,  0, 0},
			{-4, 12,-12, 4, 0},
			{ 1,-4,  6, -4, 1}
			};
			break;
		case 5: bernsteinBasis = 
			{
			{ 1,  0,  0,  0,  0, 0},
			{-5,  5,  0,  0,  0, 0},
			{ 10,-20, 10, 0,  0 ,0},
			{-10, 30,-30, 10, 0, 0},
			{ 5, -20, 30,-20, 5, 0},
			{-1,  5, -10, 10,-5, 1}
			};
		default:
			break;


	}
}
//Calculate (x,y) point based on t (val from 0-1)
vector<double> Bezier::calculateBezierPoint(double t)
{
	//Return this vector, resultant will be tMatrix*bernsteinBasis*parameterizedPoints
	vector<double> points;
	

	tMatrix[0].clear();
	//Calculate the tMatrix
	for (int i = 0; i <= degree; i++)
	{
		tMatrix[0].push_back(pow(t,i));
	}
	
	//This equals tMatrix*bernsteinBasis
	vector<vector<double>> intermediateResultant = multiply(tMatrix, bernsteinBasis);

	//These store the resultants after multiplying by the x and y control points
	vector<vector<double>> resultantX = multiply(intermediateResultant, xPoints);
	vector<vector<double>> resultantY = multiply(intermediateResultant, yPoints);

	points.push_back(resultantX[0][0]);
	points.push_back(resultantY[0][0]);

	return points;
}
//Recursive factorial
int Bezier::factorial(int n)
{
	int num = 1;
	for (int i = n; i > 1; i--)
		num *= i;
	return num;
}

//Returns combination nCk
int Bezier::binomial(int n, int k)
{
	//Stores an initial pascal to decrease processing time for low level combination calls
	int pascal[7][7] =
	{
	{ 1 },           // n=0
	{ 1, 1 },          // n=1
	{ 1, 2, 1 },         // n=2
	{ 1, 3, 3, 1 },        // n=3
	{ 1, 4, 6, 4, 1 },       // n=4
	{ 1, 5, 10, 10, 5, 1 },    // n=5
	{ 1, 6, 15, 20, 15, 6, 1 }   // n=6
	};

	//If requested value is outside scope of predefined pascal manually calculate (more intensive)
	if (n > sizeof(pascal))
	{
		if (k > sizeof(pascal[n]))
		{
			return factorial(n) / (factorial(k)*factorial(n - k));
		}
	}

	return pascal[n][k];
}

//Multiply two vectors and return the resultant
vector<vector<double>> Bezier::multiply(vector<vector<double>> &a, vector<vector<double>> &b)
{
	if (a.at(0).size() == b.size())
	{
		vector<vector<double>> result(a.size(), vector<double>(b[0].size()));
		for (uint32_t r = 0; r < a.size(); r++)
		{
			for (uint32_t c = 0; c < b.at(0).size(); c++)
			{
				for (uint32_t z = 0; z < (a.at(0)).size(); z++)
				{
					result[r][c] += ((a.at(r)[z]) * (b.at(z))[c]);
				}
			}

		}
		return result;
	}
	else
	{
		cout << "Matrices cannot be multiplied due to invalid sizes";
		return {};
	}

}

//Quick 2D matrix print
void Bezier::printMatrix(vector<vector<double>> &a)
{
	for (uint32_t x = 0; x < a.size(); x++)
	{
		cout << "[";
		for (uint32_t y = 0; y < a[x].size(); y++)
		{
			cout << a[x][y];
			if (y < a[x].size() - 1)
				cout << ", ";
		}
		cout << "]" << endl;

	}

	cout << endl;

}

