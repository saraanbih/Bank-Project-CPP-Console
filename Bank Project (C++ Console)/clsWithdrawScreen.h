#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsWithdrawScreen : protected clsScreen
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

	static void ShowWithdrawScreen()
	{
		_DrawScreenHeader("\t Withdraw Screen");

		string AccountNumber = "";
		AccountNumber = _ReadAccountNumber();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
			AccountNumber = _ReadAccountNumber();
		}


		clsBankClient Client1 = clsBankClient::Find(AccountNumber);

		_PrintClient(Client1);

		double Amount = 0;

		cout << "\nPlease enter Withdraw amount? ";
		Amount = clsInputValidate::ReadDblNumber();

		char Answer = 'n';

		cout << "\nAre you sure you want to perform this transaction ( y / n ) ? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y') {

			if (Client1.Withdraw(Amount)) {

				cout << "\nAmount Withdrawn Successfully.\n";
				cout << "\nNew Balance Is: " << Client1.AccountBalance;
			}
			else {

				cout << "\nSorry..your Balance isn't enough to withdraw this Amount,"
					"you Only have : " << Client1.AccountBalance << "\n";
			}
		}
		else {

			cout << "\nOperation was Cancelled.\n";
		}

	}

};