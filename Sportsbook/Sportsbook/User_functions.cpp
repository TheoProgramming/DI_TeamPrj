#include "stdafx.h"
#include "BetAtzis.h"
#include "Main_functions.h"
#include "Users_categories.h"
#include "hierarchy.h"

using namespace std;


//OPERATIONS//


//GUEST OPERATIONS//

bool Guest::Operation(string leitourgia, BetAtzis& interface) {
	if ((leitourgia.compare("H")==0)||(leitourgia.compare("Home")==0) || (leitourgia.compare("h") == 0) || (leitourgia.compare("home") == 0)) {
		interface.return_home();
		interface.write_log("Return Home", "Guest", " ", "SUCCESS");
		return 1;
	}
	else if ((leitourgia.compare("T") == 0) || (leitourgia.compare("Toggle") == 0) || (leitourgia.compare("t") == 0) || (leitourgia.compare("toggle") == 0)) {
		interface.write_log("Toggle", "Guest", " ", "SUCCESS");
		return 1;
	}
	else if ((leitourgia.compare("X") == 0) || (leitourgia.compare("Exit") == 0) || (leitourgia.compare("x") == 0) || (leitourgia.compare("exit") == 0)) {
		interface.write_log("Exit", "Guest", "Exiting the program ", "SUCCESS");
		cout << "Exiting the program..." << endl;
		return 0; 
	}
	else {
		interface.write_log("Operation", "Guest", "WRONG INPUT", "ERROR");
		cout << "WRONG INPUT" << endl;
		return 1;
	}
}



//PUNTER OPERATIONS//


