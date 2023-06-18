#include <iostream>
#include <fstream>
#include "Network_UI_Functions.h"
#include "MyStringSso.h"
#include "User.h"

int main()
{
	User user;

	Vector<User> users;
	readUsersFromFile(users);

	Vector<Topic> topics;
	readTopicsFromFile(topics);

	std::cout << "SOCIAL NETWORK" << std::endl;
	std::cout << " 1) Enter 'signup' command if you don't have account!" << std::endl
		<< " 2) Enter 'login' command if you have acconut" << std::endl;

	std::cout << std::endl << "Enter your command: ";

	char* command = new char;
	std::cin.getline(command, MAX_VALUES_SIZE);

	bool exit = false;
	bool logOut = false;

	while (exit == false)
	{
		if (stringComp(command, "signup") == true)
		{
			bool failRegistration = false;//Variable which will contain information about the registration condition
			//if the variable is false that means the registration was successful, otherwise the registration failed

			signUp(failRegistration, users);

			if (failRegistration == true)
			{
				std::cout << "ERROR! Registration failed!"
					<< "Some of the user's data was not entered!";
				return 0;
			}
			else
			{
				std::cout << std::endl << "Log in your account or exit!" << std::endl << std::endl;
				std::cout << "Command list: " << std::endl 
					<< "'exit' - exit the network" << std::endl 
					<< "'login' - log in" << std::endl;

				std::cout << std::endl << "Enter command : ";
				std::cin.getline(command, MAX_VALUES_SIZE);

				if (stringComp(command, "login") == true)
				{
					logIn(users, user, exit);

					if (exit == true)
					{
						return 0;
					}

					mainCommandsFunction(exit, logOut, command, user, topics, users);

					if (exit == true)
					{
						return 0;
					}

					logOutHelperFunction(logOut, command);

					if (exit == true)
					{
						return 0;
					}
				}
				else if (stringComp(command, "exit") == true)
				{
					return 0;
				}
			}
		}
		else if (stringComp(command, "login") == true)
		{
			logIn(users, user, exit);

			if (exit == true)
			{
				return 0;
			}

			mainCommandsFunction(exit, logOut, command, user, topics, users);

			if (exit == true)
			{
				return 0;
			}

			logOutHelperFunction(logOut, command);

			if (exit == true)
			{
				return 0;
			}
		}
		else if (stringComp(command, "exit") == true)
		{
			return 0;
		}
		else
		{
			std::cout << "Your command is wrong! Try again or exit!";
			std::cout << std::endl << "Enter your command ('exit' if you want to exit the network): ";
			std::cin.getline(command, MAX_VALUES_SIZE);

			if (stringComp(command, "exit") == true)
			{
				return 0;
			}
		}
	}

	delete command;

	return 0;
}
