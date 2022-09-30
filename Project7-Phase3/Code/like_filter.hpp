#ifndef LIKE_FILTER_H
#define LIKE_FILTER_H

#include <iostream>
#include <vector>
#include "criteria.hpp"
#include "song.hpp"



class like_filter :public criteria
{
public:
	like_filter(std::string _min_like, std::string _max_like);
	std::vector <song*> split_songs(std::vector <song*> intended_songs);

private:
	std::string min_like;
	std::string max_like;
};





#endif
