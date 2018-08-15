#include "stdafx.h"
#include "Bezier.h"
#include <iostream>

using namespace std;

Bezier::Bezier(int degree)
	:degree(degree)
{
}

Bezier::Bezier(vector<double> *x, vector<double> *y, int degree)
	: degree(degree)
{
	//Need to check if sizes line up
	ctrlPoints.reserve(2);

	for (int i = 0; i < x->size(); x++)
	{
		ctrlPoints[0].push_back(x->at(i));
		ctrlPoints[1].push_back(y->at(i));
	}

}

Bezier::~Bezier()
{
	degree = NULL;
	ctrlPoints.clear();
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
		{ 1, },           // n=0
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

}

