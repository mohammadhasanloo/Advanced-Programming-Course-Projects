#include "Game.hpp"
#include <cmath>
#include <vector>

using namespace std;



Game::Game(bool _ball_bead_moving, bool _goal_scored, int _turn, bool _mouse_down)
{
	turn = _turn;
	mouse_down = _mouse_down;
	goal_scored = _goal_scored;
	ball_bead_moving = _ball_bead_moving;
}

void Game::show_text_turn()
{
	if(turn==1)
		window->show_text("Turn= " + to_string(turn),SHOW_TURN_PLAYER_1,PLAYER_1_COLOUR,FONT_NAME, SCREEN_FONT_SIZE);
	else if(turn==2)
		window->show_text("Turn= " + to_string(turn),SHOW_TURN_PLAYER_2,PLAYER_2_COLOUR,FONT_NAME, SCREEN_FONT_SIZE);
}

bool Game::check_point_position()
{
	if (turn == 1)
	{
		for (int i = 0; i < beads_1.size(); i++)
		{
			if (beads_1[i]->check_bead_position(mouse_position))
				return true;
		}
	}
	else if (turn == 2)
	{
		for (int i = 0; i < beads_2.size(); i++)
		{
			if (beads_2[i]->check_bead_position(mouse_position))
				return true;
		}
	}
	return false;
}

void Game::update_point_position(int chosen_bead, Event curr_event)
{
	Point pawn_position = curr_event.get_mouse_position();
	if (turn == 1)
		beads_1[chosen_bead]->write_v_0_bead(pawn_position, mouse_position);
	else if (turn == 2)
		beads_2[chosen_bead]->write_v_0_bead(pawn_position, mouse_position);
}

int Game::take_bead_position()
{
	if (turn == 1)
	{
		for (int i = 0; i < beads_1.size(); i++)
		{
			if (beads_1[i]->check_bead_position(mouse_position))
				return i;
		}
	}
	else if (turn == 2)
	{
		for (int i = 0; i < beads_2.size(); i++)
		{
			if (beads_2[i]->check_bead_position(mouse_position))
				return i;
		}
	}
	return 0;
}

void Game::change_turn()
{
	if (turn == 1)
		turn = 2;
	else if (turn == 2)
		turn = 1;
}

void Game::make_bead_ready_to_move(Event curr_event)
{
	int chosen_bead = take_bead_position();
	update_point_position(chosen_bead, curr_event);
	change_turn();
	ball_bead_moving = true;
}

void Game::L_release_function(Event curr_event)
{
	if (check_point_position() && !ball_bead_moving)
		make_bead_ready_to_move(curr_event);
	mouse_down = false;
}

void Game::L_click_function(Event curr_event)
{
	if (!mouse_down && !ball_bead_moving)
	{
		mouse_down = true;
		mouse_position = curr_event.get_mouse_position();
	}
}

void Game::update_window()
{
	while (window->has_pending_event())
	{
		Event curr_event = window->poll_for_event();
		switch (curr_event.get_type())
		{
		case Event::EventType::QUIT:
		{
			exit(0);
			break;
		}
		case Event::EventType::LCLICK:
		{
			L_click_function(curr_event);
			break;
		}
		case Event::EventType::LRELEASE:
		{
			L_release_function(curr_event);
			break;
		}
		}
	}
}

void Game::check_collision_bead1_to_bead1()
{
	for (int i = 0; i < beads_1.size(); i++)
	{
		for (int j = (i + 1); j < beads_1.size(); j++)
			beads_1[i]->beads_collision(beads_1[j]);
	}
}

void Game::check_collision_bead2_to_bead2()
{
	for (int i = 0; i < beads_2.size(); i++)
	{
		for (int j = (i + 1); j < beads_2.size(); j++)
				beads_2[i]->beads_collision(beads_2[j]);
	}
}

void Game::check_collision_bead1_to_bead2()
{
	for (int i = 0; i < beads_1.size(); i++)
		for (int j = 0; j < beads_2.size(); j++)
				beads_1[i]->beads_collision(beads_2[j]);
}

void Game::check_collision_bead1_to_ball()
{
	for (int i = 0; i < beads_1.size(); i++)
		beads_1[i]->bead_ball_collision(ball);
}

void Game::check_collision_bead2_to_ball()
{
	for (int i = 0; i < beads_2.size(); i++)
		beads_2[i]->bead_ball_collision(ball);

}

void Game::check_collision()
{
	check_collision_bead1_to_bead1();

	check_collision_bead1_to_ball();

	check_collision_bead2_to_bead2();

	check_collision_bead2_to_ball();

	check_collision_bead1_to_bead2();
}

void Game::check_ball_bead_moving()
{
	if (ball->get_ball_touch())
		return;

	for (int i = 0; i < beads_1.size(); i++)
	{
		if (beads_1[i]->get_bead_touch())
			return;
	}

	for (int i = 0; i < beads_2.size(); i++)
	{
		if (beads_2[i]->get_bead_touch())
			return;
	}
	ball_bead_moving = false;
}

void Game::change_info_after_goal(int player_goal_scored)
{
	ball_bead_moving = false;
	if (player_goal_scored == 1)
	{
		player1->change_player_info_after_goal();
		turn = 2;
	}

	else if (player_goal_scored == 2)
	{
		player2->change_player_info_after_goal();
		turn = 1;
	}
	goal_scored = true;
}

void Game::change_bead_location_function()
{
	for (int i = 0; i < beads_1.size(); i++)
	{
		beads_1[i]->change_bead_location();
		beads_1[i]->hit_bead_to_the_table();
	}

	for (int i = 0; i < beads_2.size(); i++)
	{
		beads_2[i]->change_bead_location();
		beads_2[i]->hit_bead_to_the_table();
	}
}

