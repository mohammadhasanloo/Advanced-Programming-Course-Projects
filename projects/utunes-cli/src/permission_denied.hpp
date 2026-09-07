#ifndef PERMISSION_DENIED_H
#define PERMISSION_DENIED_H
#include <exception>


class permission_denied :public std::exception
{
public:
	const char* what() const throw() { return "Permission Denied"; }
};

#endif