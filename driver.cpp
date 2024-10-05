/*
  Title: driver.cpp
  Author: Ben Byerly
  Partner: Brett Ballew
  Section: CSC 1310-002
  Due: 4-3-2023
  Purpose: Calls upon the hashTable and sha functions to create and manage a table of username and passwords
           by using salting and hashing as encryption methods.
*/

#include <iostream>
#include <fstream>
#include "sha256.h"
//include your hash table---------------------------------------------------------------------------------------------------
#include "hashTable.h"

using namespace std;

int main()
{
	
	ifstream file("testlist.txt");
	int menuChoice;
	int numUsers;
	string user, pwd, salt;
	string username, password;

	hashTable *meine;		/*I made an educated guess an defined my hashTable pointer here. Meine was the first word.
							  that popped into my head for some reason. Guess it's because it means "my" in German.*/
	if(file.is_open()) {
	file >> numUsers;
	file.ignore(1, '\n');
	//dynamically allocate your hash table-------------------------------------------------------------------------------
	meine = new hashTable(numUsers);

	while(getline(file, user))
	{
		getline(file, pwd);
		//generate a salt and add the new user to your table--------------------------------------------------------
		salt = meine->generateSalt();
		pwd = sha256(pwd.append(salt));

		meine->addEntry(user,salt,pwd);
	}}

	do
	{
		//meine->print();		//This is for testing purposes.

		cout << "\nWhat would you like to do?\n";
		cout << "1.  Login.\n";
		cout << "2.  Create account.\n";
		cout << "3.  Delete account.\n";
		cout << "4.  Exit.\n";
		cout << "CHOOSE 1-4:  ";
		cin >> menuChoice;
		while(menuChoice < 1 || menuChoice > 4)
		{
			cout << "That is not a valid choice.\n";
			cout << "CHOOSE 1-4:  ";
			cin >> menuChoice;
		}
		
		switch(menuChoice)
		{
			case 1:	cout << "enter your username:  ";
					cin >> username;
					cout << "enter your password:  ";
					cin >> password;
					//check if the user's credentials are correct-----------------------------------
					if(meine->validateLogin(username,sha256(password.append(meine->getSalt(username)))))
						cout << "login successful\n";
					else
						cout << "invalid credentials\n";
					
					break;
					
			case 2: cout << "enter your new username:  ";
					cin >> username;
					cout << "enter your new password:  ";
					cin >> password;
					
					//generate a salt for the new user and add the user to the table--------------------
					salt = meine->generateSalt();
					password = sha256(password.append(salt));
																//added all dis
					meine->addEntry(username,salt,password);

					break;
					
			case 3:	cout << "enter your username:  ";
					cin >> username;
					cout << "enter your password:  ";
					cin >> password;
					//remove the user from the table and check if they were removed successfully----
					if(meine->removeUser(username,sha256(password.append(meine->getSalt(username)))))
						cout << "user removed successfully.\n";
					else
						cout << "invalid credentials, cannot remove user.\n";
					break;
					
			case 4:	cout << "goodbye" << endl;
					//delete the hash table-------------------------------------------------------------
					delete meine;
					break;
		}
		
	} while(menuChoice != 4);

	return 0;
}