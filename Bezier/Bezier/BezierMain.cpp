//BezierMain.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Bezier.h"
#include <iostream>
using namespace std;

int main()
{



	vector<double> x = { 0, 1.18, 3, 5 };
	vector<double> y = { 0, 2.54, 1, 2 };

	Bezier *spline = new Bezier(x, y, 3);

	vector<double> points = spline->calculateBezierPoint(0.25);
	cout << "x: " << points[0] << ", y: " << points[1] << endl;

	points = spline->calculateBezierPoint(0.5);
	cout << "x: " << points[0] << ", y: " << points[1] << endl;



	


	//vector<vector<double>> m3(spline->multiply(m1, m2));

//	spline->printMatrix(m3);


	std::cin.get();

	return 0;


}


