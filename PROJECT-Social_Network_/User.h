#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include "MyStringSso.h"

const short MIN_PASSWORD_LEN = 5;
const int BUFFER_SIZE = 1024;
const char USERS_LIST_FILE[] = "UsersList.txt";

//Variables that show where the exact value is saved in the file with the registered users
//For example each time a user is being registered his info is being saved in the 
// following sequence :  First name , Surname, Password, Id , Points
static const int firstNameIndex = 1;
static const int surnameIndex = 2;
static const int passwordIndex = 3;
static const int idIndex = 4;
static const int pointsIndex = 5;

class User
{
	MyString firstName;
	MyString surname;
	MyString password;
	size_t id = 0;
	size_t points = 0;
	size_t numberOfUser = 0;

public:

	User();

	void setFirstName(const MyString& firstName);

	void setSurname(const MyString& surname);

	void setPassword(const MyString& password);

	void setId(const size_t& id);

	void setPoints(const size_t& points);

	void setNumberOfUser(const size_t& numberOfUser);

	const MyString& getFirstName() const;

	const MyString& getSurname() const;

	const MyString& getPassword() const;

	size_t getId() const;

	size_t getPoints() const;

	size_t getNumberOfUser() const;

	bool findUser(std::ifstream& ifs);

	const void printUsersInfo() const;

	void turnCharArrIntoId(const char* arr);

	void turnCharArrIntoPoints(const char* arr);

	friend std::ostream& operator<<(std::ostream& os, const User& user);
};

size_t getCharCountFromFile(std::ifstream& ifs, char ch);

size_t getLinesCount(const char* FILENAME);

size_t stringLen(const char* string);

bool stringComp(const char* firstStr, const char* secondStr);


