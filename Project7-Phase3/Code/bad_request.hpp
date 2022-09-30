#ifndef BAD_REQUEST_H
#define BAD_REQUEST_H
#include <exception>


class bad_request :public std::exception
{
public:
	const char* what() const throw() { return "Bad Request"; }
};

#endif