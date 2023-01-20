#ifndef USER_NOT_JOINED_H
#define USER_NOT_JOINED_H
#include <exception>


class user_not_joined :public std::exception
{
public:
	const char* what() const throw() { return "User not joined"; };
};

#endif
