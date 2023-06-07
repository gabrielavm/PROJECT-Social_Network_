#pragma once
#include <iostream>
#include "MyStringSso.h"
#include "Question.h"

class Topic
{
	MyString topicName;
	MyString creatorName;
	MyString topicDescription;
	Question* questions = {};
	size_t questionsCapacity = 0;
	size_t questionsCount = 0;
	size_t id = 0;

	void free();
	void copyFrom(const Topic& other);
	void moveFrom(Topic&& other);
	void resize();

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

	void addQuestion(const Question& question);
	void addQuestion(Question&& question);

	const void printTopicInfo() const;

	friend std::ostream& operator<<(std::ostream& os, const Topic& topic);
};
