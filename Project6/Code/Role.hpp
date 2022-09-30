#ifndef ROLE_H
#define ROLE_H


#include <iostream>
#include <algorithm>
#include "Const_Values.hpp"



class Player;


class role
{
public:
	role(int _votes_cast_num, bool _is_silenced, bool _is_dead, bool _is_healed, bool _is_voted);
	virtual std::string get_role() = 0;
	bool get_is_dead() { return is_dead; }
	bool get_is_voted() { return is_voted; }
	bool get_is_silenced() { return is_silenced; }
	void add_votes_cast_num () { votes_cast_num++; }
	void change_is_voted_true () { is_voted = true; }
	int get_votes_cast_num() { return votes_cast_num; }
	void make_is_dead_true() { is_dead = true; }
	void change_information_after_day();
	virtual Player* get_who_silenced() { return nullptr; }
	void make_is_voted_true() { is_voted = true; }
	void make_is_healed_true() { is_healed=true; }
	void make_is_silenced_true() { is_silenced=true; }
	virtual void change_who_silenced(Player* player_votee) {}
	bool get_is_healed() { return is_healed; }
	virtual bool change_and_get_second_life() { return false; }
	void change_information_after_night();
	virtual void make_who_silenced_null() {}
	virtual void make_has_dead_in_day_true() {}
	virtual bool get_has_dead_in_day() { return false; }
	void change_has_silenced(bool curr_has_silenced) { is_silenced = curr_has_silenced; };

protected:
	 int votes_cast_num;
	 bool is_silenced;
	 bool is_dead;
	 bool is_healed;
	 bool is_voted;
};


#endif
