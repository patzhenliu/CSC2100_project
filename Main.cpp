//Patricia Liu
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <iomanip>
#include <vector>
#include "Item.h"
#include "Book.h"
#include "Journal.h"
#include "Magazine.h"

using namespace std;

void run();
void printMenu();
void printSearchMenu();
void searchCatalog(vector<Item*>);
void printItemsByType(vector<Item*>, int);
string itemTypeToString(int);
int searchItemByName(vector<Item*>, string);
int searchItemByAuthor(vector<Item*>, string);
void createCatalog(vector<Item*>&);
int selectItemType();
void writeToCatalog(vector<Item*>&, int, string, string);
void addToItems(vector<Item*>&, int, int, string, bool, string);
void printTypeMenu();
void printCatalog(const vector<Item*>);
void checkOut();
void checkIn();

enum itemType { NONE, BOOK, JOURNAL, MAGAZINE };

void run() {
	vector<Item*> items;
	string trash = "";
	int action = 0;

	createCatalog(items);
	printCatalog(items);
	while (true)
	{
		try
		{
			cout << setw(50) << setfill('=') << "" << endl << endl;
			cout << setfill(' ');
			printMenu();
			cout << "\nPlease select a menu option: ";
			cin >> action;
			getline(cin, trash);
			cout << endl;

			if (action == 1) {
				searchCatalog(items);
			}
			else if (action == 2) {

			}
			else if (action == 3) {

			}
			else if (action == 4) {
				int type; //prompted
				string name = ""; //prompted

				type = selectItemType();
				cout << "Enter the title: ";
				getline(cin, name);

				string other;
				if (type == BOOK) {
					cout << "Enter the author: ";
					getline(cin, other);
				}
				else if (type == JOURNAL) {
					cout << "Enter the volume: ";
					cin >> other;
				}
				else if (type == MAGAZINE) {
					cout << "Enter the issue number: ";
					cin >> other;
				}
				writeToCatalog(items, type, name, other);
				printCatalog(items);
			}
			else if (action == 5) {
				return;
			}
		}
		catch (exception e)
		{
			cout << e.what() << endl;
			cin.clear();
			getline(cin, trash);
		}
	}
}

void printMenu() {
	cout << "1. Search Catalog" << endl;
	cout << "2. Check out" << endl;
	cout << "3. Return" << endl;
	cout << "4. Add a new item" << endl;
	cout << "5. Exit" << endl;
}

void printSearchMenu() {
	cout << "Search by:" << endl;
	cout << "1. Name" << endl;
	cout << "2. Category" << endl;
	cout << "3. Author" << endl;
	cout << "4. Return to menu" << endl;
	cout << endl;
}

void searchCatalog(vector<Item*> items) {
	int searchType = 0;
	string trash = "";

	while (searchType < 1 || searchType > 4) {
		printSearchMenu();
		cout << "Enter an option: ";
		cin >> searchType;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Please enter an integer\n" << endl;
		}
	}
	getline(cin, trash);

	if (searchType == 4) {
		return;
	}

	if (searchType == 1) {
		string name;
		cout << "Enter the name of the item: ";
		getline(cin, name);
		cout << endl;
		int index = searchItemByName(items, name);
		if (index == -1) {
			cout << "Item not found." << endl;
		}
		else {
			cout << "Item found!" << endl;
			items[index]->print();
		}
		cout << endl;
	}
	else if (searchType == 2) {
		int type;
		type = selectItemType();
		cout << "\nCategory Selected: " << itemTypeToString(type) << endl;
		printItemsByType(items, type);
	}
	else if (searchType == 3) {
		string author;
		cout << "Enter the name of the author: ";
		getline(cin, author);
		cout << endl;
		int index = searchItemByAuthor(items, author);
		if (index == -1) {
			cout << "Item not found." << endl;
		}
		else {
			cout << "Item found!" << endl;
			items[index]->print();
		}
		cout << endl;
	}
}

void printItemsByType(vector<Item*> items, int type){
	for (size_t i = 0; i < items.size(); i++) {
		if (items[i]->getType() == type) {
			items[i]->print();
		}
	}
	cout << endl;
}

string itemTypeToString(int type) {
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

int searchItemByName(vector<Item*> items, string name) {
	for (size_t i = 0; i < items.size(); i++) {
		if (items[i]->getName() == name) {
			return i;
		}
	}
	return -1;
}

int searchItemByAuthor(vector<Item*> items, string author) {
	for (size_t i = 0; i < items.size(); i++) {
		if (items[i]->getType() == BOOK) {
			Book* b = static_cast<Book*>(items[i]);
			if (b->getAuthor() == author) {
				return i;
			}
		}
	}
	return -1;
}

void createCatalog(vector<Item*> &items) { //items from text file to vector
	int type;
	int id;
	string name;
	bool status;
	string other;

	ifstream inFile;
	const string fileName = "Catalog.txt";

	inFile.open(fileName);
	if (!inFile.is_open()){
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

			addToItems(items, id, type, name, status, other);
		}
		catch (...) {
		}
	}
}

int selectItemType() {
	int type = -1;
	string trash = "";
	while (type < 1 || type > 4) {
		printTypeMenu();
		cout << "Enter an item type: ";
		cin >> type;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Please enter an integer\n" << endl;
		}
	}
	getline(cin, trash);
	return type;
}

void writeToCatalog(vector<Item*> &items, int type, string name, string other) { //add new item
	
	int id = items.size(); //default
	bool status = true; //default (checked-in)

	const string fileName = "Catalog.txt";

	cout << endl;
	addToItems(items, id, type, name, status, other);
	items[id]->writeToFile(fileName);
	
}

void addToItems(vector<Item*> &items, int id, int type, string name, bool status, string other) { //add to vector 'items'

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

void printTypeMenu() {
	cout << "1. Book" << endl;
	cout << "2. Journal" << endl;
	cout << "3. Magazine" << endl;
	cout << "4. Return to menu" << endl;
	cout << endl;
}

void printCatalog(const vector<Item*> items) {
	for (size_t i = 0; i < items.size(); i++) {
		items[i]->print();
	}
	cout << endl;
}

void checkOut() {

}

void checkIn() {

}

int main()
{
	run();
	return 0;
}