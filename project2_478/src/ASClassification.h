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
	vector<ASClass> peers;
	vector<ASClass> customers;
	int degree = 0;

public:
    int getas(){return as;}
	ASClass();	//default constructor
	ASClass(int as);	//constructor
	void classification(ifstream &input);	//reads the input file
	void links(ifstream &input);	//reads the second input file
	void addPeers(int as1, int as2);	//adds the link between two peers
	void addCustomers(int as1, int as2);	//adds the link between a customer and provider
	void degrees(ASClass *ASes); // calculates the degree if all AS
    int binarySearch(int min, int max, int targetAs);
    int getPeersDegree(){return int(peers.size());}
    int getCustomersDegree(){return int(customers.size());}
    int findSpottoInsert(ASClass *newAses);
    void insertASes();
    
};


#endif 
