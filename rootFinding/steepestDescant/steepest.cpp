/*
 * =====================================================================================
 *
 *       Filename:  steepest.cpp
 *
 *    Description:  Root finding implement by steepest descant method
 *
 *        Version:  1.0
 *        Created:  11/25/16 00:13:35
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ada Kaminkure (AdaCode), ada@adacode.io
 *        Company:  ADACODE.IO
 *
 * =====================================================================================
 */

#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <iomanip>
#include "stdio.h"

using namespace std;

double f(double x[], int n);
double partial(double x[], int pos);
double grad(double x[], int n);
double norm(double x[], int n);

double f(double x[], int n)
{
	double a, b, c;
	a = 4*x[0]*x[0];
	b = 4*x[0]*x[1];
	c = 2*x[1]*x[1];
	return a-b+c;
}

double partial(double x[], int pos, int n)
{
	double temp[n], h;
	int i;
	h = 0.000001;
	for(i=0;i<n;i++)
	{
		if( i == pos)
			temp[i] = x[i]+h;
		else
			temp[i] = x[i];
	}

	return (f(temp,n)-f(x,n))/h;
}

double grad(double x[], int n)
{
	double result;
	int i;

	result = 0;

	for(i=0;i<n;i++)
	{
		result = result + partial(x, i, n);	
	}

	return result;
}

double norm(double x[], int n)
{
	double p[n], sum;
	int i;
	sum = 0;

	for(i=0;i<n;i++)
	{
		p[i] = pow(partial(x, i, n), 2);
		sum = sum + p[i];
	}

	return sqrt(sum); 
}

double * u_vector(double x[], int n)
{
	static double temp[10];
	double myNorm;
	int i;
	
	myNorm = norm(x, n);

	for(i=0;i<n;i++)
	{
		temp[i] = (-1)*partial(x, i, n)/myNorm;
	}
	return temp;
}

double steepest(double x[], double *u, int n, double t)
{	
	double x1[n];
	int i;

	for(i=0;i<n;i++)
	{
		x1[i] = x[i]+t*(*(u+i));
	}
	return f(x1, n);
}

int main ()
{
	double x0[] = {2, 3}, *u, t;
	int index;
	string line;

	ofstream resultFile;
	resultFile.open("result/steepest.txt");
	u = u_vector(x0,2);
	index = 0;
	
	printf("-------------------------------------------------\n");	
	printf("|\tIndex\t|\tt\t|\tf(x1)\t|\n");
	printf("-------------------------------------------------\n");	

	// Write to FILE HEADER	
		line = "-------------------------------------------------\n";	
		line += "|\tIndex\t|\tt\t|\tf(x1)\t|\n";
		line += "-------------------------------------------------";	
		resultFile << line << endl;
	//END FILE HEADER
	
	for(t=0;t<5;t=t+0.1)
	{
		if( steepest(x0, u, 2, t) == 0 )
			break;
		printf("|\t%d\t|\t%.2f\t",index,t);
		printf("|\t%.3f\t|\n",steepest(x0, u, 2, t));

		resultFile << setprecision(3) << "|\t" << index << "\t|\t" << t << "\t";
		resultFile << setprecision(4) << "|\t" << steepest(x0, u, 2, t) << " \t|" << endl;
		index++;
	}
	resultFile.close();
	return 0;
}


