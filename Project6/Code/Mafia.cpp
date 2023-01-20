#include "Mafia.hpp"

using namespace std;



mafia::mafia(int _votes_cast_num, bool _is_silenced, bool _is_dead, bool _is_healed, bool _is_voted)
	:role(_votes_cast_num, _is_silenced, _is_dead, _is_healed, _is_voted)
{
	votes_cast_num = _votes_cast_num;
	is_silenced = _is_silenced;
	is_dead = _is_dead;
	is_healed = _is_healed;
	is_voted = _is_voted;
}
