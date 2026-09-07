#ifndef SILENCER_H
#define SILENCER_H


#include <iostream>
#include "Role.hpp"
#include "Const_Values.hpp"

class Player;

class silencer :public role
{
public:
	silencer(int _votes_cast_num, bool _is_silenced, bool _is_dead, bool _is_healed, bool _is_voted, Player* _who_silenced);
	std::string get_role() { return SILENCER; }
	Player* get_who_silenced() { return who_silenced; }
	void change_who_silenced(Player* player_votee) { who_silenced=player_votee; }
	void make_who_silenced_null() { who_silenced = nullptr; }
private:
	Player* who_silenced;
};






#endif
