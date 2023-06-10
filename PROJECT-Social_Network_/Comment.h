#pragma once
#include "MyStringSso.h"
#include "Vector.hpp"

class Comment
{
	MyString creatorName;
	MyString commentText;
	size_t downvote = 0;
	size_t upvote = 0;
	size_t id = 0;
	size_t qId = 0;//This variable will collect the id of the question
	//that we comment about

public:

	Comment();

	void setCreatorName(const MyString& creatorName);
	void setCommentText(const MyString& commentText);
	void setDownvote(const size_t downvote);
	void setUpvote(const size_t upvote);
	void setId(const size_t id);
	void setQId(const size_t qId);

	const MyString& getCreatorName() const;
	const MyString& getCommentText() const;
	const size_t getDownvote() const;
	const size_t getUpvote() const;
	const size_t getId() const;
	const size_t getQId() const;

	const void printCommentInfo() const;

	friend std::ostream& operator<<(std::ostream& os, const Comment& comment);
};
