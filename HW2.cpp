//============================================================================
// Title         :Euler Line Calculator
// Date          :2/8/2021
// Author        : HW2 Group 2
//		   Yousef Langi
//		   Justin Comer
// Email         : ylxrz@umsystem.edu
//		   mjcd4b@umsystem.edu
// Course #      : CS 4500
// Section #     : 001
// File          :https://github.com/mjcd4b/CS4500/blob/main/HW2.cpp
// Language      : C++
// External Files: <iostream>, <cmath>, <sstream>, <iomanip>
// Description   : This program takes in three user generated points and then 
// calculates the orthocenter, centroid and circumcenter. Using the orthocenter 
// and centroid this program also calculates the euler line if the input points 
// do not form an equilateral triangle. Finally, this program will calculate the 
// distance from the circumcenter to the euler line and a percentage error.
// Resources     :
// http://www.cplusplus.com/reference/algorithm/max/
// https://stackoverflow.com/questions/18971533/c-comparison-of-two-double-values-not-working-properly
// https://www.geeksforgeeks.org/difference-between-const-int-const-int-const-and-int-const/
//============================================================================

#include <iostream>
#include <cmath>
#include <sstream>
#include <iomanip>
using namespace std;

static const int SIZE = 2;

//declaration for Triangle class.
class Triangle
{
	private:
		double ELSlope;		//Euler Line slope
		double ELYIntercept;	//Euler Line Y intercept
		double ELLength;	//Length between orthocenter and centroid, used for calculating percError.
		double D;		//Distance between euler line and circumcenter
		double percError;	//percentage error
		double* p1 = nullptr;	//p1, p2, p3 are pointers to arrays that hold user input points for
		double* p2 = nullptr;	//triangle. In each array the first element is the x value, and the
		double* p3 = nullptr;	//second element is the y value. EX: p1[0] = x, p1[1] = y.
		double* ortho = nullptr;	//orthocenter 
		double* cent = nullptr;		//centroid
		double* circ = nullptr;		//circumcenter

	public:
		Triangle();
		~Triangle();
		void outputDescription();
		void get3Points(Triangle*);
		void errMessage();
		bool checkForNonRealNums(std::string);
		double stringToDouble(std::string);
		void insertCordinate(int pointNum, std::string var, double num);
		bool deterNonColinear(Triangle*);
		double calcDist(const double*, const double*);
		void findOrthoCenter(Triangle*);
		void findCentroid(Triangle*);
		void findCircumCenter(Triangle*);
		void lineFromPoints(const double*, const double*, double&, double&, double&);
		void perpendicularBisectorFromLine(const double*, const double*, double&, double&, double&);
		double* lineLineIntersection(double, double, double, double, double, double);
		void displayCenters();
		bool checkEquilateral(double);
		void eulerLineCalc();
		void outputEulerLine();
		void distanceEL();
		void calcPercentageError();
		void setP1(double*) const;
		void setP2(double*) const;
		void setP3(double*)const;
		void setOrthocenter(double*) const;
		void setCentroid(double*) const;
		void setCircumcenter(double* point);
		const double* getP1() const;
		const double* getP2() const;
		const double* getP3() const;
		const double* getOrthocenter() const;
		const double* getCentroid() const;
		const double* getCircumcenter() const;



};


//constructor, dynamically allocates memory for arrays each pointer is pointing to.
Triangle::Triangle(){
	ELSlope = 0;
	ELYIntercept = 0;
	D = 0;
	p1 = new double[SIZE];
	p2 = new double[SIZE];
	p3 = new double[SIZE];
	ortho = new double[SIZE];
	cent = new double[SIZE];
	circ = new double[SIZE];
}

//destructor, removes dynamically allocated memory.
Triangle::~Triangle(){
	delete [] p1;
	delete [] p2;
	delete [] p3;
	delete [] ortho;
	delete [] cent;
	delete [] circ;
}

