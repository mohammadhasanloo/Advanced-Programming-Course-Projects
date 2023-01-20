#include "Bead.hpp"
#include <cmath>


using namespace std;





Bead::Bead(double _bead_x, double _bead_y, double _bead_vx, double _bead_vy, bool _bead_touch, double _bead_radius, double _bead_mass)
{
	bead_x = _bead_x;
	bead_y = _bead_y;
	bead_vx = _bead_vx;
	bead_vy = _bead_vy;
	bead_touch = _bead_touch;
	bead_radius = _bead_radius;
	bead_mass = _bead_mass;
}

void Bead::draw_beads(Window* window, string bead_photo)
{
	window->draw_img(bead_photo, Rectangle(bead_x - bead_radius, bead_y - bead_radius, 2 * bead_radius, 2 * bead_radius),
	 NULL_RECT, 0, false, false);
}

bool Bead::check_bead_position(Point mouse_position)
{
	if ((sqrt(pow(mouse_position.x - bead_x, 2) + pow(mouse_position.y - bead_y, 2))) <= bead_radius)
		return true;
	return false;
}

void Bead::calculate_v_0_bead(double radius, Point d)
{
	bead_vx = (((MOUSE_DRAG_DIRECTION * d.x) * MAX_INITIAL_SPEED) / radius);
	bead_vy = (((MOUSE_DRAG_DIRECTION * d.y) * MAX_INITIAL_SPEED) / radius);
	bead_touch = true;
}

void Bead::write_v_0_bead(Point pawn_position, Point mouse_position)
{
	Point d = mouse_position - pawn_position;
	double absolute_d = sqrt(pow(d.x, 2) + pow(d.y, 2));
	if (absolute_d >= THROW_RADIUS)
		calculate_v_0_bead(absolute_d, d);
	else
		calculate_v_0_bead(THROW_RADIUS, d);
}

double Bead::calculate_result_v_bead()
{
	return sqrt(pow(bead_vx, 2) + pow(bead_vy, 2));
}

void Bead::reset_v_bead_to_zero()
{
	bead_vx = 0;
	bead_vy = 0;
	bead_touch = false;
}

void Bead::change_bead_location()
{
	if (bead_touch)
	{
		bead_x += bead_vx * DELAY_TIME;
		bead_y += bead_vy * DELAY_TIME;
		double v = calculate_result_v_bead();
		double new_v = v - FRICTION_ACCELERATION * DELAY_TIME;
		if (new_v <= 0)
			reset_v_bead_to_zero();
		else
		{
			bead_vx *= (new_v / v);
			bead_vy *= (new_v / v);
		}
	}
}

bool Bead::check_bead_falling_out()
{
	if (((bead_x - bead_radius) < 0) || ((bead_x + bead_radius) >= FIELD_X) ||
	 ((bead_y - bead_radius) < 0) || ((bead_y + bead_radius) >= FIELD_Y))
		return true;
	return false;
}

void Bead::change_bead_values()
{
	if ((bead_x - bead_radius) < 0)
	{
		bead_x = bead_radius;
		bead_vx *= (-1);
	}
	else if ((bead_x + bead_radius) >= FIELD_X)
	{
		bead_x =  FIELD_X - bead_radius;
		bead_vx *= (-1);
	}
	else if ((bead_y - bead_radius) < 0)
	{
		bead_y = bead_radius;
		bead_vy *= (-1);
	}
	else if ((bead_y + bead_radius) >= FIELD_Y)
	{
		bead_y = FIELD_Y - bead_radius;
		bead_vy *= (-1);
	}
}

void Bead::hit_bead_to_the_table()
{
	while (check_bead_falling_out())
	{
		change_bead_values();
		change_bead_location();
	}
}

bool Bead::happens_collision(double x, double y, double radius)
{
	if (sqrt(pow(x - bead_x, 2) + pow(y - bead_y, 2)) <= (bead_radius + radius))
		return true;
	return false;
}

double Bead::abs_X1_minus_X2(double x, double y)
{
	return pow(sqrt(pow(bead_x - x, 2) + pow(bead_y - y, 2)), 2);
}

double Bead::mass_coefficient(double form_mass, double deno_mass)
{
	return (2 * form_mass) / (bead_mass + deno_mass);
}

double Bead::dot_product(double vx, double vy, double x, double y)
{
	return vx * x + vy * y;
}

void Bead::change_bead_touch()
{
	bead_touch=true;
}

