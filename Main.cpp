//Patricia Liu
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <iomanip>
#include <vector>
#include "Library.h"
#include "Item.h"
#include "Book.h"
#include "Journal.h"
#include "Magazine.h"

using namespace std;

void run();
void printMenu();
void printSearchMenu();
void printFoundItems(vector<Item*>);
vector<Item*> getSearchItems(Library&);
int selectItemType();
void printTypeMenu();
void printIsFound(Item*);
int getIntInput();
int getIntInput(int, int);
void checkingIO(Library&, bool);
void printfLine();
void runTests();

void printfLine() {
	cout << setw(50) << setfill('=') << "" << endl << endl;
	cout << setfill(' ');
}

void checkingIO(Library& lib, bool isCheckingIn) {
	int id;
	cout << "Enter item ID to return: ";
	id = getIntInput(0, lib.getSize() - 1);

	if (id != -1) {
		if (!lib.isCheckedIn(id) && isCheckingIn) { //if checked out and is checking in
			lib.checkIn(id);
			cout << "The following item has been returned:" << endl;
			lib.getItem(id)->print();
		}
		else if (lib.isCheckedIn(id) && !isCheckingIn) { //if checked in and is checking out
			lib.checkOut(id);
			cout << "The following item has been checked out:" << endl;
			lib.getItem(id)->print();
		}
		else { //checked in
			cout << "This item is already checked " << (isCheckingIn? "in":"out") << endl;
		}
		cout << endl;
	}
}

void run() {
	Library lib;
	string trash = "";
	int action = 0;

	const bool isCheckingIn = true;
	const bool isCheckingOut = not isCheckingIn;

	lib.printItems();
	while (true)
	{
		try
		{
			printfLine();
			printMenu();
			cout << "\nPlease select a menu option: ";
			action = getIntInput(1, 6);

			if (action == 1) {
				vector<Item*> vect = getSearchItems(lib);
				printFoundItems(vect);
				
			}
			else if (action == 2) {
				checkingIO(lib, isCheckingOut);

			}
			else if (action == 3) {
				checkingIO(lib, isCheckingIn);
			}
			else if (action == 4) {
				int type; //prompted
				string name = ""; //prompted

				type = selectItemType();

				if (type != 4) {
					cout << "Enter the title: ";
					getline(cin, name);

					string other;

					if (type == lib.BOOK) {
						cout << "Enter the author: ";
						getline(cin, other);
					}
					else if (type == lib.JOURNAL) {
						cout << "Enter the volume: ";
						cin >> other;
					}
					else if (type == lib.MAGAZINE) {
						cout << "Enter the issue number: ";
						cin >> other;
					}
					cout << endl;
					lib.addItem(type, name, other);
					lib.printItems();
				}
			}
			else if (action == 5) {
				return;
			}
			else if (action == 6) {
				runTests();
				
			}
		}
		catch (exception e)
		{
			cout << e.what() << endl;
			cin.clear();
			getline(cin, trash);
		}
	}
	//for (size_t i = 0; i < lib.getItems().size(); i++) { //was being called too often in Library destructor, FIX
	//	delete lib.getItems()[i];
	//	lib.getItems()[i] = 0;
	//}
}

void runTests() { 
	Book b;
	cout << "test fix function should return blah\\;blah" << endl;
	cout << b.fix("blah;blah") << endl;

	cout << "test fix function should return blah\\;blah" << endl;
	cout << b.findAndReplaceAll("blah;blah", ";", "\\;") << endl;


	string s1 = "pat";
	string s2 = s1;
	s2[0] = 'P';

	cout << "Test string manipulation" << endl;
	cout << s1 << " " << s2 << endl;
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

vector<Item*> getSearchItems(Library &lib) { //returns list of items that match
	int searchType = -1;
	string trash = "";

	while (searchType == -1) {
		printSearchMenu();
		cout << "Enter an option: ";
		searchType = getIntInput(1, 4);
	}
	getline(cin, trash);
	if (searchType == 1) {
		string name;
		cout << "Enter the name of the item: ";
		getline(cin, name);
		cout << endl;
		return lib.getItemsByName(name);
	}
	else if (searchType == 2) {
		int type;
		type = selectItemType();
		cout << "\nCategory Selected: " << lib.itemTypeToString(type) << endl;
		return lib.getItemsByType(type);
	}
	else if (searchType == 3) {
		string author;
		cout << "Enter the name of the author: ";
		getline(cin, author);
		cout << endl;
		return lib.getItemsByAuthor(author);
		
	}
	vector<Item*> empty;
	return empty;
}

void printFoundItems(vector<Item*> vect)
{
	if (vect.size() == 0) {
		cout << "Item not found.\n" << endl;
	}
	else {
		cout << "Item(s) found!" << endl;
		for (size_t i = 0; i < vect.size(); i++) {
			vect[i]->print();
		}
	}
}

int selectItemType() { //TEST
	int type = -1;
	string trash = "";
	while (type == -1) {
		printTypeMenu();
		cout << "Enter an item type: ";
		type = getIntInput(1, 4);
	}
	getline(cin, trash);
	return type;
}


void printTypeMenu() {
	cout << "1. Book" << endl;
	cout << "2. Journal" << endl;
	cout << "3. Magazine" << endl;
	cout << "4. Return to menu" << endl;
	cout << endl;
}

int getIntInput() {
	int x;
	cin >> x;
	cout << endl;
	if (cin.fail())
	{
		x = -1;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Please enter an integer\n" << endl;
	}
	return x;
}

int getIntInput(int lower, int upper) {
	int x;
	x = getIntInput();
	if (x < lower || x > upper) {
		x = -1;
		cout << "Number out of range\n" << endl;
	}
	return x;
}

int main()
{
	run();
	return 0;
}