//******************************************************************************
//outputDescription displays a description of what the progam does to the user *
//******************************************************************************
void Triangle::outputDescription(){
	cout << "This program takes in three user generated points and then calculates the\n"
			<< "orthocenter, centroid and circumcenter. Using the orthocenter and centroid\n"
			<< "this program also calculates the euler line if the input points do not form\n"
			<< "an equilateral triangle. Finally, this program will calculate the distance\n"
			<< "from the circumcenter to the euler line and a percentage error.\n\n";
}

/// <summary>
///Obtains 3 points from user, checks for Real Numbers, inserts points in object once validated
/// <summary>
/// <param name="t"> pointer for triangle object</param>
void Triangle::get3Points(Triangle* t)
{
	std::cout << "Please Enter 3 NON-COLINEAR Points(x,y) In A Cartesian Two dimensional Space\n";

	std::string n;
	double point;
	bool inValid;
	int pointNum = 0;

	do
	{
		pointNum++;

		do
		{
			std::cout << "\nPOINT " << pointNum << "|| " << "x: ";
			std::getline(std::cin, n);                             // do while loop, keeps looping until funtion call returns false, which would make input valid.
			inValid = checkForNonRealNums(n);
		}while (inValid);

		point = stringToDouble(n);
		t->insertCordinate(pointNum, "x", point);

		do
		{
			std::cout << "\nPOINT " << pointNum << "|| " << "y: ";
			std::getline(std::cin, n);							    // do while loop, keeps looping until funtion call returns false, which would make input valid.
			inValid = checkForNonRealNums(n);
		}while (inValid);

		point = stringToDouble(n);          // calls function that converts string to double inorder to insert points in object

		t->insertCordinate(pointNum, "y", point);

	}while (pointNum < 3); // stops until 3 points(x,y) have been inputed
}

//*************************************************
//errMessage displays a error message to the user *						   *
//*************************************************
void Triangle::errMessage()
{
	std::cout << "Error: POINTS MUST BE NON-COLINEAR REAL NUMBERS\n";
}

/// <summary>
/// Checks that only Real Numbers are accpeted
/// </summary>
/// <param name="n"> user input </param>
/// <returns> false if input is valid </returns>
bool Triangle::checkForNonRealNums(std::string n)
{
	int decimal = 0;
	int negative = 0;

	if (n.empty())
	{
		errMessage();		// checks if input is empty
		return true;
	}

	for (int x = 0; x < n.length(); x++) //loop through the input string to check for any user error
	{
		if (decimal == 2 || negative == 2) {
			errMessage();						// checks for more than 1 decimal or negative symbols
			return true;
		}

		if (n[x] == '.')
		{
			if (x == (n.length() - 1))
			{
				errMessage();
				return true;				// checks for decimal symbols
			}
			decimal++;
			continue;
		}
		else if (n[x] == '-')
		{
			if (x > 0 || x == (n.length() - 1))
			{
				errMessage();			   // checks for negative symbols
				return true;
			}
			negative++;
			continue;
		}
		else if (!isdigit(n[x]) || isspace(n[x]))
		{
			errMessage();				// checks for non-numbers or spaces
			return true;
		}
	}

	return false;
}

/// <summary>
/// converts userinut string to double using the <sstream> preproccessor
/// </summary>
/// <param name="s"> user input </param>
/// <returns> string as a number </returns>
double Triangle::stringToDouble(std::string s)
{
	std::stringstream convertToInt(s);
	double num;
	convertToInt >> num;

	return num;
}

//***********************************************************************
//insertCordinate inserts user coordinates into their respective arrays *
//***********************************************************************
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

/// <summary>
/// obtains the 3 points, then determines the distance between all 3 points, and determines if colinear or non-colinear
/// </summary>
/// <param name="t"> pointer for triangle object </param>
bool Triangle::deterNonColinear(Triangle* t)
{

	const double* p1 = t->getP1();
	const double* p2 = t->getP2();
	const double* p3 = t->getP3();

	double distP1P2 = calcDist(p1, p2);
	double distP2P3 = calcDist(p2, p3);
	double distP1P3 = calcDist(p1, p3);

	if ((distP1P2 + distP2P3) == distP1P3)
	{
		std::cout << "\nError: POINTS PROVIDED ARE COLINEAR, POINTS MUST BE NON-COLINEAR! PLEASE TRY AGAIN.\n";
		return false;
	}

	return true;
}

