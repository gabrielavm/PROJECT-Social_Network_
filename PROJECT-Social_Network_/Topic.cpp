#include "Topic.h"

Topic::Topic() = default;

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