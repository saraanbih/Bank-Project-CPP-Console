#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
#include "clsMainScreen.h"
#include "Global.h"

class clsLoginScreen : protected clsScreen
{
private:

	static bool _Login()
	{
		string UserName = "", Password = "";
		bool LoginFaild = false;
		short LoginFaildCount = 3;

		do
		{
			if (LoginFaild)
			{
				--LoginFaildCount;
				cout << "\n\nInvalid (UserName/Password)!\n";
				cout << "You have " << LoginFaildCount << " Trial(s) to login.\n\n";
			}

			if (LoginFaildCount == 0) {

				cout << "\nYou are Locked after 3 failed Trials\n\n";
				return false;
			}

			cout << "Enter User Name? ";
			UserName = clsInputValidate::ReadString();

			cout << "Enter Password? ";
			Password = clsInputValidate::ReadString();

			CurrentUser = clsUser::Find(UserName, Password);

			LoginFaild = CurrentUser.IsEmpty();

		} while (LoginFaild);

		CurrentUser.RegisterLogin();
		clsMainScreen::ShowMainMenue();
		return true;
	}

public:

	static bool ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\t    Login Screen");

		return _Login();
	}
};