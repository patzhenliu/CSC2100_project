#include "Library.h"

Library::Library() {
	vector<Item*> items;
	createCatalog();
	
}



void Library::printItemsByType(int type) {
	for (size_t i = 0; i < items.size(); i++) {
		if (items[i]->getType() == type) {
			items[i]->print();
		}
	}
	cout << endl;
}

string Library::itemTypeToString(int type) {
	if (type == BOOK) {
		return "Book";
	}
	else if (type == JOURNAL) {
		return "Journal";
	}
	else if (type == MAGAZINE) {
		return "Magazine";
	}
	else {
		return "Invalid item type";
	}
}

Item* Library::searchItemByName(string name) {
	for (size_t i = 0; i < items.size(); i++) {
		if (items[i]->getName() == name) {
			return items[i];
		}
	}
	return NULL;
}

Item* Library::searchItemByAuthor(string author) {
	for (size_t i = 0; i < items.size(); i++) {
		if (items[i]->getType() == BOOK) {
			Book* b = static_cast<Book*>(items[i]);
			if (b->getAuthor() == author) {
				return items[i];
			}
		}
	}
	return NULL;
}

void Library::createCatalog() { //items from text file to vector
	int type;
	int id;
	string name;
	bool status;
	string other;

	ifstream inFile;
	const string fileName = "Catalog.txt";

	inFile.open(fileName);
	if (!inFile.is_open()) {
		cout << "Error: unable to open file '"
			<< fileName << endl << endl;
	}

	string line = "";
	while (inFile.good())
	{
		try {
			getline(inFile, line, ';');
			type = stoi(line);
			getline(inFile, line, ';');
			id = stoi(line);
			getline(inFile, line, ';');
			name = line;
			getline(inFile, line, ';');
			status = stoi(line);
			getline(inFile, line, ';');
			other = line;

			addToItems(type, id, name, status, other);
		}
		catch (exception e) {
			//cout << e.what() << endl;
		}
	}
}


void Library::addItem(int type, string name, string other) { //add new item

	int id = items.size(); //default
	bool status = true; //default (checked-in)

	addToItems(type, id, name, status, other);

	items[id]->writeToFile(fileName);

}

void Library::addToItems(int type, int id, std::string &name, bool status, std::string &other)
{
	if (type == BOOK) {
		Book* b = new Book(id, name, status, other);
		items.push_back(b);
	}
	else if (type == JOURNAL) {
		Journal* j = new Journal(id, name, status, stoi(other));
		items.push_back(j);
	}
	else if (type == MAGAZINE) {
		Magazine* m = new Magazine(id, name, status, stoi(other));
		items.push_back(m);
	}
}

vector<Item*> Library::getItems() const {
	return items;
}

void Library::printItems() const{
	for (size_t i = 0; i < items.size(); i++) {
		items[i]->print();
	}
	cout << endl;
}