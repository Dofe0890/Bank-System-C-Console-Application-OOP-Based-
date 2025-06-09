#pragma once
#include <iostream>
#include "clsInputValdate.h"
#include "clsPerson.h"
#include "clsUser.h"
#include "clsScreen.h"

class clsFindUserScreen : protected clsScreen
{

private :
	static void _PrintUser(clsUser User)
	{
		
		cout << "User Card:";
		cout << "\n___________________";
  cout << "\nFirstName   : " << User.FirstName;
        cout << "\nLastName    : " << User.LastName;
        cout << "\nFull Name   : " << User.FullName();
        cout << "\nEmail       : " << User.Email;
        cout << "\nPhone       : " << User.Phone;
        cout << "\nUserName    : " << User.UserName;
        cout << "\nPassword    : " << User.Password;
        cout << "\nPermissions : " << User.Permissions;
        cout << "\n___________________\n";
	}
public :
    static void ShowFindUserScreen()
    {
        _DrawScreenHeader("\t   Find User Screen");

        string Username;
        cout << "\n Pleas enter Username:  ";
        Username = clsInputValidate::ReadString();
        while (!clsUser::IsUserExist(Username))
        {
            cout << "\nUser Not Find Put Another one: ";
            Username = clsInputValidate::ReadString();
        }

        clsUser User1 = clsUser::Find(Username);
        if (!User1.IsEmpty())
        {
            cout << "\nUser Found \n";
        }
        else 
        {
            cout << "\nUser Not Found \n";
        
        }
        _PrintUser(User1);
    }

};

