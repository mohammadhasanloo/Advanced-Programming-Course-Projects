#ifndef DOCTOR_H
#define DOCTOR_H


#include <iostream>
#include "Role.hpp"
#include "Const_Values.hpp"


class doctor :public role
{
public:
	doctor(int _votes_cast_num, bool _is_silenced, bool _is_dead, bool _is_healed, bool _is_voted);
	std::string get_role() { return DOCTOR; }
private:
};






#endif
