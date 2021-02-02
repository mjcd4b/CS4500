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
using namespace std;

static const int SIZE = 2;

class Triangle
{
	private:
		double* p1 = nullptr;
		double* p2 = nullptr;
		double* p3 = nullptr;
		double* orthocenter = nullptr;
		double* centroid = nullptr;
		double* circumcenter = nullptr;

	public:
		Triangle();
		~Triangle();
		void setP1(double*) const;
		void setP2(double*) const;
		void setP3(double*)const;
		void setOrthocenter(double*) const;
		void setCentroid(double*) const;
		void setCircumcenter(double*);
		const double* getP1() const;
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
		orthocenter[i] = point[i];
	}
}


void Triangle::setCentroid(double* point) const{
	for(int i = 0; i < SIZE; i++){
		centroid[i] = point[i];
	}
}

void Triangle::setCircumcenter(double* point){
	for(int i = 0; i < SIZE; i++){
		circumcenter[i] = point[i];
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
	return orthocenter;
}


const double* Triangle::getCentroid() const{
	return centroid;
}

const double* Triangle::getCircumcenter() const{
	return circumcenter;
}

int main(){

	//These current contents in main just serve as an example of how the pointers, and functions in
	//Triangle currently work and are meant to be used as a point of reference.
	//They can be removed at any time.

	//arrays
	double arr1[SIZE] = {1,2};
	double arr2[SIZE];

	//pointer, uses const so it cant change the contents of the array being pointed to
	const double *point = nullptr;

	//create triangle object t
	Triangle t;

	//call setter using arr1 as pointer.
	t.setP1(arr1);


	//user getter to return memory location for p1. Once point is pointing to the same
	//memory location as p1 it will keep doing so until changed.
	point = t.getP1();

	//assign values from array point is pointing to arr2
	for(int i = 0; i < SIZE; i++){
		arr2[i] = point[i];
	}

	//arr2 should contain the same values as the array point points to.
	cout << "arr2 contains: " << arr2[0] << ", " << arr2[1] << endl;
	cout << "point contains: " << point[0] << ", " << point[1] << endl;

	//reassign arr1 in order to test.
	arr1[0] = 4;
	arr1[1] = 5;

	//set values in p1 array.
	t.setP1(arr1);

	//arr2 should contain 1,2, point should contain 4,5 or whatever is currently stored in p1
	cout << "arr2 contains: " << arr2[0] << ", " << arr2[1] << endl;
	cout << "point contains: " << point[0] << ", " << point[1] << endl;

	return 0;
}
