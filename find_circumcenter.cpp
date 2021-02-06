#include "find_circumcenter.h" //inlcudes neccassry protoypes/preproccessors


/// <summary>
/// finds circumcenter of triangle
/// </summary>
/// <param name="t"> pointer to triangle object </param>
void findCircumCenter(Triangle* t)
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
void lineFromPoints(const double* p1, const double* p2, double &a, double &b, double &c)
{
    a = p2[1] - p1[1];
    b = p1[0] - p2[0];
    c = (a * p1[0]) + (b * p1[1]);
}

// Function which converts the input line to its
// perpendicular bisector. It also inputs the points
// whose mid-point lies on the bisector
void perpendicularBisectorFromLine(const double* p1, const double* p2, double& a, double& b, double& c)
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
double* lineLineIntersection(double a1, double b1, double c1, double a2, double b2, double c2)
{
    double determinant = a1 * b2 - a2 * b1;

    double x = ((b2 * c1) - (b1 * c2)) / determinant;
    double y = ((a1 * c2) - (a2 * c1)) / determinant;

    static double cir[2] = { x, y };
    

    return cir;
}