
#include <sstream> //convert int into string
#include <iostream>
#include <string>
#include <vector> 
#include <list>
#include <conio.h> //controle the console inputs
#include <cstdlib>
#include <ctime> // to get time

// current date/time based on current system
//time_t now = time(0);

// convert now to string form
//char* dt = ctime(&now);

using namespace std;

class Node   // singly link list for store the history
{

public:
	string url;
	string time;
	string user_name;
	string password;

	Node* next;

	Node()
	{
		url = -1;
		time = -1;
		user_name= -1;
		password = -1;
		next = NULL;
	}


	Node(string u1, string u, string p, string t)
	{
		url = u1;
		user_name = u;
		password = p;
		time = t;
		next = NULL;
	}



};


class Singly_Linked_List    // singly link list for store the history
{

public:
	Node* head;
	Node* tail;
	int size;

public:
	Singly_Linked_List()
	{
		head = NULL;
		tail = NULL;
		size = 0;


	}

	void Insert_First(string url,string user , string pass , string time)  
	{
		Node* temp = new Node(url,user , pass, time);
		if (head == NULL)    
		{  
			head = temp;
			tail = temp;

		}
		else
		{   
			temp->next = head;
			head = temp;

		}
		size++;
	}
	void Display()  // display history
		// time complexity =O(n)
	{
		Node* temp = head;
		for (int i = 0; i < size; i++)
		{
			cout << "URL of the web site : " << temp->url << endl;
			cout << "User name : " << temp->user_name << endl;
			cout << "Password : " << temp->password << endl;
			cout << "The time the password was edited : " << temp->time << endl;
			temp = temp->next;
		}

	}
};



class hash1
{
private:
	static const int tablesize = 190;

	struct item
	{
		string url;
		string username;
		string password;
		item* next;

	};
	item* HashTable[tablesize];

public:

	hash1()
	{
		for (int i = 0; i < tablesize; i++)
		{
			HashTable[i] = new item;
			HashTable[i]->url = "empty";
			HashTable[i]->username = "empty";
			HashTable[i]->password = "empty";
			HashTable[i]->next = NULL;
		}
	}

	int Hash(string url) {
		//time complexity = O(n)
		int hash = 0;
		int index;
		for (int i = 0; i < url.length(); i++)
		{
			hash = hash + int(url[i]);

		}

		index = hash % tablesize;
		return index;
	}



	void AddUrl(string url, string username, string password)
	{
		int index = Hash(url);
		if (HashTable[index]->url == "empty")
		{
			HashTable[index]->url = url;
			HashTable[index]->username = username;
			HashTable[index]->password = password;
		}
		else
		{
			item* ptr = HashTable[index];
			item* n = new item;
			n->url = url;
			n->username = username;
			n->password = password;
			n->next = NULL;
			while (ptr->next != NULL)
			{
				ptr = ptr->next;
			}
			ptr->next = n;
		}
	}




	int NumberOfItemsInIndex(string url) {
		int count = 0;
		int index = Hash(url);
		if (HashTable[index]->url == "empty") {
			return count;
		}
		else {
			count++;
			item* Ptr = HashTable[index];
			while (Ptr->next != NULL) {  
				count++;
				Ptr = Ptr->next;
			}
		}
		return count;
	}





	void PrintInItemUrl(string url)  // print all the all usernameres and passwords stored in same url
	{
		int index = Hash(url);
		item* ptr = HashTable[index];
		if (ptr->url == "empty")
		{
			cout << "index = " << index << " is empty" << endl;
		}
		else
		{
			cout << "index " << index << "contains the following items" << endl;
			while (ptr != NULL)
			{
				cout << "--------------------------------\n";
				cout << ptr->url << endl;
				cout << ptr->username << endl;
				cout << ptr->password << endl;
				cout << "-----------------------\n";
				ptr = ptr->next;

			}
		}
	}

	void DeleteItem(string& url, string& username, string& password)  //delete the password using the url and username
		//time complexity = O(n)
	{
		int index = Hash(url);

		item* ptr = HashTable[index];
		item* temp = NULL;
		while (ptr->next != NULL)
		{

			if (ptr->next->url == url && ptr->next->username == username && ptr->next->next == NULL)
			{
				temp = ptr->next;
				ptr->next = NULL;
				url = temp->url;
				username = temp->username;
				password = temp->password;
				delete temp;
				return;

			}
			else if (ptr->url == url && ptr->username == username)
			{
				HashTable[index] = ptr->next;
				temp = ptr;
				url = temp->url;
				username = temp->username;
				password = temp->password;
				return;
			}
			else if (ptr->next->url == url && ptr->next->next->username == username)
			{
				temp = ptr->next;
				ptr->next = temp->next;
				url = temp->url;
				username = temp->username;
				password = temp->password;
				delete temp;
				return;

			}

			ptr = ptr->next;
		}





	}