bool Punter::Operation(string leitourgia, BetAtzis& interface) {
	if ((leitourgia.compare("H") == 0) || (leitourgia.compare("Home") == 0) || (leitourgia.compare("h") == 0) || (leitourgia.compare("home") == 0)) {
		interface.return_home();
		interface.write_log("Return Home", get_username(), " ", "SUCCESS");
		return 1;
	}
	else if ((leitourgia.compare("T") == 0) || (leitourgia.compare("Toggle") == 0) || (leitourgia.compare("t") == 0) || (leitourgia.compare("toggle") == 0)) {
		Node* node = interface.get_home();										//start from home and go to every selection
		for (int a = 1; a <= node->get_vector_size(); a++) {
			node = node->get_next(a);
			for (int b = 1; b <= node->get_vector_size(); b++) {
				node = node->get_next(b);
				for (int c = 1; c <= node->get_vector_size(); c++) {
					node = node->get_next(c);
					for (int d = 1; d <= node->get_vector_size(); d++) {
						node = node->get_next(d);
						for (int e = 1; e <= node->get_vector_size(); e++) {
							node = node->get_next(e);
							string old_profit;
							node->get_profit(old_profit);
							if (interface.get_type_of_profits() == 0) {			//if profits are fractions, toggle them to decimal
								size_t klasma = old_profit.find("/");
								string sdividend, sdivisor, snew_profit;		//find dividend and divisor
								sdivisor = old_profit.substr(klasma + 1);
								sdividend = old_profit.substr(0, klasma);
								double dividend, divisor, new_profit;			//make them double
								stringstream converter1(sdividend);
								converter1 >> dividend;
								stringstream converter2(sdivisor);
								converter2 >> divisor;
								new_profit = (dividend / divisor) + 1;			//divide them and add one
								new_profit = round(new_profit * 100) / 100;		//get only 2 decimal digits
								stringstream convert;							//make them back to string
								convert << new_profit;
								snew_profit = convert.str();
								node->set_profit(snew_profit);					//set new profit
							}													
							else {												//if profits are decimals, toggle them to fractions
								double decimal;
								stringstream converter(old_profit.c_str());		//make them double
								converter >> decimal;
								decimal--;										//substract one
								decimal = decimal * 100;						//myltiply by 100 to get the 2 decimal digits up front
								double divisor = 100;							//divide by 100
								bool there_is_a_divisor = false;
								do {
									there_is_a_divisor = false;
									for (int i = 2; i <= decimal; i++) {		//try to simplify the fraction
										if ((fmod(decimal,i)==0)&&(fmod(divisor,i)==0)) {
											decimal = decimal / i;
											divisor = divisor / i;
											there_is_a_divisor = true;
											break;
										}
									}
								} while (there_is_a_divisor == true);
								string sdividend, sdivisor, snew_profit;		//make divisor and dividend back to strings
								stringstream con1, con2;
								con1 << decimal;
								sdividend = con1.str();
								con2 << divisor;
								sdivisor = con2.str();
								snew_profit = sdividend + "/" + sdivisor;
								node->set_profit(snew_profit);					//set new profit
							}
							node = node->get_back();
						}
						node = node->get_back();
					}
					node = node->get_back();
				}
				node = node->get_back();
			}
			node = node->get_back();
		}
		if (interface.get_type_of_profits() == 0) {
			cout << "Conversion from fraction to decimal was successful." << endl;
			interface.write_log("Toggle", get_username(), "Dekadika ", "SUCCESS");
			interface.set_type_of_profits("Dekadika");
		}
		else {
			cout << "Conversion from decimal to fraction was successful." << endl;
			interface.write_log("Toggle", get_username(), "Klasmatika ", "SUCCESS");
			interface.set_type_of_profits("Klasmatika");
		}
		return 1;
	}
	else if ((leitourgia.compare("A") == 0) || (leitourgia.compare("Account") == 0) || (leitourgia.compare("a") == 0) || (leitourgia.compare("account") == 0)) {
		User* user = interface.get_user();
		cout << endl << "Username: ";
		user->print_username();
		cout << endl << "Balance: ";
		user->print_balance();
		cout << endl << "Freebets: ";
		user->print_freebets();
		cout << endl;
		cout << "(R)Rename, to change your username." << endl;
		cout << "(P)Password, to change your password." << endl;
		cout << "(B)Bets, to see your bets." << endl;
		cout << "(D)Deposit, to change your account balance." << endl;
		string option;
		cin >> option;
		interface.write_log("Account", get_username(), " ", "SUCCESS");
		if ((option == "R") || (option == "Rename")) {
			cout << endl << "Please enter your new username:" << endl;
			string nusername;							//new username
			string ousername = user->get_username();	//old username
			string appuser;
			bool flag;
			do {
				cin >> nusername;
				flag = true;
				fstream file("users.csv", std::fstream::in);
				if ((file.is_open())&&(flag==true)) {
					getline(file, appuser);							//this takes the line and put it to string appuser
					while (!appuser.empty() && !file.eof()) {
						size_t pos1, pos2;
						pos1 = appuser.find("|");
						appuser = appuser.substr(pos1 + 1);
						pos2 = appuser.find("|");
						appuser = appuser.erase(pos2);
						if ((appuser.compare(nusername) == 0)) {	//this takes the line and check if there is a word in there mathcing to the given username
							cout << "This username is already taken!" << endl;
							flag = false;
							file.close();
							break;
						}
						getline(file, appuser);
					}
					file.close();
					if (flag == true) {
						interface.set_new_username(ousername, nusername);
						interface.save();
						cout << "Your username has changed successfully!" << endl;
						interface.write_log("Rename", get_username(), " ", "SUCCESS");
					}
				}
			} while (flag == false);
		}
		else if ((option == "P") || (option == "Password")) {
			string name = user->get_username();
			string pw1, pw2;
			cout << endl << "Please enter your new password:" << endl;
			cin >> pw1;
			cout << "One more time:" << endl;
			cin >> pw2;
			if (pw1 == pw2) {
				interface.set_new_password(name, pw1);
				interface.save();
				cout << "Your password has changed successfully!" << endl;
				interface.write_log("Password", get_username(), "Changed ", "SUCCESS");
			}
			else {
				interface.write_log("Password", get_username(), "no match ", "FAILED");
				cout << "Your passwords don't match!" << endl;
			}
		}
		else if ((option == "B") || (option == "Bets")) {
			cout << "BETTING HISTORY:" << endl;
			cout << "node_id|stake|result|" << endl;
			interface.print_user_bets();
			interface.write_log("Bets", get_username(), "Betting history ", "SUCCESS");
		}
		else if ((option == "D") || (option == "Deposit")) {
			string name = user->get_username();
			double add;
			cout << endl << "Please enter the amount you want to add to your balance:" << endl;
			cin >> add;
			interface.set_new_balance(name, add);
			interface.save();
			cout << "Your balance has changed successfully!" << endl;
			double nbalance = user->get_balance();
			cout << "Your new balance is: " << nbalance << endl;
			interface.write_log("Deposit", get_username(), "Changed ", "SUCCESS");
		}
		else {
			interface.write_log("Deposit", get_username(), "WRONG INPUT ", "ERROR");
			cout << "WRONG INPUT" << endl;
		}
		return 1;
	}
	else if ((leitourgia.compare("P") == 0) || (leitourgia.compare("Place") == 0) || (leitourgia.compare("p") == 0) || (leitourgia.compare("place") == 0)) {
		(interface.get_node())->place(&interface);
		interface.write_log("Place", get_username(), " ", "SUCCESS");
		return 1;
	}
	else if ((leitourgia.compare("X") == 0) || (leitourgia.compare("Exit") == 0) || (leitourgia.compare("x") == 0) || (leitourgia.compare("exit") == 0)) {
		cout << "Exiting the program..." << endl;
		interface.write_log("Exit", get_username(), "Exiting the program ", "SUCCESS");
		return 0;
	}
	else {
		interface.write_log("Operation", get_username(), "WRONG INPUT ", "FAILED");
		cout << "WRONG INPUT" << endl;
		return 1;
	}
}