bool Game::check_and_change_info_after_goal()
{
	int player_goal_scored = ball->hit_ball_to_the_table();
	if ((player_goal_scored == 1) || (player_goal_scored == 2))
	{
		change_info_after_goal(player_goal_scored);
		return true;
	}
	return false;
}

void Game::update()
{
		update_window();

	change_bead_location_function();

	ball->change_ball_location();

	if (check_and_change_info_after_goal())
		return;

	check_collision();

	if (ball_bead_moving)
		check_ball_bead_moving();
}

void Game::draw_both_team_breads()
{
	for (int i = 0; i < beads_1.size(); i++)
		beads_1[i]->draw_beads(window, BEAD_1_PHOTO);
	for (int i = 0; i < beads_2.size(); i++)
		beads_2[i]->draw_beads(window, BEAD_2_PHOTO);
}

void Game::draw()
{
	window->clear();

	window->draw_img(FIELD_PHOTO, NULL_RECT, NULL_RECT, 0, false, false);

	ball->draw_ball(window);

	draw_both_team_breads();

	player1->show_text_player(window, START_TEXT_PLAYER_1.x, START_TEXT_PLAYER_1.y, PLAYER_1_COLOUR);
	player2->show_text_player(window, START_TEXT_PLAYER_2.x, START_TEXT_PLAYER_2.y, PLAYER_2_COLOUR);

	show_text_turn();

	window->update_screen();
}

void Game::type_finishing_text(string input, RGB colour)
{
	window->clear();
	window->draw_img(FIELD_PHOTO, NULL_RECT, NULL_RECT, 0, false, false);
	window->show_text(input, SRC_FINISH_TEXT, colour, FONT_NAME, FINISH_TEXT_FONT_SIZE);
	window->update_screen();
	delay(TIME_SHOW_WINNER * DELAY_TIME);
}

bool Game::show_game_finished()
{
	if (((round % 2 == 0) && player1->finish_game(true, round)) || ((round % 2 == 1) && player1->finish_game(false, round)))
	{
		string input1 = "Player NO.1 has won with " + to_string(player1->get_round_win()) + " round";
		type_finishing_text(input1, PLAYER_1_COLOUR);
		return false;
	}
	else if (((round % 2 == 0) && player2->finish_game(true, round)) || ((round % 2 == 1) && player2->finish_game(false, round)))
	{
		string input2 = "Player NO.2 has won with " + to_string(player2->get_round_win()) + " round";
		type_finishing_text(input2, PLAYER_2_COLOUR);
		return false;
	}
	return true;
}

void Game::change_beads_location_to_first_state()
{
	beads_1[0] = new Bead(FIELD_X/8, FIELD_Y/2, 0, 0, false, BEAD_RADIUS, BEAD_MASS);
	beads_1[1] = new Bead(FIELD_X/4, FIELD_Y/6, 0, 0, false, BEAD_RADIUS, BEAD_MASS);
  beads_1[2] = new Bead(FIELD_X/4, 5*FIELD_Y/6, 0, 0, false, BEAD_RADIUS, BEAD_MASS);
	beads_1[3] = new Bead(7*FIELD_X/16, FIELD_Y/3, 0, 0, false, BEAD_RADIUS, BEAD_MASS);
	beads_1[4] = new Bead(7*FIELD_X/16, 2*FIELD_Y/3, 0, 0, false, BEAD_RADIUS, BEAD_MASS);

	beads_2[0] = new Bead(7*FIELD_X/8, FIELD_Y/2, 0, 0, false, BEAD_RADIUS, BEAD_MASS);
	beads_2[1] = new Bead(3*FIELD_X/4, FIELD_Y/6, 0, 0, false, BEAD_RADIUS, BEAD_MASS);
	beads_2[2] = new Bead(3*FIELD_X/4, 5*FIELD_Y/6, 0, 0, false, BEAD_RADIUS, BEAD_MASS);
	beads_2[3] = new Bead(9*FIELD_X/16, FIELD_Y/3, 0, 0, false, BEAD_RADIUS, BEAD_MASS);
	beads_2[4] = new Bead(9*FIELD_X/16, 2*FIELD_Y/3, 0, 0, false, BEAD_RADIUS, BEAD_MASS);
}

void Game::process_game_while_goal_scored()
{
	while (!goal_scored)
	{
		draw();
		update();
		delay(1000 * DELAY_TIME);
	}
}

void Game::initialize_objects_after_scored()
{
	change_beads_location_to_first_state();
	ball = new Ball(BALL_X, BALL_Y, 0, 0, false, BALL_RADIUS, BALL_MASS);
	goal_scored = false;
}

void Game::start_round()
{
	while ((player1->finish_round(goal)) && (player2->finish_round(goal)))
	{
		initialize_objects_after_scored();
		process_game_while_goal_scored();
	}
	player1->change_players_info_after_round(goal);
	player2->change_players_info_after_round(goal);
}

void Game::initialize_objects()
{
	cin >> round >> goal;
	player1 = new Player(0, 0);
	player2 = new Player(0, 0);
	ball = new Ball(BALL_X, BALL_Y, 0, 0, false, BALL_RADIUS, BALL_MASS);

	for(int i=0;i<BEADS_NUM1;i++)
		beads_1.push_back(new Bead(0, 0, 0, 0, false, 0, 0));

	for(int i=0;i<BEADS_NUM2;i++)
		beads_2.push_back(new Bead(0, 0, 0, 0, false, 0, 0));

	window = new Window(FIELD_X, FIELD_Y, GAME_NAME);
}

void Game::start_game()
{
	initialize_objects();

	while (show_game_finished())
		start_round();
}
