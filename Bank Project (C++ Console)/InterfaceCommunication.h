#pragma once
#include <iostream>
#include <string>
using namespace std;

//Abstract Class - Conrtact - Interface.
class InterfaceCommunication
{
public:

	virtual void SendEmail(string Title, string Body) = 0; //Pure Virtual Function.
	virtual void SendFax(string Title, string Body) = 0;
	virtual void SendSMS(string Title, string Body) = 0;

};