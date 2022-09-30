#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "rsdl.hpp"
#include "Const_Values.hpp"


class Player
{
public:
	Player(int _score, int _round_win);

	bool finish_game(bool Even, int round);
	bool finish_round(int goal);
	void change_player_info_after_goal();
	void change_players_info_after_round(int goal);
	void show_text_player(Window* window, int start_x, int start_y, RGB colour);

	int get_round_win() { return round_win; }
	int get_score() { return score; }
private:
	int score;
	int round_win;
};

#endif
