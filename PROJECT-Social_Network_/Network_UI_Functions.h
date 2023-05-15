#pragma once
#include "User.h"

void signUp()
{
	User user;

	std::cout << "Enter your first name: ";
	char* firstName = new char();
	std::cin >> firstName;
	user.setFirstName(firstName);

	std::cout << "Enter your surname: ";
	char* surname = new char();
	std::cin >> surname;
	user.setSurname(surname);

	std::cout << "Enter your password: ";
	char* password = new char();
	std::cin >> password;
	user.setPassword(password);

	srand((unsigned)time(NULL));
	user.setId(rand());

	user.setPoints(0);

	std::ofstream inputUserInFile(USERS_LIST_FILE, std::ios::app);

	if (!inputUserInFile.is_open())
	{
		std::cout << "ERROR! The file could not be opened!";
		return;
	}

	inputUserInFile << user;
	std::cout << std::endl << "Your registration has been done successfully!" << std::endl;

	inputUserInFile.close();
}

void logIn(User& user)
{
	User tempUser;

	std::cout << "Enter your name: ";
	char* firstName = new char();
	std::cin >> firstName;
	tempUser.setFirstName(firstName);

	std::cout << "Enter your password: ";
	char* password = new char();
	std::cin >> password;
	tempUser.setPassword(password);

	std::ifstream readFromFile(USERS_LIST_FILE);

	if (!readFromFile.is_open())
	{
		std::cout << "ERROR! The file could not be opened!";
		return;
	}

	if (tempUser.findUser(readFromFile) == true)
	{
		user = tempUser;
		std::cout << "Welcome back, " << user.getFirstName() << " :) !\n";
	}
	else
	{
		std::cout << "Your name or password is wrong!";
		return;
	}

	readFromFile.close();
}
