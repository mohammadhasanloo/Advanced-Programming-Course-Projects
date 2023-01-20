#ifndef VILLAGER_H
#define VILLAGER_H


#include <iostream>
#include "Role.hpp"
#include "Const_Values.hpp"


class villager :public role
{
public:
	villager(int _votes_cast_num, bool _is_silenced, bool _is_dead, bool _is_healed, bool _is_voted);
	std::string get_role() { return VILLAGER; }
private:
};






#endif