	void Search(string& url, string& username , string& password)  // shearch the password using url and username
		//time comlexity =O(n)
	{
		
		int index = Hash(url);
		item* ptr = HashTable[index];
		while (ptr->url == url, ptr->username == username)
		{
			if (ptr->url == url && ptr->username == username)
			{
				password = ptr->password;

			}
			ptr = ptr->next;

		}
	}
};














string generatePassword( int len)  // Function for create a password according to the given lenth 
// time complexity =O(n)
{ 
	int upperCount = 3;
	int numCount = 2;
	int charCount = 2;
	int lowerCount = len - (upperCount + numCount + charCount);

	string upperCase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string lowerCase = "abcdefghijklmnopqrstuvwxyz";
	string numbers = "0123456789";
	string specialChars = "!@#$%^&*";

	string password;

	
	for (int i = 0; i < upperCount; i++) {
		password += upperCase[rand() % upperCase.length()];
	}
	for (int i = 0; i < numCount; i++) {
		password += numbers[rand() % numbers.length()];
	}
	for (int i = 0; i < charCount; i++) {
		password += specialChars[rand() % specialChars.length()];
	}
	for (int i = 0; i < lowerCount; i++) {
		password += lowerCase[rand() % lowerCase.length()];
	}

	
	random_shuffle(password.begin(), password.end());

	return password;


}


/*
int UrlConvertToASCII(string url)  //convert url to ascii code to get as a key
// time complexity =O(n)
{
	int y = url.length();
	string  url1 = "";
	stringstream stream;
	for (int i = 0; i < y; i++)
	{
		int x = int(url[i]);
		string x1 = to_string(x);
		url1 = url1 + x1;

	}
	cout << "lllllllllll     " << url1 << endl;
	int url2 = stoi(url1);
	cout << "lllllllllll wwwww    " << url2 << endl;
	return url2;

}


*/







int main()
{
	char Password[20], Username[20] = "jimmy", US[10], ch;
	int u = 0;
	bool iscorrect = 0; 
	while (iscorrect == false && u < 3) {
		cout << "Enter the username : ";
		cin >> US;
		if (strcmp(Username, US) == 0)  // string compair function
		{
			cout << "Enter the password :\n"; iscorrect = true;
			for (int i = 0; i <= 7; i++)
			{
				ch = getch();
				Password[i] = ch;
				ch = '*';
				cout << ch;
				if (ch != 13)
				{
					cout << "";
				}
				else if(ch!=8)
				{
					cout << "*";
				}
				cout << "Login succesful\n";
			}
		}
		else
		{
			cout << "Wrong passwod or username\n";
		}
	}



	hash1 hesy;

	hesy.AddUrl("Alice", "Alice", "Coffee");
	hesy.AddUrl("Alice", "Bob", "Tea");
	hesy.AddUrl("Bob", "Charlie", "Water");
	hesy.AddUrl("Charlie", "Bob", "Tea");
	hesy.AddUrl("Bob", "Charlvvvvvvvvvie", "Water");
	hesy.AddUrl("Charlie", "Bob", "Tea");
	hesy.AddUrl("Bob", "33333333ggggg", "Water");
	hesy.AddUrl("Charlie", "Bob", "Tea");
	hesy.AddUrl("Bob", "Charggggggggggggglie", "Water");
	string x = "Bob";
	string y = "Charlvvvvvvvvvie";
	string z;
	hesy.DeleteItem(x, y, z);
	cout << x << endl;
	cout << y << endl;
	cout << z << endl;
	



	/*string user_name1;
	string password1;
	cout << "Enter your user name :- " << endl;
	cin >> user_name1;
	cout << "Enter your password :- " << endl;
	cin >> password1;
	

	//testcase
	cout << generatePassword(12) << endl;
	//testcase
	Singly_Linked_List s;
	s.Insert_First("yttty", "chamara", "pass", "45");
	s.Display();

	int no = 0;
	do
	{
		cout << "Enter the number :-" << endl;
		cin >> no;

		cout << "1. Store the new password " << endl;
		cout << "2. Change the system password and user name  " << endl;
		cout << "3. Store the new password " << endl;
		cout << "4. Store the new password " << endl;
		cout << "5. History of Deleting Activities " << endl;
		cout << "6. Store the new password " << endl;
		cout << "7. Store the new password " << endl;
		cout << "8. Store the new password " << endl;
		cout << "9. Store the new password " << endl;
		cout << "10. quize " << endl;

		cin >> no;

		switch (no)
		{
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 9:
			break;
		default:
			break;

		}



	} while (no == 10);

	*/



}

