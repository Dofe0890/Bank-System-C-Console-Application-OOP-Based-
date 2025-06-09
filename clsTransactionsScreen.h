#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValdate.h"
#include <iomanip>
#include "clsDepositScreen.h"
#include "clsWithdrw.h"
#include "clsTotalBalances.h"
#include "clsTransferScreen.h"
#include "clsLogScreen.h"
using namespace std;

class clsTransactionsScreen :public clsScreen
{
private:
    enum enTransactionsMenueOptions {
        eDeposit = 1, eWithdraw = 2,
        eShowTotalBalance = 3, eShowTransfer = 4, eShowLogRecord = 5,eShowMainMenue = 6
    };
    static short ReadTransactionsMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do ? [1 to 6] ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number Between 1 to 4? ");
        return Choice;

}

    static void _ShowDepositScreen()
    {
        clsDepositScreen::ShowDepositScreen();
    }

    static void _ShowWithdrawScreen()
    {
        clsWithdrawScreen::ShowWithdrawScreen();
    }

    static void _ShowTotalBalancesScreen()
    {
        clsTotalBalances::ShowClientsBalances();
    }

    static void _ShowTransferScreen()
    {
        clsTransferScreen::ShowTransferScreen();
    }
    static void _ShowTransferRecordScreen()
    {
        clsLogScreen::ShowTransferLogScreen();
    }
    static void _GoBackToTransactionsMenue()
    {
        cout << "\n\nPress any key to go back to Transactions Menue...";
        system("pause>0");
        ShowTransactionsMenue();

    }

   static void _PerformTransactionsMenueOption(enTransactionsMenueOptions TransactionsMenueOption)
    {
        switch (TransactionsMenueOption)
        {
        case enTransactionsMenueOptions::eDeposit:
        {
            system("cls");
            _ShowDepositScreen();
            _GoBackToTransactionsMenue();
            break;
        }

        case enTransactionsMenueOptions::eWithdraw:
        {
            system("cls");
            _ShowWithdrawScreen();
            _GoBackToTransactionsMenue();
            break;
        }

        case enTransactionsMenueOptions::eShowTotalBalance:
        {
            system("cls");
            _ShowTotalBalancesScreen();
            _GoBackToTransactionsMenue();
            break;
        }

        case enTransactionsMenueOptions::eShowTransfer:
            system("cls");
            _ShowTransferScreen();
            _GoBackToTransactionsMenue();
            break;
        case enTransactionsMenueOptions::eShowLogRecord:
            system("cls");
            _ShowTransferRecordScreen();
            _GoBackToTransactionsMenue();
            break;
        case enTransactionsMenueOptions::eShowMainMenue:
        {
            //do nothing here the main screen will handle it :-) ;
        }
        }


    }

public :


static void ShowTransactionsMenue()
    {

    if (!CheckAccessRights(clsUser::enPermissions::pManageUsers))
    {
        return;
    }
        system("cls");
        _DrawScreenHeader("\t  Transactions Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Transactions Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Deposit.\n";
        cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
        cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
        cout << setw(37) << left << "" << "\t[4] Transfer Actions.\n";
        cout << setw(37) << left << "" << "\t[5] Transfer Log Record.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformTransactionsMenueOption((enTransactionsMenueOptions)ReadTransactionsMenueOption());
    }

};












