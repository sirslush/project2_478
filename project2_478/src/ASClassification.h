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
#include <list>

using namespace std;

class ASClass {
private:
	int as;
	vector<ASClass> peers;
	vector<ASClass> customers;
    vector<int> prefixList;
	int degree = 0;
    int numberofIPPrefixes = 0;
    long IPSpace= 0;

public:
    int getas(){return as;}
	ASClass();	//default constructor
	ASClass(int as);	//constructor
	void classification(ifstream &input);	//reads the input file
	void links(ifstream &input);	//reads the second input file
	void addPeers(int as1, int as2);	//adds the link between two peers
	void addCustomers(int as1, int as2);	//adds the link between a customer and provider
	void degrees(); // calculates the degree if all AS
    int binarySearch(int min, int max, int targetAs);
    int getPeersDegree(){return int(peers.size());}
    int getCustomersDegree(){return int(customers.size());}
    int findSpottoInsert(ASClass *newAses);
    void insertASes();
    int getdegree(){return degree;}
    void increaseNumPre(){numberofIPPrefixes++;}
    int getNumPre(){return numberofIPPrefixes;}
    void addToPrefixVector(int num){prefixList.push_back(num);}
    vector<int> getPreFixVect(){return prefixList;}
    void addtoIPSpace(int num){IPSpace += pow(2,(32-num));}

};

class ASEC{
private:
    vector<int> as;
    int prefixlength;
    string prefix;
    
public:
    ASEC();    //default constructor
    ASEC(int as, int prefixln, string prefix);    //constructor
    ASEC(int prefixln, string prefix);    //constructor
    void addAS(int AS){as.push_back(AS);}
    vector<int> getASes(){return as;}
    int getPreLength(){return prefixlength;}

};

void printDegree();
void printclassificationForGraph4();
void printConeResults();
void Extracredit(ifstream &input);    //reads the third input file
void countNumberPrefixes();
int binarySearch(int min, int max, int targetAs);
void CalcIPSpace();
void sortASesbyASesableToReach();






#endif 
