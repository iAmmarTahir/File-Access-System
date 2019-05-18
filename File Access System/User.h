#pragma once
#include <iostream>

using namespace std;

/*USER CLASS FOR THE USERS WHO WANT TO ACCESS FILES FROM FILE REPOSITORY*/

class User
{
private:
	int userID;
	int priority;
	char access;
public:
	User(int _userID = 0, int _priority = 0, char _access = 0);
	friend ostream& operator<<(ostream& cout, const User& obj);
	friend istream& operator>>(istream& cout, User& obj);
	char getAccessType() const;
	int getUserID() const;
	bool operator<(const User& rhs) const;
	bool operator>(const User& rhs) const;
	int operator*() const;
	bool operator==(const User& rhs) const;
	bool operator!=(const User& rhs) const;
	void setPriority(int _priority);
	int getPriority() const { return priority; }
};

User::User(int _userID, int _priority, char _access)
{
	userID = _userID;
	priority = _priority;
	access = _access;
}

ostream& operator<<(ostream& cout, const User& obj)
{
	cout << obj.userID << " " << obj.priority << " " << obj.access << endl;
	return cout;
}

istream& operator>>(istream& cin, User& obj)
{
	int _userID, _priority;
	char _access;
	cin >> _userID >> _priority >> _access;
	obj.userID = _userID;
	obj.priority = _priority;
	obj.access = _access;
	return cin;
}

bool User::operator<(const User& rhs) const
{
	return this->priority < rhs.priority;
}

bool User::operator>(const User& rhs) const
{
	return this->priority > rhs.priority;
}

int User::operator*() const
{
	return this->priority;
}

bool User::operator==(const User& rhs) const
{
	return this->priority == rhs.priority;
}

bool User::operator!=(const User& rhs) const
{
	return !(this->priority == rhs.priority);
}

char User::getAccessType() const
{
	return access;
}

int User::getUserID() const
{
	return userID;
}

void User::setPriority(int _priority)
{
	priority = _priority;
}