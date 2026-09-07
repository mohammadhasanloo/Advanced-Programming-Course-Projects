#ifndef PLAY_LIST_H
#define PLAY_LIST_H

#include <iostream>
#include <vector>
#include "user.hpp"
#include "song.hpp"
#include "permission_denied.hpp"
#include "empty.hpp"
#include "bad_request.hpp"



class playlist
{
public:
	playlist(std::string _playlist_name, int _playlist_id, user* _playlist_user, bool _is_private_playlist);
	std::string get_username_of_playlist() { return playlist_user->get_username(); }
	bool show_a_user_playlists_name(bool can_show_private_playlist);
	int get_playlist_id() { return playlist_id; }
	void add_song_to_playlist(song* curr_song);
	void check_access_to_playlist();
	void show_songs_of_playlist();
	void sort_by_id();
	void delete_song_from_playlist(std::string curr_song_id);

private:
	std::string playlist_name;
	int playlist_id;
	bool is_private_playlist;
	user* playlist_user;
	std::vector <song*> playlist_songs;
};




#endif