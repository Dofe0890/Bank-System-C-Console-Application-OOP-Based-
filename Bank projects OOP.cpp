#include <iostream>
#include "clsLoginScreen.h"

using namespace std;




int main()
{
	 while (true)

	{
		if (!clsLoginScreen::ShowLoginScreen())
		{
			break;
		}
	}
	
	//clsLoginScreen::ShowLoginScreen();

	return 0;
}

