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
		return;
	}
}

void User::setId(const size_t id)
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

void User::setPoints(const size_t points)
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

const size_t User::getId() const
{
	return id;
}

const size_t User::getPoints() const
{
	return points;
}

const void User::printUsersInfo() const
{
	std::cout << "\nYour data as a user is:\n"
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