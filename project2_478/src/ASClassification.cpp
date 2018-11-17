#include "ASClassification.h"

vector<ASClass> ASes;
vector<ASClass> ASesTest;


ASClass::ASClass() {} //default constructor

ASClass::ASClass(int as) { //constructor
	this->as = as;
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

void ASClass::addPeers(int as1, int as2) {
	ASClass AS1 = ASClass(as1);
	ASClass AS2 = ASClass(as2);
	int loc1 = -1;
	int loc2 = -1;
	
	for (unsigned int i = 0; i < ASes.size(); i++) {
		if (ASes[i].as == AS1.as) {
			loc1 = i;
		}
		if (ASes[i].as == AS2.as) {
			loc2 = i;
		}
	}

	if ((loc1 >= 0) && (loc2 >= 0)) {//AS1 is already in vector & AS2 is already in vector
		/*ASClass temp1 = ASClass();
		temp1 = ASes[loc1];
		ASClass temp2 = ASClass();
		temp2 = ASes[loc2];*/

			ASes[loc1].peers.push_back(ASes[loc2]); // add the second AS to the first AS peer
			ASes[loc2].peers.push_back(ASes[loc1]);	//add the first AS to the seconf AS peer
	}
	else if ((loc1 >= 0) && !(loc2 >= 0)) { //AS1 is already in vector & AS2 is not
				ASes.push_back(AS2); // add the new AS2 to the vector of ASes
				ASes[loc1].peers.push_back(AS2); //add the new AS2 to the peers of AS1
	}
	else if (!(loc1 >= 0) && (loc2 >= 0)) { //AS1 is not in vector and AS2 is 
			ASes.push_back(AS1);
			ASes[loc2].peers.push_back(AS1);
	}
	else { //AS1 and AS2 are not in the ASes vector 
			AS1.peers.push_back(AS2);
			AS2.peers.push_back(AS1);
			ASes.push_back(AS1);
			ASes.push_back(AS2);
	}
}

void ASClass::addCustomers(int as1, int as2) {
	ASClass AS1 = ASClass(as1);
	ASClass AS2 = ASClass(as2);
	int loc1 = -1;
	int loc2 = -1;
    
    int location1 = binarySearch(0, int(ASes.size()), as1);
	for (unsigned int i = 0; i < ASes.size(); i++) {
		if (ASes[i].as == AS1.as) {
			loc1 = i;
		}
		if (ASes[i].as == AS2.as) {
			loc2 = i;
		}
	}

	if ((loc1 >= 0) && (loc2 >= 0)) {//AS1 is already in vector & AS2 is already in vector
		ASes[loc1].customers.push_back(ASes[loc2]); // add AS2 customer to AS1 provider
	}
	else if ((loc1 >= 0) && !(loc2 >= 0)) { //AS1 is already in vector & AS2 is not
		ASes.push_back(AS2); // add the new AS2 to the vector of ASes
		ASes[loc1].customers.push_back(AS2); //add the new AS2 to the peers of AS1
	}
	else if (!(loc1 >= 0) && (loc2 >= 0)) { //AS1 is not in vector and AS2 is 
		AS1.customers.push_back(ASes[loc2]); // add AS2 to AS1 customers
		ASes.push_back(AS1); // add the new AS1 to the vector of ASes
	}

	else { //AS1 and AS2 are not in the ASes vector 
		AS1.customers.push_back(AS2);
		ASes.push_back(AS1);
		ASes.push_back(AS2);
	}
}

void ASClass::links(ifstream &input) {
	string splitter = "|";
    int num = 0;
	for (string inLine; getline(input, inLine); ) {
       
		string line = inLine;
        cout << num << "\n";
		if ((line.find("#") != string::npos) || (line == "")) {
			//if a pound symbol is the line, ignore as it is a comment 
			//if line is empty then ignore
		}
		else {
			//First AS
			size_t pos0 = line.find(splitter);
			int as1 = stoi(line.substr(0, pos0), nullptr, 0);
			line.erase(0, pos0 + splitter.length());

			//Second AS
			size_t pos1 = line.find(splitter);
			int as2 = stoi(line.substr(0, pos1), nullptr, 0);
			line.erase(0, pos1 + splitter.length());
			
			//Check link type
			size_t pos2 = line.find(splitter);
			int link = stoi(line.substr(0, pos2), nullptr, 0);
			line.erase(0, pos2 + splitter.length());


			//p2c link
			if (link == -1) {
				this->addCustomers(as1, as2);

			}
			//p2p link
			else if (link == 0) {
				this->addPeers(as1, as2);
			}
			else {
				cout << "error: no link" << endl;
			}
            
		}
        num++;
	}

	cout << "done" << endl;
	cin.get();
	cout << "helllo";
}

int ASClass::binarySearch(int min, int max, int targetAs){
    if (max>=min) {
        int mid =min+(max-min)/2;
        if (ASes.at(mid).getas() == targetAs) {
            return mid;
        }
        if (ASes.at(mid).getas()>targetAs) {
            return binarySearch(min, mid-1, targetAs);
        }
        return binarySearch(mid+1, max, targetAs);
    }
    cout << "Error in search";
    return -1;
}



void ASClass::degrees() {

}
