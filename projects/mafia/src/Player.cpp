#include "Player.hpp"



using namespace std;



Player::Player(string new_role, string _player_name, Player* _votee_player)
{
	player_name = _player_name;
	votee_player = _votee_player;
	if (new_role == JOKER)
		player_role = new joker(FIRST_VOTES_CAST_NUM,false,false,false,false,false);
	else if (new_role == VILLAGER)
		player_role = new villager(FIRST_VOTES_CAST_NUM, false, false, false, false);
	else if (new_role == DOCTOR)
		player_role = new doctor(FIRST_VOTES_CAST_NUM, false, false, false, false);
	else if (new_role == DETECTIVE)
		player_role = new detective(FIRST_VOTES_CAST_NUM,false, false, false, false);
	else if (new_role == MAFIA)
		player_role = new mafia(FIRST_VOTES_CAST_NUM, false, false, false, false);
	else if (new_role == GODFATHER)
		player_role = new godfather(FIRST_VOTES_CAST_NUM, false, false, false, false);
	else if (new_role == SILENCER)
		player_role = new silencer(FIRST_VOTES_CAST_NUM, false, false, false, false, nullptr);
	else if (new_role == BULLETPROOF)
		player_role = new bulletproof(FIRST_VOTES_CAST_NUM,true, false, false, false, false);
}

bool Player::check_to_find_name(string new_name)
{
	if (new_name == player_name)
		return true;
	return false;
}

void Player::set_new_votee(Player* votee)
{
	votee_player = votee;
	player_role->change_is_voted_true();
}

void Player::mafia_night_fun(Player* player_votee)
{
	if ((get_player_role() == SILENCER) && (get_who_silenced() == nullptr))
	{
		player_votee->make_is_silenced_true();
		change_who_silenced(player_votee);
	}
	else
	{
		votee_player = player_votee;
		make_is_voted_true();
	}
}

void Player::detective_night_fun(Player* player_votee)
{
	make_is_voted_true();
	if (player_votee->get_player_role() == SILENCER || player_votee->get_player_role() == MAFIA)
		cout << YES << endl;
	else
		cout << NO << endl;

}

void Player::doctor_night_fun(Player* player_votee)
{
	make_is_voted_true();
	player_votee->make_is_healed_true();
}

void Player::change_information_after_day()
{
	votee_player = nullptr;
	player_role->change_information_after_day();
}

void Player::change_information_after_night()
{
	votee_player = nullptr;
	player_role->change_information_after_night();
}

void Player::change_info_after_swap(role* new_role,bool curr_has_silenced)
{
	player_role = new_role;
	player_role->change_has_silenced(curr_has_silenced);
}
