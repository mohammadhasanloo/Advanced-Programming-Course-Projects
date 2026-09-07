#ifndef BEAD_H
#define BEAD_H

#include <iostream>
#include "Ball.hpp"
#include "rsdl.hpp"
#include "Const_Values.hpp"



class Bead
{
public:
	Bead(double _bead_x, double _bead_y, double _bead_vx, double _bead_vy,
		 bool _bead_touch, double _bead_radius, double _bead_mass);

	void draw_beads(Window* window, std::string photo);
	bool check_bead_position(Point mouse_position);
	void calculate_v_0_bead(double radius, Point d);
	void change_bead_location();
	double calculate_result_v_bead();
	bool check_bead_falling_out();
	void hit_bead_to_the_table();
	void calculate_new_v_bead_ball(Ball* collision_ball, double pre_vx, double pre_vy);
	void bead_ball_collision(Ball* collision_ball);
	bool happens_collision(double x, double y, double radius);
	double mass_coefficient(double form_mass, double deno_mass);
	double abs_X1_minus_X2(double x, double y);
	void calculate_new_v_beads(double pre_vx,double pre_vy,Bead* collision_bead);
	void reset_v_bead_to_zero();
	void change_bead_values();
	void write_new_v_beads(Bead* collision_bead);
	double dot_product(double vx, double vy, double x, double y);
	void beads_collision(Bead* collision_bead);
	void change_bead_touch();
	void write_v_0_bead(Point pawn_position, Point mouse_position);
	void write_new_v_ball_bead(Ball* collision_ball);

	bool get_bead_touch() { return bead_touch; }
private:
	double bead_mass;
	double bead_x;
	double bead_y;
	double bead_radius;
	double bead_vx;
	double bead_vy;
	bool bead_touch;
};

#endif
