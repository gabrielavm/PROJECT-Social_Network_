#pragma once
#include "User.h"
#include "Topic.h"
#include "MyStringSso.h"

const int MAX_VALUES_SIZE = 1024;
const int MAX_TOPICS_NUMBER = 500;
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
	size_t firstStrLen = stringLen(firstStr);
	size_t secondStrLen = stringLen(secondStr);

	if (firstStrLen == secondStrLen)
	{
		int equal = 0;

		for (size_t i = 0; i < firstStrLen; ++i)
		{
			if (firstStr[i] == secondStr[i])
			{
				++equal;
			}
		}

		if (equal == firstStrLen)
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
		size_t tempId;
		size_t tempPoints;

		switch (posCounter)
		{
		case surnameIndex:
			user.setSurname(tempValue);
			break;
		case idIndex:
			tempId = turnCharArrayIntoNum(tempValue, user.getId());
			user.setId(tempId);
			break;
		case pointsIndex:
			tempPoints = turnCharArrayIntoNum(tempValue, user.getPoints());
			user.setPoints(tempPoints);
			break;
		}
	}
}

//Function that checks if some user is already registered
bool findUser(std::ifstream& ifs, User& user)
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

void logIn(User& user, bool& exit)
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
		std::cout << "\nWelcome back, " << user.getFirstName() << " :) !\n";
	}
	else
	{
		std::cout << "Your name or password is wrong!\n";
		exit = true;
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
			<< "'exit' - exit the network \n";

		std::cout << "\nEnter command: ";
		std::cin.getline(command, MAX_VALUES_SIZE);
	}
}

void readTopicsFromFile(Topic* topics)
{
	std::ifstream topicFile(TOPICS_LIST_FILE);
	if (!topicFile.is_open())
	{
		std::cout << "ERROR! The file could not be opened!";
		return;
	}

	//There is one file with information of all topics 
	//each 4 lines correspond to only one topic
	//For example the first line is the id of the first topic, the second line is the 
	//creator's name of the first topic, the third line is the name of the first topic and the
	//fourth line is the description of the first topic.
	//The next 4 lines are for the second topic and so on.
	//That is the reason why we have 'positionCount' variable which counts the lines,
	//so we know what component of the topic info to fill.
	size_t positionCount = 0;
	size_t topicsCount = 0;//increases when we have stored all the info for one topic

	while (!topicFile.eof())
	{
		char buffer[BUFFER_SIZE] = { '\0' };
		topicFile.getline(buffer, BUFFER_SIZE);
		++positionCount;
		size_t tempId;

		switch (positionCount)
		{
		case 1:
			tempId = turnCharArrayIntoNum(buffer, topics[topicsCount].getId());
			topics[topicsCount].setId(tempId);
			break;
		case 2:
			topics[topicsCount].setCreatorName(buffer);
			break;
		case 3:
			topics[topicsCount].setTopicName(buffer);
			break;
		case 4:
			topics[topicsCount].setTopicDescription(buffer);
			++topicsCount;
			positionCount = 0;
			break;
		}
	}

	topicFile.close();
}

void createTopic(const User& user, Topic* topics)
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

	delete[] topics;
	size_t linesCount = getLinesCount(TOPICS_LIST_FILE);
	size_t numberOfTopics = linesCount / 4;
	topics = new Topic[numberOfTopics];

	readTopicsFromFile(topics);

	topicFile.close();
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

