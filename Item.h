//Patricia Liu
#ifndef ITEM_H
#define ITEM_H
#include <iostream>
#include <string>

using namespace std;

class Item
{
public:
	Item();
	Item(int, string, bool);
	virtual ~Item();
	virtual void writeToFile(string) = 0;
	virtual void print() const;
	virtual int getType() const = 0;
	int getId() const;
	string getName() const;
	bool getStatus() const;
	virtual string toString();
	void setStatus(bool);
	string fix(string s);

	static const char div = ';';
	static string findAndReplaceAll(string data, string toSearch, string replaceStr);

private:
	int id;
	string name;
	bool status; //0-checked out, 1-checked in

	
};

#endif