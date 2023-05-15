#include <iostream>
#include <fstream>
#include "Network_UI_Functions.h"
#include "MyStringSso.h"
#include "User.h"

int main()
{
	User user;

	std::cout << "SOCIAL NETWORK" << std::endl;
	std::cout << " 1) Enter 'signup' command if you don't have account!" << std::endl
		<< " 2) Enter 'login' command if you have acconut" << std::endl;

	std::cout << std::endl << "Enter your command: ";

	char* command = new char();
	std::cin >> command;

	while (true)
	{
		if (stringComp(command, "signup") == true)
		{
			signUp();

			std::cout << std::endl << "Log in your account or exit! \n\n";
			std::cout << "Command list: \n" << "'quit' - exit \n" << "'login' - log in \n";

			std::cout << "\nEnter command: ";
			std::cin >> command;

			if (stringComp(command, "login") == true)
			{
				logIn(user);
			}
			else if (stringComp(command, "quit") == true)
			{
				return 0;
			}

			break;
		}
		else if (stringComp(command, "login") == true)
		{
			logIn(user);

			break;
		}
		else
		{
			std::cout << "Your command is wrong! Try again or quit!";
			std::cout << std::endl << "Enter your command ('quit' if you want to exit): ";
			std::cin >> command;

			if (stringComp(command, "quit") == true)
			{
				return 0;
			}
		}
	}

	return 0;
}
