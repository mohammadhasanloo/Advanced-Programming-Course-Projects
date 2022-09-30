#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include "rsdl.hpp"
#include "Player.hpp"
#include "Ball.hpp"
#include "Bead.hpp"
#include "Const_Values.hpp"


class Game
{
public:
	Game(bool _ball_bead_moving, bool _goal_scored, int _turn, bool _mouse_down);
	void start_game();
	void start_round();
	int take_bead_position();
	bool show_game_finished();
	void initialize_objects();
	void change_turn();
	void show_text_turn();
	void change_bead_location_function();
	void type_finishing_text(std::string input, RGB colour);
	void check_ball_bead_moving();
	void check_collision();
	void L_release_function(Event curr_event);
	void L_click_function(Event curr_event);
	void make_bead_ready_to_move(Event curr_event);
	void draw_both_team_breads();
	void initialize_objects_after_scored();
	void process_game_while_goal_scored();
	bool check_and_change_info_after_goal();
	void check_collision_bead2_to_ball();
	void check_collision_bead1_to_ball();
	void check_collision_bead1_to_bead2();
	void check_collision_bead2_to_bead2();
	void check_collision_bead1_to_bead1();
	void change_info_after_goal(int player_goal_scored);
	void update_point_position(int chosen_bead, Event curr_event);
	bool check_point_position();
	void change_beads_location_to_first_state();
	void draw();
	void update_window();
	void update();
private:
	int turn;
	int goal;
	int round;
	bool mouse_down;
	bool goal_scored;
	bool ball_bead_moving;
	Point mouse_position;
	Window* window;
	Ball* ball;
	Player* player1;
	Player* player2;
	std::vector <Bead*> beads_1;
	std::vector <Bead*> beads_2;
};

#endif
