#ifndef CHAR_ALREADY_SWAPPED_H
#define CHAR_ALREADY_SWAPPED_H
#include <exception>


class char_already_swapped :public std::exception
{
public:
	const char* what() const throw() { return "Characters already swapped"; }
};

#endif
