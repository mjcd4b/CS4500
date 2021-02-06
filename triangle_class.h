#pragma once
#include <iostream>
#include <string>
class Triangle
{
	static const int SIZE = 2;

private:
	double* p1;
	double* p2;
	double* p3;
	double* orthocenter;
	double* centroid;
	double* circumcenter;
	
public:
	Triangle();
	~Triangle();
	void insertCordinate(int,std::string, double);
	const double* getP1() const;
	const double* getP2() const;
	const double* getP3() const;
	void setOrthocenter(double*) const;
	void setCentroid(double*) const;
	void setCircumcenter(double*);
	const double* getOrthocenter() const;
	const double* getCentroid() const;
	const double* getCircumcenter() const;
};

