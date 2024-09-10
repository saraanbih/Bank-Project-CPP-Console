#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include <iomanip>

class clsAddNewClientScreen : protected clsScreen
{
	static void _ReadClientInfo(clsBankClient& Client)
	{
		cout << "\nEnter FirstName: ";
		Client.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter LastName: ";
		Client.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Email: ";
		Client.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone: ";
		Client.Phone = clsInputValidate::ReadString();

		cout << "\nEnter PinCode: ";
		Client.PinCode = clsInputValidate::ReadString();

		cout << "\nEnter Account Balance: ";
		Client.AccountBalance = clsInputValidate::ReadFloatNumber();
	}

	static void _PrintClientInfo(clsBankClient Client)
	{
		cout << "\n" << setw(5) << left << "" << "__________________________________\n";
		cout << "\n" << setw(5) << left << "" << "\t\tClient Card";
		cout << "\n" << setw(5) << left << "" << "__________________________________\n";
		cout << "\n" << setw(5) << left << "" << "-> FirstName   : " << Client.FirstName;
		cout << "\n" << setw(5) << left << "" << "-> LastName    : " << Client.LastName;
		cout << "\n" << setw(5) << left << "" << "-> Full Name   : " << Client.FullName();
		cout << "\n" << setw(5) << left << "" << "-> Email       : " << Client.Email;
		cout << "\n" << setw(5) << left << "" << "-> Phone       : " << Client.Phone;
		cout << "\n" << setw(5) << left << "" << "-> Acc. Number : " << Client.AccountNumber();
		cout << "\n" << setw(5) << left << "" << "-> Password    : " << Client.PinCode;
		cout << "\n" << setw(5) << left << "" << "-> Balance     : " << Client.AccountBalance;
		cout << "\n" << setw(5) << left << "" << "__________________________________\n";
	}

public:

	static void ShowAddNewClientScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient)) {

			return;
		}

		_DrawScreenHeader("\t Add New Client Screen");

		string AccountNumber = "";

		cout << "\nPlease Enter Account Number: ";
		AccountNumber = clsInputValidate::ReadString();

		while (clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number Is Already Used, Choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);
		_ReadClientInfo(NewClient);

		clsBankClient::enSaveResults SaveResult;

		SaveResult = NewClient.Save();

		switch (SaveResult)
		{
		case clsBankClient::enSaveResults::svSucceeded:

			cout << "\nAccount Addeded Successfully :-)\n";
			_PrintClientInfo(NewClient);
			break;

		case clsBankClient::enSaveResults::svFaildEmptyObject:

			cout << "\nError account was not saved because it's Empty";
			break;

		case clsBankClient::enSaveResults::svFaildAccountNumberExists:

			cout << "\nError account was not saved because account number is used!\n";
			break;

		}
	}

};

