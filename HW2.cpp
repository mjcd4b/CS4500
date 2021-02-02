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

class Triangle
{
	private:
		static const int SIZE = 2;
		double* p1;
		double* p2;
		double* p3;
		double* orthocenter;
		double* centroid;
		double* circumcenter;

	public:
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

void Triangle::setP1(double* point){
	for(int i = 0; i < SIZE; i++){
		p1[i] = point[i];
	}
}

void Triangle::setP2(double* point){
	for(int i = 0; i < SIZE; i++){
		p2[i] = point[i];
	}
}

void Triangle::setP3(double* point){
	for(int i = 0; i < SIZE; i++){
		p3[i] = point[i];
	}
}

void Triangle::setOrthocenter(double* point){
	for(int i = 0; i < SIZE; i++){
		orthocenter[i] = point[i];
	}
}


void Triangle::setCentroid(double* point){
	for(int i = 0; i < SIZE; i++){
		centroid[i] = point[i];
	}
}

void Triangle::setCircumcenter(double* point){
	for(int i = 0; i < SIZE; i++){
		circumcenter[i] = point[i];
	}
}

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
