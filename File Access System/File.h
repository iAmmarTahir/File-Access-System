#pragma once
#include "User.h"
#include "Queue.h"
#include <vector>
using namespace std;

/*FILE CLASS*/

class File
{
private:
	Queue<User> *waitingList; // Users waiting for their turn to access files
	int fileID;
	vector<pair<int, char>> accessUsers; // Users who are currentlty accessing the files
public:
	File(int _fileID = 0);
	char checkUserAccess() const;
	void grantAccess();				// Grant access to next available user in queue
	bool releaseAccess(int userID);	// Release the lock acquired by particular user
	void addUser(User &user, int choice = 1);
	bool noUser() const;
	bool operator==(int ID);
	friend ostream &operator<<(ostream &cout, const File &rhs);
	int usersInQueue() const { return waitingList->Size(); }
	int usersAccessing() const { return accessUsers.size(); }
	~File();
};

File::File(int _fileID)
{
	fileID = _fileID;
	waitingList = new Queue<User>;
}

bool File::releaseAccess(int userID)
{
	auto end = accessUsers.end();
	for (auto &ite = accessUsers.begin(); ite != end; ite++)
	{
		if ((*ite).first == userID)
		{
			accessUsers.erase(ite);
			return true;
		}
	}
	return false;
}

void File::addUser(User &user, int choice)
{
	if (accessUsers.empty())
	{
		accessUsers.push_back(make_pair(user.getUserID(), user.getAccessType()));
		return;
	}
	else if (user.getAccessType() == 'R' && accessUsers[accessUsers.size() - 1].second != 'W')
	{
		accessUsers.push_back(make_pair(user.getUserID(), user.getAccessType()));
		return;
	}
	else if (!waitingList->Empty())
	{
		if (user.getAccessType() == 'R' && accessUsers[accessUsers.size() - 1].second != 'W' && (user.getPriority() > waitingList->FindMax()->getPriority()))
		{
			accessUsers.push_back(make_pair(user.getUserID(), user.getAccessType()));
			return;
		}
	}
	if (choice == 2)
	{
		if (!waitingList->Empty())
		{
			User *max = waitingList->FindMax();
			user.setPriority(max->getPriority());
		}
		else
		{
			user.setPriority(INT_MAX);
		}
	}
	else if (choice == 3)
	{
		if (!waitingList->Empty())
		{
			User *min = waitingList->FindMin();
			user.setPriority(min->getPriority());
		}
		else
		{
			user.setPriority(INT_MIN);
		}
	}
	waitingList->Insert(user);
}

char File::checkUserAccess() const
{
	return waitingList->FindMax()->getAccessType();
}

void File::grantAccess()
{
	User *user = waitingList->ExtractMax();
	accessUsers.push_back(make_pair(user->getUserID(), user->getAccessType()));
}

bool File::noUser() const
{
	return waitingList->Empty() && accessUsers.empty();
}

File::~File()
{
	if (waitingList != NULL)
		delete waitingList;
}

bool File::operator==(int ID)
{
	return fileID == ID;
}

ostream &operator<<(ostream &cout, const File &rhs)
{
	cout << "File " << rhs.fileID << " ... "
		<< "Access granted to ";
	int sz = rhs.accessUsers.size();
	int i;
	if (sz == 0)
	{
		cout << "none\n";
	}
	else
	{
		for (i = 0; i < sz; i++)
		{
			cout << "User " << rhs.accessUsers[i].first << ", ";
		}
		if (rhs.accessUsers[i - 1].second == 'W')
		{
			cout << "write\n";
		}
		else
		{
			cout << "read\n";
		}
	}
	if (rhs.waitingList == 0 || rhs.waitingList->Size() == 0)
	{
		cout << "\tNext User none\n";
		cout << "\tWaiting User none\n\n";
	}
	else
	{
		User *nextUser = rhs.waitingList->FindMax();
		cout << "\tNext User " << nextUser->getUserID() << ", ";
		if (nextUser->getAccessType() == 'W')
		{
			cout << "write\n";
		}
		else
		{
			cout << "read\n";
		}
		cout << "\tWaiting " << rhs.waitingList->Size() << " users" << endl
			<< endl;
	}
	return cout;
}