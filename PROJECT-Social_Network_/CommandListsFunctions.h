#pragma once
#include <iostream>

void logOutHelperFunction(bool logOut, char* command)
{
	if (logOut == true)
	{
		std::cout << std::endl << "\nSign up, log in your account or exit! \n\n";
		std::cout << "Command list: \n" << "'signup' - sign up\n" << "'login' - log in \n"
			<< "'exit' - exit the network \n";

		std::cout << "\nEnter command: ";
		std::cin.getline(command, MAX_VALUES_SIZE);
	}
}

void printCommandsList(char* command)
{
	std::cout << "\nCommand list:\n"
		<< "'whoami' - See your information\n"
		<< "'search' - See selected topics related to keyword\n"
		<< "'create' - Create a new topic\n"
		<< "'logout' - Log out from your account\n"
		<< "'exit' - Exit the network\n";

	std::cout << "\nEnter your command: ";
	std::cin.getline(command, MAX_VALUES_SIZE);
}

void commandsListForTopics(char* commandForTopics)
{
	std::cout << "\nCommands list :\n"
		<< "'about' (id) - see the topic info by supplied id\n"
		<< "'open' - open the topic\n"
		<< "'quit' - go back to the generel menu\n"
		<< "'exit' - exit the network\n";

	std::cout << "\nEnter your command: ";
	std::cin.getline(commandForTopics, MAX_VALUES_SIZE);
}

void openTopicCommands(char* command)
{
	std::cout << "Command list:\n"
		<< "'post' - post question\n"
		<< "'p_open' - open post(question)\n"
		<< "'quit' - exit the topic\n"
		<< "'exit' = exit the network\n"
		<< "\nEnter your command: ";
}

void p_openCommandsList()
{
	std::cout << "Command list: " << std::endl
		<< "'comment' - post a comment to this question" << std::endl;
}