//TRADER OPERATIONS//
	

bool Trader::Operation(string leitourgia, BetAtzis& interface) {
	if ((leitourgia.compare("H") == 0) || (leitourgia.compare("Home") == 0) || (leitourgia.compare("h") == 0) || (leitourgia.compare("home") == 0)) {
		interface.return_home();
		interface.write_log("Return Home", get_username(), " ", "SUCCESS");
		return 1;
	}
	else if ((leitourgia.compare("T") == 0) || (leitourgia.compare("Toggle") == 0) || (leitourgia.compare("t") == 0) || (leitourgia.compare("toggle") == 0)) {
		Node* node = interface.get_home();
		for (int a = 1; a <= node->get_vector_size(); a++) {
			node = node->get_next(a);
			for (int b = 1; b <= node->get_vector_size(); b++) {
				node = node->get_next(b);
				for (int c = 1; c <= node->get_vector_size(); c++) {
					node = node->get_next(c);
					for (int d = 1; d <= node->get_vector_size(); d++) {
						node = node->get_next(d);
						for (int e = 1; e <= node->get_vector_size(); e++) {
							node = node->get_next(e);
							string old_profit;
							node->get_profit(old_profit);
							if (interface.get_type_of_profits() == 0) {			
								size_t klasma = old_profit.find("/");
								string sdividend, sdivisor, snew_profit;
								sdivisor = old_profit.substr(klasma + 1);
								sdividend = old_profit.substr(0, klasma);
								double dividend, divisor, new_profit;
								stringstream converter1(sdividend);
								converter1 >> dividend;
								stringstream converter2(sdivisor);
								converter2 >> divisor;
								new_profit = (dividend / divisor) + 1;
								new_profit = round(new_profit * 100) / 100;
								stringstream convert;
								convert << new_profit;
								snew_profit = convert.str();
								node->set_profit(snew_profit);
							}												
							else {
								double decimal;
								stringstream converter(old_profit.c_str());
								converter >> decimal;
								decimal--;
								decimal = decimal * 100;
								double divisor = 100;
								bool there_is_a_divisor = false;
								do {
									there_is_a_divisor = false;
									for (int i = 2; i <= decimal; i++) {
										if ((fmod(decimal, i) == 0) && (fmod(divisor, i) == 0)) {
											decimal = decimal / i;
											divisor = divisor / i;
											there_is_a_divisor = true;
											break;
										}
									}
								} while (there_is_a_divisor == true);
								string sdividend, sdivisor, snew_profit;
								stringstream con1, con2;
								con1 << decimal;
								sdividend = con1.str();
								con2 << divisor;
								sdivisor = con2.str();
								snew_profit = sdividend + "/" + sdivisor;
								node->set_profit(snew_profit);
							}
							node = node->get_back();
						}
						node = node->get_back();
					}
					node = node->get_back();
				}
				node = node->get_back();
			}
			node = node->get_back();
		}
		if (interface.get_type_of_profits() == 0) {
			cout << "Conversion from fraction to decimal was successful." << endl;
			interface.set_type_of_profits("Dekadika");
			interface.write_log("Toggle", get_username(), "Dekadika ", "SUCCESS");
		}
		else {
			cout << "Conversion from decimal to fraction was successful." << endl;
			interface.set_type_of_profits("Klasmatika");
			interface.write_log("Toggle", get_username(), "Klasmatika ", "SUCCESS");
		}
		return 1;
	}
	else if ((leitourgia.compare("B") == 0) || (leitourgia.compare("Bets") == 0) || (leitourgia.compare("b") == 0) || (leitourgia.compare("bets") == 0)) {
		cout << "------------------------------------" << endl;
		cout << "|           20 last bets           |" << endl;
		cout << "------------------------------------" << endl;
		cout << "bet_id|user_id|node_id|stake|result|" << endl;
		if (interface.get_bets_size() >= 20) {
			for (int i = 0; i < 20; i++) {
				cout << (interface.get_bet(i))->conversion() << endl;
			}
		}
		else {
			for (int i = 0; i < interface.get_bets_size(); i++) {
				cout << (interface.get_bet(i))->conversion() << endl;
			}
		}
		interface.write_log("Bets", get_username(), "print 20 last bets ", "SUCCESS");
		return 1;
	}
	else if ((leitourgia.compare("F") == 0) || (leitourgia.compare("Freebets") == 0) || (leitourgia.compare("f") == 0) || (leitourgia.compare("freebets") == 0)) {
		int user;
		string amount;
		interface.print_users();
		cout << endl << "Enter the id of the user you want to give a freebet." << endl;
		cin >> user;
		User * userptr = interface.get_userptr(user);
		cout << endl << "Enter the amount to be given." << endl;
		cin >> amount;
		userptr->set_freebets(amount);
		interface.write_log("Freebets", get_username(), " ", "SUCCESS");
		interface.save();
		return 1;
	}
	else if ((leitourgia.compare("V") == 0) || (leitourgia.compare("Void") == 0) || (leitourgia.compare("v") == 0) || (leitourgia.compare("void") == 0)) {
		if (interface.get_current_level() == 4) {
			cout << "Select the option you want to cancel:" << endl;
			int option;
			cin >> option;
			Node* node = interface.get_node();
			if (node->get_vector_size() >= option) {
				node = node->get_next(option);
				if (node->get_voided() == 0) {
					node->set_voided();
					interface.write_log("Void", get_username(), " ", "SUCCESS");
					cout << "Option No" << option << " was cancelled succesfully." << endl;	
					string full_id = node->get_full_id();
					interface.voided(full_id);
					interface.save();
				}
				else {
					interface.write_log("Void", get_username(), "Is already voided. ", "ERROR");
					cout << "Option No" << option << " is already voided." << endl;
				}
			}
			else {
				interface.write_log("Void", get_username(), "The option you chose does not exist. ", "ERROR");
				cout << "The option you chose does not exist." << endl;
				return 1;
			}
			return 1;
		}
		else {
			cout << "Error. In order to cancel a selection you should be in a market." << endl;
			return 0;
			interface.write_log("Void", get_username(), "In order to cancel a selection you should be in a market. ", "ERROR");
		}
	}
	else if ((leitourgia.compare("S") == 0) || (leitourgia.compare("Settle") == 0) || (leitourgia.compare("s") == 0) || (leitourgia.compare("settle") == 0)) {
		if (interface.get_current_level() == 4) {
			cout << "Choose the winning option:" << endl;
			int option;
			cin >> option;
			Node* node = interface.get_node();
			if (node->get_vector_size() >= option) {
				node = node->get_next(option);
				if (node->get_voided() == 1) {
					cout << "A voided option cannot win!" << endl;
					return 1;
				}
				string full_id = node->get_full_id();
				interface.settle(full_id, option);		//settle as winning the option and every other option losing
				string sprofit;
				node->get_profit(sprofit);
				double profit;
				if (interface.get_type_of_profits() == 0) {
					size_t klasma = sprofit.find("/");
					string sdividend, sdivisor, snew_profit;
					sdivisor = sprofit.substr(klasma + 1);
					sdividend = sprofit.substr(0, klasma);
					double dividend, divisor, new_profit;
					stringstream converter1(sdividend);
					converter1 >> dividend;
					stringstream converter2(sdivisor);
					converter2 >> divisor;
					new_profit = (dividend / divisor);
					profit = new_profit;
				}
				else {
					stringstream converter(sprofit);
					converter >> profit;
				}
				interface.pay(full_id, profit);				//pay back the winers
				interface.save();
				interface.write_log("Settle", get_username(), "Settled ", "SUCCESS");
				cout << "Option No" << option << " was settled succesfully." << endl;
			}
			else {
				interface.write_log("Settle", get_username(), "Error 404 ", "ERROR");
				cout << "The option you chose does not exist." << endl;
				return 1;
			}
			return 1;
		}
		else {
			interface.write_log("Settle", get_username(), "WRONG NODE ", "ERROR");
			cout << "Error. In order to cancel a selection you should be in a market." << endl;
			return 0;
		}
	}
	else if ((leitourgia.compare("X") == 0) || (leitourgia.compare("Exit") == 0) || (leitourgia.compare("x") == 0) || (leitourgia.compare("exit") == 0)) {
		cout << "Exiting the program..." << endl;
		interface.write_log("Exit", get_username(), " ", "SUCCESS");
		return 0;
	}
	else {
		cout << "WRONG INPUT" << endl;
		return 1;
	}
}




