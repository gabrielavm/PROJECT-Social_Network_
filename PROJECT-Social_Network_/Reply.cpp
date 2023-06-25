#include "Reply.h"

Reply::Reply() = default;

void Reply::setData(const MyString& data)
{
	if (data.length() >= 1)
	{
		this->data = data;
	}
	else
	{
		return;
	}
}

void Reply::setCreator(const MyString& creator)
{
	if (creator.length() >= 1)
	{
		this->creator = creator;
	}
	else
	{
		return;
	}
}

void Reply::setId(size_t id)
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

const MyString& Reply::getData() const
{
	return data;
}

const MyString& Reply::getCreator() const
{
	return creator;
}

const size_t Reply::getId() const
{
	return id;
}

const void Reply::printReplyInfo() const
{
	std::cout << creator << ": " << data.c_str() << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Reply& reply)
{
	return os << std::endl << "reply:" << std::endl
		<< reply.id << std::endl
		<< reply.data << std::endl
		<< reply.creator << std::endl;
}