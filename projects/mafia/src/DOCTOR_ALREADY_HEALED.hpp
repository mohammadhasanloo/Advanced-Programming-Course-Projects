#ifndef DOCTOR_ALREADY_HEALED_H
#define DOCTOR_ALREADY_HEALED_H
#include <exception>


class doctor_already_healed :public std::exception
{
public:
	const char* what() const throw() { return "Doctor has already healed"; }
};

#endif
