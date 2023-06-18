#pragma once
#include <iostream>
#include "CommandListsFunctions.h"
#include "ReadFromFileFunctions.h"

void signUp(bool& failRegistration, Vector<User>& users)
{
	User user;

	std::cout << "Enter your first name: ";
	char firstName[SIZE];
	std::cin.getline(firstName, MAX_VALUES_SIZE);
	user.setFirstName(firstName);

	std::cout << "Enter your surname: ";
	char surname[SIZE];
	std::cin.getline(surname, MAX_VALUES_SIZE);
	user.setSurname(surname);

	std::cout << "Enter your password: ";
	char password[SIZE];
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

bool findUser(Vector<User>& users, User& user)
{
	for (size_t i = 0; i < users.getSize(); ++i)
	{
		if (users[i].getFirstName() == user.getFirstName() &&
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
	users.clear();
	readUsersFromFile(users);

	User tempUser;

	std::cout << "Enter your name: ";
	char firstName[SIZE];
	std::cin.getline(firstName, MAX_VALUES_SIZE);
	tempUser.setFirstName(firstName);

	std::cout << "Enter your password: ";
	char password[SIZE];
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

void saveUserInfo(User& user, Vector<User>& users)
{
	for (size_t i = 0; i < users.getSize(); ++i)
	{
		if (user.getId() == users[i].getId())
		{
			users[i].setPoints(user.getPoints());
		}
	}

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

void logOut(User& user, Vector<User>& users)
{
	saveUserInfo(user, users);

	std::cout << "\nGoodbye, " << user.getFirstName() << " " << user.getSurname() << "!\n";
	user.setFirstName("");
	user.setSurname("");
	user.setPassword("");
	user.setId(0);
	user.setPoints(0);
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

	char topicName[SIZE];
	std::cout << "Enter the name of the topic you want to create: ";
	std::cin.getline(topicName, MAX_VALUES_SIZE);
	topic.setTopicName(topicName);

	char topicDescription[SIZE];
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

void search(char* keyword, Vector<Topic>& topics, Vector<Topic>& selectedTopics, bool& goBack)
{
	size_t countOfSelectedTopics = 0;//counter for the added topics in 'selectedTopics' array of class Topic
	//when this counter is equal to zero that means that there is no topic that include the keyword 

	selectedTopics.clear();//clearing the selectedTopics collection in case it is not the first time 
	//we want to search for topics since the beginning of the program

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

void createQuestion(Question& question, char* filename)
{
	char askQuestion[SIZE];
	std::cout << "\nEnter your question: ";
	std::cin.getline(askQuestion, MAX_VALUES_SIZE);
	question.setTitle(askQuestion);

	char content[SIZE];
	std::cout << "\nEnter the description of the question: ";
	std::cin.getline(content, MAX_VALUES_SIZE);
	question.setContent(content);

	question.setId(getLinesCount(filename));
}

void createComment(User& user, Question& question, Comment& comment, char* filename)
{
	char commentText[SIZE];
	std::cout << std::endl << "Enter your comment: ";
	std::cin.getline(commentText, MAX_VALUES_SIZE);
	comment.setCommentText(commentText);
	comment.setQId(question.getId());
	comment.setCreatorName(user.getFirstName());
	comment.setDownvote(0);
	comment.setUpvote(0);
	comment.setId(getLinesCount(filename));
}

void rewriteFileInfo(char* filename, Vector<Topic>& topics, size_t currentIndex)
{
	std::ofstream rewrite(filename, std::ios::trunc);
	if (!rewrite.is_open())
	{
		std::cout << std::endl << "ERROR! The file could not be opened!" << std::endl;
		return;
	}

	for (size_t j = 0; j < topics[currentIndex].getQuestions().getSize(); ++j)
	{
		rewrite << topics[currentIndex].getQuestions()[j];

		for (size_t k = 0; k < topics[currentIndex].getQuestions()[j].getComments().getSize(); ++k)
		{
			rewrite << topics[currentIndex].getQuestions()[j].getComments()[k];
		}
	}

	rewrite.close();
}

void upVote(bool* doUpvote, Vector<Comment>& commentsToPrint)
{
	std::cout << "Enter the id of the comment you want to vote for:";
	size_t id;
	std::cin >> id;

	for (size_t i = 0; i < commentsToPrint.getSize(); ++i)
	{
		if (id == commentsToPrint[i].getId() && doUpvote[i] == true)
		{
			commentsToPrint[i].setUpvote(commentsToPrint[i].getUpvote() - 1);
			doUpvote[i] = false;
			return;
		}
	}

	for (size_t i = 0; i < commentsToPrint.getSize(); ++i)
	{
		if (id == commentsToPrint[i].getId())
		{
			commentsToPrint[i].setUpvote(commentsToPrint[i].getUpvote() + 1);
			doUpvote[i] = true;
		}
	}
}

void downVote(bool* doDownvote, Vector<Comment>& commentsToPrint)
{
	std::cout << "Enter the id of the comment you want to vote for:";
	size_t id;
	std::cin >> id;

	for (size_t i = 0; i < commentsToPrint.getSize(); ++i)
	{
		if (id == commentsToPrint[i].getId() && doDownvote[i] == true)
		{
			commentsToPrint[i].setDownvote(commentsToPrint[i].getDownvote() - 1);
			doDownvote[i] = false;
			return;
		}
	}

	for (size_t i = 0; i < commentsToPrint.getSize(); ++i)
	{
		if (id == commentsToPrint[i].getId())
		{
			commentsToPrint[i].setDownvote(commentsToPrint[i].getDownvote() + 1);
			doDownvote[i] = true;
		}
	}
}

void p_open(size_t postIndex, char* filename, User& user, Question& question, Comment& comment, size_t currentIndex ,Vector<Topic>& topics)
{
	char command[SIZE];
	size_t counter = 0;
	bool find = false;

	//Using the 'doUpvote' and 'doDownvote' bool arrays in order to know if we  
	//already voted for some comment. For example if someone tries to upvote
	//a comment that has been upvoted from someone else earlier the upvoted will 
	//increase, but if we try to upvote one comment twice from one account the 
	//upvotes will decrease.
	bool* doUpvote = new bool[topics[currentIndex].getQuestions().getSize()];
	bool* doDownvote = new bool[topics[currentIndex].getQuestions().getSize()];

	std::cout << std::endl << "Opened post: '" << question.getTitle() << "'" << std::endl;
	std::cin.get();
	while (true)
	{
		p_openCommandsList();
		std::cout << std::endl << "Enter the command you want to use:";
		std::cin.getline(command, MAX_VALUES_SIZE);

		if (stringComp(command, "comment") == true)
		{
			createComment(user, question, comment, filename);
			question.setComment(comment);

			for (size_t i = 0; i < topics[currentIndex].getQuestions().getSize(); ++i)
			{
				if (i == question.getId())
				{
					topics[currentIndex].setQuestionAtIndex(i, question);
				}
			}

			std::ofstream writeFile(filename, std::ios::app);
			if (!writeFile.is_open())
			{
				std::cout << "ERROR! The file could not be opened!";
				return;
			}

			writeFile << comment;
			std::cout << std::endl << "Your comment has been successfully posted!" << std::endl;

			user.setPoints(user.getPoints() + 1);//Every time we comment we gain points

			writeFile.close();
		}
		else if (stringComp(command, "comments") == true)
		{
			Vector<Comment> commentsToPrint;

			readCommentsFromFile(filename, commentsToPrint);

			size_t commentsCount = 0;
			for (size_t i = 0; i < commentsToPrint.getSize(); ++i)
			{
				if (question.getId() == commentsToPrint[i].getQId())
				{
					commentsToPrint[i].printCommentInfo();
					++commentsCount;
				}
			}

			if (commentsCount == 0)
			{
				std::cout << std::endl << "There is no comments under the selected post!" << std::endl;
			}
			else
			{
				char command[SIZE];
				commentsCommandsList(command);

				if (stringComp(command, "upvote") == true)
				{
					upVote(doUpvote, commentsToPrint);
					topics[currentIndex].clearQuestionComments(postIndex);
					topics[currentIndex].setQuestionComments(postIndex, commentsToPrint);
					rewriteFileInfo(filename, topics, currentIndex);
				}
				else if (stringComp(command, "downvote") == true)
				{
					downVote(doDownvote, commentsToPrint);
					topics[currentIndex].clearQuestionComments(postIndex);
					topics[currentIndex].setQuestionComments(postIndex, commentsToPrint);
					rewriteFileInfo(filename, topics, currentIndex);
				}
				else if (stringComp(command, "quit") == true)
				{
					return;
				}
				else
				{
					std::cout << std::endl << "Wrong command!" << std::endl;
				}
			}
		}
		else if(stringComp(command, "p_close") == true)
		{
			return;
		}
		std::cin.get();
	}

	delete[] doUpvote;
	delete[] doDownvote;
}

void open(User& user, Vector<User> users, size_t currentIndex, Vector<Topic>& selectedTopics, MyString filename, bool& exit)
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

	std::cin.get();
	std::cout << "\nWelcome to '" << filename.c_str() << "'!\n\n";

	readQuestionsFromFile(readTopic, selectedTopics[currentIndex]);
	Vector<Question> tempQuestions;

	for (size_t i = 0; i < selectedTopics[currentIndex].getQuestions().getSize(); ++i)
	{
		tempQuestions = selectedTopics[currentIndex].getQuestions();
	}

	char command[SIZE];
	bool localExit = false;

	Question currentQuestion;
	Comment currentComment;

	while (localExit == false)
	{
		openTopicCommands(command);

		if (stringComp(command, "post") == true)
		{
			Question createQ;

			createQuestion(createQ, tempFilename);

			std::ofstream postQuestion(tempFilename, std::ios::app);
			if (!postQuestion.is_open())
			{
				std::cout << "\nERROR! The file could not be opened!\n";
				exit = true;
				return;
			}

			postQuestion << createQ;
			std::cout << "\nYour question has been successfully posted!\n";

			postQuestion.close();
		}
		else if (stringComp(command, "p_open") == true)
		{
			std::ifstream localReadTopic(tempFilename);
			if (!localReadTopic.is_open())
			{
				std::cout << "ERROR! The file could not be opened!\n";
				return;
			}

			std::cout << std::endl;
			Topic tempTopic = selectedTopics[currentIndex];
			
			std::cout << "POSTS:" << std::endl;

			tempTopic.clearQuestions();
			readQuestionsFromFile(localReadTopic, tempTopic);
			selectedTopics[currentIndex].clearQuestions();
			selectedTopics[currentIndex] = tempTopic;

			localReadTopic.close();

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

				for (size_t i = 0; i < selectedTopics[currentIndex].getQuestions().getSize(); ++i)
				{
					if (tempId == selectedTopics[currentIndex].getQuestions()[i].getId())
					{
						p_open(i, tempFilename, user, tempQuestions[i], currentComment, currentIndex, selectedTopics);
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
				char title[SIZE];
				std::cout << "\nEnter the title of the post you want to check: ";
				std::cin.get();
				std::cin.getline(title, MAX_VALUES_SIZE);

				for (size_t i = 0; i < selectedTopics[currentIndex].getQuestions().getSize(); ++i)
				{
					if (stringComp(title, selectedTopics[currentIndex].getQuestions()[i].getTitle().c_str()))
					{
						p_open(i, tempFilename, user, tempQuestions[i], currentComment, currentIndex, selectedTopics);
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
		else if (stringComp(command, "quit") == true)
		{
			return;
		}
		else if (stringComp(command, "exit") == true)
		{
			saveUserInfo(user, users);

			exit = true;
			return;
		}
	}

	readTopic.close();
}

void commandsForTopics(User& user, Vector<User> users, char* commandForTopics, Vector<Topic>& selectedTopics, bool& goBack, bool& exit)
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
						open(user, users, i, selectedTopics, selectedTopics[i].getTopicName(), exit);
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
				char currentTitle[SIZE];
				std::cout << "Enter the full title: ";
				std::cin.get();
				std::cin.getline(currentTitle, MAX_VALUES_SIZE);
				std::cout << "Tap to open the topic!" << std::endl;

				for (size_t i = 0; i < selectedTopics.getSize(); ++i)
				{
					if (stringComp(currentTitle, selectedTopics[i].getTopicName().c_str()))
					{
						open(user, users, i, selectedTopics, selectedTopics[i].getTopicName(), exit);
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
			saveUserInfo(user, users);
			exit = true;
			return;
		}

		commandsListForTopics(commandForTopics);
	}
}

void func(bool& exit, bool& logout, char* command, User& user, Vector<Topic>& topics, Vector<User>& users)
{
	Vector<Topic> selectedTopics;
	char commandForTopics[SIZE];

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
			char keyWord[SIZE];
			std::cin.getline(keyWord, MAX_VALUES_SIZE);
			search(keyWord, topics, selectedTopics, goBack);

			if (goBack == true)
			{
				printCommandsList(command);
			}
			else
			{
				commandsForTopics(user, users, commandForTopics, selectedTopics, goBack, exit);

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
			saveUserInfo(user, users);

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
