#pragma once
#include "MyStringSso.h"

class Question
{
	MyString title;
	MyString content;
	size_t id = 0;

public:

	Question();

	void setTitle(const MyString& title);

	void setContent(const MyString& content);

	void setId(const size_t id);

	const MyString& getTitle() const;

	const MyString& getContent() const;

	const size_t getId() const;

	const void printQuestionInfo() const;

	friend std::ostream& operator<<(std::ostream& os, const Question& question);
};
