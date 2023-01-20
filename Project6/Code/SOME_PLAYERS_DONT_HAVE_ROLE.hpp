#ifndef SOME_PLAYERS_DONT_HAVE_ROLE_H
#define SOME_PLAYERS_DONT_HAVE_ROLE_H
#include <exception>


class some_players_dont_have_role :public std::exception
{
public:
	const char* what() const throw() { return "One or more players do not have a role"; }
};

#endif
