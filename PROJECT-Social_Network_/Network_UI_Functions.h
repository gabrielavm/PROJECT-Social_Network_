#pragma once
#include "User.h"
#include "Topic.h"
#include "MyStringSso.h"

const int MAX_VALUES_SIZE = 1024;
const char USERS_LIST_FILE[] = "UsersList.txt";
const char TOPICS_LIST_FILE[] = "TopicsList.txt";

//Variables that show where the exact value is saved in the file with the registered users
//For example each time a user is being registered his info is being saved in the 
// following sequence :  First name , Surname, Password, Id , Points
static const int firstNameIndex = 1;
static const int surnameIndex = 2;
static const int passwordIndex = 3;
static const int idIndex = 4;
static const int pointsIndex = 5;

//Helper function to find the length of string
size_t stringLen(const char* string)
{
	size_t length = 0;

	while (string[length] != '\0')
	{
		++length;
	}

	return length;
}

//Helper function that compares two strings
bool stringComp(const char* firstStr, const char* secondStr)
{
	if (stringLen(firstStr) == stringLen(secondStr))
	{
		int equal = 0;

		for (size_t i = 0; i < strlen(firstStr); ++i)
		{
			if (firstStr[i] == secondStr[i])
			{
				++equal;
			}
		}

		if (equal == stringLen(firstStr))
		{
			return true;
		}
	}

	return false;
}

void stringCopy(MyString& original, char* copy)
{
	for (int i = 0; i < original.length() + 1; ++i)
	{
		if (i != original.length())
		{
			copy[i] = original[i];
		}
		else
		{
			copy[i] = '\0';
		}
	}
}

//Using the 'getCharCountFromFile' and 'getLinesCount' functions that we implemented during lectures
//github: Angeld55
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
		std::cout << "ERROR! The file could not be opened!";
		return 0;
	}

	return getCharCountFromFile(file, '\n') + 1;

	file.close();
}

void signUp(bool& failRegistration)
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

	size_t id = getLinesCount(USERS_LIST_FILE);//the id for every user will be the row on which the
	//exact user's info is saved. That way the id for each user will be unique and we will know the 
	//position of this user in the file
	user.setId(id);

	user.setPoints(0);

	if (stringLen(firstName) < 1 ||
		stringLen(surname) < 1 ||
		stringLen(password) < 1) //Checking if some data isn't entered
		//if first name, surname or password isn't entered it is not successfull registration
	{
		failRegistration = true;
		return;
	}

	std::ofstream inputUserInFile(USERS_LIST_FILE, std::ios::app);

	if (!inputUserInFile.is_open())
	{
		std::cout << "ERROR! The file could not be opened!";
		return;
	}

	inputUserInFile << user;
	std::cout << std::endl << "Successful registration!" << std::endl;

	inputUserInFile.close();
}

size_t turnCharArrayIntoNum(const char* arr, size_t num)
{
	std::stringstream stream(arr);
	stream >> num;

	return num;
}

//Helper function for 'findUser' func that set surname, id and points to the user when we log in our account
//(when we check for existance of some user in the registered users list we have only first name and password,
//so we have to set the other components of the user's info)
void fillUserInfo(const char* buffer, User& user)
{
	size_t posCounter = 0;
	std::stringstream stream(buffer);

	while (!stream.eof())
	{
		char tempValue[BUFFER_SIZE] = { '\0' };

		++posCounter;
		stream.getline(tempValue, BUFFER_SIZE, ' ');

		if (posCounter == surnameIndex)
		{
			user.setSurname(tempValue);
		}
		else if (posCounter == idIndex)
		{
			size_t tempId = turnCharArrayIntoNum(tempValue, user.getId());
			user.setId(tempId);
		}
		else if (posCounter == pointsIndex)
		{
			size_t tempPoints = turnCharArrayIntoNum(tempValue, user.getPoints());
			user.setPoints(tempPoints);
		}
	}
}

