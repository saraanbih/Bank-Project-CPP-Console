#pragma once
#include <iostream>
#include "clsUser.h"
#include "Global.h"
#include "clsDate.h"
#include <iomanip>
using namespace std;

class clsScreen
{
protected:

	static void _DrawScreenHeader(string Title, string SubTitle = "")
	{
		cout << "\t\t\t\t\t______________________________________";
		cout << "\n\n\t\t\t\t\t " << Title;
		if (SubTitle != "")
		{
			cout << "\n\t\t\t\t\t " << SubTitle;
		}
		cout << "\n\t\t\t\t\t______________________________________\n\n";

		cout << setw(40) << left << "" << "User: " << CurrentUser.UserName << endl;
		cout << setw(40) << left << "" << "Date: " << clsDate::DateToString(clsDate()) << "\n\n";

		//clsDate Date1 = clsDate::GetSystemDate();
		//cout << setw(40) << left << "" << "Date: " << Date1.DateToString() << "\n\n";
	}

	static bool CheckAccessRights(clsUser::enPermissions Permission)
	{
		if (!CurrentUser.CheckAccessPermissions(Permission))
		{
			cout << "\t\t\t\t\t______________________________________";
			cout << "\n\n\t\t\t\t\t " << "  Access Denied Contact your Admin.";
			cout << "\n\t\t\t\t\t______________________________________\n\n";

			return false;
		}
		else
			return true;
	}

};
