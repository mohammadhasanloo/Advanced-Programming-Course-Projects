#include "like_filter.hpp"


using namespace std;


like_filter::like_filter(std::string _min_like, std::string _max_like)
{
	min_like = _min_like;
	max_like = _max_like;
}

vector <song*> like_filter::split_songs(vector <song*> intended_songs)
{
	vector <song*> search_song;

	for (int i = 0; i < intended_songs.size(); i++)
	{
		bool has_condition = intended_songs[i]->check_like_conditions(min_like, max_like);

		if (has_condition)
			search_song.push_back(intended_songs[i]);
	}

	return search_song;
}