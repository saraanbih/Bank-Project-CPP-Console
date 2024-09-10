#pragma once
#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include <fstream>
#include "clsBankClient.h"

class clsTransferLogScreen : protected clsScreen
{
private:

	static void TransferLogHeader()
	{
		cout << "\n" << setw(6) << left << "" << "_______________________________________________________";
		cout << "____________________________________________________\n" << endl;

		cout << setw(6) << left << "";
		cout << "| " << left << setw(25) << "Date/Time";
		cout << "| " << left << setw(12) << "S.AccNumber";
		cout << "| " << left << setw(12) << "D.AccNumber";
		cout << "| " << left << setw(10) << "Amount";
		cout << "| " << left << setw(12) << "S.Balance";
		cout << "| " << left << setw(12) << "D.Balance";
		cout << "| " << left << setw(9) << "User";

		cout << "\n" << setw(6) << left << "" << "_______________________________________________________";
		cout << "____________________________________________________\n" << endl;
	}

	static void PrintTransferLogRecordLine(clsBankClient::stTransferLogRecord TransferLogRecord)
	{
		cout << setw(6) << left << "";
		cout << "| " << left << setw(25) << TransferLogRecord.DateTime;
		cout << "| " << left << setw(12) << TransferLogRecord.SourceAccountNumber;
		cout << "| " << left << setw(12) << TransferLogRecord.DestinationAccountNumber;
		cout << "| " << left << setw(10) << TransferLogRecord.Amount;
		cout << "| " << left << setw(12) << TransferLogRecord.srcBalanceAfter;
		cout << "| " << left << setw(12) << TransferLogRecord.destBalanceAfter;
		cout << "| " << left << setw(9) << TransferLogRecord.UserName;
	}

public:

	static void ShowTransferLogScreen()
	{
		vector <clsBankClient::stTransferLogRecord> vTransferLogRecord;
		vTransferLogRecord = clsBankClient::GetTransfersLogList();

		string Title = "\tTransfer Log List Screen";
		string Subtitle = "\t   (" + to_string(vTransferLogRecord.size()) + ") Record(s).";

		_DrawScreenHeader(Title, Subtitle);

		TransferLogHeader();

		if (vTransferLogRecord.size() == 0) {

			cout << "\t\t\t\tNo Transfer Log Records Available In the System!";
		}
		else {

			//Ranged loop.
			for (clsBankClient::stTransferLogRecord& LogRecord : vTransferLogRecord)
			{
				PrintTransferLogRecordLine(LogRecord);
				cout << endl;
			}
		}

		cout << "\n" << setw(6) << left << "" << "_______________________________________________________";
		cout << "____________________________________________________\n" << endl;

	}

};