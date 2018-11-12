#include "ASClassification.h"

vector<ASClass> ASes;

ASClass::ASClass() {} //default constructor

ASClass::ASClass(int as, string source, string type) { //constructor
	this->as = as;
	this->source = source;
	this->type = type;
}

void ASClass::classification(ifstream &input){ //reads the input file
	int linesCount = 0;
	double totalCount = 0;
	double tx_acCount = 0;
	double contentCount = 0;
	double enterpriseCount = 0;
	string splitter = "|";

	for (string inLine; getline(input, inLine); linesCount++) {
		string line = inLine;
		if ((line.find("#") != string::npos) || (line == "")) {
			//if a pound symbol is the line, ignore as it is a comment 
			//if line is empty then ignore
		}
		else {
			
			//AS number
			size_t pos0 = line.find(splitter); 
			int as = stoi(line.substr(0, pos0), nullptr, 0);
			line.erase(0, pos0 + splitter.length());

			//source
			size_t pos1 = line.find(splitter);
			string source = line.substr(0, pos1);
			line.erase(0, pos1 + splitter.length());

			//type
			string type = line;

			//check what type the AS is 
			if (type.compare("Content") == 0) {
				contentCount++;
			}
			else if (type.compare("Enterpise") == 0) { //Should be enterprise
				enterpriseCount++;
			}
			else if (type.compare("Transit/Access") == 0) {
				tx_acCount++;
			}
			totalCount++;
			//ASClass as = ASClass(as, source, type); //add to vector of ASes
		}
	}

	cout << "Total ASes: " << totalCount << endl;
	cout << "Types: " << endl;
	cout << "\t" << "Content : " << setprecision(2) << fixed << (contentCount / totalCount) * 100 << "%" << endl;
	cout << "\t" << "Enterprise : " << setprecision(2) << fixed << (enterpriseCount / totalCount) * 100 << "%"  << endl;
	cout << "\t" << "Transit/Access : " << setprecision(2) << fixed << (tx_acCount / totalCount) * 100 << "%" << endl;
}
