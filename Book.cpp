//Patricia Liu
#include "Book.h"

Book::Book() : Item(){
	authorName = "unknown";
}

Book::Book(int i, string n, bool s, string a) : Item(i, n, s) {
	authorName = a;
}

Book::~Book(){

}

void Book::writeToFile(string fileName) {
	ofstream outFile;
	outFile.open(fileName, ofstream::app);
	if (!outFile.is_open()) {
		cout << "Error: unable to open file '"
			<< fileName << "'." << endl << endl;
	}
	outFile << itemType << ";" << Item::getId() << ";" << Item::getName() << ";" << Item::getStatus() << ";" << authorName << ";\n";
	outFile.close();
}

string Book::toString() {
	return (to_string(itemType) + ";" + to_string(Item::getId()) + ";" + Item::getName() + ";" + to_string(Item::getStatus()) + ";" + authorName + ";\n");
}

void Book::print() const{
	Item::print();
	cout << "Author: " << authorName << endl; 
}

int Book::getType() const {
	return itemType;
}

string Book::getAuthor() const {
	return authorName;
}