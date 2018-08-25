#include "stdafx.h"
#include "BezierSpline.h"
#include <iostream>

#define PI 3.14159265359

using namespace std;


BezierSpline::BezierSpline(vector<vector<double>> waypoints, vector<double>headings)
	: waypoints(waypoints)
	 ,headings(headings)
{
	convertHeadingToSlope();
	generateCubicBezier();
}

//Constructor for standard bezier that takes N degree and N+1 points for both x and y
BezierSpline::~BezierSpline()
{

}

vector<double> BezierSpline::calculateSplinePoint(double t)
{
	vector<double>point = piecewiseBeziers[(int)t].calculateBezierPoint(t-(double)((int)t));
	return point;
}

void BezierSpline::convertHeadingToSlope()
{
	for (int i = 0; i < headings.size(); i++)
	{
		if (headings[i] == 0.0)
			slopes.push_back(DBL_MAX-2000);
		else
			if (headings[i] == 180.0)
				slopes.push_back(DBL_MIN+2000);
		else
			slopes.push_back(1 / tan(headings[i] * PI / 180));
	}
}

void BezierSpline::generateCubicBezier()
{
	for (int i = 0; i < waypoints[0].size() - 1; i++) 
	{
		piecewiseBeziers.push_back(createCubicBezierSegment(waypoints[0][i], waypoints[1][i], waypoints[0][i+1], waypoints[1][i+1], slopes[i], slopes[i+1]));
		//cout << "Creating Cubic Bezier: " << endl << " x: " << waypoints[0][i] << endl << " y: " << waypoints[1][i] << endl << " x end: " << waypoints[0][i + 1] << endl << " y end: " << waypoints[1][i + 1] << endl << " slope: " << slopes[i] << endl << " slope end:" << slopes[i + 1] << endl;

	}
}

Bezier BezierSpline::createCubicBezierSegment(double startX, double startY, double endX, double endY, double ts, double te)
{
	cout << "STARTX: " << startX << endl;
	cout << "TS: " << ts << endl;
	cout << "TE: " << te << endl;
	cout << "ENDX: " << endX << endl;

	vector<double> x = { startX, (1.0/3.0)*1 + startX, endX - (1.0/3.0)*1, endX };
	vector<double> y = { startY, (1.0/3.0)*ts + startY, endY - (1.0/3.0)*te, endY };

	cout << "PO:" << startX << ", P1:" << (1.0 / 3.0)*1 + startX << ", P2:" << endX - (1.0 / 3.0)*1 << ", P3:" << endX << endl;
	cout << "PO:" << startY << ", P1:" << (1.0 / 3.0)*ts + startY << ", P2:" << endY - (1.0 / 3.0)*te << ", P3:" << endY << endl << endl;
	Bezier spline(x, y);
	return spline;
}
