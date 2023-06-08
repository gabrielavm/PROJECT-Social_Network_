#pragma once
#include "User.h"
#include "Topic.h"
#include "MyStringSso.h"
#include "Vector.hpp"

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

void signUp(bool& failRegistration, Vector<User>& users)
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

	//the id for every user will be the number of registered users (users.getSize() + 1).
	//That way the id for each user will be unique and we will know the 
	//position of this user in the file because the id relate to the line in the file
	//in which the user's data is saved
	user.setId(users.getSize() + 1);

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

void readUsersFromFile(Vector<User>& users)
{
	User tempUser;

	std::ifstream readUsers(USERS_LIST_FILE);
	if (!readUsers.is_open())
	{
		std::cout << "\nERROR! The file could not be opened!\n";
		return;
	}

	while (!readUsers.eof())
	{
		size_t posCounter = 0;
		char buffer[BUFFER_SIZE] = { '\0' };
		readUsers.getline(buffer, BUFFER_SIZE);

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
			case firstNameIndex:
				tempUser.setFirstName(tempValue);
				break;

			case surnameIndex:
				tempUser.setSurname(tempValue);
				break;

			case passwordIndex:
				tempUser.setPassword(tempValue);
				break;

			case idIndex:
				tempId = turnCharArrayIntoNum(tempValue, tempUser.getId());
				tempUser.setId(tempId);
				break;

			case pointsIndex:
				tempPoints = turnCharArrayIntoNum(tempValue, tempUser.getPoints());
				tempUser.setPoints(tempPoints);
				users.pushBack(tempUser);
				posCounter = 0;
				break;
			}
		}
	}

	readUsers.close();
}

bool findUser(Vector<User>& users, User& user)
{
	for (size_t i = 0; i < users.getSize(); ++i)
	{
		if (users[i].getFirstName() == user.getFirstName() ||
			users[i].getPassword() == user.getPassword())
		{
			user = users[i];
			return true;
		}
	}

	return false;
}

void logIn(Vector<User>& users, User& user, bool& exit)
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

	if (findUser(users, tempUser) == true)
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

void logOut(User& user, Vector<User>& users)
{
	std::cout << "\nGoodbye, " << user.getFirstName() << " " << user.getSurname() << "!\n";
	user.setFirstName("");
	user.setSurname("");
	user.setPassword("");
	user.setId(0);
	user.setPoints(0);

	//During the program the number of the points of each user can be changed 
	//so we have to save the information again in otder to save the new data
	std::ofstream saveNewInfo(USERS_LIST_FILE, std::ios::trunc);
	if (!saveNewInfo.is_open())
	{
		std::cout << "\nERROR! The file coud not be opened!\n";
		return;
	}

	for (size_t i = 0; i < users.getSize(); ++i)
	{
		saveNewInfo << users[i];
	}

	saveNewInfo.close();
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

void readTopicsFromFile(Vector<Topic>& topics)
{
	Topic tempTopic;

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
			tempId = turnCharArrayIntoNum(buffer, tempTopic.getId());
			tempTopic.setId(tempId);
			break;
		case 2:
			tempTopic.setCreatorName(buffer);
			break;
		case 3:
			tempTopic.setTopicName(buffer);
			break;
		case 4:
			tempTopic.setTopicDescription(buffer);
			topics.pushBack(tempTopic);
			++topicsCount;
			positionCount = 0;
			break;
		}
	}

	topicFile.close();
}

bool topicExistance(Vector<Topic>& topics, const MyString& topicName)
{
	for (size_t i = 0; i < topics.getSize(); ++i)
	{
		if (topics[i].getTopicName() == topicName)
		{
			return true;
		}
	}

	return false;
}

