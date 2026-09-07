#ifndef BALL_H
#define BALL_H

#include <iostream>
#include "rsdl.hpp"
#include "Const_Values.hpp"

using namespace std;

class Ball
{
public:
	Ball(double _ball_x, double _ball_y, double _ball_vx, double _ball_vy,
		 bool _ball_touch, double _ball_radius, double _ball_mass);

	int hit_ball_to_the_table();
	bool check_ball_falling_out();
	void change_ball_location();
	void reset_v_ball_to_zero();
	double calculate_result_v_ball();
	bool goal_condition();
	void draw_ball(Window* window);

	double get_ball_x() { return ball_x; }
	double get_ball_y() { return ball_y; }
	double get_ball_vx() { return ball_vx; }
	double get_ball_vy() { return ball_vy; }
	double get_ball_mass() { return ball_mass; }
	double get_ball_radius() { return ball_radius; }
	bool get_ball_touch() { return ball_touch; }


private:
	double ball_x;
	double ball_y;
	double ball_radius;
	double ball_mass;
	double ball_vx;
	double ball_vy;
	bool ball_touch;
};

#endif
