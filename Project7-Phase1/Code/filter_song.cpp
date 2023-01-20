#include "filter_song.hpp"


using namespace std;


filter_song::filter_song()
{
	vector <criteria*> _filters(FILTERS_NUM, nullptr);
	filters = _filters;
}

filter_song::~filter_song()
{
	for (int i = 0; i < filters.size(); i++)
	{
		if (filters[i] != nullptr)
		{
			criteria* pre = filters[i];
			filters[i] = nullptr;
			delete pre;
		}
	}
}

void filter_song::remove_curr_filter(int filter_num)
{
	if (filters[filter_num] != nullptr)
	{
		criteria* pre = filters[filter_num];
		filters[filter_num] = nullptr;
		delete pre;
	}
}

void filter_song::add_artist_filter(string curr_artist)
{
	remove_curr_filter(ARTST_FILTER);
	filters[ARTST_FILTER] = new artist_filter(curr_artist);
}

void filter_song::add_year_filter(std::string curr_min_year, std::string curr_max_year)
{
	remove_curr_filter(YEAR_FILTER);
	filters[YEAR_FILTER] = new year_filter(curr_min_year, curr_max_year);
}

void filter_song::add_like_filter(string curr_min_like, string curr_max_like)
{
	remove_curr_filter(LIKE_FILTER);
	filters[LIKE_FILTER] = new like_filter(curr_min_like, curr_max_like);
}

void filter_song::delete_filters()
{
	for (int i = 0; i < filters.size(); i++)
		remove_curr_filter(i);
}

vector <song*> filter_song::get_intended_songs(vector <song*> songs)
{
	vector <song*> intended_songs = songs;
	for (int i = 0; i < filters.size(); i++)
	{
		if (filters[i] != nullptr)
		{
			intended_songs = filters[i]->split_songs(intended_songs);
			if (intended_songs.size() <= 0)
				throw empty_err();
		}
	}
	return intended_songs;
}

