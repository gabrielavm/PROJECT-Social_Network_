#include "User.h"

User::User() = default;

void User::setFirstName(const MyString& firstName)
{
	if (firstName.length() >= 1)
	{
		this->firstName = firstName;
	}
	else
	{
		std::cout << "ERROR! You have to enter your first name!";
		return;
	}
}

void User::setSurname(const MyString& surname)
{
	if (surname.length() >= 1)
	{
		this->surname = surname;
	}
	else
	{
		std::cout << "ERROR! You have to enter your surname!";
		return;
	}
}

void User::setPassword(const MyString& password)
{
	if (password.length() >= 1)
	{
		this->password = password;
	}
	else
	{
		std::cout << "ERROR! You have to enter your password!";
		return;
	}
}

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
	if (stringLen(firstStr) == stringLen(secondStr))
	{
		int equal = 0;

		for (size_t i = 0; i < strlen(firstStr); ++i)
		{
			if (firstStr[i] == secondStr[i])
			{
				++equal;
			}
		}

		if (equal == stringLen(firstStr))
		{
			return true;
		}
	}

	return false;
}

//Helper function for 'setId'. It turns char array (which contains the id of user symbol by symbol) 
//into valid type for id.
void User::turnCharArrIntoId(const char* arr)
{
	std::stringstream stream(arr);
	stream >> this->id;
}

void User::turnCharArrIntoPoints(const char* arr)
{
	std::stringstream stream(arr);
	stream >> this->points;
}

void User::setId(const size_t& id)
{
	User user;

	//The ID is unique for each user, therefore the ID of every user who is already registered
	//must be checked at each new registration in order to prevent repeating IDs
	//If the ID already exist this function will generate a new one 

	size_t idArray[BUFFER_SIZE] = {};
	size_t idCounter = 0;

	std::ifstream is(USERS_LIST_FILE);

	if (!is.is_open())
	{
		std::cout << "ERROR! The file could not be opened!";
		return;
	}

	while (!is.eof())
	{
		bool exist = false;//variable which will contain information about the existance of particular 
		// user's id. If this id already exists in the file with the registered users the value of 
		// the variable will be true.

		for (int i = 0; i < idCounter; ++i)
		{
			if (idArray[i] == id)
			{
				exist = true;
			}
		}

		if (exist == true)//If the value of the variable is true the program will generate new id
			//and go back to the setId function to check if the new id exist too.
		{
			srand((unsigned)time(NULL));
			setId(rand());
		}
		else
		{
			this->id = id;
		}
	}

	is.close();
}

void User::setPoints(const size_t& points)
{
	if (points < 0)
	{
		return;
	}
	else
	{
		this->points = points;
	}
}

void User::setNumberOfUser(const size_t& numberOfUser)
{
	if (numberOfUser < 0)
	{
		return;
	}
	else
	{
		this->numberOfUser = numberOfUser;
	}
}

const MyString& User::getFirstName() const
{
	return firstName;
}

const MyString& User::getSurname() const
{
	return surname;
}

const MyString& User::getPassword() const
{
	return password;
}

size_t User::getId() const
{
	return id;
}

size_t User::getPoints() const
{
	return points;
}

size_t User::getNumberOfUser() const
{
	return numberOfUser;
}

bool User::findUser(std::ifstream& ifs)
{
	User user;

	while (!ifs.eof())
	{
		char buffer[BUFFER_SIZE] = { '\0' };
		ifs.getline(buffer, BUFFER_SIZE);

		size_t counter = 0;
		bool correctName = false;
		bool correctPassword = false;

		std::stringstream stream(buffer);

		while (!stream.eof())
		{
			char temp[BUFFER_SIZE] = { '\0' };

			++counter;
			stream.getline(temp, BUFFER_SIZE, ' ');

			if (counter == firstNameIndex)
			{
				user.setFirstName(temp);
				if (user.firstName == this->firstName)
				{
					correctName = true;
				}
			}
			else if (counter == passwordIndex)
			{
				user.setPassword(temp);
				if (user.password == this->password)
				{
					correctPassword = true;
				}
			}

			if (correctName == true && correctPassword == true)//if the name and the password are correct
				//at the same time (both belong to the same user) it means that this user exist in the file
				// with the registered users
			{
				return true;
			}
		}
	}

	return false;
}

const void User::printUsersInfo() const
{
	std::cout << "Your data as a user is:\n"
		<< "First name: " << this->firstName << std::endl
		<< "Surname: " << this->surname << std::endl
		<< "ID: " << this->id << std::endl
		<< "Points: " << this->points << std::endl;
}

std::ostream& operator<<(std::ostream& os, const User& user)
{
	return os << user.firstName << " "
		<< user.surname << " "
		<< user.password << " "
		<< user.id << " "
		<< user.points << std::endl;
}