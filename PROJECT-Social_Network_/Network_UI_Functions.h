#pragma once
#include "User.h"
#include "MyStringSso.h"

const int MAX_VALUES_SIZE = 1024;

size_t getCharCountFromFile(std::ifstream& ifs, char ch)
{
	size_t currentPosition = ifs.tellg();
	ifs.seekg(0, std::ios::beg);

	if (!ifs.is_open())
	{
		return 0;
	}

	unsigned int count = 0;

	while (true)
	{
		char current = ifs.get();

		if (ifs.eof())
		{
			break;
		}

		if (current == ch)
		{
			count++;
		}
	}

	ifs.clear();
	ifs.seekg(currentPosition);

	return count;
}

size_t getLinesCount(const char* FILENAME)
{
	std::ifstream file(FILENAME);

	if (!file.is_open())
	{
		return 0;
	}

	return getCharCountFromFile(file, '\n') + 1;

	file.close();
}

void signUp()
{
	User user;

	std::cout << "Enter your first name: ";
	char* firstName = new char;
	std::cin.getline(firstName, MAX_VALUES_SIZE);
	user.setFirstName(firstName);

	std::cout << "Enter your surname: ";
	char* surname = new char;
	std::cin.getline(surname, MAX_VALUES_SIZE);
	user.setSurname(surname);

	std::cout << "Enter your password: ";
	char* password = new char;
	std::cin.getline(password, MAX_VALUES_SIZE);
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
	char* firstName = new char;
	std::cin.getline(firstName, MAX_VALUES_SIZE);
	tempUser.setFirstName(firstName);

	std::cout << "Enter your password: ";
	char* password = new char;
	std::cin.getline(password, MAX_VALUES_SIZE);
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
