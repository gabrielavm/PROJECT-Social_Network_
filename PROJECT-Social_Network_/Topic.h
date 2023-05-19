#pragma once
#include <iostream>
#include "MyStringSso.h"

class Topic
{
	MyString topicName;
	MyString creatorName;
	MyString topicDescription;
	size_t id = 0;

public:

	Topic();

	void setTopicName(const MyString& topicName);

	void setCreatorName(const MyString& creatorName);

	void setTopicDescription(const MyString& topicDescription);

	void setId(const size_t id);

	const MyString& getTopicName() const;

	const MyString& getCreatorName() const;

	const MyString& getTopicDescription() const;

	const size_t getId() const;

	const void printTopicInfo() const;

	friend std::ostream& operator<<(std::ostream& os, const Topic& topic);
};
