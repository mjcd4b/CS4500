#include "main_function_headers.h" // neccassry headers to run program 

/// <summary>
/// gets 3 points from user, determines if points are non-colinear,
/// then finds the orthocenter, centriod, and circumcenter.
/// </summary>
/// <returns>0</returns>
int main()
{
	Triangle* triangle = new Triangle(); // creating new triangle object

	get3Points(triangle);
	deterNonColinear(triangle);
	findOrthoCenter(triangle);
	findCentroid(triangle);
	findCircumCenter(triangle);

	return 0;
}
