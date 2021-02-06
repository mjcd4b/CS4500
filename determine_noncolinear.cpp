#include "determine_nonColinear.h" //inlcudes neccassry protoypes/preproccessors

/// <summary>
/// obtains the 3 points, then determines the distance between all 3 points, and determines if colinear or non-colinear 
/// </summary>
/// <param name="t"> pointer for triangle object </param>
void deterNonColinear(Triangle* t)
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

double calcDist(const double* p1, const double* p2)
{
	return sqrt(pow(p2[0] - p1[0], 2) + pow(p2[1] - p1[1], 2)); //distance formula
}