//********************************************************************************
//calcDist calculates the distance between two points using the distance formula *
//********************************************************************************
double Triangle::calcDist(const double* p1, const double* p2)
{
	return sqrt(pow(p2[0] - p1[0], 2) + pow(p2[1] - p1[1], 2)); //distance formula
}

/// <summary>
/// finds the orthcenter of triangle
/// </summary>
/// <param name="t"> pointer to triangle object </param>
void Triangle::findOrthoCenter(Triangle* t)
{
	const double* p1 = t->getP1();
	const double* p2 = t->getP2();
	const double* p3 = t->getP3();

    // gets values x,y for point4
    double perpY = -p2[0] + p1[0];
    double perpX = p2[1] - p1[1];

    double y2 = perpY + p3[1];
    double x2 = perpX + p3[0];
    // gets values x,y for point4

    double p4[2] = { x2, y2 };


    // gets values x,y for point5
    perpY = -p3[0] + p2[0];
    perpX = p3[1] - p2[1];

    double y3 = perpY + p1[1];
    double x3 = perpX + p1[0];
     // gets values x,y for point5

    double p5[2] = { x3, y3 };


    // Line P3P4 represented as a1x + b1y = c1
    double a1 = p4[1] - p3[1];
    double b1 = p3[0] - p4[0];
    double c1 = a1 * (p3[0]) + b1 * (p3[1]);
    // Line P3P4 represented as a1x + b1y = c1


    // Line P1P5 represented as a2x + b2y = c2
    double a2 = p5[1] - p1[1];
    double b2 = p1[0] - p5[0];
    double c2 = a2 * (p1[0]) + b2 * (p1[1]);
    // Line P1P5 represented as a2x + b2y = c2

    double determinant = a1 * b2 - a2 * b1;

    double x = (b2 * c1 - b1 * c2) / determinant;  // gets values x,y for orthocenter
    double y = (a1 * c2 - a2 * c1) / determinant;

    double orthoCenter[2] = { x ,y };

    t->setOrthocenter(orthoCenter);

}

//******************************************************
//findCentroid calculates the position of the centroid *
//******************************************************
void Triangle::findCentroid(Triangle* t)
{
	const double* p1 = t->getP1();
	const double* p2 = t->getP2();
	const double* p3 = t->getP3();

	double x = (p1[0] + p2[0] + p3[0]) / 3; // calculates x,y for centriod
	double y = (p1[1] + p2[1] + p3[1]) / 3;

	double centroid[2] = { x, y };

	t->setCentroid(centroid);

}

/// <summary>
/// finds circumcenter of triangle
/// </summary>
/// <param name="t"> pointer to triangle object </param>
void Triangle::findCircumCenter(Triangle* t)
{
    const double* p1 = t->getP1();
    const double* p2 = t->getP2();
    const double* p3 = t->getP3();

    // Line p1p2 is represented as ax + by = c
    double a, b, c;
    lineFromPoints(p1, p2, a, b, c);

    // Line p2p3 is represented as ex + fy = g
    double e, f, g;
    lineFromPoints(p2, p3, e, f, g);

    // Converting lines p1p2 and p2p3 to perpendicular bisectors. After this, L = ax + by = c,  M = ex + fy = g
    perpendicularBisectorFromLine(p1, p2, a, b, c);
    perpendicularBisectorFromLine(p2, p3, e, f, g);

    // The point of intersection of L and M gives the circumcenter
    double* circumCenter = lineLineIntersection(a, b, c, e, f, g);

    t->setCircumcenter(circumCenter);
}

// Function to find the line given two points
void Triangle::lineFromPoints(const double* p1, const double* p2, double &a, double &b, double &c)
{
    a = p2[1] - p1[1];
    b = p1[0] - p2[0];
    c = (a * p1[0]) + (b * p1[1]);
}