void Bead::calculate_new_v_beads(double pre_vx,double pre_vy,Bead* collision_bead)
{
	bead_vx -= mass_coefficient(collision_bead->bead_mass, collision_bead->bead_mass) *
	(dot_product(bead_vx - collision_bead->bead_vx, bead_vy - collision_bead->bead_vy, bead_x - collision_bead->bead_x, bead_y - collision_bead->bead_y) /
	abs_X1_minus_X2(collision_bead->bead_x, collision_bead->bead_y)) * (bead_x - collision_bead->bead_x);

	bead_vy -= mass_coefficient(collision_bead->bead_mass, collision_bead->bead_mass) *
	(dot_product(bead_vx - collision_bead->bead_vx, bead_vy - collision_bead->bead_vy, bead_x - collision_bead->bead_x, bead_y - collision_bead->bead_y) /
	abs_X1_minus_X2(collision_bead->bead_x, collision_bead->bead_y)) * (bead_y - collision_bead->bead_y);

	collision_bead->bead_vx -= mass_coefficient(bead_mass, collision_bead->bead_mass) *
	(dot_product(collision_bead->bead_vx - pre_vx, collision_bead->bead_vy - pre_vy, collision_bead->bead_x - bead_x, collision_bead->bead_y - bead_y) /
	abs_X1_minus_X2(collision_bead->bead_x, collision_bead->bead_y)) * (collision_bead->bead_x - bead_x);

	collision_bead->bead_vy -= mass_coefficient(bead_mass, collision_bead->bead_mass) *
	 (dot_product(collision_bead->bead_vx - pre_vx, collision_bead->bead_vy - pre_vy, collision_bead->bead_x - bead_x, collision_bead->bead_y - bead_y) /
	abs_X1_minus_X2(collision_bead->bead_x, collision_bead->bead_y)) * (collision_bead->bead_y - bead_y);
}

void Bead::write_new_v_beads(Bead* collision_bead)
{
	if(!bead_touch)
		bead_touch=true;
	collision_bead->change_bead_touch();

	change_bead_location();
	collision_bead->change_bead_location();
}

void Bead::beads_collision(Bead* collision_bead)
{
	if (happens_collision(collision_bead->bead_x, collision_bead->bead_y, collision_bead->bead_radius))
	{
		double pre_vx = bead_vx;
		double pre_vy = bead_vy;

		calculate_new_v_beads(pre_vx,pre_vy,collision_bead);

		write_new_v_beads(collision_bead);
	}
}

void Bead::calculate_new_v_bead_ball(Ball* collision_ball, double pre_vx, double pre_vy)
{
	double ball_x = collision_ball->get_ball_x();
	double ball_y = collision_ball->get_ball_y();
	double ball_vy = collision_ball->get_ball_vy();
	double ball_vx = collision_ball->get_ball_vx();
	double ball_mass = collision_ball->get_ball_mass();
	double ball_radius = collision_ball->get_ball_radius();

	bead_vx -= mass_coefficient(ball_mass, ball_mass) *
	 (dot_product(bead_vx - ball_vx, bead_vy - ball_vy, bead_x - ball_x, bead_y - ball_y) /
		abs_X1_minus_X2(ball_x, ball_y)) * (bead_x - ball_x);

	bead_vy -= mass_coefficient(ball_mass, ball_mass) *
	 (dot_product(bead_vx - ball_vx, bead_vy - ball_vy, bead_x - ball_x, bead_y - ball_y) /
		abs_X1_minus_X2(ball_x, ball_y)) * (bead_y - ball_y);

		ball_vx -= mass_coefficient(bead_mass, ball_mass) *
		 (dot_product(ball_vx - pre_vx, ball_vy - pre_vy, ball_x - bead_x, ball_y - bead_y) /
			abs_X1_minus_X2(ball_x, ball_y)) * (ball_x - bead_x);

		ball_vy -= mass_coefficient(bead_mass, ball_mass) *
		 (dot_product(ball_vx - pre_vx, ball_vy - pre_vy, ball_x - bead_x, ball_y - bead_y) /
			abs_X1_minus_X2(ball_x, ball_y)) * (ball_y - bead_y);

		*collision_ball = Ball(ball_x, ball_y, ball_vx, ball_vy, true, BALL_RADIUS, BALL_MASS);
}

void Bead::write_new_v_ball_bead(Ball* collision_ball)
{
	if(!bead_touch)
		bead_touch=true;
	change_bead_location();
	collision_ball->change_ball_location();
}

void Bead::bead_ball_collision(Ball* collision_ball)
{
	double ball_x = collision_ball->get_ball_x();
	double ball_y = collision_ball->get_ball_y();
	double ball_radius = collision_ball->get_ball_radius();

	if (happens_collision(ball_x, ball_y, ball_radius))
	{
		double pre_vx = bead_vx;
		double pre_vy = bead_vy;

		calculate_new_v_bead_ball(collision_ball, pre_vx, pre_vy);

		write_new_v_ball_bead(collision_ball);
	}
}
