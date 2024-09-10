#pragma once
#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include <fstream>
#include "clsUser.h"

class clsLoginRegisterScreen : protected clsScreen
{
private:

	static void LoginRegisterHeader()
	{
		cout << "\n" << setw(6) << left << "" << "_______________________________________________________";
		cout << "____________________________________________________\n" << endl;

		cout << setw(6) << left << "";
		cout << "| " << left << setw(35) << "Date/Time";
		cout << "| " << left << setw(25) << "User Name";
		cout << "| " << left << setw(25) << "Password";
		cout << "| " << left << setw(13) << "Permissins";

		cout << "\n" << setw(6) << left << "" << "_______________________________________________________";
		cout << "____________________________________________________\n" << endl;
	}

	static void PrintLoginRegisterRecordLine(clsUser::stLoginRegisterRecord LoginRegisterRecord)
	{
		cout << setw(6) << left << "";
		cout << "| " << left << setw(35) << LoginRegisterRecord.DateTime;
		cout << "| " << left << setw(25) << LoginRegisterRecord.UserName;
		cout << "| " << left << setw(25) << LoginRegisterRecord.Password;
		cout << "| " << left << setw(13) << LoginRegisterRecord.Permissions;
	}

public:

	static void ShowLoginRegisterScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pLoginRegister)) {

			return;
		}

		vector <clsUser::stLoginRegisterRecord> vLoginRegisterRecord;
		vLoginRegisterRecord = clsUser::GetLoginRegisterList();

		string Title = "     Login Register List Screen";
		string Subtitle = "\t    (" + to_string(vLoginRegisterRecord.size()) + ") Record(s).";

		_DrawScreenHeader(Title, Subtitle);

		LoginRegisterHeader();

		//ranged loop.
		for (clsUser::stLoginRegisterRecord& Record : vLoginRegisterRecord)
		{
			PrintLoginRegisterRecordLine(Record);
			cout << endl;
		}

		cout << "\n" << setw(6) << left << "" << "_______________________________________________________";
		cout << "____________________________________________________\n" << endl;
	}

};