#pragma once
#include"clsPerson.h";
#include "clsString.h";
#include <vector>
#include<fstream>
#include <iostream>
#include <string>
#include "clsDate.h"

using namespace std;
class clsBankClient :public clsPerson
{
private:


	enum enMode { EmptyMode = 0, UpdateMode = 1 , AddNewMod = 2 };
	enMode _Mode;

	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkForDelete = false;
	static clsBankClient _ConvertLineToClientObject(string Line, string Seperator = "#//#")
	{

		vector<string> vClientData;
		vClientData = clsString::Split(Line, Seperator);

		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));

	}
	struct stTransferLogRecord;
	static string _ConvertClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
	{
		string stClientRecord = "";

		stClientRecord += Client.FirstName + Seperator;
		stClientRecord += Client.LastName + Seperator;
		stClientRecord += Client.Email + Seperator;
		stClientRecord += Client.Phone + Seperator;
		stClientRecord += Client.AccountNumber() + Seperator;
		stClientRecord += Client.PinCode + Seperator;
		stClientRecord += to_string(Client.AccountBalance);

		return stClientRecord;

	}
	static stTransferLogRecord _ConvertTransferLogRecordToLine(string Line, string Seperator = "#//#")
	{
stTransferLogRecord TrnsferLogRecord;

        vector <string> vTrnsferLogRecordLine = clsString::Split(Line, Seperator);
        TrnsferLogRecord.DateTime = vTrnsferLogRecordLine[0];
        TrnsferLogRecord.SourceAccountNumber = vTrnsferLogRecordLine[1];
        TrnsferLogRecord.DestinationAccountNumber = vTrnsferLogRecordLine[2];
        TrnsferLogRecord.Amount = stod(vTrnsferLogRecordLine[3]);
        TrnsferLogRecord.srcBalanceAfter = stod(vTrnsferLogRecordLine[4]);
        TrnsferLogRecord.destBalanceAfter = stod(vTrnsferLogRecordLine[5]);
        TrnsferLogRecord.UserName = vTrnsferLogRecordLine[6];

        return TrnsferLogRecord;



		

	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}
	string _PrepareTransferLogRecord(float Amount, clsBankClient DestinationClient,
		string UserName, string Seperator = "#//#")
	{
		string TransferLogRecord = "";
		TransferLogRecord += clsDate::GetSystemDateTimeString() + Seperator;
		TransferLogRecord += AccountNumber() + Seperator;
		TransferLogRecord += DestinationClient.AccountNumber() + Seperator;
		TransferLogRecord += to_string(Amount) + Seperator;
		TransferLogRecord += to_string(AccountBalance) + Seperator;
		TransferLogRecord += to_string(DestinationClient.AccountBalance) + Seperator;
		TransferLogRecord += UserName;
		return TransferLogRecord;
	}

	void _RegisterTransferLog(float Amont , clsBankClient DestionationClient,string Username)
	{
		string stData = _PrepareTransferLogRecord(Amont, DestionationClient, Username);
		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << stData << endl;

			MyFile.close();
		}
	}
static	vector <clsBankClient> _LoadClientsDataFromFile()
	{

		vector <clsBankClient> vClients;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{

			string Line;

			while (getline(MyFile, Line))
			{

			clsBankClient Client = _ConvertLineToClientObject(Line);

				vClients.push_back(Client);
			}

			MyFile.close();

		}

		return vClients;

	}


