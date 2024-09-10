#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsDeleteUserScreen : protected clsScreen
{
private:

	static void _PrintUserInfo(clsUser User)
	{
		cout << "\n" << setw(5) << left << "" << "__________________________________\n";
		cout << "\n" << setw(5) << left << "" << "\t\tUser Card";
		cout << "\n" << setw(5) << left << "" << "__________________________________\n";
		cout << "\n" << setw(5) << left << "" << "-> FirstName   : " << User.FirstName;
		cout << "\n" << setw(5) << left << "" << "-> LastName    : " << User.LastName;
		cout << "\n" << setw(5) << left << "" << "-> Full Name   : " << User.FullName();
		cout << "\n" << setw(5) << left << "" << "-> Email       : " << User.Email;
		cout << "\n" << setw(5) << left << "" << "-> Phone       : " << User.Phone;
		cout << "\n" << setw(5) << left << "" << "-> User Name   : " << User.UserName;
		cout << "\n" << setw(5) << left << "" << "-> Password    : " << User.Password;
		cout << "\n" << setw(5) << left << "" << "-> Permissions : " << User.Permissions;
		cout << "\n" << setw(5) << left << "" << "__________________________________\n";
	}

public:

	static void ShowDeleteUserScreen()
	{
		_DrawScreenHeader("\t Delete User Screen");

		string UserName = "";

		cout << "\nPlease Enter User Name: ";
		UserName = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(UserName))
		{
			cout << "\nUser Name is not found, choose another one: ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::Find(UserName);

		_PrintUserInfo(User);

		char Answer = 'n';

		cout << "\nAre you sure you want to delete this User (y/n)? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			if (User.Delete()) {

				cout << "\nUser Deleted Successfully :-)\n";
				_PrintUserInfo(User);
			}
			else {

				cout << "\nError User Was not Deleted\n";
			}
		}
		else {

			cout << "\nOperation was Cancelled\n";
		}
	}

};
