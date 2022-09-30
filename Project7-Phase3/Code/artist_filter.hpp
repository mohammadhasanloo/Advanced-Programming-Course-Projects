#ifndef ARTIST_FILTER_H
#define ARTIST_FILTER_H

#include <iostream>
#include <vector>
#include "criteria.hpp"
#include "song.hpp"



class artist_filter :public criteria
{
public:
	artist_filter(std::string _intended_artist);
	std::vector <song*> split_songs(std::vector <song*> intended_songs);

private:
	std::string intended_artist;
};





#endif