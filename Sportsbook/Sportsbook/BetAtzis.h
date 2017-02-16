#pragma once
#include "Users_categories.h"
#include "stdafx.h"
#include "hierarchy.h"

class BetAtzis {
private:
	long double profits;
	double promitheia;
	string type_ofProfits;
	string Current_lvl;
	User* user; //arithmos users.
	Home * home; // to home den einai node opote to vazw edw ksexorista gia na exw panta prosvasi xoris pollapla back
	Node* node;
public:
	BetAtzis();
	~BetAtzis();
	void print() {
		node->print_options();
	};
	void print_operations() {
		user->Print_Operations();
	}
	void set_level(string lvl) {
		Current_lvl = lvl;
	}
	string get_level() {
		return Current_lvl;
	}
	void set_user(User *usr) {
		user = usr;
	}
};