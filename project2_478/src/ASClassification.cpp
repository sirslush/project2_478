#include "ASClassification.h"

vector<ASClass> ASes;
list<ASClass> ASesTest;


ASClass::ASClass() {} //default constructor

ASClass::ASClass(int as) { //constructor
	this->as = as;
}

void printclassification(){
    int enterprise = 0, content = 0, transit = 0;
    
    for (unsigned int i = 0; i < ASes.size(); i++) {
        if (ASes.at(i).getdegree() > 2 && ASes.at(i).getCustomersDegree()==0) {
            enterprise++;
        }
        else if (ASes.at(i).getdegree() < 2 && ASes.at(i).getCustomersDegree()==0 && ASes.at(i).getPeersDegree() !=0 ){
            content++;
        }
        else if (ASes.at(i).getCustomersDegree()>0){
            transit++;
        }
    }
    cout << "Total ASes that are enterprise = " << enterprise << "\n";
    cout << "Total ASes that are content = " << content << "\n";
    cout << "Total ASes that are transit = " << transit << "\n";
    
}


void printDegree(){
    int tot1 = 0, tot2_5 = 0, tot5_100 = 0, tot100_200 = 0, tot200_1000 = 0, tot_1000 = 0;
    for (unsigned int i = 0; i < ASes.size(); i++) {
        if (ASes.at(i).getdegree() == 1) {
            tot1++;
        }
        else if (ASes.at(i).getdegree() >= 2 && ASes.at(i).getdegree() < 5) {
            tot2_5++;
        }
        else if (ASes.at(i).getdegree() >= 5 && ASes.at(i).getdegree() < 100) {
            tot5_100++;
        }
        else if (ASes.at(i).getdegree() >= 100 && ASes.at(i).getdegree() < 200) {
            tot100_200++;
        }
        else if (ASes.at(i).getdegree() >= 200 && ASes.at(i).getdegree() < 1000) {
            tot200_1000++;
        }
        else if (ASes.at(i).getdegree() >= 1000) {
            tot_1000++;
        }
    }
    
    cout << "Total ASes with 1 degree = " << tot1 << "\n";
    cout << "Total ASes with 2-5 degree = " << tot2_5 << "\n";
    cout << "Total ASes with 5-100 degree = " << tot5_100 << "\n";
    cout << "Total ASes with 100-200 degree = " << tot100_200 << "\n";
    cout << "Total ASes with 200-1000 degree = " << tot200_1000 << "\n";
    cout << "Total ASes with 1000+ degree = " << tot_1000 << "\n\n\n";

    
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

    
    
//    ASesTest.sort([](const ASClass& a, const ASClass & b) { return a.as < b.as; });
    
    if (!ASes.empty()) {
        loc1 = binarySearch(0, ASes.size()-1, AS1.as);
        loc2 = binarySearch(0, ASes.size()-1, AS2.as);
    }
	
//    for (unsigned int i = 0; i < ASes.size(); i++) {
//        if (ASes[i].as == AS1.as) {
//            loc1 = i;
//        }
//        if (ASes[i].as == AS2.as) {
//            loc2 = i;
//        }
//    }

	if ((loc1 >= 0) && (loc2 >= 0)) {//AS1 is already in vector & AS2 is already in vector
		/*ASClass temp1 = ASClass();
		temp1 = ASes[loc1];
		ASClass temp2 = ASClass();
		temp2 = ASes[loc2];*/

			ASes[loc1].peers.push_back(ASes[loc2]); // add the second AS to the first AS peer
			ASes[loc2].peers.push_back(ASes[loc1]);	//add the first AS to the seconf AS peer
	}
	else if ((loc1 >= 0) && !(loc2 >= 0)) { //AS1 is already in vector & AS2 is not
                AS2.insertASes();
                //ASes.push_back(AS2); // add the new AS2 to the vector of ASes
				ASes[loc1].peers.push_back(AS2); //add the new AS2 to the peers of AS1
	}
	else if (!(loc1 >= 0) && (loc2 >= 0)) { //AS1 is not in vector and AS2 is 
            AS1.insertASes();
            //ASes.push_back(AS1);
			ASes[loc2].peers.push_back(AS1);
	}
	else { //AS1 and AS2 are not in the ASes vector 
			AS1.peers.push_back(AS2);
			AS2.peers.push_back(AS1);
        
            AS1.insertASes();
            AS2.insertASes();
        
//            ASes.push_back(AS1);
//            ASes.push_back(AS2);
	}
}

