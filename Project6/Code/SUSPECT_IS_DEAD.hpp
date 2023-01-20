#ifndef SUSPECT_IS_DEAD_H
#define SUSPECT_IS_DEAD_H
#include <exception>


class suspect_is_dead :public std::exception
{
public:
	const char* what() const throw() { return "Suspect is dead"; }
};

#endif
