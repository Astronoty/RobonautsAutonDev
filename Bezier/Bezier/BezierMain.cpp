//BezierMain.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "Bezier.h"
#include "CSVWriter.h"
#include <iostream>
using namespace std;

int main()
{
	vector<double> x = { 0, 5, 10, 20, 40 };
	vector<double> y = { 0, 50, 0, 100, -200 };

	Bezier *spline = new Bezier(x, y);

	CSVWriter csv(",");
	csv.newRow() << "t" << "x" << "y";
	for (double i = 0.0; i <= 1.0; i += 0.001)
	{
		vector<double> points = spline->calculateBezierPoint(i);
		cout << "t: " << i << ", x: " << points[0] << ", y: " << points[1] << endl;
		csv.newRow() << i << points[0] << points[1];
	}

	csv.writeToFile("PointsExport.csv");

	std::cin.get();

	return 0;


}