//DIRECTOR OPERATIONS//


bool Director::Operation(string leitourgia, BetAtzis& interface) {
	if ((leitourgia.compare("H") == 0) || (leitourgia.compare("Home") == 0) || (leitourgia.compare("h") == 0) || (leitourgia.compare("home") == 0)) {
		interface.return_home();
		interface.write_log("Return Home", get_username(), " ", "SUCCESS");
		return 1;
	}
	else if ((leitourgia.compare("T") == 0) || (leitourgia.compare("Toggle") == 0) || (leitourgia.compare("t") == 0) || (leitourgia.compare("toggle") == 0)) {
		Node* node = interface.get_home();
		for (int a = 1; a <= node->get_vector_size(); a++) {
			node = node->get_next(a);
			for (int b = 1; b <= node->get_vector_size(); b++) {
				node = node->get_next(b);
				for (int c = 1; c <= node->get_vector_size(); c++) {
					node = node->get_next(c);
					for (int d = 1; d <= node->get_vector_size(); d++) {
						node = node->get_next(d);
						for (int e = 1; e <= node->get_vector_size(); e++) {
							node = node->get_next(e);
							string old_profit;
							node->get_profit(old_profit);
							if (interface.get_type_of_profits() == 0) {			
								size_t klasma = old_profit.find("/");
								string sdividend, sdivisor, snew_profit;
								sdivisor = old_profit.substr(klasma + 1);
								sdividend = old_profit.substr(0, klasma);
								double dividend, divisor, new_profit;
								stringstream converter1(sdividend);
								converter1 >> dividend;
								stringstream converter2(sdivisor);
								converter2 >> divisor;
								new_profit = (dividend / divisor) + 1;
								new_profit = round(new_profit * 100) / 100;
								stringstream convert;
								convert << new_profit;
								snew_profit = convert.str();
								node->set_profit(snew_profit);
							}													
							else {
								double decimal;
								stringstream converter(old_profit.c_str());
								converter >> decimal;
								decimal--;
								decimal = decimal * 100;
								double divisor = 100;
								bool there_is_a_divisor = false;
								do {
									there_is_a_divisor = false;
									for (int i = 2; i <= decimal; i++) {
										if ((fmod(decimal, i) == 0) && (fmod(divisor, i) == 0)) {
											decimal = decimal / i;
											divisor = divisor / i;
											there_is_a_divisor = true;
											break;
										}
									}
								} while (there_is_a_divisor == true);
								string sdividend, sdivisor, snew_profit;
								stringstream con1, con2;
								con1 << decimal;
								sdividend = con1.str();
								con2 << divisor;
								sdivisor = con2.str();
								snew_profit = sdividend + "/" + sdivisor;
								node->set_profit(snew_profit);
							}
							node = node->get_back();
						}
						node = node->get_back();
					}
					node = node->get_back();
				}
				node = node->get_back();
			}
			node = node->get_back();
		}
		if (interface.get_type_of_profits() == 0) {
			cout << "Conversion from fraction to decimal was successful." << endl;
			interface.set_type_of_profits("Dekadika");
			interface.write_log("Toggle", get_username(), "Dekadika ", "SUCCESS");
		}
		else {
			cout << "Conversion from decimal to fraction was successful." << endl;
			interface.set_type_of_profits("Klasmatika");
			interface.write_log("Toggle", get_username(), "Klasmatika ", "SUCCESS");
		}
		return 1;
	}
	else if ((leitourgia.compare("B") == 0) || (leitourgia.compare("Bets") == 0) || (leitourgia.compare("b") == 0) || (leitourgia.compare("bets") == 0)) {
		cout << "------------------------------------" << endl;
		cout << "|           20 last bets           |" << endl;
		cout << "------------------------------------" << endl;
		cout << "bet_id|user_id|node_id|stake|result|" << endl;
		if (interface.get_bets_size() >= 20) {
			for (int i = 0; i < 20; i++) {
				cout << (interface.get_bet(i))->conversion() << endl;
			}
		}
		else {
			for (int i = 0; i < interface.get_bets_size(); i++) {
				cout << (interface.get_bet(i))->conversion() << endl;
			}
		}
		interface.write_log("Bets", get_username(), "print 20 last bets ", "SUCCESS");
		return 1;
	}
	else if ((leitourgia.compare("F") == 0) || (leitourgia.compare("Freebets") == 0) || (leitourgia.compare("f") == 0) || (leitourgia.compare("freebets") == 0)) {
		int user;
		string amount;
		interface.print_users();
		cout << endl << "Enter the id of the user you want to give a freebet." << endl;
		cin >> user;
		User * userptr = interface.get_userptr(user);
		cout << endl << "Enter the amount to be given." << endl;
		cin >> amount;
		userptr->set_freebets(amount);
		interface.save();
		interface.write_log("Freebets", get_username(), " ", "SUCCESS");
		return 1;
	}
	else if ((leitourgia.compare("S") == 0) || (leitourgia.compare("Save") == 0) || (leitourgia.compare("s") == 0) || (leitourgia.compare("save") == 0)) {
		bool save = true;
		save = interface.save();
		if (save == true) {
			interface.write_log("Save", get_username(), " ", "SUCCESS");
			cout << "Files update successful!" << endl;
		}
		else {
			interface.write_log("Save", get_username(), " ", "FAILED");
			cout << "An error occured! Current state could not be saved." << endl;
		}
		return 1;
	}
	else if ((leitourgia.compare("X") == 0) || (leitourgia.compare("Exit") == 0) || (leitourgia.compare("x") == 0) || (leitourgia.compare("exit") == 0)) {
		cout << "Exiting the program..." << endl;
		interface.write_log("Exit", get_username(), "Exiting the program ", "SUCCESS");
		return 0;
	}
	else if ((leitourgia.compare("L") == 0) || (leitourgia.compare("Logs") == 0) || (leitourgia.compare("l") == 0) || (leitourgia.compare("logs") == 0)) {
		cout << "_______________________________" << endl;
		cout << "|        25 last logs          |" << endl;
		cout << "-------------------------------" << endl;
		interface.Logs();
		interface.write_log("Logs", get_username(), " ", "SUCCESS");
		return 1;
	}
	else if ((leitourgia.compare("U") == 0) || (leitourgia.compare("Users") == 0) || (leitourgia.compare("u") == 0) || (leitourgia.compare("users") == 0)) {
		cout << "Select a choice:" << endl;
		cout << "V(View), to view users info." << endl;
		cout << "S(Search), to search a user." << endl;
		cout << "L(Lock), to change the exclusion state of a user." << endl;
		string option;
		cin >> option;
		if ((option == "V") || (option == "View")) {
			interface.print_users();
			cout << endl;
		}
		else if ((option == "S") || (option == "Search")) {
			cout << "Type the username:" << endl;
			string username;
			cin >> username;
			interface.search_user(username);
			cout << endl;
		}
		else if ((option == "L") || (option == "Lock")) {
			cout << "Type the username:" << endl;
			string username;
			cin >> username;
			interface.lock_user(username);
			cout << endl;
			interface.save();
		}
		else {
			interface.write_log("Users", get_username(), " ", "ERROR");
			cout << "WRONG INPUT" << endl;;
		}
		interface.write_log("Users", get_username(), " ", "SUCCESS");
		return 1;
	}
	else if ((leitourgia.compare("V") == 0) || (leitourgia.compare("Visibility") == 0) || (leitourgia.compare("v") == 0) || (leitourgia.compare("visibility") == 0)) {
		cout << "Select the node you want to change its visibility:" << endl;
		int option;
		cin >> option;
		interface.set_visibility(option);
		interface.save();
		interface.write_log("Visibility", get_username(), " ", "SUCCESS");
		return 1;
	}
	else if ((leitourgia.compare("R") == 0) || (leitourgia.compare("Rename") == 0) || (leitourgia.compare("r") == 0) || (leitourgia.compare("rename") == 0)) {
		cout << "Type the ID of the node you want to rename:" << endl;
		interface.print_options();
		cout << "Cancel/Abort, to exit." << endl;
		string soption;
		cin >> soption;
		if ((soption == "Cancel") || (soption == "cancel") || (soption == "C") || (soption == "c") || (soption == "Abort") || (soption == "abort") || (soption == "A") || (soption == "a")) return 1;
		cout << "Type the new name of the node:" << endl;
		cout << "Cancel/Abort, to exit." << endl;
		string name;
		cin >> name;
		if ((name == "Cancel") || (name == "cancel") || (name == "C") || (name == "c") || (name == "Abort") || (name == "abort") || (name == "A") || (name == "a")) return 1;
		if ((name == "Rename") || (name == "New") || (name == "Copy") || (name == "Delete")) {
			cout << "This cannot be used as a node's name." << endl;
			return 1;
		}
		int option;
		stringstream converter(soption);
		converter >> option;
		Node* node = interface.get_node();
		node = node->get_next(option);
		node->set_name(name);
		interface.save();
		interface.write_log("Rename", get_username(), " ", "SUCCESS");
		cout << "Node name has changed successfully." << endl;
		return 1;
	}
	else if ((leitourgia.compare("N") == 0) || (leitourgia.compare("New") == 0) || (leitourgia.compare("n") == 0) || (leitourgia.compare("new") == 0)) {
		string name;
		Node* node = interface.get_node();
		if (interface.get_current_level() == 0) {
			cout << "Type the name of the category:" << endl;
			cin >> name;
		}
		else if (interface.get_current_level() == 1) {
			cout << "Type the name of the subcategory:" << endl;
			cin >> name;
		}
		else if (interface.get_current_level() == 2) {
			cout << "Type the name of the event:" << endl;
			cin >> name;
		}
		else if (interface.get_current_level() == 3) {
			cout << "Type the name of the market:" << endl;
			cin >> name;
		}
		else if (interface.get_current_level() == 4) {
			cout << "Type the name of the selection:" << endl;
			cin >> name;
		}
		interface.write_log("New", get_username(), " ", "SUCCESS");
		return 1;
	}
	else if ((leitourgia.compare("C") == 0) || (leitourgia.compare("Copy") == 0) || (leitourgia.compare("c") == 0) || (leitourgia.compare("copy") == 0)) {
		interface.write_log("Copy", get_username(), " ", "SUCCESS");
		return 1;
	}
	else if ((leitourgia.compare("D") == 0) || (leitourgia.compare("Delete") == 0) || (leitourgia.compare("d") == 0) || (leitourgia.compare("delete") == 0)) {
		cout << "Type th ID of the node you want to delete:" << endl;
		interface.print_options();
		cout << "Cancel/Abort, to exit." << endl;
		string soption;
		cin >> soption;
		if ((soption == "Cancel") || (soption == "cancel") || (soption == "C") || (soption == "c") || (soption == "Abort") || (soption == "abort") || (soption == "A") || (soption == "a")) return 1;
		cout << "Are you sure you wante to delete this node?" << endl;
		cout << "Cancel/Abort, to exit." << endl;
		string answer;
		cin >> answer;
		if ((answer == "Cancel") || (answer == "cancel") || (answer == "C") || (answer == "c") || (answer == "Abort") || (answer == "abort") || (answer == "A") || (answer == "a")) return 1;
		if (answer == "Y") {
			int option;
			stringstream converter(soption);
			converter >> option;
			Node* node = interface.get_node();
			string full_id = (node->get_next(option))->get_full_id();
			interface.delete_node(full_id);
			interface.save();
			interface.write_log("Delete", get_username(), "Node deleted successfully. ", "SUCCESS");
			cout << "Node deleted successfully." << endl;
			return 1;
		}
		else if (answer == "N") {
			return 1;
		}
		else {
			interface.write_log("Delete", get_username(), "delete node ", "ERROR");
			cout << "WRONG INPUT" << endl;
			return 1;
		}
		return 1;
	}
	else {
		interface.write_log("Delete", get_username(), "delete node ", "ERROR");
		cout << "WRONG INPUT" << endl;
		return 1;
	}
}




