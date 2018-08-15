#pragma once
#include <vector>

using namespace std;
class Bezier
{
	public:
			Bezier(int degree); //Instantiates a Bezier of degree deg
			Bezier(vector<double> *x, vector<double> *y, int degree); //Instantiates a Bezier of degree deg with (x,y) control points
			~Bezier();


			vector<vector<double>> ctrlPoints;

			
			vector<vector<double>> multiply(vector<vector<double>> &a, vector<vector<double>> &b);

			

		
			int factorial(int n); //Returns factorial of number n
			void printMatrix(vector<vector<double>> &a);
	private:
			//Basis functions for bernstein polynomials
			
			vector<vector<double>> bernstein3 = {
												{1, 0, 0, 0}, 
												{-3, 3, 0, 0}, 
												{3, -6, 3, 0},
												{1, 3, -3, 1}
												};

			//Matrix helper methods
			int binomial(int n, int k); //nCk, Optimized binomial method using pascals - will default to factorial definition if out of scope
			int degree; //Stores the degree of the Bezier
			
			



	
};

