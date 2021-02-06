#include "find_orthocenter.h" //inlcudes neccassry protoypes/preproccessors


/// <summary>
/// finds the orthcenter of triangle
/// </summary>
/// <param name="t"> pointer to triangle object </param>
void findOrthoCenter(Triangle* t)
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