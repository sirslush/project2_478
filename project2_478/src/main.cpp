#include "ASClassification.h"

using namespace std;

int main(int argc, char* argv[]) {
	
	//2.1 AS Classification
	/*ifstream inputFile;
	inputFile.open("20150801.as2types.txt");

	if (inputFile.is_open()) {
		cout << "2.1 AS Classification" << endl;
		ASClass AS = ASClass();
		AS.classification(inputFile);
		inputFile.close();

	}
	else {
		cout << "Could not open file: 20150801.as2types.txt" << endl;
		cout << "Please make sure the file is in the same folder as InternetTopology.exe and try again" << endl;
		return EXIT_FAILURE;
	}

	cout << "Press enter to continue" << endl;
	cin.get();*/

	////////////////////////////////////////////////////////

	//2.2 Topology Inference Through AS links
	ifstream inputFile2;
	inputFile2.open("20170901.as-rel2.txt");

	if (inputFile2.is_open()) {
		cout << "2.2 Topology Inference Through AS links" << endl;
		ASClass AS = ASClass();
		AS.links(inputFile2);

		inputFile2.close();
	}
	else {
		cout << "Could not open file: 20170901.as-rel2.txt" << endl;
		cout << "Please make sure the file is in the same folder as InternetTopology.exe and try again" << endl;
		return EXIT_FAILURE;
	}

	cout << "Press enter to continue" << endl;
	cin.get();



	return EXIT_SUCCESS;
}