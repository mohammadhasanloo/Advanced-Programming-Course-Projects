#ifndef USER_IS_DEAD_H
#define USER_IS_DEAD_H
#include <exception>

class user_is_dead :public std::exception
{
public:
	const char* what() const throw() { return "User is dead"; }
};

#endif
