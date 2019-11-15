#include "Library.h"

Library::Library() {
	vector<Item*> items;
	createCatalog();
	
}

Library::~Library() {
	for (size_t i = 0; i < items.size(); i++) {
		delete items[i];
		items[i] = 0;
	}
}

vector<Item*> Library::getItemsByType(int type) {
	vector<Item*> vect;
	for (size_t i = 0; i < items.size(); i++) {
		if (items[i]->getType() == type) {
			vect.push_back(items[i]);
		}
	}
	return vect;
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

vector<Item*> Library::getItemsByName(string name) {
	vector<Item*> vect;
	for (size_t i = 0; i < items.size(); i++) {
		if (toUpper(items[i]->getName()).find(toUpper(name)) != string::npos) {
			vect.push_back(items[i]);
		}
	}
	return vect;
}

vector<Item*> Library::getItemsByAuthor(string author) {
	vector<Item*> vect;
	for (size_t i = 0; i < items.size(); i++) {
		if (items[i]->getType() == BOOK) {
			Book* b = static_cast<Book*>(items[i]);
			if (toUpper(b->getAuthor()).find(toUpper(author)) != string::npos) {
				vect.push_back(items[i]);
			}
		}
	}
	return vect; //is calling destructor here, how to fix
}

void Library::createCatalog() { //items from text file to vector
	int type;
	int id;
	string name;
	bool status;
	string other;

	ifstream inFile;

	inFile.open(fileName);
	if (!inFile.is_open()) {
		cout << "Error: unable to open file '"
			<< fileName << endl << endl;
	}

	string line = "";
	while (inFile.good())
	{
		try {
			getline(inFile, line, Item::div);
			type = stoi(line);
			getline(inFile, line, Item::div);
			id = stoi(line);
			name = getLineUntil(inFile);
			getline(inFile, line, Item::div);
			status = stoi(line);
			other = getLineUntil(inFile);

			addToItems(type, id, name, status, other);
		}
		catch (exception e) {
			//cout << e.what() << endl;
		}
	}
	inFile.close();
}

string Library::getLineUntil(ifstream &inFile) {
	string s = "";
	string line = "";
	
	getline(inFile, s, Item::div);
	while (s.size() > 0 && s.back() == '\\') {
		
		s.back() = Item::div;
		getline(inFile, line, Item::div);
		s = s + line;
	}
	return s;
}

void Library::addItem(int type, string name, string other) { //add new item

	int id = items.size(); //default
	bool status = true; //default (checked-in)

	addToItems(type, id, name, status, other);

	items[id]->writeToFile(fileName);

}

void Library::addToItems(int type, int id, string name, bool status, string other)
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

Item* Library::getItem(int index) const {
	return items[index];
}

void Library::printItems() const{
	for (size_t i = 0; i < items.size(); i++) {
		items[i]->print();
	}
	cout << endl;
}

void Library::save() {
	ofstream outFile;
	outFile.open(fileName);
	for (size_t i = 0; i < items.size(); i++) {
		outFile << items[i]->toString();
	}
	outFile.close();
}

string Library::toUpper(string s) {
	for (size_t i = 0; i < s.size(); i++) {
		s[i] = toupper(s[i]);
	}
	return s;
}

bool Library::isCheckedIn(int id) {
	return items[id]->getStatus();
}

void Library::checkOut(int id) {
	items[id]->setStatus(false);
	save();
}

void Library::checkIn(int id) {
	items[id]->setStatus(true);
	save();
}

int Library::getSize() const {
	return items.size();
}