//PRINT OPERATIONS//


void Guest::Print_Operations(BetAtzis& interface) {
	cout << "Press the ID of the node you want to enter." << endl;
	cout << "H(Home), to return to home screen." << endl;
	cout << "T(Toggle), to toggle prices." << endl;
	cout << "X(Exit), to exit." << endl;
}

void Punter::Print_Operations(BetAtzis& interface) {
	cout << "Press the ID of the node you want to enter." << endl;
	cout << "H(Home), to return to home screen." << endl;
	cout << "T(Toggle), to toggle prices." << endl;
	cout << "A(Account), to change your account settings." << endl;
	if (interface.get_current_level() == 4) {
		cout << "P(Place), to place your bet." << endl;
	}
	cout << "X(Exit), to exit." << endl;
}

void Trader::Print_Operations(BetAtzis& interface) {
	cout << "Press the ID of the node you want to enter." << endl;
	cout << "H(Home), to return to home screen." << endl;
	cout << "T(Toggle), to toggle prices." << endl;
	cout << "B(Bets), to see the last 20 bets." << endl;
	cout << "F(Freebets), to give coupon to punter." << endl;
	if (interface.get_current_level() == 4) {
		cout << "V(Void), to cancel a selection." << endl;
		cout << "S(Settle), to settle the market." << endl;
	}
	cout << "X(Exit), to exit." << endl;
}