//Function that checks if some user is already registered
bool findUser(std::ifstream& ifs , User& user)
{
	User tempUser;
	size_t lineNumber = 0;//The line with the user's info

	while (!ifs.eof())
	{
		char buffer[BUFFER_SIZE] = { '\0' };
		ifs.getline(buffer, BUFFER_SIZE);

		++lineNumber;
		size_t counter = 0;
		bool correctName = false;
		bool correctPassword = false;

		std::stringstream stream(buffer);

		while (!stream.eof())
		{
			char temp[BUFFER_SIZE] = { '\0' };

			++counter;
			stream.getline(temp, BUFFER_SIZE, ' ');

			if (counter == firstNameIndex)
			{
				tempUser.setFirstName(temp);
				if (tempUser.getFirstName() == user.getFirstName())
				{
					correctName = true;
				}
			}
			else if (counter == passwordIndex)
			{
				tempUser.setPassword(temp);
				if (tempUser.getPassword() == user.getPassword())
				{
					correctPassword = true;
				}
			}

			if (correctName == true && correctPassword == true)//if the name and the password are correct
				//at the same time (both belong to the same user) it means that this user exist in the file
				// with the registered users
			{
				fillUserInfo(buffer, user);
				return true;
			}
		}
	}

	return false;
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

	if (findUser(readFromFile, tempUser) == true)
	{
		user = tempUser;
		std::cout << "Welcome back, " << user.getFirstName() << " :) !\n";
	}
	else
	{
		std::cout << "Your name or password is wrong!\n";
		return;
	}

	readFromFile.close();
}

void logOut(User& user)
{
	std::cout << "\nGoodbye, " << user.getFirstName() << " " << user.getSurname() << "!\n";
	user.setFirstName("");
	user.setSurname("");
	user.setPassword("");
	user.setId(0);
	user.setPoints(0);
}

void logOutHelperFunction(bool logOut, char* command)
{
	if (logOut == true)
	{
		std::cout << std::endl << "\nSign up, log in your account or exit! \n\n";
		std::cout << "Command list: \n" << "'signup' - sign up\n" << "'login' - log in \n"
			<< "'quit' - exit the network \n"  ;

		std::cout << "\nEnter command: ";
		std::cin.getline(command, MAX_VALUES_SIZE);
	}
}

void createTopic(const User& user)
{
	Topic topic;

	char* topicName = new char;
	std::cout << "Enter the name of the topic you want to create: ";
	std::cin.getline(topicName, MAX_VALUES_SIZE);
	topic.setTopicName(topicName);

	char* topicDescription = new char;
	std::cout << "Enter the description of the topic: ";
	std::cin.getline(topicDescription, MAX_VALUES_SIZE);
	topic.setTopicDescription(topicDescription);

	size_t id = getLinesCount(TOPICS_LIST_FILE);//the id for each topic will be the row on which the
	//exact topic's info is saved. That way the id for each topic will be unique and we will know the 
	//position of this topic in the file

	topic.setId(id);
	
	topic.setCreatorName(user.getFirstName());

	std::ofstream writeInFile(TOPICS_LIST_FILE, std::ios::_Nocreate | std::ios::app);
	if (!writeInFile.is_open())
	{
		std::cout << "ERROR! The file could not be opened!";
		return;
	}

	writeInFile << topic;

	writeInFile.close();

	MyString topicFileName(topic.getTopicName());
	topicFileName += (".txt");//creating the name of the file for the topic 

	char* tempTopicFileName = new char[topicFileName.length() + 1];
	stringCopy(topicFileName, tempTopicFileName);

	std::ofstream topicFile(tempTopicFileName);//Create a file for each topic
	if (!topicFile.is_open())
	{
		std::cout << "ERROR! The file could not be created!";
		return;
	}

	std::cout << "The topic is created successfully!\n";

	topicFile.close();
}

void printCommandsList(char* command)
{
	std::cout << "\nCommand list:\n"
		<< "'whoami' - See your information\n"
		<< "'create' - Create a new topic\n"
		<< "'quit' - Exit the network\n"
		<< "'logout' - Log out from your account\n\n";

	std::cout << "Enter your command: ";
	std::cin.getline(command, MAX_VALUES_SIZE);
}

void func(bool& exit, bool& logout, char* command, User& user)
{
	printCommandsList(command);

	bool quit = false;

	while (quit == false)
	{
		if (stringComp(command, "create") == true)
		{
			createTopic(user);
			printCommandsList(command);
		}
		else if (stringComp(command, "whoami") == true)
		{
			user.printUsersInfo();
			printCommandsList(command);
		}
		else if (stringComp(command, "quit") == true)
		{
			exit = true;
			return;
		}
		else if(stringComp(command, "logout") == true)
		{
			logOut(user);
			logout = true;
			return;
		}
		else
		{
			std::cout << "\nERROR! Wrong command! Try again or exit!\n";
			std::cin.getline(command, MAX_VALUES_SIZE);
		}
	}
}
