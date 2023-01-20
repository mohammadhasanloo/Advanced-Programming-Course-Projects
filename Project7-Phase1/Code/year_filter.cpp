#include "year_filter.hpp"


using namespace std;


year_filter::year_filter(std::string _min_year, std::string _max_year)
{
	min_year = _min_year;
	max_year = _max_year;
}

vector <song*> year_filter::split_songs(vector <song*> intended_songs)
{
	vector <song*> search_song;


	for (int i = 0; i < intended_songs.size(); i++)
	{
		bool has_condition = intended_songs[i]->check_year_conditions(min_year, max_year);

		if (has_condition)
			search_song.push_back(intended_songs[i]);
	}

	return search_song;
}