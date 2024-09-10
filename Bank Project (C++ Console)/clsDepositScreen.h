#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsDepositScreen : protected clsScreen
{
private:

	static string _ReadAccountNumber()
	{
		string AccountNumber = "";

		cout << "\nPlease Enter client Account Number? ";
		AccountNumber = clsInputValidate::ReadString();

		return AccountNumber;
	}

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

	static void ShowDepositScreen()
	{
		_DrawScreenHeader("\t Deposit Screen");

		string AccountNumber = _ReadAccountNumber();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
			AccountNumber = _ReadAccountNumber();
		}

		clsBankClient Client1 = clsBankClient::Find(AccountNumber);

		_PrintClient(Client1);

		cout << "\nPlease enter deposit amount? ";
		double Amount = 0;
		Amount = clsInputValidate::ReadDblNumber();

		char Answer = 'n';

		cout << "\nAre you sure you want to perform this transaction ( y / n ) ? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y') {

			Client1.Deposit(Amount);

			cout << "\nAmount Deposited Successfully.\n";
			cout << "\nNew Balance Is: " << Client1.AccountBalance;
		}
		else {

			cout << "\nOperation was Cancelled.\n";
		}
	}

};
