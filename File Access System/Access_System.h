#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include "File.h"
#include "HashTable.h"

using namespace std;

/*CLASS FOR IMPLEMENTING THE FUNCTIONALITY OF ACCESS SYSTEM*/

class AccessSystem
{
private:
	HashTable<int, File> fileRepository;

public:
	AccessSystem(const int &size = 1001);
	~AccessSystem();
	void loadFile();              // Loads data from file
	void insertFile();            // Insert any new file
	void addUser();               // Request of any new user to access  a file
	void accessGrant(int fileID); // Business logic of access grant
	void deleteFile();            // Delete any file in repository
	void printHashTable() const;
	void showMenu() const;
	inline void showLine() const;
	void choiceMaker(char choice);
	void UserInput();
	void releaseFile();
	void subMenu() const; // Submenu for setting priority of user
};

void AccessSystem::UserInput()
{
	char choice = '0';
	while (choice != 'E')
	{
		showMenu();
		cout << "Please make a choice: ";
		cin >> choice;
		cout << endl;
		choiceMaker(choice);
		showLine();
	}
}

void AccessSystem::subMenu() const
{
	cout << "1- Input priority of user\n"
		<< "2- Assign the highest priority\n"
		<< "3- Assign the lowest priority\n\n";
}

void AccessSystem::showLine() const
{
	for (int i = 0; i < 50; i++)
	{
		cout << '-';
	}
	cout << endl;
}

void AccessSystem::choiceMaker(char choice)
{
	switch (choice)
	{
	case '1':
		loadFile();
		break;
	case '2':
		printHashTable();
		break;
	case '3':
		insertFile();
		break;
	case '4':
		deleteFile();
		break;
	case '5':
		addUser();
		break;
	case '6':
		releaseFile();
		break;
	default:
		break;
	}
}

void AccessSystem::showMenu() const
{
	showLine();
	cout << "\t\t\tMENU\n";
	showLine();
	cout << "1- Load data from file\n"
		<< "2- Print hash table\n"
		<< "3- Add new file\n"
		<< "4- Delete a file\n"
		<< "5- Request access to file\n"
		<< "6- Release a file\n"
		<< "E- EXIT \n";
}

AccessSystem::AccessSystem(const int &size)
{
	fileRepository.resize(size);
}

void AccessSystem::addUser()
{
	int fileID;
	cout << "Enter the FileID of file to be accessed : ";
	cin >> fileID;
	File *elem;
	if (fileRepository.Find(fileID, elem))
	{
		int userID;
		cout << "Enter the ID of User which needs file access: ";
		cin >> userID;
		char access;
		cout << "Enter the User access type: ";
		cin >> access;
		subMenu();
		int choice;
		cout << "Please make a choice: ";
		cin >> choice;
		int priority = 0;
		if (choice == 1)
		{
			cout << "Enter the User priority: ";
			cin >> priority;
		}
		User user(userID, priority, access);
		elem->addUser(user, choice);
		cout << "User added successfully\n\n";
	}
	else
	{
		cout << "File does not exist\n\n";
	}
}

void AccessSystem::accessGrant(int fileID)
{
	File *elem;
	if (fileRepository.Find(fileID, elem))
	{
		bool writeAccess = false;
		int users = elem->usersInQueue() - 1;
		int i = 0;
		while (i < users && !elem->noUser() && elem->checkUserAccess() == 'R')
		{
			elem->grantAccess();
			writeAccess = true;
			i++;
		}
		if (!elem->noUser() && elem->checkUserAccess() == 'R')
		{
			elem->grantAccess();
			return;
		}
		if (elem->usersAccessing() == 0 && !writeAccess && !elem->noUser() && elem->checkUserAccess() == 'W')
		{
			elem->grantAccess();
			return;
		}
		return;
	}
	else
	{
		cout << "File does not exist\n\n";
	}
}

void AccessSystem::loadFile()
{
	ifstream input("Data.txt");
	string buffer;

	if (input)
	{
		cout << "File loaded successfully.\n\n";
	}

	while (getline(input, buffer))
	{
		int fileID, userID, priority;
		char accessType;
		stringstream s(buffer);
		s >> fileID;
		s.ignore(1);
		s >> userID;
		s.ignore(1);
		s >> priority;
		s.ignore(1);
		s >> accessType;

		User u(userID, priority, accessType);

		File *f = new File(fileID);
		f->addUser(u);
		fileRepository.Insert(fileID, f);
	}
}

void AccessSystem::insertFile()
{
	int fileID;
	cout << "Enter the FileID of file to be inserted : ";
	cin >> fileID;
	File *f = new File(fileID);
	if (fileRepository.Insert(fileID, f))
	{
		cout << "File " << fileID << " added successfully to the repositry.\n\n";
	}
}

void AccessSystem::deleteFile()
{
	int fileID;
	cout << "Enter the fileID which is to be deleted: ";
	cin >> fileID;
	File *elem;
	if (fileRepository.Find(fileID, elem))
	{
		if (elem->noUser())
		{
			fileRepository.Delete(fileID);
			cout << "File deleted successfully.\n\n";
		}
		else
		{
			cout << "Currently, some users are accessing the file.\n\n";
		}
	}
	else
	{
		cout << "File does not exist.\n\n";
	}
}

void AccessSystem::printHashTable() const
{
	fileRepository.print();
}

void AccessSystem::releaseFile()
{
	int fileID;
	cout << "Enter the FileID of file to be released by user: ";
	cin >> fileID;
	File *elem;
	if (fileRepository.Find(fileID, elem))
	{
		int userID;
		cout << "Enter the UserID of the user: ";
		cin >> userID;
		if (elem->releaseAccess(userID))
		{
			cout << "The file access of File " << fileID << " is released successfully by User " << userID << '.' << endl
				<< endl;
			accessGrant(fileID);
		}
		else
		{
			cout << "The specfied User does not have access to File " << fileID << '.' << endl
				<< endl;
		}
	}
	else
	{
		cout << "File does not exist.\n\n";
	}
}

AccessSystem::~AccessSystem()
{
	fileRepository.clear();
}