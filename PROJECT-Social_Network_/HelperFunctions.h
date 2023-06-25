#pragma once
#include <iostream>
#include "User.h"
#include "Topic.h"
#include "MyStringSso.h"
#include "Vector.hpp"

const int SIZE = 100;
const int MAX_TOPICS_NUMBER = 500;
const char USERS_LIST_FILE[] = "UsersList.txt";
const char TOPICS_LIST_FILE[] = "TopicsList.txt";

//Variables that show where the exact value is saved in the file with the registered users
//For example each time a user is being registered his info is being saved in the 
// following sequence :  First name , Surname, Password, Id , Points
const int firstNameIndex = 1;
const int surnameIndex = 2;
const int passwordIndex = 3;
const int idIndex = 4;
const int pointsIndex = 5;

//Helper function to find the length of string
size_t stringLen(const char* string)
{
	size_t length = 0;

	while (string[length] != '\0')
	{
		++length;
	}

	return length;
}

//Helper function that compares two strings
bool stringComp(const char* firstStr, const char* secondStr)
{
	size_t firstStrLen = stringLen(firstStr);
	size_t secondStrLen = stringLen(secondStr);

	if (firstStrLen == secondStrLen)
	{
		int equal = 0;

		for (size_t i = 0; i < firstStrLen; ++i)
		{
			if (firstStr[i] == secondStr[i])
			{
				++equal;
			}
		}

		if (equal == firstStrLen)
		{
			return true;
		}
	}

	return false;
}

void stringCopy(const MyString& original, char* copy)
{
	for (int i = 0; i < original.length() + 1; ++i)
	{
		if (i != original.length())
		{
			copy[i] = original[i];
		}
		else
		{
			copy[i] = '\0';
		}
	}
}

//Using the 'getCharCountFromFile' and 'getLinesCount' functions that we implemented during lectures
//github: Angeld55
size_t getCharCountFromFile(std::ifstream& ifs, char ch)
{
	size_t currentPosition = ifs.tellg();
	ifs.seekg(0, std::ios::beg);

	if (!ifs.is_open())
	{
		return 0;
	}

	unsigned int count = 0;

	while (true)
	{
		char current = ifs.get();

		if (ifs.eof())
		{
			break;
		}

		if (current == ch)
		{
			count++;
		}
	}

	ifs.clear();
	ifs.seekg(currentPosition);

	return count;
}

size_t getLinesCount(const char* FILENAME)
{
	std::ifstream file(FILENAME);

	if (!file.is_open())
	{
		std::cout << "ERROR! The file could not be opened!";
		return 0;
	}

	return getCharCountFromFile(file, '\n') + 1;

	file.close();
}

size_t turnCharArrayIntoNum(const char* arr, size_t num)
{
	std::stringstream stream(arr);
	stream >> num;

	return num;
}