// Function which converts the input line to its
// perpendicular bisector. It also inputs the points
// whose mid-point lies on the bisector
void Triangle::perpendicularBisectorFromLine(const double* p1, const double* p2, double& a, double& b, double& c)
{

    double x = (p1[0] + p2[0]) / 2;
    double y = (p1[1] + p2[1]) / 2;
    double midPoint[2] = {x, y};

    // c = -bx + ay
    c = (-b * midPoint[0]) + (a * midPoint[1]);

    double temp = a;
    a = -b;
    b = temp;
}

// Returns the intersection point of two lines
double* Triangle::lineLineIntersection(double a1, double b1, double c1, double a2, double b2, double c2)
{
    double determinant = a1 * b2 - a2 * b1;

    double x = ((b2 * c1) - (b1 * c2)) / determinant;
    double y = ((a1 * c2) - (a2 * c1)) / determinant;

    static double cir[2] = { x, y };


    return cir;
}

//***********************************************************************************************
//displayCenters displays the traingles orthocenter, centroid, and circcumcenter to the console *
//***********************************************************************************************
void Triangle::displayCenters(){
		cout << "\nOrthocenter: ( " << ortho[0] << " , " << ortho[1] << " )\n";
		cout << "Centroid: ( " << cent[0] << " , " << cent[1] << " )\n";
		cout << "Circumcenter: ( " << circ[0] << " , " << circ[1] << " )\n";
}


//***********************************************************************************************
//checkEquilateral checks whether the triangle is equilateral by comparing the distances of the *
//centers to epsilon which is an assigned small quantity.					*
//***********************************************************************************************
bool Triangle::checkEquilateral(double epsilon = 0.01){
	double d1 = sqrt(pow(ortho[0]-cent[0], 2)+ pow(ortho[1]-cent[1], 2));
	double d2 = sqrt(pow(ortho[0]-circ[0], 2)+ pow(ortho[1]-circ[1], 2));
	double d3 = sqrt(pow(circ[0]-cent[0], 2)+ pow(circ[1]-cent[1], 2));

	if(d1 < epsilon){
		if(d2 < epsilon){
			if(d3 < epsilon){
				cout << "The input points create an equilateral triangle" << endl;
				cout << "The largest distance between centers is: " << max(d1, max(d2, d3)) << endl;
				return true;
			}
		}
	}

	return false;
}

//***********************************************************************************************
//eulerLineCalc calculates the slope, yintercept and length of the Euler Line for slope 	*
//intercept form: y = mx + b.									*
//***********************************************************************************************
void Triangle::eulerLineCalc(){
	//calculate slope: m = (y1 - y2) / (x1 - x2)
	ELSlope = (ortho[1] - cent[1]) / (ortho[0] - cent[0]);
	//calc y intercept: b = (m * -x1) +y 1
	ELYIntercept = (ELSlope * -cent[0]) + cent[1];
	////calculate length using distance formula
	ELLength = sqrt(pow(ortho[0] - cent[0], 2) + pow(ortho[1] - cent[1], 2));
}

//********************************************************************
// outputEulerLine displays the Euler line in slope intercept form.  *
//********************************************************************
void Triangle::outputEulerLine(){

	//conditional that tests the slope of the Euler line in order to determine if
	//it is vertical, horizontal, or neither.
	if(ELSlope == 0){ 
		cout << "Euler Line: Y = " << ELYIntercept << endl;
	}
	else if (isinf(ELSlope)){
		cout << "Euler Line: X = " << ortho[0] << endl;
	}
	else {
		cout << "Euler Line: Y = " << ELSlope << "X + ( " << ELYIntercept << " )" << endl;
	}

}


