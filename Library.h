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
	
	void printItemsByType(int);
	string itemTypeToString(int);
	Item* searchItemByName(string);
	Item* searchItemByAuthor(string);
	void addItem(int, string, string);

	void addToItems(int type, int id, std::string &name, bool status, std::string &other);
	
	vector<Item*> getItems() const;
	void printItems() const;

	enum itemType { NONE, BOOK, JOURNAL, MAGAZINE };

private:
	const string fileName = "Catalog.txt";
	vector<Item*> items;
	void createCatalog();
};

#endif