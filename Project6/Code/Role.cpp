#include "Role.hpp"





using namespace std;







role::role(int _votes_cast_num, bool _is_silenced, bool _is_dead, bool _is_healed, bool _is_voted)
{
	is_silenced = _is_silenced;
	is_dead = _is_dead;
	is_healed = _is_healed;
	is_voted = _is_voted;
	votes_cast_num = _votes_cast_num;
};

void role::change_information_after_night()
{
	is_voted = false;
	is_healed = false;
	votes_cast_num = 0;
	if (get_role() == SILENCER)
		make_who_silenced_null();
}



void role::change_information_after_day()
{
	is_voted = false;
	votes_cast_num = 0;
	is_silenced = false;
	is_healed = false;
}
