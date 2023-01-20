#ifndef PERSON_IS_DEAD_H
#define PERSON_IS_DEAD_H
#include <exception>


class person_is_dead :public std::exception
{
public:
	const char* what() const throw() { return "Person is dead"; }
};

#endif
