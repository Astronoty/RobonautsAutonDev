#pragma once
#include <vector>
#include "Bezier.h"

using namespace std;

/*Generic spline class to construct splines of given type, composed of piecewise segments*/

class BezierSpline 
{
public:
	BezierSpline(vector<vector<double>> waypoints, vector<double> headings); //Initialize with a list of defined waypoints
	~BezierSpline();


	//TODO: organize splines and classes into proper inherited structure
	//Include different methods to generate respective splines?

	//First and second derivative at start(ts and as), first and second derivatice at end(te and ae)
	void generateCubicBezier(); //Generates a spline of piecewise quintic beziers to be stored in bezierSpline


	//If you have n curves in the spline, give a value from 0 - n ... (ex. 1.5 would be calling t=0.5 for the second curve)
	vector<double> calculateSplinePoint(double t); 


private:
	vector<vector<double>> waypoints;
	vector<double>headings; //Value from 0-360 degrees (heading as understood by robot)
	vector<double> slopes; //Headings converted to numerical slope (as understood by interpolation technique)

	vector<Bezier> piecewiseBeziers; //Stores bezier curves generated for future reference

	//Helper method to create a single bezier segment to store in bezierSpline, called multiple times by generateQuinticBezier
	
	//Currently also needs explicit first derivative at start and end point(ts and te) - ts and te denote in slope form, whereas the constructor takes an array of headings
	void convertHeadingToSlope();
	Bezier createCubicBezierSegment(double startX, double startY, double endX, double endY, double ts, double te);
};