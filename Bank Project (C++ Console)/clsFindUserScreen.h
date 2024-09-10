#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsFindUserScreen : protected clsScreen
{
private:

	static void _PrintUserInfo(clsUser User1)
	{
		cout << "\n" << setw(5) << left << "" << "__________________________________\n";
		cout << "\n" << setw(5) << left << "" << "\t\tUser Card";
		cout << "\n" << setw(5) << left << "" << "__________________________________\n";
		cout << "\n" << setw(5) << left << "" << "-> FirstName   : " << User1.FirstName;
		cout << "\n" << setw(5) << left << "" << "-> LastName    : " << User1.LastName;
		cout << "\n" << setw(5) << left << "" << "-> Full Name   : " << User1.FullName();
		cout << "\n" << setw(5) << left << "" << "-> Email       : " << User1.Email;
		cout << "\n" << setw(5) << left << "" << "-> Phone       : " << User1.Phone;
		cout << "\n" << setw(5) << left << "" << "-> User Name   : " << User1.UserName;
		cout << "\n" << setw(5) << left << "" << "-> Password    : " << User1.Password;
		cout << "\n" << setw(5) << left << "" << "-> Permissions : " << User1.Permissions;
		cout << "\n" << setw(5) << left << "" << "__________________________________\n";
	}

public:

	static void ShowFindUserScreen()
	{
		_DrawScreenHeader("\t   Find User Screen");

		string UserName = "";

		cout << "\nPlease Enter User Name: ";
		UserName = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(UserName))
		{
			cout << "\nUser is not found, choose another one: ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser User1 = clsUser::Find(UserName);

		if (!User1.IsEmpty())
		{
			cout << "\nUser Found :-)\n";
		}
		else
		{
			cout << "\nUser Was not Found :-(\n";
		}

		_PrintUserInfo(User1);
	}
};