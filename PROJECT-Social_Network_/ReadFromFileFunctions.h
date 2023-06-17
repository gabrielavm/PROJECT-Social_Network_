#pragma once
#include <iostream>
#include "HelperFunctions.h"

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

void readCommentsFromFile(char* filename, Vector<Comment>& comments)
{
	Comment tempComment;
	Question tempQuestion;
	size_t counter = 0;
	bool isComment = false;
	size_t tempId;
	size_t tempQId;
	size_t tempUpvote;
	size_t tempDownvote;
	size_t numberOfComments = 0;

	std::ifstream stream(filename);
	if (!stream.is_open())
	{
		std::cout << std::endl << "ERROR! The file could nt be opened!" << std::endl;
	}

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
			tempQId = turnCharArrayIntoNum(buffer, tempComment.getQId());
			tempComment.setQId(tempQId);
		}
		else if (counter == 2 && isComment == true)
		{
			tempId = turnCharArrayIntoNum(buffer, tempComment.getId());
			tempComment.setId(tempId);
		}
		else if (counter == 3 && isComment == true)
		{
			tempComment.setCreatorName(buffer);
		}
		else if (counter == 4 && isComment == true)
		{
			tempComment.setCommentText(buffer);
		}
		else if (counter == 5 && isComment == true)
		{
			tempUpvote = turnCharArrayIntoNum(buffer, tempComment.getUpvote());
			tempComment.setUpvote(tempUpvote);
		}
		else if (counter == 6 && isComment == true)
		{
			tempDownvote = turnCharArrayIntoNum(buffer, tempComment.getDownvote());
			tempComment.setDownvote(tempDownvote);

			comments.pushBack(tempComment);

			++numberOfComments;
			counter = 0;
			isComment = false;
		}

		if (isComment == true)
		{
			++counter;
		}
	}

	stream.close();
}
