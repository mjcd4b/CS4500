#pragma once
#include "triangle_class.h" // for configuring triangle object 

//function prototypes//
void findCircumCenter(Triangle*);
void lineFromPoints(const double*, const double*, double&, double&, double&);
void perpendicularBisectorFromLine(const double*, const double*, double&, double&, double&);
double* lineLineIntersection(double, double, double, double, double, double);
//function prototypes//