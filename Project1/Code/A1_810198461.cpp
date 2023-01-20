#include <iostream>
#include <vector>
#include <utility>
#include <math.h>
#include <cstdlib>


using namespace std;

const char PLAYER_MARK = '@';
const char ROBOT_MARK = '+';
const char TRAP_MARK = '*';
const char DOT_MARK = '.';
const char LEFT = 'h';
const char UP_LEFT = 'y';
const char UP = 'k';
const char UP_RIGHT = 'u';
const char RIGHT = 'l';
const char DOWN_RIGHT = 'n';
const char DOWN = 'j';
const char DOWN_LEFT = 'b';
const char PORT = 't';
const string PLAYER_WINS = "Player Wins!";
const string ROBOTS_WINS = "Robots Win!";
const pair<int, int> LEFT_LOC(0, -1);
const pair<int, int> UP_LOC(-1, 0);
const pair<int, int> DOWN_LOC(1, 0);
const pair<int, int> RIGHT_LOC(0, 1);
const pair<int, int> UP_LEFT_LOC(-1, -1);
const pair<int, int> UP_RIGHT_LOC(-1, 1);
const pair<int, int> DOWN_LEFT_LOC(1, -1);
const pair<int, int> DOWN_RIGHT_LOC(1, 1);
const vector < pair<int, int >> LOCATIONS = { {0,-1}, {-1, 0}, {1, 0}, {0, 1}, {-1, -1}, {1, -1}, {-1, 1}, {1, 1} };






class Player
{
public:
	Player() {};
	Player(pair <int, int> _location) { location = _location; };
	void change_location(int dx, int dy, int side_number);
	void make_random_location(int new_row, int new_column);
	pair <int, int> get_location() { return location; }

private:
	bool check_correct_numbers(pair <int, int> curr_location, int side_number);
	pair <int, int> location;
};

void Player::change_location(int dx, int dy, int side_number)
{
	pair<int, int> new_location;
	new_location.first = location.first + dx;
	new_location.second = location.second + dy;
	if (check_correct_numbers(new_location, side_number))
	{
		location.first += dx;
		location.second += dy;
	}
}

void Player::make_random_location(int new_row, int new_column)
{
	location.first = new_row;
	location.second = new_column;
}

bool Player::check_correct_numbers(pair <int, int> curr_location, int side_number)
{
	if (curr_location.first < 0 || curr_location.first >= side_number || curr_location.second < 0 || curr_location.second >= side_number)
		return false;
	return true;
}



class Robot
{
public:
	Robot(pair <int, int> _location) { location = _location; };
	void change_location(pair <int, int> player_location, int side_number);
	bool check_destroy_robot_condtion(const vector <vector < char >>& table);
	pair<int, int> get_location() { return location; }

private:
	double player_and_robot_distance(pair <int, int> robot_location, pair <int, int> player_location);
	bool check_correct_numbers(pair <int, int> curr_location, int side_number);
	pair <int, int> location;
};

double Robot::player_and_robot_distance(pair <int, int> robot_location, pair <int, int> player_location)
{
	return sqrt(pow(robot_location.first-player_location.first,2) +pow(robot_location.second-player_location.second,2));
}

bool Robot::check_correct_numbers(pair <int, int> curr_location, int side_number)
{
	if (curr_location.first < 0 || curr_location.first >= side_number || curr_location.second < 0 || curr_location.second >= side_number)
		return false;
	return true;
}

void Robot::change_location(pair <int, int> player_location, int side_number)
{
	pair <int, int> pre_location = location;
	pair <int, int> new_location = location;
	double pre_distance = player_and_robot_distance(pre_location, player_location);
	pair <int, int> curr_location;

	for (int i = 0; i < LOCATIONS.size(); i++)
	{
		curr_location.first = location.first + LOCATIONS[i].first;
		curr_location.second = location.second + LOCATIONS[i].second;
		double curr_distance = player_and_robot_distance(curr_location, player_location);

		if (curr_distance < pre_distance && check_correct_numbers(curr_location,side_number))
		{
			new_location = curr_location;
			pre_distance = curr_distance;
			pre_location = curr_location;
		}
	}
	location = new_location;
}

