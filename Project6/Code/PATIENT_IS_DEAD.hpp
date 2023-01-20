#ifndef PATIENT_IS_DEAD_H
#define PATIENT_IS_DEAD_H
#include <exception>


class patient_is_dead :public std::exception
{
public:
	const char* what() const throw() { return "Patient is dead"; }
};

#endif
