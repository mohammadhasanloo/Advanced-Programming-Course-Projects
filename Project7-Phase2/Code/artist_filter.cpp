#include "artist_filter.hpp"



using namespace std;




artist_filter::artist_filter(string _intended_artist)
{
	intended_artist = _intended_artist;
}

vector <song*> artist_filter::split_songs(vector <song*> intended_songs)
{
	vector <song*> search_song;


	for (int i = 0; i < intended_songs.size(); i++)
	{
		bool has_condition = intended_songs[i]->check_artist_name_conditions(intended_artist);

		if (has_condition)
			search_song.push_back(intended_songs[i]);
	}

	return search_song;
}