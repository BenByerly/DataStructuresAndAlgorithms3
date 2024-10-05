/*
  Title: hashTable.cpp
  Author: Ben Byerly
  Partner: Brett Ballew
  Section: CSC 1310-002
  Due: 4-3-2023
  Purpose: Contains the hashTable class function implementations along with the entry class function
           impleentations. I am so bad at wording that.
*/
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "hashTable.h"
using std::string;
using std::cout;
using std::endl;		//I added this to make it easier on us.

hashTable::hashTable(int size){	
	tableSize = size;
	hashArray = new entry*[size];
	for(int i = 0; i < size; i++){		//Iterates through the dynamically allocated array of entry pointers
		hashArray[i] = NULL;			//setting each index's/bucket first item to NULL.
	}
	srand (time(0));	//this needs to be in the constructor, otherwise every user gets the same salt
}

hashTable::~hashTable(){		//DONE
	entry *temp, *toRemove;
	for(int i = 0; i < tableSize; i++){
		temp = hashArray[i];		//Iterates through the whole array. 
		while(temp != NULL){
			toRemove = temp;
			temp = temp->next;		//Deletes list stored in each bucket/index.
			delete toRemove;
		}
	}
	delete [] hashArray;		//Finally deletes the whole array.
}

void hashTable::print(){
	entry *temp;
	for(int i = 0; i < tableSize; i++){
		temp = hashArray[i];
		cout << "\nBucket " << i << ": ";		//I just used this as a way to vizualize the issues in the program.
		while(temp != NULL){
			cout << temp->getUsername() << " -> ";
			temp = temp->next;
		}
	}
	cout << endl;
}

string hashTable::getSalt(string usernama){
	entry *temp = getEntry(usernama);		//Calls get entry to obtain an account with matching username.

	if(temp == NULL){
		return "empty";		//If the account does not exist (entry is NULL) it returns empty.
	}else{
		return temp->getSalt();		//If the account does exist. It simply returns the salt.
	}
}

bool hashTable::removeUser(string usernama,string hashedpwda){
	entry *temp = getEntry(usernama);
	entry *before;		
	int index = hash(usernama);		//Obtain matching account based on username and then get index/bucket.

	if(temp != NULL){
		if(temp->getHashedpwd() == hashedpwda){		//Proceed to remove if hashed passwords match.
			before = hashArray[index];
			if(before == temp){
				hashArray[index] = temp->next;
				delete temp;					//In the event it's the first item in a bucket list.
				return true;
			}else{
				while(before->next != temp){
					before = before->next;
				}
				before->next = temp->next;		//In the event the account is not the first entry in a bucket.
				delete temp;
				return true;
			}
		}else{
			return false;		//In the event the attempted password is wrong.
		}
	}else{
		return false;		//In the event the user they are looking to delete does not exist.
	}
	
}

bool hashTable::validateLogin(string usernama, string hashedpwda){
	entry *temp = getEntry(usernama);
											//Calls get entry to obtain matching entry based on username.
	if(temp == NULL){
		return false;		//In the event a user does not exist based on username credential.
	}else{
		if(temp->getHashedpwd() == hashedpwda){
			return true;		//If hashed passwords are the same. Return true.
		}else{
			return false;		//Hashed password is incorrect. Return false.
		}
	}
}

void hashTable::addEntry(string usernama, string salta, string pwd){
	entry *temp = new entry(usernama,salta,pwd);		
	entry *placeHolder;		//Dynamically allocate an entry based on inputs from driver.

	int index = hash(usernama);		//Obtain bucket index.

	if(hashArray[index] == NULL){
		hashArray[index] = temp;	//In the event the bucket is empty.
	}else{
		placeHolder = hashArray[index];
		while(placeHolder->next != NULL){
			if(placeHolder->getUsername() == usernama){
				cout << "\nUsername already exists. Could not add account.\n";
				return;
			}
			placeHolder = placeHolder->next;	//Traverses and checks each element to make sure the account doesn't already exist.
		}
		placeHolder->next = temp;	//Finally places new entry at end of bucket list.
	}

}

hashTable::entry* hashTable::getEntry(string usernama){	
	int index = hash(usernama);
	entry *temp = hashArray[index];		//Obtains first entry of the bucket that matches desired username.

	while((temp != NULL) && (temp->getUsername() != usernama)){		//Checks to see if entry is  not NULL AND the usernames don't match.
		temp = temp->next;
	}
	if(temp == NULL){
		return NULL;	//If goes through list with no matches. Returns NULL.
	}else{
		return temp;	//If a match is found it returns that entry pointer.
	}
}

//don't touch this!
int hashTable::hash(string key)
{
	int sum = 0;
	for(int i = 0; i < key.size(); i++)
		sum += key[i];
	
	return sum % tableSize;
}

//don't touch this!
string hashTable::generateSalt()
{
	string s = "";
	
	for(int i = 0; i < tableSize; i++)
		s = s + char('!' + (rand() % 93));
	return s;
}

hashTable::entry::entry(string usernama, string salta, string hashedpwda){
	username = usernama;
	salt = salta;		
	hashedpwd = hashedpwda;		//Assigns values based on program instructions.
	next = NULL;
}

string hashTable::entry::getUsername(){
	return username;
}
string hashTable::entry::getSalt(){
	return salt;
}
string hashTable::entry::getHashedpwd(){
	return hashedpwd;
}

