#ifndef DETECTIVE_ALREADY_ASKED_H
#define DETECTIVE_ALREADY_ASKED_H
#include <exception>


class detective_already_asked :public std::exception
{
public:
	const char* what() const throw() { return "Detective has already asked"; }
};

#endif
