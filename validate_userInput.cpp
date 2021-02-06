#include "validate_userInput.h" //inlcudes neccassry protoypes/preproccessors


/// <summary>
/// obtains 3 points from user, checks for Real Numbers, inserts points in object once validated
/// </summary>
/// <param name="t"> pointer for triangle object</param>
void get3Points(Triangle* t)
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

void errMessage()
{
	std::cout << "Error: POINTS MUST BE NON-COLINEAR REAL NUMBERS\n";
}

/// <summary>
/// Checks that only Real Numbers are accpeted
/// </summary>
/// <param name="n"> user input </param>
/// <returns> false if input is valid </returns>
bool checkForNonRealNums(std::string n)
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
double stringToDouble(std::string s)
{
	std::stringstream convertToInt(s);
	double num;
	convertToInt >> num;

	return num;
}
