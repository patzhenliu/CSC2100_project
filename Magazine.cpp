//Patricia Liu
#include "Magazine.h"

Magazine::Magazine() : Item() {
	issueNumber = 0;
}

Magazine::Magazine(int i, string n, bool s, int in)
	: Item(i, n, s) {
	issueNumber = in;
}

Magazine::~Magazine() {

}

void Magazine::writeToFile(string fileName) {
	ofstream outFile;
	outFile.open(fileName, ofstream::app);
	if (!outFile.is_open()) {
		cout << "Error: unable to open file '"
			<< fileName << "'." << endl << endl;
	}
	outFile << itemType << ";" << Item::getId() << ";" << Item::getName() << ";" << Item::getStatus() << ";" << issueNumber << ";\n";
	outFile.close();
}

string Magazine::toString() {
	return (to_string(itemType) + ";" + to_string(Item::getId()) + ";" + Item::getName() + ";" + to_string(Item::getStatus()) + ";" + to_string(issueNumber) + ";\n");
}

void Magazine::print() const{
	Item::print();
	cout << "Issue Number: " << issueNumber << endl;
}

int Magazine::getType() const {
	return itemType;
}