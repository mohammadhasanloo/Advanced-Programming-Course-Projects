#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <exception>
#include <sstream>
#include <algorithm>
#include "Player.hpp"
#include "Role.hpp"
#include "Const_Values.hpp"
#include "USER_NOT_JOINED.hpp"
#include "NO_GAME_CREATED.hpp"
#include "SOME_PLAYERS_DONT_HAVE_ROLE.hpp"
#include "GAME_HAS_ALREADY_STARTED.hpp"
#include "VOTER_IS_SILENCED.hpp"
#include "VOTEE_ALREADY_DEAD.hpp"
#include "USER_IS_DEAD.hpp"
#include "DETECTIVE_ALREADY_ASKED.hpp"
#include "DOCTOR_ALREADY_HEALED.hpp"
#include "SUSPECT_IS_DEAD.hpp"
#include "PATIENT_IS_DEAD.hpp"
#include "PERSON_IS_DEAD.hpp"
#include "CANT_WAKE_UP_DURING_NIGHT.hpp"
#include "CANT_SWAP_BEFORE_END_NIGHT.hpp"
#include "VOTING_IN_PROGRESS.hpp"
#include "CHAR_ALREADY_SWAPPED.hpp"


class Game
{
public:
	Game(bool _is_day, bool _finish_condition, int _mafias_num, int _villagers_num, int _day_num, int _night_num,bool _is_create_game,
		bool _is_game_stared, bool _is_every_one_voted, bool _day_processing, bool _after_night, bool _swap_twice);

	void run();
	std::vector <std::string> separate(std::string input, char character);
	void create_game(std::vector <std::string> names);
	void assign_role(std::vector <std::string> give_role_to_player);
	void search_player(std::string name);
	void start_game();
	void check_assign_role_to_all();
	void register_player_to_game(std::string new_name, std::string new_role);
	bool check_previous_names(std::string new_name, std::string new_role);
	void show_names_and_roles();
	std::string search_curr_player_name(std::string curr_player_name);
	void check_start_game_errors();
	void add_new_mafia_or_villager_number(std::string new_role);
	void change_mafia_and_villager_number(std::string new_role, std::string previous_role);
	void get_game_state();
	void process_game(std::vector <std::string> names);
	void check_process_day_error(std::string voter, std::string votee);
	void process_day(std::string voter, std::string votee);
	void end_vote_fun();
	void finish_condition_fun();
	bool has_joker_dead_in_day();
	void count_players_cast_votes(Player* player_votee);
	Player* find_killed_player(Player* previous_player, Player* curr_player);
	Player* take_smaller_alphabet_player(Player* previous_player, Player* curr_player);
	void rewrite_new_number_of_roles(std::string role);
	bool check_is_role_villager(std::string role);
	bool check_is_role_mafia(std::string role);
	void delete_killed_player();
	void end_night_fun();
	void swap_char_fun(std::vector <std::string> swap_players);
	void check_swap_char_errors(std::string player1, std::string player2);
	void check_process_night_error(std::string voter, std::string votee);
	void check_user_is_dead_fun(std::string player);
	void write_role_and_name_before_night();
	bool has_player_act(std::string role);
	void swap_players_fun(std::string player1, std::string player2);
	void check_mafia_errors(std::string votee);
	void check_dec_doc_error(std::string votee, bool is_voted, std::string role);
	void check_silencer_errors(std::string votee, Player* who_silenced);
	void start_night_errors(std::string voter, std::string votee);
	void check_roll_players_errors(std::string voter, std::string votee);
	void process_night(std::string voter, std::string votee);
	void write_silenced_players();
	void write_role_and_name_before_day(Player* killed_player);
	void function_after_day(Player* killed_player);
	void function_after_night(Player* killed_player);
	void show_names_and_roles_before_night(std::string curr_player);////


private:
	bool is_day;
	bool finish_condition;
	std::vector <Player*> players;
	std::vector <std::string> player_names;
	int mafias_num;
	int villagers_num;
	int day_num;
	int night_num;
	bool is_game_created;
	bool is_game_started;
	bool is_every_one_voted;
	bool day_processing;
	bool after_night;
	bool swap_twice;
};



#endif