void ASClass::addCustomers(int as1, int as2) {
	ASClass AS1 = ASClass(as1);
	ASClass AS2 = ASClass(as2);
    int loc1 = -1;
    int loc2 = -1;
    
//    int loc1 = AS1.insertAses(&AS1); // inserting AS1
//    vector<ASClass>::iterator it = ASes.begin();
//    ASes.insert(it+loc1, AS1);

//    int loc2 = AS2.insertAses(&AS2);  // inserting AS2
//    vector<ASClass>::iterator it2 = ASes.begin();
//    ASes.insert(it2+loc2, AS2);
    
//    int location1 = binarySearch(0, int(ASes.size()), as1);
//    int location2 = binarySearch(0, int(ASes.size()), as2);
//
    if (!ASes.empty()) {
        loc1 = binarySearch(0, ASes.size()-1, AS1.as);
        loc2 = binarySearch(0, ASes.size()-1, AS2.as);
    }
    
//    for (unsigned int i = 0; i < ASes.size(); i++) {
//        if (ASes[i].as == AS1.as) {
//            loc1 = i;
//        }
//        if (ASes[i].as == AS2.as) {
//            loc2 = i;
//        }
//    }

	if ((loc1 >= 0) && (loc2 >= 0)) {//AS1 is already in vector & AS2 is already in vector
		ASes[loc1].customers.push_back(ASes[loc2]); // add AS2 customer to AS1 provider
	}
	else if ((loc1 >= 0) && !(loc2 >= 0)) { //AS1 is already in vector & AS2 is not
        AS2.insertASes();
        //ASes.push_back(AS2); // add the new AS2 to the vector of ASes
		ASes[loc1].customers.push_back(AS2); //add the new AS2 to the peers of AS1
	}
	else if (!(loc1 >= 0) && (loc2 >= 0)) { //AS1 is not in vector and AS2 is 
		AS1.customers.push_back(ASes[loc2]); // add AS2 to AS1 customers
        AS1.insertASes();
        //ASes.push_back(AS1); // add the new AS1 to the vector of ASes
        
	}

	else { //AS1 and AS2 are not in the ASes vector 
		AS1.customers.push_back(AS2);
        
        AS1.insertASes();
        AS2.insertASes();
//        ASes.push_back(AS1);
//        ASes.push_back(AS2);
	}
}

void ASClass::links(ifstream &input) {
	string splitter = "|";
    int num = 0;
	for (string inLine; getline(input, inLine); ) {
       
		string line = inLine;
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
	}

    for (int i = 0; i < ASes.size(); i++) {
        ASes.at(i).degrees();
    }
    printDegree();
    printclassification();
	cout << "done" << endl;
	//cin.get();
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
    return -1;
}

int ASClass::findSpottoInsert(ASClass *newASes){
    for (unsigned int i = 0; i < ASes.size(); i++) {
        if (ASes[i].as > newASes->as) {
            return i;
        }
    }
    return int(ASes.size());
}
    

void ASClass::degrees(){
    this->degree = this->getPeersDegree()+this->getCustomersDegree();
}

void ASClass::insertASes(){
        int loc1 = this->findSpottoInsert(this); // inserting AS1
        vector<ASClass>::iterator it = ASes.begin();
        ASes.insert(it+loc1, *this);
}




