#include "Game.hpp"



using namespace std;








Game::Game(bool _is_day,bool _finish_condition,int _mafias_num, int _villagers_num,int _day_num,int _night_num,
	bool _is_create_game, bool _is_game_started, bool _is_every_one_voted,bool _day_processing, bool _after_night, bool _swap_twice)
{
	is_day = _is_day;
	finish_condition = _finish_condition;
	mafias_num = _mafias_num;
	villagers_num = _villagers_num;
	day_num = _day_num;
	night_num = _night_num;
	is_game_created = _is_create_game;
	is_game_started = _is_game_started;
	is_every_one_voted = _is_every_one_voted;
	day_processing = _day_processing;
	after_night = _after_night;
	swap_twice = _swap_twice;
}

vector<string> Game::separate(string input, char character)
{
	stringstream current(input);
	vector<string> result;

	while (current.good())
	{
		string substr;
		getline(current, substr, character);
		result.push_back(substr);
	}
	return result;
}

void Game::create_game(vector <string> names)
{
	for (int i = 1; i < names.size(); i++)
		player_names.push_back(names[i]);
	is_game_created = true;
}

void Game::search_player(string name)
{
	for (int i = 0; i < player_names.size(); i++)
	{
		if (name == player_names[i])
			return;
	}
	throw user_not_joined();
}

bool Game::check_is_role_villager(string role)
{
	if (role == VILLAGER || role == BULLETPROOF || role == DOCTOR || role == DETECTIVE)
		return true;
	return false;
}

bool Game::check_is_role_mafia(string role)
{
	if (role == MAFIA || role == GODFATHER || role == SILENCER)
		return true;
	return false;
}

void Game::change_mafia_and_villager_number(string new_role,string previous_role)
{
	if (check_is_role_mafia(previous_role))
		mafias_num--;
	else if (check_is_role_villager(previous_role))
		villagers_num--;

	if (check_is_role_mafia(new_role))
		mafias_num++;
	else if (check_is_role_villager(new_role))
		villagers_num++;
}

bool Game::check_previous_names(string new_name, string new_role)
{
	for (int i = 0; i < players.size(); i++)
	{
		if (players[i]->check_to_find_name(new_name))
		{
			change_mafia_and_villager_number(new_role,players[i]->get_player_role());
			players[i] = new Player(new_role, new_name, nullptr);
			return true;
		}
	}
	return false;
}

void Game::add_new_mafia_or_villager_number(string new_role)
{
	if (new_role == VILLAGER || new_role == BULLETPROOF || new_role == DOCTOR || new_role == DETECTIVE)
		villagers_num++;
	else if (new_role == MAFIA || new_role == GODFATHER || new_role == SILENCER)
		mafias_num++;
}

void Game::register_player_to_game(string new_name,string new_role)
{
	if ((!check_is_role_mafia(new_role)) && (!check_is_role_villager(new_role)) && (new_role!=JOKER))
		throw;

	bool have_same_name=check_previous_names(new_name, new_role);
	if (!have_same_name)
	{
		add_new_mafia_or_villager_number(new_role);
		players.push_back(new Player(new_role, new_name, nullptr));
	}
}

void Game::assign_role(vector <string> give_role_to_player)
{
	if (is_game_created)
	{
		search_player(give_role_to_player[NAME_LOCATION]);
		register_player_to_game(give_role_to_player[NAME_LOCATION],give_role_to_player[ROLE_LOCATION]);
	}
	else
		throw no_game_created();
}

void Game::check_assign_role_to_all()
{
	if (players.size() != player_names.size())
		throw some_players_dont_have_role();
}

string Game::search_curr_player_name(string curr_player_name)
{
	for (int i = 0; i < players.size(); i++)
	{
		if (curr_player_name == players[i]->get_player_name())
			return players[i]->get_player_name() + ": " + players[i]->get_player_role();
	}
}

void Game::show_names_and_roles()
{
	for (int i = 0; i < player_names.size(); i++)
		cout << search_curr_player_name(player_names[i]) << endl;
}

void Game::check_start_game_errors()
{
	if (!is_game_created)
		throw no_game_created();
	check_assign_role_to_all();
	if (is_game_started)
		throw game_has_already_started();
}

void Game::start_game()
{
	check_start_game_errors();

	is_game_started = true;

	show_names_and_roles();
	day_num++;
	cout << START_GAME_MESSAGE << endl << DAY << " " << day_num << endl;
}

