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
void printFound(Item*);
void searchLibrary(Library);
int selectItemType();
void printTypeMenu();
void checkOut();
void checkIn();
void printFound(Item*);

void run() {
	Library lib;
	string trash = "";
	int action = 0;

	lib.printItems();
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
				searchLibrary(lib);
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
				lib.addItem(type, name, other);
				lib.printItems();
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

void searchLibrary(Library lib) {
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
		Item* tempItem = lib.searchItemByName(name);
		printFound(tempItem);
		cout << endl;
	}
	else if (searchType == 2) {
		int type;
		type = selectItemType();
		cout << "\nCategory Selected: " << lib.itemTypeToString(type) << endl;
		lib.printItemsByType(type);
	}
	else if (searchType == 3) {
		string author;
		cout << "Enter the name of the author: ";
		getline(cin, author);
		cout << endl;
		Item* tempItem = lib.searchItemByAuthor(author);
		printFound(tempItem);
		cout << endl;
	}
}

void printFound(Item * tempItem)
{
	if (tempItem == NULL) {
		cout << "Item not found." << endl;
	}
	else {
		cout << "Item found!" << endl;
		tempItem->print();
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


void printTypeMenu() {
	cout << "1. Book" << endl;
	cout << "2. Journal" << endl;
	cout << "3. Magazine" << endl;
	cout << "4. Return to menu" << endl;
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