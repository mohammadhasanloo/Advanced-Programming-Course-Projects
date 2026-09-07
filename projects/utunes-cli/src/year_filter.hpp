#ifndef YEAR_FILTER_H
#define YEAR_FILTER_H

#include <iostream>
#include <vector>
#include "criteria.hpp"
#include "song.hpp"



class year_filter :public criteria
{
public:
	year_filter(std::string _min_year, std::string _max_year);
	std::vector <song*> split_songs(std::vector <song*> intended_songs);

private:
	std::string min_year;
	std::string max_year;
};





#endif