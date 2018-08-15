#pragma once
#include <vector>
#include <cmath>

using namespace std;
class Bezier
{
public:
	Bezier(int degree); //Instantiates a Bezier of degree deg
	Bezier(vector<double> &x, vector<double> &y, int degree); //Instantiates a Bezier of degree deg with (x,y) control points
	~Bezier();


	vector<double> calculateBezierPoint(double t);

	void printMatrix(vector<vector<double>> &a);
private:
	vector<vector<double>> bernsteinBasis;
	vector<vector<double>> tMatrix;

	void setBernsteinBasis(int degree);
	int degree; //Stores the degree of the Bezier
	vector<vector<double>> xPoints;
	vector<vector<double>> yPoints;


	//Matrix helper methods
	vector<vector<double>> multiply(vector<vector<double>> &a, vector<vector<double>> &b);
	int binomial(int n, int k); //nCk, Optimized binomial method using pascals - will default to factorial definition if out of scope
	int factorial(int n); //Returns factorial of number n






};

