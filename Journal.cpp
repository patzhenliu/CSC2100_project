//Patricia Liu
#include "Journal.h"

Journal::Journal() : Item(){
	volume = 0;
}

Journal::Journal(int i, string n, bool s, int v) 
	: Item(i, n, s) {
	volume = v;
}

Journal::~Journal(){
	
}

void Journal::writeToFile(string fileName) {
	ofstream outFile;
	outFile.open(fileName, ofstream::app);
	if (!outFile.is_open()) {
		cout << "Error: unable to open file '"
			<< fileName << "'." << endl << endl;
	}
	outFile << itemType << ";" << Item::getId() << ";" << Item::getName() << ";" << Item::getStatus() << ";" << volume << ";\n";
	outFile.close();
}

string Journal::toString() {
	return (to_string(itemType) + ";" + to_string(Item::getId()) + ";" + Item::getName() + ";" + to_string(Item::getStatus()) + ";" + to_string(volume) + ";\n");
}

void Journal::print() const{
	Item::print();
	cout << "Volume: " << volume << endl;
}

int Journal::getType() const {
	return itemType;
}