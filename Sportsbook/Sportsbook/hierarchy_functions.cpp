#include "stdafx.h"
#include "hierarchy.h"
#include "BetAtzis.h"

using namespace std; //

Node::Node(int ID, string NAME) {
	id = ID;
	name = NAME;
	//cout<<"A Node has been constructed."<<endl;
}

Home::Home() :Node(0,"Home"){//auti einai i mia prosgisi opou to home einai kai auto ksexoristi klasi paidi tou node, i alli prosegisi einai to home na einai to betatzis
	set_location("/BetAtzis");
	set_back(NULL);
	//cout << "Home has been constructed" << endl;
}

Category::Category(int ID, string NAME) :Node(ID, NAME) {
	//cout<<"A Category has been constructed."<<endl;
}

Subcategory::Subcategory(int ID, string NAME) :Node(ID, NAME) {
	//cout<<"A Subcategory has been constructed."<<endl;
}

Event::Event(int ID, string NAME, string DATE_TIME) :Node(ID, NAME) {
	date_time = DATE_TIME;
	//cout<<"An Event has been constructed."<<endl;
}

Market::Market(int ID, string NAME) :Node(ID, NAME) {
	//cout<<"A Market has been constructed."<<endl;
}

Selection::Selection(int ID, string NAME, string PROFIT) :Node(ID, NAME) {
	profit = PROFIT;
	voided = 0;
	result = "-";
	//cout<<"A Selection has been constructed."<<endl;
}

Node::~Node() {
	//cout<<"A Node will be destroyed."<<endl;
}

Home::~Home() {
	//cout << "Home will be destroyed."<<endl;
}

Category::~Category() {
	//cout<<"A Category will be destroyed."<<endl;
}

Subcategory::~Subcategory() {
	//cout<<"A Subcategory will be destroyed."<<endl;
}

Event::~Event() {
	//cout<<"An Event will be destroyed."<<endl;
}

Market::~Market() {
	//cout<<"A Market will be destroyed."<<endl;
}

Selection::~Selection() {
	//cout<<"A Selection will be destroyed."<<endl;
}

void Home::set_location(string LOCATION) {
	Node::set_location(LOCATION);
}

void Category::set_location(string LOCATION) {
	string location, name;
	Node* temp = get_back();
	temp->get_location(location);
	location.append("/");
	get_name(name);
	location.append(name);
	Node::set_location(location);
}

void Subcategory::set_location(string LOCATION) {
	string location, name;
	Node* temp = get_back();
	temp->get_location(location);
	location.append("/");
	get_name(name);
	location.append(name);
	Node::set_location(location);
}

void Event::set_location(string LOCATION) {
	string location, name;
	Node* temp = get_back();
	temp->get_location(location);
	location.append("/");
	get_name(name);
	location.append(name);
	Node::set_location(location);
}

void Market::set_location(string LOCATION) {
	string location, name;
	Node* temp = get_back();
	temp->get_location(location);
	location.append("/");
	get_name(name);
	location.append(name);
	Node::set_location(location);
}

void Selection::set_location(string LOCATION) {
	string location, name;
	Node* temp = get_back();
	temp->get_location(location);
	location.append("/");
	get_name(name);
	location.append(name);
	Node::set_location(location);
}


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//kosta poli pithanon auti i ylopoiisi na einai lathos, den tin allazw akoma, alla logika thelei to vector na einai sto node me vector < node * > Nodes kai oles oi sinartiseis virtual!

Category* Home::set_category(string NAME) {
	Category * ctg_ptr;
	ctg_ptr = new Category(Categories.size()+1,NAME); //Categories.size = ID
	Categories.push_back(ctg_ptr);
	return ctg_ptr;
}

Subcategory* Category::set_subcategory(string NAME) {
	Subcategory * sctg_ptr;
	sctg_ptr = new Subcategory(Subcategories.size()+1, NAME); //vector.size = ID
	Subcategories.push_back(sctg_ptr);
	return sctg_ptr;
}

Event* Subcategory::set_event(string NAME,string DATE_TIME) {
	Event * event_ptr;
	event_ptr = new Event(Events.size()+1, NAME, DATE_TIME); //vector.size = ID
	Events.push_back(event_ptr);
	return event_ptr;
}

