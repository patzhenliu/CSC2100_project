//Patricia Liu
#ifndef JOURNAL_H
#define JOURNAL_H
#include <iostream>
#include <string>
#include <fstream>
#include "Item.h"

using namespace std;

class Journal : public Item
{
public:
	Journal();
	Journal(int, string, bool, int);
	virtual ~Journal();
	virtual void writeToFile(string);
	virtual void print() const;
	virtual int getType() const;

	virtual string toString();

private:
	int volume;
	const int itemType = 2;
};

#endif