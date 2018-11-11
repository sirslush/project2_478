#pragma once
#ifndef ASCLASSIFICATION_H
#define ASCLASSIFICATION_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <iomanip>

using namespace std;

class ASClass {
private:
	int as;
	string source;
	string type;

public:

	ASClass();	//default constructor
	ASClass(int as, string source, string type); //constructor
	void classification(ifstream &input); //reads the input file
};


#endif 