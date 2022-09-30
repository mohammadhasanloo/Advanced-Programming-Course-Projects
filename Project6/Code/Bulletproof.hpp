#ifndef BULLETPROOF_H
#define BULLETPROOF_H


#include <iostream>
#include "Role.hpp"
#include "Const_Values.hpp"


class bulletproof :public role
{
public:
	bulletproof(int _votes_cast_num, bool _second_life, bool _is_silenced, bool _is_dead, bool _is_healed, bool _is_voted);
	std::string get_role() { return BULLETPROOF; }
  bool change_and_get_second_life();

	
private:
	bool second_life;
};






#endif
