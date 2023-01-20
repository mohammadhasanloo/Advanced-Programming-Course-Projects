#include <iostream>
#include "Const_Values.hpp"
#include "Game.hpp"

using namespace std;


int main()
{
	Game new_game=Game(START_WITH_DAY,false, FIRST_MAFIAS_NUM, FIRST_VILLAGERS_NUM,
		FIRST_DAY_NUM, FIRST_NIGHT_NUM,false,false, false, false,false,false);
	new_game.run();
	return 0;
}