void Game::get_game_state()
{
	cout << "Mafia = " << mafias_num << endl;
	cout << "Villager = " << villagers_num << endl;
}

void Game::check_process_day_error(string voter,string votee)
{
	search_player(voter);
	search_player(votee);
	for (int i = 0; i < players.size(); i++)
	{
		if ((voter == players[i]->get_player_name()) && (players[i]->get_is_silenced()))
			throw voter_is_silenced();
		if ((votee == players[i]->get_player_name()) && (players[i]->get_is_dead()))
			throw votee_already_dead();
	}
}

void Game::process_day(string voter, string votee)
{
	Player* votee_player = nullptr;
	for (int i = 0; i < players.size(); i++)
	{
		if (players[i]->check_to_find_name(votee))
			votee_player = players[i];
	}

	for (int i = 0; i < players.size(); i++)
	{
		if (players[i]->check_to_find_name(voter))
			players[i]->set_new_votee(votee_player);
	}
}

void Game::check_user_is_dead_fun(string player)
{
	for (int i = 0; i < players.size(); i++)
	{
		if ((players[i]->get_player_name() == player) && (players[i]->get_is_dead()))
			throw user_is_dead();
	}
}

bool Game::has_player_act(string role)
{
	if (role == DOCTOR || role == MAFIA || role == SILENCER || role == GODFATHER || role == DETECTIVE)
		return true;
	return false;
}

void Game::check_mafia_errors(string votee)
{
	for (int i = 0; i < players.size(); i++)
	{
		if ((players[i]->get_player_name() == votee) && (players[i]->get_is_dead()))
			throw votee_already_dead();
	}
}

void Game::check_dec_doc_error(string votee,bool is_voted, string role)
{
	if ((is_voted) && (role==DETECTIVE))
		throw detective_already_asked();
	else if ((is_voted) && (role == DOCTOR))
		throw doctor_already_healed();

	for (int i = 0; i < players.size(); i++)
	{
		if ((players[i]->get_player_name() == votee) && (players[i]->get_is_dead()) && (role == DETECTIVE))
			throw suspect_is_dead();
		else if ((players[i]->get_player_name() == votee) && (players[i]->get_is_dead()) && (role == DOCTOR))
			throw patient_is_dead();
	}
}

void Game::check_silencer_errors(string votee, Player* who_silenced)
{
	if (who_silenced != nullptr)
		return;
	for (int i = 0; i < players.size(); i++)
	{
		if ((players[i]->get_player_name() == votee) && (players[i]->get_is_dead()))
			throw person_is_dead();
	}

}

void Game::start_night_errors(string voter, string votee)
{
	check_user_is_dead_fun(voter);

	for (int i = 0; i < players.size(); i++)
	{
		if ((players[i]->get_player_name() == voter) && (!has_player_act(players[i]->get_player_role())))
			throw cant_wake_up_during_night();
	}
	search_player(voter);
	search_player(votee);
}

void Game::check_roll_players_errors(string voter, string votee)
{
	for (int i = 0; i < players.size(); i++)
	{
		if (players[i]->check_to_find_name(voter))
		{
			if ((players[i]->get_player_role() == DETECTIVE) || (players[i]->get_player_role() == DOCTOR))
				check_dec_doc_error(votee, players[i]->get_is_voted(), players[i]->get_player_role());

			else if (players[i]->get_player_role() == SILENCER)
				check_silencer_errors(votee, players[i]->get_who_silenced());

			if (check_is_role_mafia(players[i]->get_player_role()))
				check_mafia_errors(votee);
		}
	}

}

void Game::check_process_night_error(string voter, string votee)
{
	start_night_errors(voter, votee);
	check_roll_players_errors(voter, votee);
}

void Game::process_night(string voter, string votee)
{
	Player* votee_player = nullptr;
	for (int i = 0; i < players.size(); i++)
	{
		if (players[i]->check_to_find_name(votee))
			votee_player = players[i];
	}

	for (int i = 0; i < players.size(); i++)
	{
		if (players[i]->check_to_find_name(voter) && (players[i]->get_player_role() == DOCTOR))
			players[i]->doctor_night_fun(votee_player);

		else if (players[i]->check_to_find_name(voter) && (players[i]->get_player_role() == DETECTIVE))
			players[i]->detective_night_fun(votee_player);

		else if (players[i]->check_to_find_name(voter) && check_is_role_mafia(players[i]->get_player_role()))
			players[i]->mafia_night_fun(votee_player);
	}
}