bool Robot::check_destroy_robot_condtion(const vector <vector < char >>& table)
{
	if (table[location.first][location.second] == TRAP_MARK)
		return true;
	return false;
}





class Game_Handler
{
public:
	Game_Handler(int _side_number, const vector <vector < char >>& _table, const vector <char>& _move_form,
		const vector <Robot*>& _robots, Player* _player);
	void run();


private:
	void print_row_of_table(const vector <char>& table_row);
	void print_table();
	void change_robots_location();
	void check_collision_between_robots();
	bool check_collision(Robot* robot1, Robot* robot2);
	void check_robots_dead();
	void check_player_dead();
	void check_robots_number();
	void initialize_new_table();
	void put_player_in_table();
	void put_robots_in_table();
	void teleport_function();
	void check_collision_with_traps();
	void find_type_of_moving(int move_number);

	bool finish_condition;
	int side_number;
	vector <vector < char >> table;
	vector <char> move_form;
	Player* player;
	vector <Robot*> robots;
};

void Game_Handler::initialize_new_table()
{
	for (int i = 0; i < table.size(); i++)
	{
		for (int j = 0; j < table[i].size(); j++)
		{
			if (table[i][j] != TRAP_MARK)
				table[i][j] = DOT_MARK;
		}
	}
}

void Game_Handler::put_player_in_table()
{
	pair <int, int> player_location = player->get_location();
	table[player_location.first][player_location.second] = PLAYER_MARK;
}

void Game_Handler::put_robots_in_table()
{
	for (int i = 0; i < robots.size(); i++)
	{
		pair <int, int> robot_location = robots[i]->get_location();
		table[robot_location.first][robot_location.second] = ROBOT_MARK;
	}
}

void Game_Handler::print_row_of_table(const vector <char>& table_row)
{
	for (int i = 0; i < table_row.size(); i++)
		cout << table_row[i];

	cout << endl;
}

void Game_Handler::print_table()
{
	initialize_new_table();
	put_player_in_table();
	put_robots_in_table();

	for (int i = 0; i < table.size(); i++)
		print_row_of_table(table[i]);

	cout << endl;
}

bool Game_Handler::check_collision(Robot* robot1, Robot* robot2)
{
	if (robot1->get_location() == robot2->get_location())
		return true;
	return false;
}

void Game_Handler::check_collision_between_robots()
{
	for (int i = 0; i < robots.size(); i++)
	{
		for (int j = i + 1; j < robots.size(); j++)
		{
			if (check_collision(robots[i], robots[j]))
			{
				pair<int, int> robots_location = robots[i]->get_location();
				robots.erase(robots.begin() + i);
				robots.erase(robots.begin() + j - 1);
				table[robots_location.first][robots_location.second] = TRAP_MARK;
			}
		}
	}
}

void Game_Handler::check_robots_number()
{
	if (robots.size() <= 0)
	{
		finish_condition = true;
		cout << PLAYER_WINS;
		return;
	}
}

void Game_Handler::change_robots_location()
{
	for (int i = 0; i < robots.size(); i++)
		robots[i]->change_location(player->get_location(), side_number);
}

void Game_Handler::check_collision_with_traps()
{
	for (int i = 0; i < robots.size(); i++)
	{
		bool dead_condition = robots[i]->check_destroy_robot_condtion(table);

		if (dead_condition)
			robots.erase(robots.begin() + i);
	}
}

void Game_Handler::check_robots_dead()
{
	check_collision_between_robots();

	check_collision_with_traps();

	check_robots_number();
}

void Game_Handler::check_player_dead()
{
	pair<int, int> player_location = player->get_location();
	if (table[player_location.first][player_location.second] == TRAP_MARK)
	{
		finish_condition = true;
		cout << ROBOTS_WINS;
		return;
	}

	for (int i = 0; i < robots.size(); i++)
	{
		pair<int, int> robot_location = robots[i]->get_location();

		if (player_location == robot_location)
		{
			finish_condition = true;
			cout << ROBOTS_WINS;
			return;
		}
	}
}

void Game_Handler::teleport_function()
{
	int x = rand() % side_number;
	int y = rand() % side_number;
	player->make_random_location(x, y);
}

