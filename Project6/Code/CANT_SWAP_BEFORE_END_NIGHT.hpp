#ifndef CANT_SWAP_BEFORE_END_NIGHT_H
#define CANT_SWAP_BEFORE_END_NIGHT_H
#include <exception>


class cant_swap_before_end_night :public std::exception
{
public:
	const char* what() const throw() { return "Can't swap before end of night"; }
};

#endif