static void _SaveClientsDataToFile(vector <clsBankClient> vClients)
    {

        fstream MyFile;
        MyFile.open("Clients.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

			for (clsBankClient C : vClients)
			{
				if ( C._MarkForDelete == false)
				{

					DataLine = _ConvertClientObjectToLine(C);
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
		if (C.AccountNumber() == AccountNumber())
		{
			C = *this;
			break;
		}

	}

	_SaveClientsDataToFile(_vClients);

}


void _AddDataLineToFile(string stDateLine)
{

	fstream MyFile;
	MyFile.open("Client.txt", ios::out | ios::app);

	if (MyFile.is_open())
	{
		MyFile << stDateLine << endl;
		MyFile.close();
	}

}


public:

	struct stTransferLogRecord
	{
		string DateTime;
		string SourceAccountNumber;
		string DestinationAccountNumber;
		float Amount;
		float srcBalanceAfter;
		float destBalanceAfter;
		string UserName;
	};
	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode, float AccountBalance) :
		clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;

	}


	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}


	string AccountNumber()
	{
		return _AccountNumber;
	}


	void setPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}
	string getPinCode()
	{
		return _PinCode;
	}
	__declspec(property(get = getPinCode, put = setPinCode))string PinCode;


	void setAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}
	float getAccountBalance()
	{
		return _AccountBalance;
	}
	__declspec(property(get = getAccountBalance, put = setAccountBalance))float AccountBalance;



	void Deposit(double Amount)
	{
		_AccountBalance += Amount;
		Save();
	}
	bool Withdraw(double Amount)
	{
		if (Amount > _AccountBalance)
		{
			return false;
	}
		else
		{
			_AccountBalance -= Amount;
			Save();
		}
	}
	bool Delete()
	{
		vector<clsBankClient> _vClient;
		_vClient = _LoadClientsDataFromFile();
		for (clsBankClient& C : _vClient)
		{
			if (C.AccountNumber() == _AccountNumber)
			{
				C._MarkForDelete = true;
				break;
			}
		}
		_SaveClientsDataToFile(_vClient);

		*this = _GetEmptyClientObject();
		return true;
	}


	static clsBankClient Find(string AccountNumber)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{

			string  Line;
			while (getline(MyFile, Line))
			{

				clsBankClient Client = _ConvertLineToClientObject(Line);
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
				clsBankClient Client = _ConvertLineToClientObject(Line);
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


enum enSaveResults {svFaildEmptyObject = 0 , svSucceeded = 1 , svFaildAccountAlreadyExists = 2};


enSaveResults Save()
{

	switch (_Mode)
	{
	case enMode::EmptyMode:
	{
		return enSaveResults::svFaildEmptyObject;
	}
	case enMode::UpdateMode:
	{
		_Update();
		return enSaveResults::svSucceeded;
		break;
	}
	case enMode::AddNewMod:
	{
		if (clsBankClient::IsClientExist(_AccountNumber))
		{
			return enSaveResults::svFaildAccountAlreadyExists;
		}
		else
		{
			
			_AddNew();
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

	static clsBankClient GetAddNewClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMod, "", "", "", "", AccountNumber, "",0);

	}
	static vector <clsBankClient> GetClientList()
	{
		return _LoadClientsDataFromFile();
	}

	static double GetTotalBalnce()
	{

		vector <clsBankClient> vClient = clsBankClient::GetClientList();
		double TotalBalnces = 0;

		for (clsBankClient Client : vClient)
		{
			TotalBalnces += Client.AccountBalance;
		}
		return TotalBalnces;

	}
	bool Transfer(float Amount, clsBankClient& DestanationClient )
	{
		string UserName;
		if (Amount > AccountBalance)
		{
			return false;
		}
		
		Withdraw(Amount);
		DestanationClient.Deposit(Amount);
		_RegisterTransferLog(Amount, DestanationClient, UserName);
		return true;
	}
	 static vector <stTransferLogRecord> GetTransferLogList()
	{
		 vector <stTransferLogRecord> vTransferRecord;

		 fstream MyFile;
		 MyFile.open("TransferLog.txt", ios::in);

		 if (MyFile.is_open())
		 {
			 string Line;

			 stTransferLogRecord TransferLogRecord;

			 while (getline(MyFile, Line))
			 {
				 TransferLogRecord = _ConvertTransferLogRecordToLine(Line);
				 vTransferRecord.push_back(TransferLogRecord);
			 }
			 MyFile.close();
		 }
		 return vTransferRecord;
	}
};