#include "Comment.h"

Comment::Comment() = default;

void Comment::setCreatorName(const MyString& creatorName)
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

void Comment::setCommentText(const MyString& commentText)
{
	if (commentText.length() >= 1)
	{
		this->commentText = commentText;
	}
	else
	{
		return;
	}
}

void Comment::setDownvote(const size_t downvote)
{
	if (downvote < 0)
	{
		this->downvote = 0;
	}
	else
	{
		this->downvote = downvote;
	}
}

void Comment::setUpvote(const size_t upvote)
{
	if (upvote < 0)
	{
		this->upvote = 0;
	}
	else
	{
		this->upvote = upvote;
	}
}

void Comment::setId(const size_t id)
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

void Comment::setQId(const size_t qId)
{
	if (qId < 0)
	{
		return;
	}
	else
	{
		this->qId = qId;
	}
}

const MyString& Comment::getCreatorName() const
{
	return creatorName;
}

const MyString& Comment::getCommentText() const
{
	return commentText;
}

const size_t Comment::getDownvote() const
{
	return downvote;
}

const size_t Comment::getUpvote() const
{
	return upvote;
}

const size_t Comment::getId() const
{
	return id;
}

const size_t Comment::getQId() const
{
	return qId;
}

const void Comment::printCommentInfo() const
{
	std::cout << std::endl << "Comment: " << this->commentText << std::endl
		<< "By: " << this->creatorName << std::endl
		<< "Comment about: {id: " << this->qId << "}" << std::endl
		<< "downvote: " << this->downvote << " | " << "unvote: " << this->upvote << std::endl
		<< "ID: " << this->id << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Comment& comment)
{
	return os << comment.id << std::endl
		<< comment.creatorName << std::endl
		<< comment.commentText << std::endl
		<< comment.upvote << std::endl
		<< comment.downvote << std::endl;
	//saving the id of the topic in the file first in order to know where the information
	//about the new topic begins
}