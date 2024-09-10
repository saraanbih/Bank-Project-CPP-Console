#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>
#include "clsDate.h"
#include "clsUtil.h"
using namespace std;

class clsUser : public clsPerson
{
private:

	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };

	enMode _Mode;
	string _UserName;
	string _Password;
	int _Permissions;
	bool _MarkedForDeleted = false;

	struct stLoginRegisterRecord; //Function Declaration.

	static clsUser _ConvertLineToUserObject(string Line, string Separator = "#//#")
	{
		vector <string> vStringDataLine;
		vStringDataLine = clsString::Split(Line, Separator);

		return clsUser(clsUser::enMode::UpdateMode, vStringDataLine[0], vStringDataLine[1], vStringDataLine[2],
			vStringDataLine[3], vStringDataLine[4], clsUtil::DecryptText(vStringDataLine[5], 4), stoi(vStringDataLine[6]));
	}

	static string _ConverUserObjectToLine(clsUser User, string Separator = "#//#")
	{
		string sUserDataLine = "";

		sUserDataLine += User.FirstName + Separator;
		sUserDataLine += User.LastName + Separator;
		sUserDataLine += User.Email + Separator;
		sUserDataLine += User.Phone + Separator;
		sUserDataLine += User.UserName + Separator;
		sUserDataLine += clsUtil::EncryptText(User.Password, 4) + Separator;
		sUserDataLine += to_string(User.Permissions);

		return sUserDataLine;
	}

	static clsUser _GetEmptyUserObject()
	{
		return clsUser(clsUser::enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static vector <clsUser> _LoadUsersDataFromFile()
	{
		vector <clsUser> vUsers;

		fstream MyFile;
		string DataLine = "";

		MyFile.open("Users.txt", ios::in); //Read Mode.

		if (MyFile.is_open())
		{
			while (getline(MyFile, DataLine))
			{
				if (DataLine != "")
				{
					clsUser User = _ConvertLineToUserObject(DataLine);

					vUsers.push_back(User);
				}
			}

			MyFile.close();
		}

		return vUsers;
	}

	static void _SaveUsersDataToFile(vector <clsUser> vUsers)
	{
		fstream MyFile;
		string DataLine = "";

		MyFile.open("Users.txt", ios::out); //Overwrite Mode.

		if (MyFile.is_open())
		{
			//ranged loop
			for (clsUser& U : vUsers)
			{
				if (!U.MarkedForDeleted())
				{
					DataLine = _ConverUserObjectToLine(U);

					MyFile << DataLine << endl;
				}
			}

			MyFile.close();
		}
	}

	void _AddDataLineToFile(string sDataLine)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::out | ios::app); // Append Mode.

		if (MyFile.is_open())
		{
			MyFile << sDataLine << endl;

			MyFile.close();
		}
	}

	void _Update()
	{
		vector <clsUser> vUsers;
		vUsers = _LoadUsersDataFromFile();

		//ranged loop
		for (clsUser& U : vUsers)
		{
			if (U._UserName == _UserName)
			{
				U = *this;
				break;
			}
		}

		_SaveUsersDataToFile(vUsers);
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConverUserObjectToLine(*this));
	}

	string _PrepareLoginRecord(string Separator = "#//#")
	{
		string LoginRecord = "";

		LoginRecord += clsDate::GetSystemDateTimeString() + Separator;
		LoginRecord += _UserName + Separator;
		LoginRecord += clsUtil::EncryptText(_Password, 4) + Separator;
		LoginRecord += to_string(_Permissions);

		return LoginRecord;
	}

	static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string Line, string Separator = "#//#")
	{
		stLoginRegisterRecord LoginRegisterRecord;

		vector <string> vLoginRegisterDataLine;
		vLoginRegisterDataLine = clsString::Split(Line, Separator);

		LoginRegisterRecord.DateTime = vLoginRegisterDataLine[0];
		LoginRegisterRecord.UserName = vLoginRegisterDataLine[1];
		LoginRegisterRecord.Password = clsUtil::DecryptText(vLoginRegisterDataLine[2], 4);
		LoginRegisterRecord.Permissions = stoi(vLoginRegisterDataLine[3]);

		return LoginRegisterRecord;
	}

