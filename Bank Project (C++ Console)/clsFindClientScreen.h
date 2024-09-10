#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsFindClientScreen : protected clsScreen
{
private:

	static void _PrintClient(clsBankClient Client)
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

	static void ShowFindClientScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pFindClient)) {

			return;
		}

		_DrawScreenHeader("\t Find Client Screen");

		string AccountNumber = "";

		cout << "\nPlease Enter client Account Number: ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount number is not found, choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client1 = clsBankClient::Find(AccountNumber);

		if (!Client1.IsEmpty())
		{
			cout << "\nClient Found :-)\n";
		}
		else
		{
			cout << "\nClient Was not Found :-(\n";
		}

		_PrintClient(Client1);
	}

};

