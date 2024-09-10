#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>
using namespace std;

class clsBankClient : public clsPerson
{
private:

	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };

	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	double _AccountBalance;
	bool _MarkedForDelete = false;

	struct stTransferLogRecord; //Function Declaration.

	static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
	{
		vector<string> vClientData;
		vClientData = clsString::Split(Line, Seperator);
		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
			vClientData[3], vClientData[4], clsUtil::DecryptText(vClientData[5], 4), stod(vClientData[6]));
	}

	static string _ConverClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
	{
		string stClientRecord = "";
		stClientRecord += Client.FirstName + Seperator;
		stClientRecord += Client.LastName + Seperator;
		stClientRecord += Client.Email + Seperator;
		stClientRecord += Client.Phone + Seperator;
		stClientRecord += Client.AccountNumber() + Seperator;
		stClientRecord += clsUtil::EncryptText(Client.PinCode, 4) + Seperator;
		stClientRecord += to_string(Client.AccountBalance);
		return stClientRecord;
	}

	static vector <clsBankClient> _LoadClientsDataFromFile()
	{
		vector <clsBankClient> vClients;
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);//read Mode
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLinetoClientObject(Line);
				vClients.push_back(Client);
			}
			MyFile.close();
		}
		return vClients;
	}

	static void _SaveCleintsDataToFile(vector <clsBankClient> vClients)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out);//overwrite
		string DataLine;
		if (MyFile.is_open())
		{
			for (clsBankClient& C : vClients)
			{
				if (C.MarkedForDeleted() == false)
				{
					//we only write records that are not marked for delete.
					DataLine = _ConverClientObjectToLine(C);
					MyFile << DataLine << endl;
				}
			}
			MyFile.close();
		}
	}

	void _Update()
	{
		vector <clsBankClient> _vClients;

		_vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : _vClients)
		{
			if (C.AccountNumber() == _AccountNumber)
			{
				C = *this;
				break;
			}
		}
		_SaveCleintsDataToFile(_vClients);
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConverClientObjectToLine(*this));
	}

	void _AddDataLineToFile(string stDataLine)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out | ios::app);
		if (MyFile.is_open())
		{
			MyFile << stDataLine << endl;
			MyFile.close();
		}
	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	string _PrepareTransferLogRecord(clsBankClient ClientDestination, double Amount, string Separator = "#//#")
	{
		string sTransferLogDataLine = "";

		sTransferLogDataLine += clsDate::GetSystemDateTimeString() + Separator;
		sTransferLogDataLine += _AccountNumber + Separator;
		sTransferLogDataLine += ClientDestination._AccountNumber + Separator;
		sTransferLogDataLine += to_string(Amount) + Separator;
		sTransferLogDataLine += to_string(_AccountBalance) + Separator;
		sTransferLogDataLine += to_string(ClientDestination._AccountBalance) + Separator + CurrentUser.UserName;

		return sTransferLogDataLine;
	}

	void RegisterTransferLog(clsBankClient ClientDestination, double Amount)
	{
		fstream MyFile;
		string Line = "";

		MyFile.open("TransferLog.txt", ios::out | ios::app); // Append Mode.

		if (MyFile.is_open())
		{
			Line = _PrepareTransferLogRecord(ClientDestination, Amount);

			MyFile << Line << endl;
			MyFile.close();
		}
	}

	static stTransferLogRecord _ConvertTransferLogDataLineToRecord(string Line, string Separator = "#//#")
	{
		stTransferLogRecord TransferLogRecord;

		vector <string> vTransferLogDataLine;
		vTransferLogDataLine = clsString::Split(Line, Separator);

		TransferLogRecord.DateTime = vTransferLogDataLine[0];
		TransferLogRecord.SourceAccountNumber = vTransferLogDataLine[1];
		TransferLogRecord.DestinationAccountNumber = vTransferLogDataLine[2];
		TransferLogRecord.Amount = stod(vTransferLogDataLine[3]);
		TransferLogRecord.srcBalanceAfter = stod(vTransferLogDataLine[4]);
		TransferLogRecord.destBalanceAfter = stod(vTransferLogDataLine[5]);
		TransferLogRecord.UserName = vTransferLogDataLine[6];

		return TransferLogRecord;
	}

