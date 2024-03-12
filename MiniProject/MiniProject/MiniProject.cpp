#include <sstream> //convert int into string
#include <iostream>
#include <string> 
#include <algorithm>
#include <conio.h> //controle the console inputs
#include <cstdlib>
#include <Windows.h>
#include <limits>

#define TEAL "\033[1;36m"
#define RESET "\033[0m"
#define GREEN "\033[1;32m"
#define RED "\033[1;31m"
#define DELAY 1500


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
		user_name = -1;
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

	void Insert_First(string url, string user, string pass, string Time)
	{
		Node* temp = new Node(url, user, pass, Time);
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
		if (temp == NULL) {
			system("cls");
			cout << RED << "History is Empty" << RESET << endl;
			Sleep(DELAY);
			system("cls");
			return;
		}
		else {
			for (int i = 0; i < size; i++)
			{
				system("cls");
				cout << "________________________________________________________________________________\n" << endl;
				cout << "URL of the web site : " << temp->url << endl;
				cout << "User name : " << temp->user_name << endl;
				cout << "Password : " << temp->password << endl;
				cout << "Deleted " << temp->time << endl;
				cout << "________________________________________________________________________________\n" << endl;
				temp = temp->next;
			}
		}
	}
};



class hash1
{
private:
	static const int tablesize = 200;

	struct item
	{
		string url;
		string username;
		string password;
		item* next;
		item* prev;

		item() {
			url = "";
			username = "";
			password = "";
			next = NULL;
			prev = NULL;
		}

	};
	item* HashTable[tablesize];

	string caesarDecrypt(string input) {
		// tie complexity O(n)
		int shift = 13;
		string dPassword = "";
		for (char c : input) {
			if (isalpha(c)) {
				char base = isupper(c) ? 'A' : 'a';
				int shiftedValue = (c - base - shift + 26) % 26;
				dPassword += static_cast<char>(shiftedValue + base);
			}
			else {
				dPassword += c;
			}
		}
		return dPassword;
	}

	string caesarEncrypt(string input) {
		// time complexity O(n)
		int shift = 13;
		string ePassword = "";
		for (char c : input) {
			if (isalpha(c)) {
				char base = isupper(c) ? 'A' : 'a';
				ePassword += static_cast<char>((c - base + shift) % 26 + base);
			}
			else {
				ePassword += c;
			}
		}
		return ePassword;
	}

public:


	hash1()
	{
		for (int i = 0; i < tablesize; i++)
		{
			HashTable[i] = new item;
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
		//Time Complexity O(n^2) 
		int index = Hash(url);
		if (HashTable[index]->url == "")
		{
			HashTable[index]->url = url;
			HashTable[index]->username = caesarEncrypt(username);
			HashTable[index]->password = caesarEncrypt(password);
		}
		else
		{
			item* ptr = HashTable[index];
			item* n = new item;
			n->url = url;
			n->username = caesarEncrypt(username);
			n->password = caesarEncrypt(password);
			n->next = NULL;
			while (ptr->next != NULL)
			{
				ptr->next->prev = ptr;
				ptr = ptr->next;
			}
			ptr->next = n;
		}
	}

	int NumberOfItemsInIndex(string url) {
		//Time Complexity O(n)
		int count = 0;
		int index = Hash(url);
		if (HashTable[index]->url == "") {
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
		//Time complexity O(n^2)
		int index = Hash(url);
		item* ptr = HashTable[index];
		if (ptr->url == "")
		{
			system("cls");
			cout << RED << "There are no account for the given URL" << RESET << endl;
			Sleep(DELAY);
			system("cls");
		}
		else
		{
			cout << "All the Accounts for the Given URL" << endl;
			while (ptr != NULL)
			{
				cout << endl << "--------------------------------\n";
				cout << ptr->url << endl;
				cout << caesarDecrypt(ptr->username) << endl;
				cout << caesarDecrypt(ptr->password) << endl;
				cout << "--------------------------------\n" << endl;
				ptr = ptr->next;

			}
		}
	}

	int DeleteItem(string url, string username, string& password)  //delete the password using the url and username
		//time complexity = O(n)
	{
		int index = Hash(url);
		string encryptUsername = caesarEncrypt(username);
		item* ptr = HashTable[index];
		item* temp = NULL;

		if (ptr->url == "") {
			system("cls");
			cout << RED << "There is no Such Account" << RESET << endl;
			Sleep(DELAY);
			system("cls");
			return 0;
		}

		if (ptr->url != "" && ptr->next == NULL) {

			if (ptr->url == url && ptr->username == encryptUsername) {
				password = caesarDecrypt(ptr->password);
				ptr->url = "";
				ptr->username = "";
				ptr->password = "";
			}
			return 1;
		}
		else if (ptr->url != "" && ptr->next != NULL) {
			if (ptr->url == url && ptr->username == encryptUsername) {
				HashTable[index] = ptr->next;
				password = caesarDecrypt(ptr->password);
				delete ptr;
			}
			return 1;

		}
		else {

			while (ptr->next != NULL)
			{

				if (ptr->next->url == url && ptr->next->username == encryptUsername && ptr->next->next == NULL)
				{
					temp = ptr->next;
					ptr->next = NULL;
					password = caesarDecrypt(temp->password);
					delete temp;
					return 1;

				}
				else if (ptr->url == url && ptr->username == encryptUsername)
				{
					temp = ptr;
					ptr->prev->next = ptr->next;
					password = caesarDecrypt(temp->password);
					delete temp;
					return 1;
				}

				ptr = ptr->next;
			}
			system("cls");
			cout << RED << "There is no Such Account" << RESET << endl;
			Sleep(DELAY);
			system("cls");
			return 0;
		}

	}

	void Search(string& url, string& username)  // search the password using url and username
		//time comlexity =O(n)
	{
		int index = Hash(url);
		item* ptr = HashTable[index];
		if (ptr->url == "") {
			system("cls");
			cout << RED << "There is no Such Account" << RESET << endl;
			Sleep(DELAY);
			system("cls");
			return;
		}
		else {
			while (ptr->next != NULL)
			{
				if (ptr->url == url && ptr->username == caesarEncrypt(username))
				{
					break;
				}
				ptr = ptr->next;

			}
			if (ptr->url == url && ptr->username == caesarEncrypt(username)) {
				system("cls");
				cout << "URL = " << ptr->url << endl;
				cout << "Username = " << caesarDecrypt(ptr->username) << endl;
				cout << "Password = " << caesarDecrypt(ptr->password) << endl << endl;
			}
			else
			{
				system("cls");
				cout << RED << "There is no Such Account" << RESET << endl;
				Sleep(DELAY);
				system("cls");
			}
		}

	}

	void Update(string url, string username, string password)
	{
		int index = Hash(url);
		item* ptr = HashTable[index];
		string encryptUsername = caesarEncrypt(username);
		string encryptPassword = caesarEncrypt(password);
		int count = 0;
		while (ptr->url == url && ptr->username != encryptUsername)
		{
			if (ptr->url == url && ptr->username != encryptUsername)
			{
				ptr->password = encryptPassword;
				count = count + 1;
				break;

			}
			ptr = ptr->next;

		}


		if (ptr->url == "" || count == 0) {
			system("cls");
			cout << RED << "There is no Such Account" << RESET << endl;
			Sleep(DELAY);
			system("cls");
		}
		else {
			system("cls");
			cout << GREEN << "Password Successfully Updated" << RESET << endl;
			Sleep(DELAY);
			system("cls");
		}
	}
};


bool checkPW(string& pw)
{
	int u = 0;
	int n = 0;
	int s = 0;

	for (char c : pw)
	{
		if ('A' <= c && c <= 'Z')
		{
			u = u + 1;
		}
		else if ('0' <= c && c <= '9')
		{
			n = n + 1;
		}
		else if (c == '!' || c == '@' || c == '#' || c == '$' || c == '%' || c == '^' || c == '&')
		{
			s = s + 1;
		}
	}

	if (pw.length() >= 8 && s >= 1 && n >= 2 && u >= 2)
	{

		return 1;
	}
	else {
		return 0;
	}

}

void dummyData(hash1& hesy) {
	hesy.AddUrl("account.google.com", "abc@gmail.com", "AbcD@12htgdG");
	hesy.AddUrl("account.google.com", "xyz@gmail.com", "zcfD@12GuekdA");
	hesy.AddUrl("www.facebook.com/login/", "abc@gmail.com", "Iker45@hkFd^");
	hesy.AddUrl("twitter.com/i/flow/login", "abc@gmail.com", "Yne@D2ft5kel");
	hesy.AddUrl("www.instagram.com/accounts/login/", "xyz@gmail.com", "O89hn$0dlsw");
	hesy.AddUrl("github.com/login", "abc@gmail.com", "T67&hkJo8");

}


int main()
{
	hash1 hesy;
	Singly_Linked_List s;
	dummyData(hesy);
	string no = "0";
	string no2 = "0";
	cout << endl;
	cout << TEAL << "\t\t _____________ WELCOME _____________\n\n\n" << RESET;
	int count;
	string userId, password, id, pass;
	id = "admin";
	pass = "admin";


	do {
		cout << "1. Login " << endl;
		cout << "2. Exit " << endl;
		cout << "\nSelect Option : ";
		cin >> no2;


		switch (no2[0])
		{
		case '1':
			system("cls");
			cout << "Please enter the username and password  " << endl;
			cout << "" << endl;
			cout << "Username : ";
			cin >> userId;
			cout << "Password : ";
			cin >> password;

			if (userId == id && password == pass)
			{
				system("cls");
				cout << GREEN << "LOGIN Successfull" << RESET;
				Sleep(DELAY);
				system("cls");

				do
				{

					cout << TEAL << "___________ Password Management System ___________" << RESET << endl;
					cout << endl;

					cout << "1. Add new Account " << endl;
					cout << "2. Change Existing Password  " << endl;
					cout << "3. Delete Existing password " << endl;
					cout << "4. Search Password " << endl;
					cout << "5. Number of Accounts in Same URL " << endl;
					cout << "6. Show All the Account in a URL " << endl;
					cout << "7. Deleted History " << endl;
					cout << "8. Quit " << endl;
					cout << "\nSelect Option : ";
					cin >> no;



					switch (no[0])
					{
					case '1':
					{
						string url1;
						string username1;
						string password1;
						cout << " Enter the url : ";
						cin >> url1;
						cout << " Enter the userename : ";
						cin >> username1;
						bool q = 0;
						while (q != 1) {
							cout << " Enter the password : ";
							cin >> password1;
							q = checkPW(password1);
							if (q == 1) {
								hesy.AddUrl(url1, username1, password1);
								system("cls");
								cout << GREEN << "Account Successfully Added" << RESET << endl;
								Sleep(DELAY);
								system("cls");
							}
							else {
								cout << RED << "\nEntered password is not secure enough." << RESET << endl;
								cout << RED << " Use at least two upper case letters, numbers and one symbol" << RESET << endl;
								cout << RED << "Also there should be at least 8 characters." << RESET << endl;
								Sleep(DELAY * 2);
								system("cls");
							}
						}
						system("cls");
					}
					break;
					case '2': {
						string url1;
						string username1;
						string password1;
						cout << " Enter the url : ";
						cin >> url1;
						cout << " Enter the username : ";
						cin >> username1;
						bool q = 0;
						while (q != 1) {
							cout << " Enter the new password : ";
							cin >> password1;
							q = checkPW(password1);
							if (q == 1) {
								hesy.Update(url1, username1, password1);
							}
							else {
								cout << RED << "\nEntered password is not secure enough." << RESET << endl;
								cout << RED << " Use at least two upper case letters, numbers and one symbol" << RESET << endl;
								cout << RED << "Also there should be at least 8 characters." << RESET << endl;
								Sleep(DELAY * 2);
								system("cls");
							}

						}
					}
							break;

					case '3':
					{
						string url1;
						string username1;
						string password1 = "";
						cout << " Enter the url : ";
						cin >> url1;
						cout << " Enter the username : ";
						cin >> username1;
						int status = hesy.DeleteItem(url1, username1, password1);
						if (status == 1) {
							time_t currentTime;
							time(&currentTime);

							struct tm localTime;
							localtime_s(&localTime, &currentTime);

							int day = localTime.tm_mday;
							int month = localTime.tm_mon + 1;  // Month is 0-indexed, so add 1
							int year = localTime.tm_year + 1900;  // Years since 1900
							int houre = localTime.tm_hour;
							int mini = localTime.tm_min;
							int sec = localTime.tm_sec;
							string t = "Date : " + to_string(day) + "/" + to_string(month) + "/" + to_string(year) + "  Time : " + to_string(houre) + ":" + to_string(mini) + ":" + to_string(sec);
							s.Insert_First(url1, username1, password1, t);
							system("cls");
							cout << GREEN << "Account Successfully Deleted" << RESET << endl;
							Sleep(DELAY);
							system("cls");
						}
						system("cls");


					}
					break;
					case '4':
					{
						string url1;
						string username1;
						string password1;
						cout << " Enter the url : ";
						cin >> url1;
						cout << " Enter the username : ";
						cin >> username1;
						hesy.Search(url1, username1);


					}

					break;
					case '5':
					{
						string url1;
						cout << " Enter the url : ";
						cin >> url1;
						int count = hesy.NumberOfItemsInIndex(url1);
						if (count <= 0) {
							system("cls");
							cout << RED << "There are no accounts in the system for the given URL" << RESET << endl;
							Sleep(DELAY * 2);
							system("cls");
						}
						system("cls");
						cout << endl;
						cout << "Number of account in same url : " << hesy.NumberOfItemsInIndex(url1) << endl;
					}
					break;
					case '6':
					{
						string url1;
						cout << " Enter the url : ";
						cin >> url1;
						system("cls");
						hesy.PrintInItemUrl(url1);

					}
					break;
					case '7':
					{
						s.Display();
					}
					break;
					case '8':
					{
						system("cls");
						main();
					}
					break;
					default:
					{
						system("cls");
						cout << RED << "Invalid Input. Try Again" << RESET << endl;
						Sleep(DELAY);
						system("cls");

					}
					break;
					}
				} while (true);
			}
			else
			{
				cout << RED << "\n LOGIN ERROR \n please check your user name and password \n" << RESET;

				Sleep(DELAY);
				system("cls");
				main();

			}
			break;
		case '2':
			exit(0);
		default:
			system("cls");
			cout << RED << "Invalid Input Try Again" << RESET << endl;
			Sleep(DELAY);
			system("cls");
			main();
		}

	} while (no[0] <= 2);

}