//*********************************************************************************
// distanceEL calculates D, the distance between the euler line and circumcenter. *
//*********************************************************************************
void Triangle::distanceEL(){

	double pSlope;
	double pYInt;
	double inter[2];
	
	//conditional that tests the slope of the Euler line in order to determine if
	//it is vertical, horizontal, or neither.
	if (ELSlope == 0){	//If the EL is horizontal...
		
		//D = |y1 - y2| where we use the y values from circumcenter and orthocenter.
		//Orthocenter because it was used to calculate euler line
		D = abs(circ[1] - ortho[1]);
	}
	else if (isinf(ELSlope)){	//If the EL is vertical...
		
		//D = |x1 - x2| where we use the x values from circumcenter and orthocenter.
		D = abs(circ[0] - ortho[0]);
	}
	else{ 	//Other lines
		
		//calculated slope for perpendicular line: m2 = -1/m1
		pSlope = -1/ELSlope;
		//calc y intercept: b = (m * -x1) + y1
		pYInt = -circ[0] * pSlope + circ[1];

		//point of intercept between EL and perpendicular line used to calculating distance.
		// xvalue = (b2 - b1) / (m1 - m2)
		inter[0] = (pYInt -ELYIntercept) / (ELSlope - pSlope);
		// yvalue = m * xvalue + b
		inter[1] = pSlope * inter[0] + pYInt;

		//D = distance between circumcenter and point of intersection between EL and
		//line perpendiculr to EL that goes through circumcenter.
		D = sqrt(pow(circ[0] - inter[0], 2) + pow(circ[1] - inter[1], 2));
	}



	cout << fixed << "D: " << D << endl;
}

//*********************************************************************************
// calcPercentageError calculates the percentage error.	  			  *
//*********************************************************************************
void Triangle::calcPercentageError(){
	percError = (D / ELLength) * 100;
	cout << "Percentage Error: %" << setprecision(2) << fixed << percError << endl;
}

//***************
//setter for p1 *
//***************
void Triangle::setP1(double* point) const{
	for(int i = 0; i < SIZE; i++){
		p1[i] = point[i];
	}
}

//***************
//setter for p2 *
//***************
void Triangle::setP2(double* point) const{
	for(int i = 0; i < SIZE; i++){
		p2[i] = point[i];
	}
}

//***************
//setter for p3 *
//***************
void Triangle::setP3(double* point) const{
	for(int i = 0; i < SIZE; i++){
		p3[i] = point[i];
	}
}

//************************
//setter for orthocenter *
//************************
void Triangle::setOrthocenter(double* point) const{
	for(int i = 0; i < SIZE; i++){
		ortho[i] = point[i];
	}
}

//*********************
//setter for centroid *
//*********************
void Triangle::setCentroid(double* point) const{
	for(int i = 0; i < SIZE; i++){
		cent[i] = point[i];
	}
}

//*************************
//setter for circumcenter *
//*************************
void Triangle::setCircumcenter(double* point){
	for(int i = 0; i < SIZE; i++){
		circ[i] = point[i];
	}
}

//***************
//getter for p1 *
//***************
const double* Triangle::getP1() const{
	return p1;
}

//***************
//getter for p2 *
//***************
const double* Triangle::getP2() const{
	return p2;
}

//***************
//getter for p3 *
//***************
const double* Triangle::getP3() const{
	return p3;
}

//************************
//getter for orthocenter *
//************************
const double* Triangle::getOrthocenter() const{
	return ortho;
}


//*********************
//getter for centroid *
//*********************
const double* Triangle::getCentroid() const{
	return cent;
}

//*************************
//getter for circumcenter *
//*************************
const double* Triangle::getCircumcenter() const{
	return circ;
}

int main(){

	Triangle t;
	t.outputDescription();
	t.get3Points(&t);
	if(!t.deterNonColinear(&t))
	{
		std::cout << "\nPress ENTER to exit.\n";
		cin.ignore();
		return 0;
	}
	t.findOrthoCenter(&t);
	t.findCentroid(&t);
	t.findCircumCenter(&t);
	t.displayCenters();
	if(t.checkEquilateral()){
		cout << "Press ENTER to exit program";
		cin.ignore();
		return 0;
	}
	t.eulerLineCalc();
	t.outputEulerLine();
	t.distanceEL();
	t.calcPercentageError();
	cout << "Press ENTER to exit program";
	cin.ignore();

	return 0;
}