void Director::Print_Operations(BetAtzis& interface) {
	cout << "Press the ID of the node you want to enter." << endl;
	cout << "H(Home), to return to home screen." << endl;
	cout << "T(Toggle), to toggle prices." << endl;
	cout << "B(Bets), to see the last 20 bets." << endl;
	cout << "F(Freebets), to give coupon to punter." << endl;
	cout << "S(Save), to save current state and synchronize system files." << endl;
	cout << "X(Exit), to exit." << endl;
	cout << endl << "MANAGEMENT:" << endl;
	cout << "L(Logs), to see the last 25 logs." << endl;
	cout << "U(Users), to manage users." << endl;
	cout << "V(Visibility), to change the visibility of a node." << endl;
	cout << "R(Rename), to rename a node." << endl;
	cout << "N(New), to create a new node." << endl;
	cout << "C(Copy), to copy a node(hidden)." << endl;
	cout << "D(Delete), to delete a node." << endl;
}





void Punter::set_freebets(string freebet) {
	if ((freebets != "-") && (!freebets.empty())) {
		freebets.append(", ");
	}
	else {
		freebets.clear();
	}
	freebets.append(freebet); 
}


//SAVING VECTOR TO FILE//

string Punter::conversion() {
	string sid, sbalance, appuser;
	stringstream converter;
	converter << this->get_id();
	sid = converter.str();
	stringstream converter2;
	converter2 << this->get_balance();
	sbalance = converter2.str();
	if (sbalance.empty()) sbalance = "-";
	appuser = sid + "|" + this->get_username() + "|" + this->get_fullname() + "|" + this->get_password() + "|1|" + this->get_Status() + "|" + sbalance + "|" + this->get_free_bets() + "|";
	return appuser;
}

