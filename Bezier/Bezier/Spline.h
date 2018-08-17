#pragma once
#include <vector>
#include "Bezier.h"

using namespace std;

class Spline 
{

	/*The wrapper class for a list of Bezier curves
	Functionality includes:
	1st derivative checking at intersection points
	2nd derivative checking at intersection points
	Manipulation of points while maintaining localism*/

	Spline(vector<Bezier> curves); //Initialize with a list of defined bezier curves


};