void Game_Handler::find_type_of_moving(int move_number)
{
	if (move_form[move_number] == LEFT)
	{
		player->change_location(LEFT_LOC.first, LEFT_LOC.second,side_number);
	}
	else if (move_form[move_number] == RIGHT)
	{
		player->change_location(RIGHT_LOC.first, RIGHT_LOC.second, side_number);
	}
	else if (move_form[move_number] == UP)
	{
		player->change_location(UP_LOC.first, UP_LOC.second, side_number);
	}
	else if (move_form[move_number] == DOWN)
	{
		player->change_location(DOWN_LOC.first, DOWN_LOC.second, side_number);
	}
	else if (move_form[move_number] == UP_LEFT)
	{
		player->change_location(UP_LEFT_LOC.first, UP_LEFT_LOC.second, side_number);
	}
	else if (move_form[move_number] == UP_RIGHT)
	{
		player->change_location(UP_RIGHT_LOC.first, UP_RIGHT_LOC.second, side_number);
	}
	else if (move_form[move_number] == DOWN_LEFT)
	{
		player->change_location(DOWN_LEFT_LOC.first, DOWN_LEFT_LOC.second, side_number);
	}
	else if (move_form[move_number] == DOWN_RIGHT)
	{
	player->change_location(DOWN_RIGHT_LOC.first, DOWN_RIGHT_LOC.second, side_number);
	}
	else if (move_form[move_number] == PORT)
	{
		teleport_function();
	}
}

void Game_Handler::run()
{
	for (int i = 0; i < move_form.size(); i++)
	{
		find_type_of_moving(i);
		
		change_robots_location();
		check_robots_dead();

		check_player_dead();

		if (finish_condition)
		{
			cout << endl;
			break;
		}

		print_table();
	}
}

Game_Handler::Game_Handler(int _side_number, const vector <vector < char >>& _table, const vector <char>& _move_form,
	const vector <Robot*>& _robots, Player* _player)
{
	side_number = _side_number;
	table = _table;
	move_form = _move_form;
	robots = _robots;
	player = _player;
	finish_condition = false;
}







class Command_Handler
{
public:
	Command_Handler() {};
	void get_inputs();

private:
	vector <Robot*> find_robots_location(const vector <vector <char>>& table);
	Player* find_player_location(const vector <vector <char>>& table);
	vector <char> get_input_char_by_char(string input, int side_number);

	Game_Handler* new_game;
};

vector <char> Command_Handler::get_input_char_by_char(string input, int side_number)
{
	vector <char> output;
	for (int i = 0; i < side_number; i++)
		output.push_back(input[i]);

	return output;
}

Player* Command_Handler::find_player_location(const vector <vector <char>>& table)
{
	Player* curr_player=new Player();
	pair <int, int> location;

	for (int i = 0; i < table.size(); i++)
	{
		for (int j = 0; j < table[i].size(); j++)
		{
			if (table[i][j] == PLAYER_MARK)
			{
				location.first = i;
				location.second = j;
				curr_player = new Player(location);
			}
		}
	}
	return curr_player;
}

vector <Robot*> Command_Handler::find_robots_location(const vector <vector <char>>& table)
{
	vector <Robot*> robots;
	pair <int, int> location;
	for (int i = 0; i < table.size(); i++)
	{
		for (int j = 0; j < table[i].size(); j++)
		{
			if (table[i][j] == ROBOT_MARK)
			{
				location.first = i;
				location.second = j;
				robots.push_back(new Robot(location));
			}
		}
	}
	return robots;
}

void Command_Handler::get_inputs()
{
	int side_number;
	cin >> side_number;

	vector <vector <char>> table(side_number);
	for (int i = 0; i < side_number; i++)
	{
		string one_line;
		cin >> one_line;
		table[i] = (get_input_char_by_char(one_line, side_number));
	}

	string move_shape;
	cin >> move_shape;
	vector <char> move_form = (get_input_char_by_char(move_shape, move_shape.size()));

	Player* player = find_player_location(table);
	vector <Robot*> robots = find_robots_location(table);

	new_game = new Game_Handler(side_number, table, move_form, robots, player);
	new_game->run();
}







int main(int argc, char const* argv[])
{
	int seed = atoi(argv[1]);
	srand(seed);

	Command_Handler* new_program= new Command_Handler();
	new_program->get_inputs();

	return 0;
}