public:

	clsUser(enMode Mode, string FirstName, string LastName, string Email,
		string Phone, string UserName, string Password, int Permissions)
		: clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Permissions;
	}

	struct stLoginRegisterRecord
	{
		string DateTime;
		string UserName;
		string Password;
		int Permissions = 0;
	};

	enum enPermissions {
		pAll = -1, pShowClientList = 1, pAddNewClient = 2, pDeleteClient = 4,
		pUpdateClient = 8, pFindClient = 16, pTransactions = 32, pManageUsers = 64,
		pLoginRegister = 128
	};

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	bool MarkedForDeleted()
	{
		return (_MarkedForDeleted == true);
	}

	void SetUserName(string UserName)
	{
		_UserName = UserName;
	}

	string GetUserName()
	{
		return _UserName;
	}

	__declspec(property(get = GetUserName, put = SetUserName)) string UserName;

	void SetPassword(string Password)
	{
		_Password = Password;
	}

	string GetPassword()
	{
		return _Password;
	}

	__declspec (property(get = GetPassword, put = SetPassword)) string Password;

	void SetPermissions(int Permissions)
	{
		_Permissions = Permissions;
	}

	int GetPermissions()
	{
		return _Permissions;
	}

	__declspec (property(get = GetPermissions, put = SetPermissions)) int Permissions;

	static clsUser Find(string UserName)
	{
		fstream MyFile;

		MyFile.open("Users.txt", ios::in); //Read Mode.

		if (MyFile.is_open())
		{
			string Line = "";
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);

				if (User._UserName == UserName)
				{
					MyFile.close();
					return User;
				}
			}

			MyFile.close();
		}

		return _GetEmptyUserObject();
	}

	static clsUser Find(string UserName, string Password)
	{
		fstream MyFile;

		MyFile.open("Users.txt", ios::in); //Read Mode.

		if (MyFile.is_open())
		{
			string Line = "";
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);

				if (User._UserName == UserName && User._Password == Password)
				{
					MyFile.close();
					return User;
				}
			}

			MyFile.close();
		}

		return _GetEmptyUserObject();
	}

	static bool IsUserExist(string UserName)
	{
		clsUser User = Find(UserName);

		return (!User.IsEmpty());
	}

	static bool IsUserExist(string UserName, string Password)
	{
		clsUser User = Find(UserName, Password);

		return (!User.IsEmpty());
	}

	static clsUser GetAddNewUserObject(string UserName)
	{
		return clsUser(clsUser::enMode::AddNewMode, "", "", "", "", UserName, "", 0);
	}

	bool Delete()
	{
		vector <clsUser> vUsers;
		vUsers = _LoadUsersDataFromFile();

		//ranged loop 
		for (clsUser& U : vUsers)
		{
			if (U._UserName == _UserName)
			{
				U._MarkedForDeleted = true;
				break;
			}
		}
		_SaveUsersDataToFile(vUsers);

		*this = _GetEmptyUserObject();

		return true;
	}

	static vector <clsUser> GetUsersList()
	{
		return _LoadUsersDataFromFile();
	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildObjectexists = 2 };

	enSaveResults Save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:

			if (IsEmpty())
			{
				return enSaveResults::svFaildEmptyObject;
			}

		case enMode::UpdateMode:

			_Update();
			return enSaveResults::svSucceeded;

		case enMode::AddNewMode:

			if (IsUserExist(_UserName))
			{
				return enSaveResults::svFaildObjectexists;
			}
			else {

				_AddNew();
				_Mode = enMode::UpdateMode;

				return enSaveResults::svSucceeded;
			}
		}
	}

	bool CheckAccessPermissions(enPermissions Permission)
	{
		if (this->Permissions == enPermissions::pAll)
			return true;

		if ((Permission & this->Permissions) == Permission)
			return true;

		else
			return false;
	}

	void RegisterLogin()
	{
		fstream MyFile;
		string sDataLine = "";

		MyFile.open("LoginRegister.txt", ios::out | ios::app); //Append Mode.

		if (MyFile.is_open())
		{
			sDataLine = _PrepareLoginRecord();

			MyFile << sDataLine << endl;
			MyFile.close();
		}
	}

	static vector <stLoginRegisterRecord> GetLoginRegisterList()
	{
		vector <stLoginRegisterRecord> vLoginRegisterRecord;
		stLoginRegisterRecord LoginRegisterRecord;

		fstream MyFile;

		MyFile.open("LoginRegister.txt", ios::in); //Read Mode.

		if (MyFile.is_open())
		{
			string Line = "";
			while (getline(MyFile, Line))
			{
				if (Line != "")
				{
					LoginRegisterRecord = _ConvertLoginRegisterLineToRecord(Line);
					vLoginRegisterRecord.push_back(LoginRegisterRecord);
				}
			}
			MyFile.close();
		}

		return vLoginRegisterRecord;
	}

};
