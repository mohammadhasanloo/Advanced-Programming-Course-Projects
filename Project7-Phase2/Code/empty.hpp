#ifndef EMPTY_H
#define EMPTY_H
#include <exception>


class empty_err :public std::exception
{
public:
	const char* what() const throw() { return "Empty"; }
};

#endif