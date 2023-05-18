#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include "MyStringSso.h"

const short MIN_PASSWORD_LEN = 5;
const int BUFFER_SIZE = 1024;
const char USERS_LIST_FILE[] = "UsersList.txt";

class User
{
	MyString firstName;
	MyString surname;
	MyString password;
	size_t id = 0;
	size_t points = 0;

public:

	User();

	void setFirstName(const MyString& firstName);

	void setSurname(const MyString& surname);

	void setPassword(const MyString& password);

	void setId(const size_t& id);

	void setPoints(const size_t& points);

	const MyString& getFirstName() const;

	const MyString& getSurname() const;

	const MyString& getPassword() const;

	size_t getId() const;

	size_t getPoints() const;

	const void printUsersInfo() const;

	friend std::ostream& operator<<(std::ostream& os, const User& user);
};