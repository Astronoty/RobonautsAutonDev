//BezierMain.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Bezier.h"
#include <iostream>
using namespace std;

int main()
{
	Bezier *spline = new Bezier(1);


	vector<vector<double>> m1 = { { 1,2,3 },{ 4,5,6 } };
	vector<vector<double>> m2 = { { 7,8 },{ 9,10 },{ 11,12 } };



	vector<vector<double>> m3(spline->multiply(m1, m2));
	spline->printMatrix(m3);


	std::cin.get();

	return 0;


}


