#pragma once
#include <vector>
#include "Bezier.h"

using namespace std;

/*Generic spline class to construct splines of given type, composed of piecewise segments*/

class Spline 
{
public:
	Spline(vector<vector<double>> waypoints); //Initialize with a list of defined waypoints
	~Spline();


	//TODO: organize splines and classes into proper inherited structure
	//Include different methods to generate respective splines?

	void generateQuinticBezier(); //Generates a spline of piecewise quintic beziers to be stored in bezierSpline


private:
	vector<vector<double>> waypoints;

	vector<Bezier> bezierSpline; //Stores beziers generated for future reference

	//Helper method to create a single bezier segment to store in bezierSpline, called multiple times by generateQuinticBezier
	//Currently also needs explicit first and second derivative at start (ts and as), first and second derivatice at end (te and ae)
	Bezier createQuinticBezierSegment(double startPoint, double endPoint, double ts, double as, double te, double ae); 
};