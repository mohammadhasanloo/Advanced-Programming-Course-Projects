#include <iostream>
#include <vector>
#include <cmath>
#include "rsdl.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include "Ball.hpp"
#include "Bead.hpp"
#include "Const_Values.hpp"

using namespace std;


int main()
{
	Game new_game = Game(false, false, PLAYER_START, false);
	new_game.start_game();
	return 0;
}
