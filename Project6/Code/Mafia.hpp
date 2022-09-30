#ifndef MAFIA_H
#define MAFIA_H


#include <iostream>
#include "Role.hpp"
#include "Const_Values.hpp"


class mafia :public role
{
public:
	mafia(int _votes_cast_num, bool _is_silenced, bool _is_dead, bool _is_healed, bool _is_voted);
	std::string get_role() { return MAFIA; }
private:
};






#endif
