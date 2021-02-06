#pragma once
#include <iostream>
#include "triangle_class.h" // for configuring triangle object 
#include <sstream> // used for string to double convertion

//function prototypes//
void get3Points(Triangle*);
void errMessage();
bool checkForNonRealNums(std::string);
double stringToDouble(std::string);
//function prototypes//