string Trader::conversion() {
	string sid,appuser;
	stringstream converter;
	converter << this->get_id();
	sid = converter.str();
	appuser = sid + "|" + this->get_username() + "|" + this->get_fullname() + "|" + this->get_password() + "|2| | | |";
	return appuser;
}

string Director::conversion() {
	string sid, appuser;
	stringstream converter;
	converter << this->get_id();
	sid = converter.str();
	appuser = sid + "|" + this->get_username() + "|" + this->get_fullname() + "|" + this->get_password() + "|3| | | |";
	return appuser;
}

bet::bet(int betid, int userid, string nodeid, double stk, string rslt, User * USER, Node* NODE) {
	bet_id = betid;
	user_id = userid;
	node_id = nodeid;
	stake = stk;
	result = rslt;
	user = USER;
	node = NODE;
}

void Punter::place(BetAtzis& Interface) {														//place a bet
	string operation;
	cout << "Balance: " << get_balance() << endl << "Select option to place the bet. " << endl;
	cin >> operation;
	bool validation = (Interface.get_node())->is_operation_valid(operation);
	if (validation == true) {
		if (operation == "Cancel") {															//if cancel return
			return;
		}
		else {
			cout << "betting on node: " << (Interface.get_node())->get_full_id() << "." << operation << endl;			//show the node id
			string freebets;
			freebets = get_free_bets();
			vector<string> frbts;
			string temp;
			size_t pos;
			char c = 'a';
			cout << "Your free bets: " << endl;
			if (freebets != "-"){																//if freebets are not empty
				while (!freebets.empty()) {
					temp = freebets;
					pos = temp.find(",");
					if (pos != -1) {
						temp.erase(temp.begin() + pos, temp.end());
						cout << c << ". " << temp << endl;										//show letter for option and amount of freebet
						frbts.push_back(temp);													//add to vector
						c++;																	//go to the next letter
						freebets = freebets.substr(pos + 1);
					}
					else {
						cout << c << ". " << temp << endl;
						frbts.push_back(temp);
						c++;
						freebets.clear();
					}
					
				}
			}
			else {																				//if freebets are empty
				cout << "No freebets available." << endl;
			}
			cout << "Enter the amount, or choose the coupon you wish(if there is available)." << endl;
			string sbounty;
			cin >> sbounty;
			int selection;
			stringstream converter2(operation);
			converter2 >> selection;
			if (!(isdigit(sbounty[0]) == 0)) {													//if you type a number go to balance
				int bounty;
				stringstream converter(sbounty);
				converter >> bounty;
				if (bounty < 0) {
					cout << "You can't place a negative bounty" << endl;
					return;
				}
				if (get_balance() == 0) {
					cout << "Your balance is 0. Please fill your wallet from the the main menu. " << endl;
					return;
				}
				if (bounty > get_balance()) {
					cout << "Please enter a smaller bet. Your balance is smaller than the bet you played. " << endl;
				}
				else {
					set_balance(-bounty);
					string node_id;
					node_id = (Interface.get_node())->get_next(selection)->get_full_id();
					Interface.set_bet(node_id, bounty, selection);
					Interface.save();
					cout << "Bet placed. "<< bounty << " credits were removed from your wallet." << endl;
				}
			}
			else {																				//if you type a letter
				int coupon = sbounty[0] - '0';
				coupon -= 48;																	// converting from ascii -48 .
				int selection;
				stringstream converter(operation);
				converter >> selection;
				converter.clear();
				stringstream converter2(frbts[coupon-1]);
				int bounty;
				converter2 >> bounty;
				string node_id = (Interface.get_node())->get_next(selection)->get_full_id();
				Interface.set_bet(node_id, bounty, selection);									//set bet to node
				frbts.erase(frbts.begin() + coupon - 1);										//delete freebet
				freebets.clear();
				if (frbts.size() > 1) {
					for (int i = 0; i < frbts.size() - 1; i++) {
						freebets += frbts[i] + ",";
					}
					freebets += frbts[frbts.size()];
				}
				else if(frbts.size()>0){
					freebets = frbts[frbts.size()-1];
				}
				else {
					freebets.clear();
				}
				initialize_freebets(freebets);
				Interface.save();
				cout << "Bet placed." << endl;
			}
		}
	}
	return;
}

string bet::conversion() {
	string sid, sstake, sbetid, bet;
	stringstream converter;
	converter << this->get_user_id();
	sid = converter.str();
	stringstream converter2;
	converter2 << this->get_stake();
	sstake = converter2.str();
	stringstream converter3;
	converter3 << this->get_bet_id();
	sbetid = converter3.str();
	bet = sbetid + "|" + sid + "|" + this->get_nodeid() + "|" + sstake + "|" + this->get_result() + "|";
	return bet;
}