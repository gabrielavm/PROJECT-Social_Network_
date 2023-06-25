#pragma once
#include "MyStringSso.h"
#include "Comment.h"
#include "Vector.hpp"

class Question
{
	Vector<Comment> comments;
	MyString title;
	MyString content;
	size_t id = 0;

public:

	Question();

	void setTitle(const MyString& title);
	void setContent(const MyString& content);
	void setComment(const Comment& comment);
	void setCommentReplies(size_t index, const Vector<Reply> replies);
	void setId(const size_t id);

	void clearComments();
	void clearCommentsReplies(size_t index);

	const MyString& getTitle() const;
	const MyString& getContent() const;
	const Vector<Comment>& getComments() const;
	const size_t getId() const;

	const void printQuestionInfo() const;
	friend std::ostream& operator<<(std::ostream& os, const Question& question);
};
