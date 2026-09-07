#ifndef JOKER_H
#define JOKER_H


#include <iostream>
#include "Role.hpp"
#include "Const_Values.hpp"


class joker :public role
{
public:
	joker(int _votes_cast_num,bool _is_silenced, bool _is_dead, bool _is_healed, bool _is_voted, bool _has_dead_in_day);
	std::string get_role() { return JOKER; }
	void make_has_dead_in_day_true() { has_dead_in_day = true; }
	bool get_has_dead_in_day() { return has_dead_in_day; }
private:
	bool has_dead_in_day;
};






#endif
