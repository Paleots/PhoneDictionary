#include <iostream>
#include "PhoneBook.hpp"

int main() {
	PhoneBook* t = new PhoneBook();
	t->loadPhonebook("tst_big.csv");
	t->openTerminal();
	delete t;
	return 0;
}