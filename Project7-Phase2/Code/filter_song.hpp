#ifndef FILTER_SONG_H
#define FILTER_SONG_H

#include <iostream>
#include <vector>
#include "criteria.hpp"
#include "artist_filter.hpp"
#include "year_filter.hpp"
#include "like_filter.hpp"
#include "song.hpp"

const int FILTERS_NUM = 3;
const int ARTST_FILTER = 0;
const int YEAR_FILTER = 1;
const int LIKE_FILTER = 2;

class filter_song
{
public:
	filter_song();
	~filter_song();
	void add_artist_filter(std::string curr_artist);
	void remove_curr_filter(int filter_num);
	void add_year_filter(std::string curr_min_year, std::string curr_max_year);
	void add_like_filter(std::string curr_min_like, std::string curr_max_like);
	void delete_filters();
	std::vector <song*> get_intended_songs(std::vector <song*> songs);

private:
	std::vector <criteria*> filters;
};





#endif