#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>
#include "clsUtil.h"

class clsTotalBalancesScreen : protected clsScreen
{
private:

	static void _PrintClientRecordBalanceLine(clsBankClient Client)
	{
		cout << setw(15) << left << "" << "\t\t";
		cout << "| " << setw(15) << left << Client.AccountNumber();
		cout << "| " << setw(40) << left << Client.FullName();
		cout << "| " << setw(12) << left << Client.AccountBalance;
	}

	static void _TotalBalancesScreenHeader(vector <clsBankClient> vClients)
	{
		cout << "\n" << setw(15) << left << "" << "________________________________________";
		cout << "_______________________________________\n\n";
		cout << setw(15) << left << "" << "\t\t";
		cout << "| " << left << setw(15) << "Accout Number";
		cout << "| " << left << setw(40) << "Client Name";
		cout << "| " << left << setw(12) << "Balance";
		cout << "\n" << setw(15) << left << "" << "________________________________________";
		cout << "_______________________________________\n\n";
	}

	static void _TotalBalancesClientsList(vector <clsBankClient> vClients, double TotalBalances)
	{
		if (vClients.size() == 0) {

			cout << "\t\t\t\tNo Clients Available In the System!";
		}
		else {

			//ranged loop.
			for (clsBankClient& Client : vClients)
			{
				_PrintClientRecordBalanceLine(Client);
				cout << endl;
			}
			cout << "\n" << setw(15) << left << "" << "________________________________________";
			cout << "_______________________________________\n\n";

			cout << setw(68) << left << "" << "Total Balances = " << TotalBalances << endl;
			cout << setw(50) << left << "" << "( " << clsUtil::NumberToText(TotalBalances) << ")";
		}
	}

public:

	static void ShowTotalBalancesScreen()
	{
		vector <clsBankClient> vClients = clsBankClient::GetClientsList();


		string Title = "\t Total Balances Screen";
		string Subtitle = "\t   (" + to_string(vClients.size()) + ") Client(s).";

		_DrawScreenHeader(Title, Subtitle);

		_TotalBalancesScreenHeader(vClients);

		double TotalBalances = clsBankClient::GetTotalBalances();

		_TotalBalancesClientsList(vClients, TotalBalances);
	}

};