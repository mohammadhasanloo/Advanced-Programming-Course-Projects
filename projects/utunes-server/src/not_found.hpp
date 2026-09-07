#ifndef NOT_FOUND_H
#define NOT_FOUND_H
#include <exception>


class not_found :public std::exception
{
public:
	const char* what() const throw() { return "Not Found"; }
};

#endif