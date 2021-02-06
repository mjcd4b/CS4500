#include "find_centroid.h" //inlcudes neccassry protoypes/preproccessors


/// <summary>
/// finds centriod of triangle
/// </summary>
/// <param name="t"> pointer for triangle object </param>
void findCentroid(Triangle* t)
{
	const double* p1 = t->getP1();
	const double* p2 = t->getP2();
	const double* p3 = t->getP3();

	double x = (p1[0] + p2[0] + p3[0]) / 3; // calculates x,y for centriod 
	double y = (p1[1] + p2[1] + p3[1]) / 3;

	double centroid[2] = { x, y };

	t->setCentroid(centroid);

}