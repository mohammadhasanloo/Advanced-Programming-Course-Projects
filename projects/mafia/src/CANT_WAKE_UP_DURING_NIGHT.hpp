#ifndef CANT_WAKE_UP_DURING_NIGHT_H
#define CANT_WAKE_UP_DURING_NIGHT_H
#include <exception>


class cant_wake_up_during_night :public std::exception
{
public:
	const char* what() const throw() { return "User can not wake up during night"; }
};

#endif
