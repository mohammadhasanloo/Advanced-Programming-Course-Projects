#include "Ball.hpp"
#include <cmath>

using namespace std;



Ball::Ball(double _ball_x, double _ball_y, double _ball_vx, double _ball_vy, bool _ball_touch, double _ball_radius, double _ball_mass)
{
	ball_x = _ball_x;
	ball_y = _ball_y;
	ball_vx = _ball_vx;
	ball_vy = _ball_vy;
	ball_touch = _ball_touch;
	ball_radius = _ball_radius;
	ball_mass = _ball_mass;
}

void Ball::draw_ball(Window* window)
{
	window->draw_img(BALL_PHOTO, Rectangle(ball_x - ball_radius, ball_y - ball_radius, 2 * ball_radius, 2 * ball_radius), NULL_RECT, 0, false, false);
}

bool Ball::check_ball_falling_out()
{
	if (((ball_x - ball_radius) < 0) || ((ball_x + ball_radius) >= FIELD_X) || ((ball_y - ball_radius) < 0) || ((ball_y + ball_radius) >= FIELD_Y))
		return true;
	return false;
}

bool Ball::goal_condition()
{
	if ((ball_y >= DOWN_FOOTBALL_GATE) && (ball_y <= UP_FOOTBALL_GATE))
		return true;
	return false;
}

int Ball::hit_ball_to_the_table()
{
	while (check_ball_falling_out())
	{
		if ((ball_x - ball_radius) < 0)
		{
			if (goal_condition())
				return 2;

			ball_x = ball_radius;
			ball_vx *= (-1);
		}
		else if ((ball_x + ball_radius) >= FIELD_X)
		{
			if (goal_condition())
				return 1;
			ball_x = FIELD_X - ball_radius;
			ball_vx *= (-1);
		}
		else if ((ball_y - ball_radius) < 0)
		{
			ball_y = ball_radius;
			ball_vy *= (-1);
		}
		else if ((ball_y + ball_radius) >= FIELD_Y)
		{
			ball_y = FIELD_Y - ball_radius;
			ball_vy *= (-1);
		}
		change_ball_location();
	}
	return 0;
}

double Ball::calculate_result_v_ball()
{
	return sqrt(pow(ball_vx, 2) + pow(ball_vy, 2));
}

void Ball::reset_v_ball_to_zero()
{
	ball_vx = 0;
	ball_vy = 0;
	ball_touch = false;
}

void Ball::change_ball_location()
{
	if (ball_touch)
	{
		ball_x += ball_vx * DELAY_TIME;
		ball_y += ball_vy * DELAY_TIME;
		double v = calculate_result_v_ball();
		double new_v = v - FRICTION_ACCELERATION * DELAY_TIME;
		if (new_v <= 0)
			reset_v_ball_to_zero();
		else
		{
			ball_vx *= (new_v / v);
			ball_vy *= (new_v / v);
		}
	}
}
