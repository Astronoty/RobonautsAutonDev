//BezierMain.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "Bezier.h"
#include "BezierSpline.h"
#include "CSVWriter.h"
#include <iostream>
#define PI 3.14159265359
using namespace std;

int main()
{

		/*
		vector<double> x = { 0, 0, -100, -100, -150 };
		vector<double> y = { 0, 200, 200, 400, 800 };

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
		*/
	
	vector<vector<double>> waypoints = { { 0, 50, 70, 80 }, { 0, 10, 60, 200} };
	vector<double> theta = { 0.01, 50, 0.01 , 90};
	BezierSpline *spline = new BezierSpline(waypoints, theta);

	CSVWriter csv(",");
	csv.newRow() << "t" << "x" << "y";
	for (double i = 0.0; i <= 3.0; i += 0.005)
	{
		vector<double> points = spline->calculateSplinePoint(i);
		cout << "t: " << i << ", x: " << points[0] << ", y: " << points[1] << endl;
		csv.newRow() << i << points[0] << points[1];
	}

	csv.writeToFile("PointsExport.csv");
	std::cin.get();

	return 0;


}


