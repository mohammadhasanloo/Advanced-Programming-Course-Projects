#ifndef GAME_HAS_ALREADY_STARTED_H
#define GAME_HAS_ALREADY_STARTED_H
#include <exception>


class game_has_already_started :public std::exception
{
public:
	const char* what() const throw() { return "Game has already started"; }
};

#endif