void createTopic(const User& user, Vector<Topic>& topics)
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

	//the id for each topic will be the number of the created topics by that time.
	//That way the id for each topic will be unique.
	topic.setId(topics.getSize() + 1);

	topic.setCreatorName(user.getFirstName());

	if (!topicExistance(topics, topic.getTopicName()))
	{
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

		//readTopicsFromFile(topics);

		topicFile.close();

		//We can create a new topic during the program and not only in the beginning 
		//so we have to refill the collection of topics every time we create new topic
		//in order to not skip any topic while using the other commands in the program
		topics.clear();
		readTopicsFromFile(topics);
	}
	else
	{
		std::cout << "\nThis topic already exists!\n";
		return;
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

void search(char* keyword, Vector<Topic>& topics, Vector<Topic>& selectedTopics, bool& goBack)
{
	size_t countOfSelectedTopics = 0;//counter for the added topics in 'selectedTopics' array of class Topic
	//when this counter is equal to zero that means that there is no topic that include the keyword 

	for (size_t i = 0; i < topics.getSize(); ++i)
	{
		char* tempKeyword = new char[topics[i].getTopicName().length()];
		std::stringstream stream(topics[i].getTopicName().c_str());

		while (!stream.eof())
		{
			stream.getline(tempKeyword, topics[i].getTopicName().length(), ' ');

			if (stringComp(tempKeyword, keyword) == true)
			{
				selectedTopics.pushBack(topics[i]);
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

void createQuestion(Question& question, char* filename)
{
	char* askQuestion = new char;
	std::cout << "\nEnter your question: ";
	std::cin.getline(askQuestion, MAX_VALUES_SIZE);
	question.setTitle(askQuestion);

	char* content = new char;
	std::cout << "\nEnter the description of the question: ";
	std::cin.getline(content, MAX_VALUES_SIZE);
	question.setContent(content);

	question.setId(getLinesCount(filename));
}

void readQuestionsFromFile(std::ifstream& stream, Topic& topic)
{
	Question tempQuestion;
	size_t counter = 0;
	bool isQuestion = false;
	size_t tempId;
	size_t numberOfQuestions = 0;

	while (!stream.eof())
	{
		char buffer[BUFFER_SIZE] = { '\0' };
		stream.getline(buffer, BUFFER_SIZE);

		if (stringComp(buffer, "question:"))
		{
			isQuestion = true;
		}

		if (counter == 1 && isQuestion == true)
		{
			tempId = turnCharArrayIntoNum(buffer, tempQuestion.getId());
			tempQuestion.setId(tempId);
		}
		else if (counter == 2 && isQuestion == true)
		{
			tempQuestion.setTitle(buffer);
		}
		else if (counter == 3 && isQuestion == true)
		{
			tempQuestion.setContent(buffer);
			topic.setQuestion(tempQuestion);
			++numberOfQuestions;
			counter = 0;
			isQuestion = false;
		}

		if (isQuestion == true)
		{
			++counter;
		}
	}

	for (size_t i = 0; i < numberOfQuestions; ++i)
	{
		std::cout << i + 1 << ". " << topic.getQuestions()[i].getTitle() << " {id: "
			<< topic.getQuestions()[i].getId() << "}\n";
	}
	std::cout << std::endl;
}

void readCommentsFromFile(std::ifstream& stream, Topic& topic, size_t currentIndex)
{
	Comment tempComment;
	Question tempQuestion;
	size_t counter = 0;
	bool isComment = false;
	size_t tempId;
	size_t tempUpvote;
	size_t tempDownvote;
	size_t numberOfComments = 0;

	while (!stream.eof())
	{
		char buffer[BUFFER_SIZE] = { '\0' };
		stream.getline(buffer, BUFFER_SIZE);

		if (stringComp(buffer, "comment:"))
		{
			isComment = true;
		}

		if (counter == 1 && isComment == true)
		{
			tempId = turnCharArrayIntoNum(buffer, tempComment.getId());
			tempComment.setId(tempId);
		}
		else if (counter == 2 && isComment == true)
		{
			tempComment.setCreatorName(buffer);
		}
		else if (counter == 3 && isComment == true)
		{
			tempComment.setCommentText(buffer);
		}
		else if (counter == 4 && isComment == true)
		{
			tempUpvote = turnCharArrayIntoNum(buffer, tempComment.getUpvote());
			tempComment.setId(tempUpvote);
		}
		else if (counter == 4 && isComment == true)
		{
			tempDownvote = turnCharArrayIntoNum(buffer, tempComment.getDownvote());
			tempComment.setDownvote(tempDownvote);
			tempQuestion.setComment(tempComment);
			topic.setQuestion(tempQuestion);

			++numberOfComments;
			counter = 0;
			isComment = false;
		}

		if (isComment == true)
		{
			++counter;
		}
	}

	for (size_t i = 0; i < numberOfComments; ++i)
	{
		std::cout << i + 1 << ". " << topic.getQuestions()[currentIndex].getComments()[i].getCommentText()
			<< " {id: " << topic.getQuestions()[currentIndex].getComments()[i].getId() << "}\n";
	}
	std::cout << std::endl;
}

void openTopicCommands(char* command)
{
	std::cout << "Command list:\n"
		<< "'post' - post question\n"
		<< "'p_open' - open post(question)\n"
		<< "'comment' - add comment\n"
		<< "'quit' - exit the topic\n"
		<< "'exit' = exit the network\n"
		<< "\nEnter your command: ";

	std::cin.get();
	std::cin.getline(command, MAX_VALUES_SIZE);
}

void open(size_t currentIndex, Vector<Topic>& selectedTopics, MyString filename, bool& exit)
{
	MyString tempString = filename;
	tempString += ".txt";
	char* tempFilename = new char[tempString.length() + 1];
	stringCopy(tempString, tempFilename);

	std::ifstream readTopic(tempFilename);
	if (!readTopic.is_open())
	{
		std::cout << "ERROR! The file could not be opened!\n";
		return;
	}

	std::cout << "\nWelcome to " << filename << "!\n\n";

	readQuestionsFromFile(readTopic, selectedTopics[currentIndex]);

	char* command = new char;
	bool localExit = false;

	while (localExit == false)
	{
		openTopicCommands(command);

		if (stringComp(command, "post") == true)
		{
			Question question;
			createQuestion(question, tempFilename);

			std::ofstream postQuestion(tempFilename, std::ios::app);
			if (!postQuestion.is_open())
			{
				std::cout << "\nERROR! The file could not be opened!\n";
				exit = true;
				return;
			}

			postQuestion << question;
			std::cout << "\nYour question has been successfully posted!\n";

			postQuestion.close();
		}
		else if (stringComp(command, "p_open") == true)
		{
			std::cout << "\n1. Open post(question) by supplied id\n"
				<< "2. Open post(question) by supplied title\n"
				<< "\nEnter the number of the command you want to use(1 or 2):";

			int choice;
			std::cin >> choice;

			if (choice == 1)
			{
				bool find = false;
				size_t tempId;
				std::cout << "\nEnter the id of the post you want to check: ";
				std::cin >> tempId;

				for (size_t i = 0; i < selectedTopics.getSize(); ++i)
				{
					if (tempId == selectedTopics[i].getId())
					{
						find = true;
					}
				}

				if (find == false)
				{
					std::cout << "\nWrong id!\n";
				}

				break;

			}
			else if (choice == 2)
			{
				bool find = false;
				char* title = new char;
				std::cout << "\nEnter the title of the topic you want to check: ";
				std::cin.getline(title, MAX_VALUES_SIZE);

				for (size_t i = 0; i < selectedTopics.getSize(); ++i)
				{
					if (stringComp(title, selectedTopics[i].getTopicName().c_str()))
					{
						find = true;
					}
				}

				if (find == false)
				{
					std::cout << "\nWrong title!\n";
				}

				break;
			}
			else
			{
				std::cout << "ERROR! Wrong command!";
			}
		}
		else if (stringComp(command, "comment") == true)
		{

		}
		else if (stringComp(command, "quit") == true)
		{
			return;
		}
		else if (stringComp(command, "exit") == true)
		{
			exit = true;
			return;
		}
	}

	readTopic.close();
}

void commandsForTopics(char* commandForTopics, Vector<Topic>& selectedTopics, bool& goBack, bool& exit)
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

			for (size_t i = 0; i < selectedTopics.getSize(); ++i)
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
				bool find = false;
				int currentId;
				std::cout << "Enter the id: ";
				std::cin >> currentId;

				for (size_t i = 0; i < selectedTopics.getSize(); ++i)
				{
					if (currentId == selectedTopics[i].getId())
					{
						open(i, selectedTopics, selectedTopics[i].getTopicName(), exit);
						find = true;
					}
				}

				if (find == false)
				{
					std::cout << "\nWrong id!\n";
					std::cin.get();
				}
			}
			else if (choice == 2)
			{
				bool find = false;
				char* currentTitle = new char;
				std::cout << "Enter the full title: ";
				std::cin.get();
				std::cin.getline(currentTitle, MAX_VALUES_SIZE);

				for (size_t i = 0; i < selectedTopics.getSize(); ++i)
				{
					if (currentTitle == selectedTopics[i].getTopicName().c_str())
					{
						open(i, selectedTopics, selectedTopics[i].getTopicName(), exit);
						find = true;
					}
				}

				if (find == false)
				{
					std::cout << "\nWrong title!\n";
				}

				if (exit == true)
				{
					return;
				}

			}
			else
			{
				std::cout << "\nWrong command!\n";
				std::cin.get();
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

void func(bool& exit, bool& logout, char* command, User& user, Vector<Topic>& topics, Vector<User>& users)
{
	Vector<Topic> selectedTopics;
	char* commandForTopics = new char;

	printCommandsList(command);

	bool quit = false;

	while (quit == false)
	{
		if (stringComp(command, "create") == true)
		{
			size_t id = topics.getSize() + 1;
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
			search(keyWord, topics, selectedTopics, goBack);

			if (goBack == true)
			{
				printCommandsList(command);
			}
			else
			{
				commandsForTopics(commandForTopics, selectedTopics, goBack, exit);

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
			logOut(user, users);
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