public:

	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode, double AccountBalance) :
		clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

	struct stTransferLogRecord
	{
		string DateTime;
		string SourceAccountNumber;
		string DestinationAccountNumber;
		double Amount = 0.00;
		double srcBalanceAfter = 0.00;
		double destBalanceAfter = 0.00;
		string UserName;
	};

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	bool MarkedForDeleted()
	{
		return _MarkedForDelete;
	}

	string AccountNumber()
	{
		return _AccountNumber;
	}

	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}

	string GetPinCode()
	{
		return _PinCode;
	}

	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	void SetAccountBalance(double AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}

	double GetAccountBalance()
	{
		return _AccountBalance;
	}

	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) double AccountBalance;

	/*
	void Print()
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName : " << FirstName;
		cout << "\nLastName : " << LastName;
		cout << "\nFull Name : " << FullName();
		cout << "\nEmail : " << Email;
		cout << "\nPhone : " << Phone;
		cout << "\nAcc. Number : " << _AccountNumber;
		cout << "\nPassword : " << _PinCode;
		cout << "\nBalance : " << _AccountBalance;
		cout << "\n___________________\n";
	}*/

	static clsBankClient Find(string AccountNumber)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);//read Mode
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLinetoClientObject(Line);
				if (Client.AccountNumber() == AccountNumber)
				{
					MyFile.close();
					return Client;
				}
			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber, string PinCode)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);//read Mode
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLinetoClientObject(Line);
				if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
				{
					MyFile.close();
					return Client;
				}
			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2 };

	enSaveResults Save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:
		{
			if (IsEmpty())
			{
				return enSaveResults::svFaildEmptyObject;
			}
		}
		case enMode::UpdateMode:
		{
			_Update();
			return enSaveResults::svSucceeded;
			break;
		}
		case enMode::AddNewMode:
		{
			//This will add new record to file or database
			if (clsBankClient::IsClientExist(_AccountNumber))
			{
				return enSaveResults::svFaildAccountNumberExists;
			}
			else
			{
				_AddNew();
				//We need to set the mode to update after add new
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}
			break;
		}
		}
	}

	static bool IsClientExist(string AccountNumber)
	{
		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		return (!Client1.IsEmpty());
	}

	bool Delete()
	{
		vector <clsBankClient> _vClients;

		_vClients = _LoadClientsDataFromFile();
		for (clsBankClient& C : _vClients)
		{
			if (C.AccountNumber() == _AccountNumber)
			{
				C._MarkedForDelete = true;
				break;
			}
		}
		_SaveCleintsDataToFile(_vClients);
		*this = _GetEmptyClientObject();
		return true;
	}

	static clsBankClient GetAddNewClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	static vector <clsBankClient> GetClientsList()
	{
		return _LoadClientsDataFromFile();
	}

	static double GetTotalBalances()
	{
		vector <clsBankClient> vClients = clsBankClient::GetClientsList();
		double TotalBalances = 0;
		for (clsBankClient& Client : vClients)
		{
			TotalBalances += Client.AccountBalance;
		}
		return TotalBalances;
	}

	void Deposit(double Amount)
	{
		_AccountBalance += Amount;
		Save();
	}

	bool Withdraw(double Amount)
	{
		if (Amount > _AccountBalance) {

			return false;
		}
		else {

			_AccountBalance -= Amount;
			Save();
			return true;
		}
	}

	bool Transfer(double Amount, clsBankClient& ClientDestination)
	{
		if (Amount > _AccountBalance) {

			return false;
		}

		Withdraw(Amount);
		ClientDestination.Deposit(Amount);
		RegisterTransferLog(ClientDestination, Amount);
		return true;
	}

	static vector <stTransferLogRecord> GetTransfersLogList()
	{
		vector <stTransferLogRecord> vTransferLogRecord;
		stTransferLogRecord TransferRecord;
		string Line = "";

		fstream MyFile;

		MyFile.open("TransferLog.txt", ios::in); //Read Mode.

		if (MyFile.is_open())
		{
			while (getline(MyFile, Line))
			{
				if (Line != "")
				{
					TransferRecord = _ConvertTransferLogDataLineToRecord(Line);
					vTransferLogRecord.push_back(TransferRecord);
				}
			}

			MyFile.close();
		}

		return vTransferLogRecord;
	}

};