void Game::process_game(vector <string> names)
{
	if (is_day)
	{
		check_process_day_error(names[VOTER_LOCATION], names[VOTEE_LOCATION]);
		day_processing = true;
		swap_twice = false;
		after_night = false;
		process_day(names[VOTER_LOCATION], names[VOTEE_LOCATION]);
	}
	else
	{
		check_process_night_error(names[VOTER_LOCATION], names[VOTEE_LOCATION]);
		process_night(names[VOTER_LOCATION], names[VOTEE_LOCATION]);
	}
}

bool Game::has_joker_dead_in_day()
{
	for (int i = 0; i < players.size(); i++)
	{
		if ((players[i]->get_player_role() == JOKER) && (players[i]->get_has_dead_in_day()))
			return true;
	}
	return false;
}

void Game::finish_condition_fun()
{
	if (mafias_num == 0)
	{
		cout << VILLAGERS_WON << endl;
		finish_condition = true;
	}
	else if (villagers_num <= mafias_num)
	{
		cout << MAFIA_WON << endl;
		finish_condition = true;
	}
	else if (has_joker_dead_in_day())
	{
		cout << JOKER_WON << endl;
		finish_condition = true;
	}
}

void Game::count_players_cast_votes(Player* player_votee)
{
	for (int i = 0; i < players.size(); i++)
	{
		if (players[i]->get_player_name() == player_votee->get_player_name())
			players[i]->add_votes_cast_num();
	}
}

Player* Game::take_smaller_alphabet_player(Player* previous_player, Player* curr_player)
{
	if (previous_player->get_player_name() <= curr_player->get_player_name())
		return previous_player;
	if (previous_player->get_player_name() > curr_player->get_player_name())
		return curr_player;
}

Player* Game::find_killed_player(Player* previous_player, Player* curr_player)
{
	if (previous_player->get_votes_cast_num() < curr_player->get_votes_cast_num())
		return curr_player;
	else if (previous_player->get_votes_cast_num() == curr_player->get_votes_cast_num())
		return take_smaller_alphabet_player(previous_player, curr_player);
	else
		return previous_player;
}

void Game::rewrite_new_number_of_roles(string role)
{
	if (check_is_role_mafia(role))
		mafias_num--;
	else if (check_is_role_villager(role))
		villagers_num--;
}

void Game::write_silenced_players()
{
	vector <string> silenced_players;
	for (int i = 0; i < players.size(); i++)
	{
		if (players[i]->get_is_silenced())
			silenced_players.push_back(players[i]->get_player_name());
	}
	if (silenced_players.size() != 0)
	{
		cout << "Silenced ";
		sort(silenced_players.begin(), silenced_players.end());
		for (int i = 0; i < silenced_players.size(); i++)
		{
			cout << silenced_players[i];
			if (i != (silenced_players.size() - 1))
				cout << " ";
		}
		cout << endl;
	}
}

void Game::write_role_and_name_before_day(Player* killed_player)
{
	cout << DAY << " " << day_num << endl;

	if (killed_player->get_is_dead())
		cout << killed_player->get_player_name() << " " << WAS_KILLED << endl;

	write_silenced_players();
}

void Game::function_after_day(Player* killed_player)
{
	if (killed_player->get_player_role() == JOKER)
		killed_player->make_has_dead_in_day_true();

	killed_player->make_is_dead_true();
	cout << killed_player->get_player_name() << " " << DEAD << endl;

	rewrite_new_number_of_roles(killed_player->get_player_role());
}

void Game::function_after_night(Player* killed_player)
{
	cout << MAFIA_TRIED_TO_KILL << " " << killed_player->get_player_name() << endl;
	if (!killed_player->get_is_healed())
	{
		if (!killed_player->change_and_get_second_life())
		{
			killed_player->make_is_dead_true();
			rewrite_new_number_of_roles(killed_player->get_player_role());
		}
	}
}

void Game::delete_killed_player()
{
	Player* killed_player = players[0];
	for (int i = 1; i < players.size(); i++)
		killed_player = find_killed_player(killed_player, players[i]);

	if (is_day)
		function_after_day(killed_player);

	else
	{
		function_after_night(killed_player);

		finish_condition_fun();
		if (!finish_condition)
			write_role_and_name_before_day(killed_player);
	}
}