void search(char* keyword, const Topic* topics, Topic* selectedTopics, const size_t numberOfTopics, bool& goBack)
{
	size_t countOfSelectedTopics = 0;//counter for the added topics in 'selectedTopics' array of class Topic
	//when this counter is equal to zero that means that there is no topic that include the keyword 

	for (size_t i = 0; i < numberOfTopics; ++i)
	{
		char* tempKeyword = new char[topics[i].getTopicName().length()];
		std::stringstream stream(topics[i].getTopicName().c_str());

		while (!stream.eof())
		{
			stream.getline(tempKeyword, topics[i].getTopicName().length(), ' ');

			if (stringComp(tempKeyword, keyword) == true)
			{
				selectedTopics[countOfSelectedTopics] = topics[i];
				++countOfSelectedTopics;
				break;//brake in order not to continue check the other words of the exact 
				//topic name after finding the keyword
			}
		}
	}

	if (countOfSelectedTopics == 0)
	{
		std::cout << "\nERROR! There is no topic that contains this keyword!\n";
		goBack = true;
		return;
	}
	else
	{
		std::cout << "\nSearch results for keyword '" << keyword << "' :\n";
		for (size_t i = 0; i < countOfSelectedTopics; ++i)
		{
			std::cout << i + 1 << ". " << selectedTopics[i].getTopicName()
				<< " {id: " << selectedTopics[i].getId() << "}\n";
		}
	}
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

void open(MyString filename)
{
	filename += ".txt";
	char* tempFilename = new char[filename.length() + 1];
	stringCopy(filename, tempFilename);

	std::ifstream readTopic(tempFilename);
	if (!readTopic.is_open())
	{
		std::cout << "ERROR! The file could not be opened!\n";
		return;
	}

	std::cout << "FILE OPENED!!!!!\n";

	readTopic.close();
}

void commandsForTopics(char* commandForTopics, Topic* selectedTopics, size_t numberOfTopics, bool& goBack, bool& exit)
{
	bool localExit = false;

	commandsListForTopics(commandForTopics);

	while (localExit == false)
	{
		if (stringComp(commandForTopics, "about") == true)
		{
			bool find = false;

			std::cout << "\nEnter the id of the topic you want to check info about: ";
			size_t id;
			std::cin >> id;

			for (size_t i = 0; i < numberOfTopics; ++i)
			{
				if (id == selectedTopics[i].getId())
				{
					find = true;
					selectedTopics[i].printTopicInfo();
				}
			}

			if (find == false)
			{
				std::cout << "Incorrect id!\n";
			}

			std::cin.get();
		}
		else if (stringComp(commandForTopics, "open") == true)
		{
			std::cout << "\n1. Open topic by supplied id\n"
				<< "2. Open topic by supplied full topic title\n"
				<< "\nEnter the number of the command you want to use(1 or 2):";

			int choice;
			std::cin >> choice;

			if (choice == 1)
			{
				int currentId;
				std::cout << "Enter the id: ";
				std::cin >> currentId;

				for (size_t i = 0; i < numberOfTopics; ++i)
				{
					if (currentId == selectedTopics[i].getId())
					{
						open(selectedTopics[i].getTopicName());
					}
				}
			}
			else if (choice == 2)
			{
				MyString title;
				char* currentTitle = new char;
				std::cout << "Enter the full title: ";
				std::cin.get();
				std::cin.getline(currentTitle, MAX_VALUES_SIZE);

				title = (currentTitle);

				for (size_t i = 0; i < numberOfTopics; ++i)
				{
					if (title == selectedTopics[i].getTopicName())
					{
						open(selectedTopics[i].getTopicName());
					}
				}
			}
			else
			{
				std::cout << "Wrong command!";
			}
		}
		else if (stringComp(commandForTopics, "quit") == true)
		{
			goBack = true;
			return;
		}
		else if (stringComp(commandForTopics, "exit") == true)
		{
			exit = true;
			return;
		}

		commandsListForTopics(commandForTopics);
	}
}

void func(bool& exit, bool& logout, char* command, User& user, Topic* topics)
{
	size_t numberOfTopics = getLinesCount(TOPICS_LIST_FILE) / 4;
	Topic* selectedTopics = new Topic[numberOfTopics];
	char* commandForTopics = new char;

	printCommandsList(command);

	bool quit = false;

	while (quit == false)
	{
		if (stringComp(command, "create") == true)
		{
			createTopic(user, topics);
			printCommandsList(command);
		}
		else if (stringComp(command, "whoami") == true)
		{
			user.printUsersInfo();
			printCommandsList(command);
		}
		else if (stringComp(command, "search") == true)
		{
			bool goBack = false;

			std::cout << "\nEnter key word: ";
			char* keyWord = new char;
			std::cin.getline(keyWord, MAX_VALUES_SIZE);
			search(keyWord, topics, selectedTopics, numberOfTopics, goBack);

			if (goBack == true)
			{
				printCommandsList(command);
			}
			else
			{
				commandsForTopics(commandForTopics, selectedTopics, numberOfTopics, goBack, exit);

				if (goBack == true)
				{
					printCommandsList(command);
				}
			}

			if (exit == true)
			{
				return;
			}
		}
		else if (stringComp(command, "logout") == true)
		{
			logOut(user);
			logout = true;
			return;
		}
		else if (stringComp(command, "exit") == true)
		{
			exit = true;
			return;
		}
		else
		{
			std::cout << "\nERROR! Wrong command! Try again or exit!\n";
			std::cin.getline(command, MAX_VALUES_SIZE);
		}
	}
}
