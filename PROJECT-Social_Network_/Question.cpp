#include "Question.h"

Question::Question() = default;

void Question::setTitle(const MyString& title)
{
	if (title.length() >= 1)
	{
		this->title = title;
	}
	else
	{
		return;
	}
}

void Question::setContent(const MyString& content)
{
	if (content.length() >= 1)
	{
		this->content = content;
	}
	else
	{
		return;
	}
}

void Question::setComment(const Comment& comment)
{
	comments.pushBack(comment);
}

void Question::setId(const size_t id)
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

const MyString& Question::getTitle() const
{
	return title;
}

const MyString& Question::getContent() const
{
	return content;
}

const Vector<Comment>& Question::getComments() const
{
	return comments;
}

const size_t Question::getId() const
{
	return id;
}

const void Question::printQuestionInfo() const
{
	std::cout << std::endl << "Title of the question: " << this->title << std::endl
		<< "Content of the question: " << this->content << std::endl
		<< "ID: " << this->id << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Question& question)
{
	return os << "question:" << std::endl
		<< question.id << std::endl
		<< question.title << std::endl
		<< question.content << std::endl;
	//saving the id of the topic in the file first in order to know where the information
	//about the new topic begins
}