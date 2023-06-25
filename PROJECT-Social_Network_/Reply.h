#pragma once
#include <iostream>
#include "MyStringSso.h"

class Reply
{
	MyString data;
	MyString creator;
	size_t id = 0;//This variable will be for the id of the comment
	//we reply to
	
public:

	Reply();

	void setData(const MyString& data);
	void setCreator(const MyString& creator);
	void setId(size_t id);

	const MyString& getData() const;
	const MyString& getCreator() const;
	const size_t getId() const;

	const void printReplyInfo() const;

	friend std::ostream& operator<<(std::ostream& os, const Reply& reply);
};
