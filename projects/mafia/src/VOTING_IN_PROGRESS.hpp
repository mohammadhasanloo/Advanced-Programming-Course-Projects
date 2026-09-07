#ifndef VOTING_IN_PROGRESS_H
#define VOTING_IN_PROGRESS_H
#include <exception>


class voting_in_progress :public std::exception
{
public:
	const char* what() const throw() { return "Voting in progress"; }
};

#endif