void Game::show_names_and_roles_before_night(string curr_player)/////
{
	for (int i = 0; i < players.size(); i++)
	{
		if(curr_player==players[i]->get_player_name())
			if (!players[i]->get_is_dead() && has_player_act(players[i]->get_player_role()))
				cout << players[i]->get_player_name() << ": " << players[i]->get_player_role() << endl;
	}
}

void Game::write_role_and_name_before_night()
{
	for(int i=0;i<player_names.size();i++)
		show_names_and_roles_before_night(player_names[i]);////
}

void Game::end_vote_fun()
{
	day_processing = false;
	night_num++;

	for (int i = 0; i < players.size(); i++)
	{
		if (players[i]->get_is_voted())
			count_players_cast_votes(players[i]->get_votee_player());
	}
	delete_killed_player();

	for (int i = 0; i < players.size(); i++)
		players[i]->change_information_after_day();

	finish_condition_fun();
	if (!finish_condition)
	{
		cout << NIGHT << " " << night_num << endl;
		write_role_and_name_before_night();
	}

	is_day = false;
}

void Game::end_night_fun()
{
	after_night = true;
	day_num++;

	for (int i = 0; i < players.size(); i++)
	{
		if ((check_is_role_mafia(players[i]->get_player_role())) && (!players[i]->get_is_dead()))
			count_players_cast_votes(players[i]->get_votee_player());
	}
	delete_killed_player();

	for (int i = 0; i < players.size(); i++)
		players[i]->change_information_after_night();

	is_day = true;
}

void Game::check_swap_char_errors(string player1, string player2)
{
	search_player(player1);
	search_player(player2);
	check_user_is_dead_fun(player1);
	check_user_is_dead_fun(player2);
	if (swap_twice)
		throw char_already_swapped();
		else if (day_processing)
			throw voting_in_progress();
	else if (!after_night)
		throw cant_swap_before_end_night();
}

void Game::swap_players_fun(string player1, string player2)
{
	role* role_1=nullptr;
	role* role_2=nullptr;
	bool has_silenced_1=false;
	bool has_silenced_2=false;

	for (int i = 0; i < players.size(); i++)
	{
		if (players[i]->get_player_name() == player1)
		{
			role_1 = players[i]->get_role();
			has_silenced_1 = players[i]->get_is_silenced();
		}
		else if (players[i]->get_player_name() == player2)
		{
			role_2 = players[i]->get_role();
			has_silenced_2 = players[i]->get_is_silenced();
		}
	}

	for (int i = 0; i < players.size(); i++)
	{
		if (players[i]->get_player_name() == player1)
			players[i]->change_info_after_swap(role_2, has_silenced_1);
		else if (players[i]->get_player_name() == player2)
			players[i]->change_info_after_swap(role_1, has_silenced_2);
	}

}

void Game::swap_char_fun(vector <string> swap_players)
{
	check_swap_char_errors(swap_players[SWAPPING_PLAYER_1],swap_players[SWAPPING_PLAYER_2]);

	swap_players_fun(swap_players[SWAPPING_PLAYER_1], swap_players[SWAPPING_PLAYER_2]);

	swap_twice = true;
}

void Game::run()
{
	string input;
	while (getline(cin, input))
	{
		vector <string> separated_input = separate(input, SEPARATOR_CHAR);
		try
		{
			if (separated_input[FUNCTION] == CREATE_GAME)
				create_game(separated_input);

			else if (separated_input[FUNCTION] == ASSIGN_ROLE)
				assign_role(separated_input);

			else if (separated_input[FUNCTION] == START_GAME)
				start_game();

			else if (separated_input[FUNCTION] == GET_GAME_STATE)
				get_game_state();

			else if (separated_input[FUNCTION] == END_VOTE)
				end_vote_fun();

			else if (separated_input[FUNCTION] == END_NIGHT)
				end_night_fun();

			else if (separated_input[FUNCTION] == SWAP_CHARACTER)
				swap_char_fun(separated_input);

			else if (is_game_started)
				process_game(separated_input);

			if (finish_condition)
				break;
		}
		catch(exception& error)
		{
			cout << error.what() << "\n";
		}
	}
}
