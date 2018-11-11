#include "ASClassification.h"

using namespace std;

int main(int argc, char* argv[]) {
	
	//2.1 AS Classification
	ifstream inputFile;
	inputFile.open("20150801.as2types.txt");

	if (inputFile.is_open()) {
		cout << "2.1 AS Classification" << endl;
		ASClass AS = ASClass();
		AS.classification(inputFile);
	}
	else {
		cout << "Could not open file: 20150801.as2types.txt" << endl;
		cout << "Please make sure the file is in the same folder as InternetTopology.exe and try again" << endl;
	}

	cout << "Press enter to continue" << endl;
	cin.get();

	return EXIT_SUCCESS;
}