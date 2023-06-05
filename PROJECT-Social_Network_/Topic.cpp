#include "Topic.h"

void Topic::free()
{
	delete[] questions;
	questionsCapacity = 0;
	questionsCount = 0;
}

void Topic::copyFrom(const Topic& other)
{
	questionsCount = other.questionsCount;
	questionsCapacity = other.questionsCapacity;

	questions = new Question[questionsCapacity];

	for (int i = 0; i < questionsCount; ++i)
	{
		questions[i] = other.questions[i];
	}

	topicName = other.topicName;
	creatorName = other.creatorName;
	topicDescription = other.topicDescription;
	id = other.id;
}

void Topic::moveFrom(Topic&& other)
{
	questions = other.questions;
	other.questions = nullptr;

	questionsCount = other.questionsCount;
	other.questionsCount = 0;

	questionsCapacity = other.questionsCapacity;
	other.questionsCapacity = 0;

	topicName = other.topicName;
	creatorName = other.creatorName;
	topicDescription = other.topicDescription;

	id = other.id;
	other.id = 0;
}

void Topic::resize()
{
	Question* tempQuestions = questions;
	questions = new Question[questionsCapacity * 2];

	for (int i = 0; i < questionsCount; ++i)
	{
		questions[i] = tempQuestions[i];
	}

	questionsCapacity *= 2;
	delete[] tempQuestions;
}

Topic::Topic()
{
	size_t questionsCapacity = 8; // default value
	Question* questions = new Question[questionsCapacity];
	size_t id = 0;
}

Topic::Topic(const Topic& other)
{
	copyFrom(other);
}

Topic& Topic::operator=(const Topic& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Topic::~Topic()
{
	free();
}

Topic::Topic(Topic&& other) noexcept
{
	moveFrom(std::move(other));
}

Topic& Topic::operator=(Topic&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

void Topic::setTopicName(const MyString& topicName)
{
	if (topicName.length() >= 1)
	{
		this->topicName = topicName;
	}
	else
	{
		return;
	}
}

void Topic::setCreatorName(const MyString& creatorName)
{
	if (creatorName.length() >= 1)
	{
		this->creatorName = creatorName;
	}
	else
	{
		return;
	}
}

void Topic::setTopicDescription(const MyString& topicDescription)
{
	if (topicDescription.length() >= 1)
	{
		this->topicDescription = topicDescription;
	}
	else
	{
		return;
	}
}

void Topic::setId(const size_t id)
{
	if (id < 0)
	{
		return;
	}
	else
	{
		this->id = id;
	}
}

const MyString& Topic::getTopicName() const
{
	return topicName;
}

const MyString& Topic::getCreatorName() const
{
	return creatorName;
}

const MyString& Topic::getTopicDescription() const
{
	return topicDescription;
}

const size_t Topic::getId() const
{
	return id;
}

void Topic::addQuestion(const Question& question)
{
	if (questionsCount >= questionsCapacity)
	{
		resize();
	}

	questions[questionsCount++] = question;
}

void Topic::addQuestion(Question&& question)
{
	if (questionsCount >= questionsCapacity)
	{
		resize();
	}

	questions[questionsCount++] = std::move(question);
}

const void Topic::printTopicInfo() const
{
	std::cout << "\nName: " << this->topicName << std::endl
		<< "Description: " << this->topicDescription << std::endl
		<< "Created by: " << this->creatorName << std::endl
		<< "ID: " << this->id << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Topic& topic)
{
	return os << topic.id << std::endl
		<< topic.creatorName << std::endl
		<< topic.topicName << std::endl
		<< topic.topicDescription << std::endl;
	//saving the id of the topic in the file first in order to know where the information
	//about the new topic begins
}