#ifndef CRITERIA_H
#define CRITERIA_H

#include <iostream>
#include <vector>
#include "song.hpp"



class criteria
{
public:
	virtual std::vector <song*> split_songs(std::vector <song*> intended_songs) = 0;
};





#endif