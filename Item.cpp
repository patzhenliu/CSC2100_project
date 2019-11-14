//Patricia Liu
#include <iomanip>
#include "Item.h"

Item::Item() {
	id = 0;
	name = "unknown";
	status = 0;
}

Item::Item(int i, string n, bool s) {
	id = i;
	name = n;
	status = s;
}

Item::~Item() {
	//No code is needed in the destructor
	//No dynamic allocation in the class
}

void Item::print() const{

	cout << "ID: " << setw(5) << left << id;
	cout << "Name: " << setw(30) << name;
	cout << "Status: " << setw(15) << (status? "Checked in": "Checked out");
}

int Item::getId() const {
	return id;
}

string Item::getName() const {
	return name;
}

bool Item::getStatus() const {
	return status;
}

void Item::setStatus(bool s) {
	status = s;
}