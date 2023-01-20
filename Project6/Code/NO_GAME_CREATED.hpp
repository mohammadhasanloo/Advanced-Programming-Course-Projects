#ifndef NO_GAME_CREATED_H
#define NO_GAME_CREATED_H
#include <exception>


class no_game_created :public std::exception
{
public:
	const char* what() const throw() { return "No game created"; };
};

#endif
