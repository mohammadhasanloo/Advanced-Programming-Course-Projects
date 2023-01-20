#ifndef PLAYER_H
#define PLAYER_H


#include <iostream>
#include <vector>
#include <algorithm>
#include "Role.hpp"
#include "Const_Values.hpp"
#include "Joker.hpp"
#include "Mafia.hpp"
#include "Villager.hpp"
#include "Doctor.hpp"
#include "Detective.hpp"
#include "Silencer.hpp"
#include "Godfather.hpp"
#include "Bulletproof.hpp"





class Player
{
public:
	Player(std::string new_role, std::string _player_name, Player* _votee_player);

	bool check_to_find_name(std::string new_name);
	std::string get_player_name() { return player_name; }
	std::string get_player_role() { return player_role->get_role(); }
	bool get_is_dead() { return player_role->get_is_dead(); }
	void set_new_votee(Player* votee);
	bool get_is_voted() { return player_role->get_is_voted(); }
	bool get_is_silenced() { return player_role->get_is_silenced(); }
	void add_votes_cast_num() { player_role->add_votes_cast_num(); };
	void make_votee_player_null() { votee_player = nullptr; }
	Player* get_votee_player() { return votee_player; }
	int get_votes_cast_num() { return player_role->get_votes_cast_num(); }
	void make_is_dead_true() { player_role->make_is_dead_true(); }
	void change_information_after_day();
	Player* get_who_silenced() { return player_role->get_who_silenced(); }
	void doctor_night_fun(Player* player_votee);
	void make_is_voted_true() { player_role->make_is_voted_true(); }
	void make_is_healed_true() { player_role->make_is_healed_true(); }
	void detective_night_fun(Player* player_votee);
	void mafia_night_fun(Player* player_votee);
	void make_is_silenced_true() { player_role->make_is_silenced_true(); }
	void change_who_silenced(Player* player_votee) { player_role->change_who_silenced(player_votee); }
	bool get_is_healed() { return player_role->get_is_healed(); }
	bool change_and_get_second_life() { return player_role->change_and_get_second_life(); };
	void change_information_after_night();
	bool get_has_dead_in_day() { return player_role->get_has_dead_in_day(); }
	void make_has_dead_in_day_true() { player_role->make_has_dead_in_day_true(); }
	role* get_role() { return player_role; };
	void change_info_after_swap(role* new_role, bool curr_has_silenced);


private:
	std::string player_name;
	role* player_role;
	Player* votee_player;
};


#endif
