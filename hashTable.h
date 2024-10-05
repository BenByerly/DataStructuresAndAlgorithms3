/*
  Title: hashTable.h
  Author: Ben Byerly
  Partner: Brett Ballew
  Section: CSC 1310-002
  Due: 4-3-2023
  Purpose: Contains the hashTable class and the nested entry class with function definitions. Apologies for 
           reorganizing this file. I couldn't follow it the way it was written and when I added stuff it looked
		   like a mess (my fault). 
*/
#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <string>
using std::string;

class hashTable
{
	public:
		hashTable(int size);
			/*Dynamically allocates new array of entry pointer and sets every ellement to NULL. We also seed
			  the random number generator here. Which that confused me a lot at first.*/
		~hashTable();
			/*Deletes every entry from the hashArray by looping through and deleting each bucket's list.*/
		void print();
			/*This was just for test case items.*/
		string generateSalt();
			/*We did not touch this as instructed.*/
		string getSalt(string);
			/*Uses the getEntry function to obtain an entry pointer that matches usernames. Then returns the salt
			  of that entry if it exists. As in the entry exists and getEntry didn't return NULL.*/
		bool removeUser(string usernama, string hashedpwda);
			/*Uses get entry to find the entry that matches the username that was given by the input. If the user
			  exists, then we compare the hashed passwords to make sure the credentials are correct. If the user exists
			  and the credentials are correct, then we delete the entry based on what location it is at in the bucket 
			  list and return true. Otherwise we return false.*/
		bool validateLogin(string usernama, string hashedpwda);
			/*Calls getEntry function to obtain account that has a matching username. If such an account exists,
			  then the hashed passwords are compared. If they match we return true, else false.*/
		void addEntry(string usernama,string salta,string hashedpwda);
			/*Dynamically allocates a new entry. Uses the hash function to determine which bucket to store it in.
			  It the checks the bucket to see if it's empty. If it is then the fist item in the list of that bucket
			  is the new entry. Else we will traverese to the end of the list then add it at the tail.*/
	private:
		class entry{
			public:
				entry(string usernama,string salta,string hashedpwda);
					/*Assigns each attribute of the entry based on what was passed as parameters.*/
				string getUsername();
					/*Returns entry username.*/
				string getSalt();
					/*Returns entry salt.*/
				string getHashedpwd();
					/*Returns entry salted and hashed password.*/
				entry *next;
					/*Pointer to the next entry in the list.*/
			private:
				string username;
				string salt;
				string hashedpwd;
					/*Just attributes that are unique to each account.*/
		};

		int tableSize;
			/*Size to allocate the hashTable array.*/
		int hash(string usernama);
			/*Did not touch as stated by instructions.*/
		entry **hashArray;
			/*An array of entry pointer which is the main array for the object.*/
		entry* getEntry(string usernama);
			/*Uses the hash function to get bucket index based on the username. Traverses the list of that bucket
			  until an entry with a matching username is found. Retuns that entry pointer if found, else returns NULL.*/
};

#endif