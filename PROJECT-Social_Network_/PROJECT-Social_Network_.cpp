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

	char* command = new char;
	std::cin.getline(command, MAX_VALUES_SIZE);

	bool exit = false;

	while (exit == false)
	{
		if (stringComp(command, "signup") == true)
		{
			bool failRegistration = false;//Variable which will contain information about the registration condition
			//if the variable is false that means the registration was successful, otherwise the registration failed

			signUp(failRegistration);

			if (failRegistration == true)
			{
				std::cout << "ERROR! Registration failed!\nSome of the user's data was not entered!";
				return 0;
			}
			else
			{
				std::cout << std::endl << "Log in your account or exit! \n\n";
				std::cout << "Command list: \n" << "'quit' - exit \n" << "'login' - log in \n";

				std::cout << "\nEnter command: ";
				std::cin.getline(command, MAX_VALUES_SIZE);

				if (stringComp(command, "login") == true)
				{
					logIn(user);
				}
				else if (stringComp(command, "quit") == true)
				{
					return 0;
				}
			}

			exit = true;
		}
		else if (stringComp(command, "login") == true)
		{
			logIn(user);

			user.printUsersInfo();

			exit = true;
		}
		else
		{
			std::cout << "Your command is wrong! Try again or quit!";
			std::cout << std::endl << "Enter your command ('quit' if you want to exit): ";
			std::cin.getline(command, MAX_VALUES_SIZE);

			if (stringComp(command, "quit") == true)
			{
				return 0;
			}
		}
	}

	std::cout << user.getFirstName();

	return 0;
}
