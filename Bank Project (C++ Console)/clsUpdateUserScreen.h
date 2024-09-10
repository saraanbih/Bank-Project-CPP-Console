#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsUpdateUserScreen : protected clsScreen
{
private:

	static void _ReadUserInfo(clsUser& User1)
	{
		cout << "\nEnter FirstName: ";
		User1.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter LastName: ";
		User1.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Email: ";
		User1.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone: ";
		User1.Phone = clsInputValidate::ReadString();

		cout << "\nEnter Password: ";
		User1.Password = clsInputValidate::ReadString();

		cout << "\nEnter Permission: ";
		User1.Permissions = _ReadPermissionToSet();
	}

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

	static void ShowUpdateUserScreen()
	{
		_DrawScreenHeader("\t  Update User Screen");

		string UserName = "";

		cout << "\nPlease Enter User Name: ";
		UserName = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(UserName))
		{
			cout << "\nUser Name is not found, choose another one: ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser User1 = clsUser::Find(UserName);
		_PrintUserInfo(User1);

		char Answer = 'n';

		cout << "\nAre you sure you want to Update this User ? (y/n)? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y') {

			cout << "\n\nUpdate User Info:";
			cout << "\n____________________\n";

			_ReadUserInfo(User1);

			clsUser::enSaveResults SaveResult;

			SaveResult = User1.Save();

			switch (SaveResult)
			{
			case clsUser::enSaveResults::svSucceeded:

				cout << "\nUser Updated Successfully :-)\n";
				_PrintUserInfo(User1);
				break;

			case clsUser::enSaveResults::svFaildEmptyObject:

				cout << "\nError user was not saved because it's Empty";
				break;
			}
		}
	}

};