Market* Event::set_market(string NAME) {
	Market * mrk_ptr;
	mrk_ptr = new Market(Markets.size()+1, NAME); //vector.size = ID
	Markets.push_back(mrk_ptr);
	return mrk_ptr;
}

Selection* Market::set_selection(string NAME,string profit) {
	Selection * sl_ptr;
	sl_ptr = new Selection(Selections.size()+1, NAME, profit); //vector.size = ID
	Selections.push_back(sl_ptr);
	return sl_ptr;
}

void Home::print_options() {
	for (int i = 0; i < Categories.size(); i++) { // kosta evgala to <= giati ama einai =0 tote tha mpei sto for eno den exei kanena stoixeio, an =1 tha mpei gia 2 ofres ena exei mono 1 stoixeio kai paei legontas
		Categories[i]->print_id();
		cout << ". ";
		Categories[i]->print_name();
		cout << endl;
	}
}

void Category::print_options() {
	for (int i = 0; i < Subcategories.size(); i++) {
		Subcategories[i]->print_id();
		cout << ". ";
		Subcategories[i]->print_name();
		cout << endl;
	}
}

void Subcategory::print_options() {
	for (int i = 0; i < Events.size(); i++) {
		Events[i]->print_id();
		cout << ". ";
		Events[i]->print_name();
		Events[i]->print_date_time();
		cout << endl;
	}
}

void Event::print_options() {
	for (int i = 0; i < Markets.size(); i++) {
		Markets[i]->print_id();
		cout << ". ";
		Markets[i]->print_name();
		cout << endl;
	}
}

void Market::print_options() {
	for (int i = 0; i < Selections.size(); i++) {
		Selections[i]->print_id();
		cout << ". ";
		Selections[i]->print_name();
		cout << " #";
		Selections[i]->print_profit();					//se periptwsh pou exei akyrw8ei h epilogh
		if (Selections[i]->get_voided() == 1) {
			cout << " (VOIDED)";
		}
		cout << endl;
	}
}

void Market::place(BetAtzis* Interface) {
	User* user = Interface->get_user();
	user->place(*Interface);
}

Node * Home::get_node_byid(string id)
{
	string node_id = id, node_id2 = id, node_id3 = id, node_id4 = id, node_id5 = id;
	size_t pos, pos2;
	int digit_node_id;
	Node * ptr;

	pos = node_id.find(".");
	node_id.erase(node_id.begin() + pos, node_id.end());
	stringstream converter(node_id);
	converter >> digit_node_id;
	ptr = get_next(digit_node_id);
	converter.clear();

	for (int j = 0; j < 1; j++) {
		pos2 = node_id2.find(".");
		node_id2 = node_id2.substr(pos2 + 1);
	}
	pos = node_id2.find(".");
	node_id2.erase(node_id2.begin() + pos, node_id2.end());
	stringstream converter2;
	converter2 << node_id2;
	converter2 >> digit_node_id;
	ptr = ptr->get_next(digit_node_id);
	converter2.clear();


	for (int j = 0; j < 2; j++) {
		pos2 = node_id3.find(".");
		node_id3 = node_id3.substr(pos2 + 1);
	}
	pos = node_id3.find(".");
	node_id3.erase(node_id3.begin() + pos, node_id3.end());
	stringstream converter3(node_id3);
	converter3 >> digit_node_id;
	ptr = ptr->get_next(digit_node_id);
	converter3.clear();


	for (int i = 0; i<3; i++) {
		pos2 = node_id4.find(".");
		node_id4 = node_id4.substr(pos2 + 1);
	}
	pos = node_id4.find(".");
	node_id4.erase(node_id4.begin() + pos, node_id4.end());
	stringstream converter4(node_id4);
	converter4 >> digit_node_id;
	ptr = ptr->get_next(digit_node_id);
	converter4.clear();


	for (int i = 0; i<4; i++) {
		pos2 = node_id5.find(".");
		node_id5 = node_id5.substr(pos2 + 1);
	}
	stringstream converter5(node_id5);
	converter5 >> digit_node_id;
	ptr = ptr->get_next(digit_node_id);
	converter5.clear();
	return ptr;
}