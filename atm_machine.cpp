// ATM Machine
#include <iostream>
#include <fstream>
#include <conio.h>
using namespace std;

string save_dir = "data\\";

void withdraw(double &balance, string &filename)
{
	double amount;
	char key;
	system("cls");
	cout<<"Current Balance: $"<<balance<<endl;
	cout<<"Please enter amount to Withdraw: $";
	cin>>amount;
	if(amount > 0 && amount <= balance)
	{
		balance -= amount;
		cout<<"Amount Deposit: $"<<amount<<endl;
		cout<<"Current Balance: $"<<balance<<endl;

		//save to file
		ofstream file(filename.c_str());
		file << balance;
		file.close();

		cout<<"If you want to proceed with another deposit press Y (any other to go back): ";
		cin>>key;

		if(key == 'y' || key == 'Y') withdraw(balance, filename);
		else system("cls");
	}
	else
	{
		cout<<"Please enter a valid amount"<<endl;
	}
}

void deposit(double &balance, string &filename)
{
	double amount;
	char key;
	system("cls");
	cout<<"Current Balance: $"<<balance<<endl;
	cout<<"Please enter amount to Deposit: $";
	cin>>amount;
	if(amount > 0)
	{
		balance += amount;
		cout<<"Amount Deposit: $"<<amount<<endl;
		cout<<"Current Balance: $"<<balance<<endl;

		//save to file
		ofstream file(filename.c_str());
		file << balance;
		file.close();

		cout<<"If you want to proceed with another deposit press Y (any other to go back): ";
		cin>>key;

		if(key == 'y' || key == 'Y') deposit(balance, filename);
		else system("cls");
	}
	else
	{
		cout<<"Please enter a valid amount"<<endl;
	}
}

void loadBalance(double &balance, string &filename)
{
	ifstream file(filename.c_str());
	if (file.is_open()) file >> balance;
	file.close();
}

int main()
{
	int max_attempts = 3;
	int d_max_attempts = max_attempts;
	while(max_attempts >= 1)
	{
		bool loggedin = false;
		double c_balance = 14999;

		// usernames are in serial starting from index 0 upto how much you want.
		//string users[3] = {"aakash", "maya", "jack"};

		// now 2d array which is more good and maybe easy.
		string users[3][2] ={ {"aakash", "1234"}, {"maya", "5678"}, {"lilly", "0000"} };

		// the passwords are important to be in the same index as the usernames(users) to be assigned to that user.
		//int pins[3] = {4789, 1234, 0000};
		string username;

		int users_arr_size = sizeof(users) / sizeof(users[0]);

		string pin_input;

		int option, i;
		
		cout<<"\t>>> Welcome to Aakash's ATM <<<"<<endl<<endl;
		cout<<"Please Enter username & password (type exit to quit): "<<endl;
		while(!loggedin)
		{
			cout<<"Username: ";
			cin>>username;
			
			if(username == "exit") return 0;

			cout<<"Password: ";
			cin>>pin_input;

			bool isFound = false;

			for(i = 0; i < users_arr_size;  i++)
			{
				if(username == users[i][0] && pin_input == users[i][1])
				{
					loadBalance(c_balance, users[i][0]);
					max_attempts = d_max_attempts;
					loggedin = true;
					isFound = true;
					ifstream file(users[i][0].c_str());
					if(file.is_open())
						file >> c_balance;
					else
					{
						ofstream file(users[i][0].c_str());
						file << c_balance;
						file.close();
					}
					system("cls");
					break;
				}
			}

			if(!isFound)
			{
				if(max_attempts >= 1)
				{
					max_attempts--;
					cout<<"Incorrect username or password. Try Again!\nYou have "<<max_attempts<<" attempts remaining."<<endl;
				}
				else
				{
					cout<<"You are locked out. Please Try again after a few moments."<<endl;
					break;
				}
			}
		}

		while(loggedin)
		{
			cout<<"\t\tWelcome Back, "<<username<<endl;
			cout<<"<<<Please Choose an option>>>"<<endl;
			cout<<"1. Withdraw Money"<<endl;
			cout<<"2. Deposit Money"<<endl;
			cout<<"3. Check Current Balance"<<endl;
			cout<<"4. Logout"<<endl;
			cout<<"5. Exit"<<endl;

			cin>>option;

			switch(option)
			{
				case 1:
					withdraw(c_balance, users[i][0]);
					break;
				case 2:
					deposit(c_balance, users[i][0]);
					break;
				case 3:
					system("cls");
					cout<<"Current Balance: $"<<c_balance<<endl<<endl;
					break;
				case 4:
					loggedin = false;
					system("cls");
					break;
				case 5:
					return 0;
				default:
					cout<<"\aPlease enter a valid option"<<endl;
					break;
			}
		}
	}

	return 0;
}
