#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsTransferScreen : protected clsScreen
{
private:

	static void _PrintClient(clsBankClient Client)
	{
		cout << "\n" << setw(5) << left << "" << "__________________________________\n";
		cout << "\n" << setw(5) << left << "" << "\t\tClient Card";
		cout << "\n" << setw(5) << left << "" << "__________________________________\n";
		cout << "\n" << setw(5) << left << "" << "-> Full Name   : " << Client.FullName();
		cout << "\n" << setw(5) << left << "" << "-> Acc. Number : " << Client.AccountNumber();
		cout << "\n" << setw(5) << left << "" << "-> Balance     : " << Client.AccountBalance;
		cout << "\n" << setw(5) << left << "" << "__________________________________\n";
	}

	static string ReadClientAccNumber(string Massage)
	{
		string AccountNumber = "";

		cout << "\n" << Massage;
		AccountNumber = clsInputValidate::ReadString();
		//Validation.
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount number is not found, choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}
		return AccountNumber;
	}

	static double _ReadTransferAmount(clsBankClient ClientSource)
	{
		double Amount = 0;
		cout << "\n\nEnter Transfer Amount? ";
		Amount = clsInputValidate::ReadDblNumber();

		//Validation for Amount
		while (Amount > ClientSource.AccountBalance)
		{
			cout << "\nAmount Exceeds the available Balance, Enter another Amount ? ";
			Amount = clsInputValidate::ReadDblNumber();
		}

		return Amount;
	}

public:

	static void ShowTransferScreen()
	{
		_DrawScreenHeader("\t    Transfer Screen");
		string AccountNumber = "";

		AccountNumber = ReadClientAccNumber("Please Enter Account Number to Transfer From: ");
		clsBankClient ClientSource = clsBankClient::Find(AccountNumber);
		_PrintClient(ClientSource);

		//_______________________________________//

		//Validation for AccNumber Frequency.
		AccountNumber = ReadClientAccNumber("Please Enter Account Number to Transfer To: ");
		while (ClientSource.AccountNumber() == AccountNumber)
		{
			cout << "\nError!! You can NOT tranfer to the Same Account Number, choose another one:\n";
			AccountNumber = ReadClientAccNumber("Please Enter Account Number to Transfer To: ");
		}

		clsBankClient ClientDestination = clsBankClient::Find(AccountNumber);
		_PrintClient(ClientDestination);

		double Amount = _ReadTransferAmount(ClientSource);

		//_______________________________________//

		char Answer = 'n';
		cout << "\nAre you sure you want to perform this operation? (y/n)? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y') {

			ClientSource.Transfer(Amount, ClientDestination);

			cout << "\nTransfer done Successfully :-)\n";
			_PrintClient(ClientSource);
			_PrintClient(ClientDestination);
		}
		else {

			cout << "\nOperation was Cancelled :-(\n";
		}
	}
};