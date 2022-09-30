#include "Player.hpp"


using namespace std;



Player::Player(int _score, int _round_win)
{
	score = _score;
	round_win = _round_win;
}

void Player::show_text_player(Window* window, int start_x, int start_y, RGB colour)
{
	string input = "round= " + to_string(round_win) + "  score= " + to_string(score);
	Point src_text(start_x, start_y);
	window->show_text(input, src_text, colour, FONT_NAME, SCREEN_FONT_SIZE);
}

void Player::change_player_info_after_goal()
{
	score++;
}

bool Player::finish_round(int goal)
{
	if (score == goal)
		return false;
	else
		return true;
}

void Player::change_players_info_after_round(int goal)
{
	if (score == goal)
		round_win++;
	score = 0;
}

bool Player::finish_game(bool Even, int round)
{
	if (Even)
	{
		if (round_win == (round / 2))
			return true;
		return false;
	}
	else
	{
		if (round_win == ((round / 2) + 1))
			return true;
		return false;
	}
}
