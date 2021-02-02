//============================================================================
// Title         :
// Date          :
// Author        : Yousef Langi
//		   Justin Comer
// Email         : 
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
using namespace std;

//Triangle class
class Triangle
{
	private:
		static const int SIZE = 2; //size of arrays for coordinates
		
		//These pointers are used to point to arrays that hold the coordinates of all the points.
		//p1, p2, p3 are all angles of the triangle that the user will in out, and orthocenter,
		//centroid, and circumcenter are all what the names say.
		double* p1;
		double* p2;
		double* p3;
		double* orthocenter;
		double* centroid;
		double* circumcenter;

	public:
		//File headers including for constructor and destructor.
		Triangle();
		~Triangle();
		void setP1(double*);
		void setP2(double*);
		void setP3(double*);
		void setOrthocenter(double*);
		void setCentroid(double*);
		void setCircumcenter(double*);
		double* getP1() const;
		const double* getP2() const;
		const double* getP3() const;
		const double* getOrthocenter() const;
		const double* getCentroid() const;
		const double* getCircumcenter() const;

};

//constructor, dynamically allocates memory for arrays each pointer is pointing to.
Triangle::Triangle(){
	p1 = new double[SIZE];
	p2 = new double[SIZE];
	p3 = new double[SIZE];
	orthocenter = new double[SIZE];
	centroid = new double[SIZE];
	circumcenter = new double[SIZE];
}

//destructor, removes dynamically allocated memory.
Triangle::~Triangle(){
	delete [] p1;
	delete [] p2;
	delete [] p3;
	delete [] orthocenter;
	delete [] centroid;
	delete [] circumcenter;
}

//setter for p1, assigns the passed pointer to p1
void Triangle::setP1(double* point){
	p1 = point;
}

void Triangle::setP2(double* point){
	p2 = point;
}

void Triangle::setP3(double* point){
	p3 = point;
}

void Triangle::setOrthocenter(double* point){
	orthocenter = point;
}


void Triangle::setCentroid(double* point){
	centroid = point;
}

void Triangle::setCircumcenter(double* point){
	circumcenter = point;
}

//getter, returns the memory location stored in p1
double* Triangle::getP1() const{
	return p1;
}

const double* Triangle::getP2() const{
	return p2;
}

const double* Triangle::getP3() const{
	return p3;
}

const double* Triangle::getOrthocenter() const{
	return orthocenter;
}


const double* Triangle::getCentroid() const{
	return centroid;
}

const double* Triangle::getCircumcenter() const{
	return circumcenter;
}

int main(){

	double point1[2] = {2,2};
	double* point2;
	Triangle t;

	t.setP1(point1);
	point2 = t.getP1();
	cout << *point2 << ", " << *(point2 + 1) << endl;

	return 0;
}
