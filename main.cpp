#include <iostream>

#include "Automat.h"

int main()
{
	Automat automat;
	automat.loadFromFile("test1.txt");
	automat.isAcceptably("m/b-0/!0");
	return 0;
}