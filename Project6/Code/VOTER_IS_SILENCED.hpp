#ifndef VOTER_IS_SILENCED_H
#define VOTER_IS_SILENCED_H
#include <exception>


class voter_is_silenced :public std::exception
{
public:
	const char* what() const throw() { return "Voter is silenced"; }
};

#endif
