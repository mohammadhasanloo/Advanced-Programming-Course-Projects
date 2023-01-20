#ifndef SONG_H
#define SONG_H

#include <iostream>
#include <string>
#include <vector>
#include "comment.hpp"
#include "empty.hpp"



class song
{
public:
	song(std::string _song_id, std::string _song_title, std::string _song_artist, std::string _song_release_year, std::string _song_link,
		int _num_of_likes, int _num_of_comments, int _num_of_playlists);
	~song();
	std::string get_id() { return song_id; }
	void show_song_info();
	void show_one_song_info();
	void add_liked_song_num();
	void remove_liked_song_num();
	void add_comment_to_song(std::string new_time, std::string new_comment, std::string curr_username);
	void show_comments();
	void sort_comments();
	void sort_comments_by_time(int pre, int curr);
	void add_playlist_to_song();
	void remove_playlist_song_num();
	bool check_year_conditions(std::string curr_min_year, std::string curr_max_year);
	bool check_like_conditions(std::string curr_min_like, std::string curr_max_like);
	bool check_artist_name_conditions(std::string curr_intended_artist);

private:
	std::string song_id;
	std::string song_title;
	std::string song_artist;
	std::string song_release_year;
	std::string song_link;
	int num_of_likes;
	int num_of_comments;
	int num_of_playlists;
	std::vector <comment*> comments;
};




#endif