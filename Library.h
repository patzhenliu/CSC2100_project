//Patricia Liu
#ifndef LIBRARY_H
#define LIBRARY_H
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

class Library
{
public:
	Library();
	~Library();
	
	vector<Item*> getItemsByType(int);
	string itemTypeToString(int);
	vector<Item*> getItemsByName(string); // print
	vector<Item*> getItemsByAuthor(string); // print
	void addItem(int, string, string);

	void addToItems(int, int, string, bool, string);
	Item* getItem(int) const;
	vector<Item*> getItems() const;
	void printItems() const;
	bool isCheckedIn(int);
	void checkOut(int);
	void checkIn(int);
	int getSize() const;
	
	enum itemType { NONE, BOOK, JOURNAL, MAGAZINE };

private:
	const string fileName = "Catalog.txt";
	vector<Item*> items;

	void createCatalog();
	void save();
	string toUpper(string);
	string getLineUntil(ifstream &inFile);
};

#endif