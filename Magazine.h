//Patricia Liu
#ifndef MAGAZINE_H
#define MAGAZINE_H
#include <iostream>
#include <string>
#include <fstream>
#include "Item.h"

using namespace std;

class Magazine : public Item
{
public:
	Magazine();
	Magazine(int, string, bool, int);
	virtual ~Magazine();
	virtual void writeToFile(string);
	virtual void print() const;
	virtual int getType() const;
	virtual string toString();

private:
	int issueNumber;
	const int itemType = 3;
};

#endif