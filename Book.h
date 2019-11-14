//Patricia Liu
#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include <string>
#include <fstream>
#include "Item.h"

using namespace std;

class Book : public Item
{
public:
	Book();
	Book(int, string, bool, string);
	virtual ~Book();
	virtual void writeToFile(string);
	virtual void print() const;
	virtual int getType() const;
	string getAuthor() const;
	virtual string toString();

private:
	string authorName;
	const int itemType = 1;
};

#endif