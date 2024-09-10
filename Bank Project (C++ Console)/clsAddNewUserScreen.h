#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include <iomanip>

class clsAddNewUserScreen : protected clsScreen
{
private:

	static void _ReadUserInfo(clsUser& User)
	{
		cout << "\nEnter FirstName: ";
		User.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter LastName: ";
		User.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Email: ";
		User.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone: ";
		User.Phone = clsInputValidate::ReadString();

		cout << "\nEnter Password: ";
		User.Password = clsInputValidate::ReadString();

		cout << "\nEnter Permission: ";
		User.Permissions = _ReadPermissionToSet();
	}

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

	static int _ReadPermissionToSet()
	{
		int Permission = 0;
		char Answer = 'n';

		cout << "\n\nDo you want to give full access? (y/n)? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y') {

			return -1;
			//return Permission += clsUser::enPermissions::pAll;
		}

		//if Answer is No.

		cout << "\nDo you want to give access to:\n";

		cout << "\nShow Client List? (y/n)? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y') {

			Permission += clsUser::enPermissions::pShowClientList;
		}

		cout << "\nAdd New Client? (y/n)? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y') {

			Permission += clsUser::enPermissions::pAddNewClient;
		}

		cout << "\nDelete Client? (y/n)? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y') {

			Permission += clsUser::enPermissions::pDeleteClient;
		}

		cout << "\nUpdate Client? (y/n)? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y') {

			Permission += clsUser::enPermissions::pUpdateClient;
		}

		cout << "\nFind Client? (y/n)? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y') {

			Permission += clsUser::enPermissions::pFindClient;
		}

		cout << "\nTransactions? (y/n)? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y') {

			Permission += clsUser::enPermissions::pTransactions;
		}

		cout << "\nManage Users? (y/n)? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y') {

			Permission += clsUser::enPermissions::pManageUsers;
		}

		cout << "\nShow Login Register? (y/n)? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y') {

			Permission += clsUser::enPermissions::pLoginRegister;
		}

		return Permission;
	}

public:

	static void ShowAddNewUserScreen()
	{
		_DrawScreenHeader("\t Add New User Screen");

		string UserName = "";

		cout << "\nPlease Enter User Name: ";
		UserName = clsInputValidate::ReadString();

		while (clsUser::IsUserExist(UserName))
		{
			cout << "\nUser Name Is Already Used, Choose another one: ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::GetAddNewUserObject(UserName);

		_ReadUserInfo(User);

		clsUser::enSaveResults SaveResults;
		SaveResults = User.Save();

		switch (SaveResults)
		{
		case clsUser::enSaveResults::svSucceeded:

			cout << "\nUser Addeded Successfully :-)\n";
			_PrintUserInfo(User);
			break;

		case clsUser::enSaveResults::svFaildEmptyObject:

			cout << "\nError User was not saved because it's Empty";
			break;

		case clsUser::svFaildObjectexists:

			cout << "\nError User was not saved because User Name is used!\n";
			break;
		}
	}

};