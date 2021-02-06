#include "triangle_class.h"

Triangle::Triangle()
{
	p1 = new double[SIZE];
	p2 = new double[SIZE];
	p3 = new double[SIZE];
	orthocenter = new double[SIZE];
	centroid = new double[SIZE];
	circumcenter = new double[SIZE];
}

Triangle::~Triangle() {
	delete[] p1;
	delete[] p2;
	delete[] p3;
	delete[] orthocenter;
	delete[] centroid;
	delete[] circumcenter;
}

void Triangle::insertCordinate(int pointNum, std::string var, double num)
{
	if (pointNum == 1)
	{
		if (var == "x")
		{
			p1[0] = num;
		}
		else if (var == "y")
		{
			p1[1] = num;
		}
	}
	else if (pointNum == 2)
	{
		if (var == "x")
		{
			p2[0] = num;
		}
		else if (var == "y")
		{
			p2[1] = num;
		}
	}
	else if (pointNum == 3)
	{
		if (var == "x")
		{
			p3[0] = num;
		}
		else if (var == "y")
		{
			p3[1] = num;
		}
	}
}

const double* Triangle::getP1() const {
	return p1;
}

const double* Triangle::getP2() const {
	return p2;
}

const double* Triangle::getP3() const {
	return p3;
}

void Triangle::setOrthocenter(double* point) const {
	for (int i = 0; i < SIZE; i++) {
		orthocenter[i] = point[i];
	}
}

void Triangle::setCentroid(double* point) const {
	for (int i = 0; i < SIZE; i++) {
		centroid[i] = point[i];
	}
}

void Triangle::setCircumcenter(double* point) {
	for (int i = 0; i < SIZE; i++) {
		circumcenter[i] = point[i];
	}
}

const double* Triangle::getOrthocenter() const {
	return orthocenter;
}


const double* Triangle::getCentroid() const {
	return centroid;
}

const double* Triangle::getCircumcenter() const {
	return circumcenter;
}