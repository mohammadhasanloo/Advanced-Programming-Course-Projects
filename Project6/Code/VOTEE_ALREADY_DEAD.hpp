#ifndef VOTEE_ALREADY_DEAD_H
#define VOTEE_ALREADY_DEAD_H
#include <exception>


class votee_already_dead :public std::exception
{
public:
	const char* what() const throw() { return "Votee already dead"; }
};

#endif
