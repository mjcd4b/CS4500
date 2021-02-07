//============================================================================
// Title         :
// Date          :
// Author        : Yousef Langi
//		   Justin Comer
// Email         : ylxrz@umsystem.edu
//		   mjcd4b@umsystem.edu
// Course #      : CS 4500
// Section #     : 001
// File          :
// Language      : C++
// External Files:
// Description   :
// Resources     :
//============================================================================

#include <iostream>
#include <cmath>
#include <sstream>
using namespace std;

static const int SIZE = 2;

class Triangle
{
	private:
		double ELSlope;
		double ELYIntercept;
		double ELLength;
		double D;
		double percError;
		double* p1 = nullptr;
		double* p2 = nullptr;
		double* p3 = nullptr;
		double* ortho = nullptr;
		double* cent = nullptr;
		double* circ = nullptr;

	public:
		Triangle();
		~Triangle();
		void get3Points(Triangle*);
		void errMessage();
		bool checkForNonRealNums(std::string);
		double stringToDouble(std::string);
		void insertCordinate(int pointNum, std::string var, double num);
		void deterNonColinear(Triangle*);
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

/// <summary>
/// obtains 3 points from user, checks for Real Numbers, inserts points in object once validated
/// </summary>
/// <param name="t"> pointer for triangle object</param>
void Triangle::get3Points(Triangle* t)
{
	std::cout << "Hello Please Enter 3 NON-COLINEAR Points(x,y) In A Cartesian Two dimensional Space\n";

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
void Triangle::deterNonColinear(Triangle* t)
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
		std::cout << "\nPress ENTER to exit.\n";
		std::string n;
		std::getline(std::cin, n);
		if (n == "\n")
		{
			exit(0);
		}
	}
}

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

//Displays calculated centers to console.
void Triangle::displayCenters(){
		cout << "Orthocenter: ( " << ortho[0] << " , " << ortho[1] << " )\n";
		cout << "Centroid: ( " << cent[0] << " , " << cent[1] << " )\n";
		cout << "Circumcenter: ( " << circ[0] << " , " << circ[1] << " )\n";
}

//checks whether the triangle is equilateral by comparing the distances of the centers to
//epsilon which is an assigned small quantity. 
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

//calculates the slope, yintercept and length of the Euler Line.
void Triangle::eulerLineCalc(){
	ELSlope = (ortho[1] - cent[1]) / (ortho[0] - cent[0]);
	ELYIntercept = cent[1] - (ELSlope * cent[0]);
	ELLength = sqrt(pow(ortho[0] - cent[0], 2) + pow(ortho[1] - cent[1], 2));
}

//Display Euler line in slope intercept form.
void Triangle::outputEulerLine(){
	cout << "Euler Line: Y = " << ELSlope << "X + ( " << ELYIntercept << " )" << endl;
}


//Calculates D, the distance between the euler line and circumcenter.
void Triangle::distanceEL(){
	
	//The equation used is |Ax + By + C| / sqrt(A^2 + B^2)
	//The x and y value are the circumcenter and B = 1 in all cases since
	//converting from slope intercept to standard form.
	double top = abs((-ELSlope * circ[0]) + (circ[1]) + (-ELYIntercept));
	double bottom = sqrt(pow(-ELSlope, 2) + 1);

	cout << top << " " << bottom << endl;

	D = top / bottom;

	cout << "D: " << D;
}

void Triangle::calcPercentageError(){
	percError = D / ELLength;
}

//setter that allows user to change contents of array but not memory location the user is
//pointing to.
void Triangle::setP1(double* point) const{
	for(int i = 0; i < SIZE; i++){
		p1[i] = point[i];
	}
}

void Triangle::setP2(double* point) const{
	for(int i = 0; i < SIZE; i++){
		p2[i] = point[i];
	}
}

void Triangle::setP3(double* point) const{
	for(int i = 0; i < SIZE; i++){
		p3[i] = point[i];
	}
}

void Triangle::setOrthocenter(double* point) const{
	for(int i = 0; i < SIZE; i++){
		ortho[i] = point[i];
	}
}


void Triangle::setCentroid(double* point) const{
	for(int i = 0; i < SIZE; i++){
		cent[i] = point[i];
	}
}

void Triangle::setCircumcenter(double* point){
	for(int i = 0; i < SIZE; i++){
		circ[i] = point[i];
	}
}

//getter for p1 which returns the memory location that p1 is pointing at.
const double* Triangle::getP1() const{
	return p1;
}

const double* Triangle::getP2() const{
	return p2;
}

const double* Triangle::getP3() const{
	return p3;
}

const double* Triangle::getOrthocenter() const{
	return ortho;
}


const double* Triangle::getCentroid() const{
	return cent;
}

const double* Triangle::getCircumcenter() const{
	return circ;
}

int main(){

	Triangle t;
	t.get3Points(&t);
	t.deterNonColinear(&t);
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


	return 0;
}
