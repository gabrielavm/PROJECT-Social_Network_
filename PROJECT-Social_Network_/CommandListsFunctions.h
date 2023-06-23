#pragma once
#include <iostream>

const int MAX_VALUES_SIZE = 1024;

const void logOutHelperFunction(bool logOut, char* command)
{
	if (logOut == true)
	{
		std::cout << std::endl << std::endl 
			<< "Sign up, log in your account or exit!" 
			<< std::endl << std::endl;

		std::cout << "Command list: " << std::endl 
			<< "'signup' - sign up" << std::endl 
			<< "'login' - log in " << std::endl
			<< "'exit' - exit the network" << std::endl;

		std::cout << std::endl << "Enter command: ";
		std::cin.getline(command, MAX_VALUES_SIZE);
	}
}

const void printCommandsList(char* command)
{
	std::cout << std::endl << "Command list:" << std::endl
		<< "'whoami' - See your information" << std::endl
		<< "'search' - See selected topics related to keyword" << std::endl
		<< "'create' - Create a new topic" << std::endl
		<< "'logout' - Log out from your account" << std::endl
		<< "'exit' - Exit the network" << std::endl;

	std::cout << std::endl << "Enter your command: ";
	std::cin.getline(command, MAX_VALUES_SIZE);
}

const void commandsListForTopics(char* commandForTopics)
{
	std::cout << std::endl << "Commands list :" << std::endl
		<< "'about' (id) - see the topic info by supplied id" << std::endl
		<< "'open' - open the topic" << std::endl
		<< "'quit' - go back to the generel menu" << std::endl
		<< "'exit' - exit the network" << std::endl;

	std::cout << std::endl << "Enter your command: ";
	std::cin.getline(commandForTopics, MAX_VALUES_SIZE);
}

const void openTopicCommands(char* command)
{
	std::cout << "Command list:" << std::endl
		<< "'post' - post question" << std::endl
		<< "'p_open' - open post(question)" << std::endl
		<< "'quit' - exit the topic" << std::endl
		<< "'exit' - exit the network" << std::endl
		<< std::endl << "Enter your command: ";
	std::cin.getline(command, MAX_VALUES_SIZE);
}

const void p_openCommandsList()
{
	std::cout << std::endl << "Command list: " << std::endl
		<< "'comment' - post a comment to this question" << std::endl
		<< "'comments' - see all the comments for this topic" << std::endl
		<< "'p_close' - close the current post" << std::endl;
}

const void commentsCommandsList(char* command)
{
	std::cout << std::endl << "Commands list:" << std::endl
		<< "1. 'upvote'" << std::endl
		<< "2. 'downvote'" << std::endl
		<< "3. 'replies<id>' - see all the replies for some comment(by supplied comment's id)" << std::endl
		<< "4. 'reply<id>' - reply to a comment by supplied id" << std::endl
		<< "5. 'quit'" << std::endl
		<< std::endl << "Enter your command: ";

	std::cin.getline(command, MAX_VALUES_SIZE);
}
