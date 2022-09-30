#include "Bulletproof.hpp"

using namespace std;


bulletproof::bulletproof(int _votes_cast_num, bool _second_life, bool _is_silenced, bool _is_dead, bool _is_healed, bool _is_voted)
	:role(_votes_cast_num, _is_silenced, _is_dead, _is_healed, _is_voted)
{
	votes_cast_num = _votes_cast_num;
	second_life = _second_life;
	is_silenced = _is_silenced;
	is_dead = _is_dead;
	is_healed = _is_healed;
	is_voted = _is_voted;
}



bool bulletproof::change_and_get_second_life()
{
	if (second_life)
	{
		second_life = false;
		return true;
	}
	else
		return second_life;
}
