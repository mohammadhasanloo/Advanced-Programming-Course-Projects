#ifndef UTUNES_H
#define UTUNES_H

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include "user.hpp"
#include "song.hpp"
#include "empty.hpp"
#include "not_found.hpp"
#include "playlist.hpp"
#include "permission_denied.hpp"
#include "filter_song.hpp"
#include "recommended_songs.hpp"
#include "server/server.hpp"

const std::string ID = "id";
const std::string TITLE = "title";
const std::string ARTIST = "artist";
const std::string RELEASE_YEAR = "release_year";
const std::string LINK = "link";
const std::string PASSWORD = "password";
const std::string USERNAME = "username";
const std::string EMAIL = "email";
const std::string LIKED_SONGS_ORDER = "liked_songs";

const int EMAIL_NUM_SIGNUP = 4;
const int USER_NUM_SIGNUP = 6;
const int PASS_NUM_SIGNUP = 8;
const int COUNT_OF_RECOMMENDED_SONGS=4;

class utunes
{
public:
	utunes(int _playlists_num, user* _user_logged_in,bool _has_filtered);
	~utunes();
	void read_files(const std::vector <std::string>& separated_lines,  std::map <std::string, int> column);
	void read_liked_songs_files(const std::vector <std::string>& separated_lines, std::map <std::string, int> column);
	void check_sign_up_errors(std::string username, std::string email, std::string password);
	void add_new_user(std::string username, std::string email, std::string password);
	void login_user(std::string input_username, std::string input_pass);
	void logout_user();
	void get_all_songs_info();
	void sort_by_id(std::vector <song*> curr_song);
	void like_a_song(std::string liked_song_id);
	void check_is_existed_song(std::string liked_song_id);
	void show_liked_songs();
	void delete_liked_song(std::string curr_song_id, std::string curr_username);
	void make_new_playlist(std::string new_playlist_name, bool new_is_private);
	void add_song_to_playlist(std::string curr_playlist_id, std::string curr_song_id);
	void search_curr_playlist(song* curr_song, std::string curr_playlist_id);
	void show_songs_of_playlist(std::string curr_playlist_id);
	void delete_song_from_playlist(std::string curr_playlist_id, std::string curr_song_id);
	void filter_with_artist(std::string curr_artist);
	void filter_with_year(std::string curr_min_year, std::string curr_max_year);
	void check_positive_num_errors(std::string curr_min_year, std::string curr_max_year);
	void filter_with_like(std::string curr_min_like, std::string curr_max_like);
	void delete_filters();
	bool has_repetitious_username(std::string new_username);
	song* search_intended_song(std::string new_liked_song);
	void get_similar_users(int count);


	std::string get_recommeded_songs(int count);
	std::string get_songs();
	std::string get_curr_song_info(std::string song_id);
	song* search_curr_song(std::string song_id);
	std::string get_liked_songs(std::string username);
	std::string show_playlists(std::string username);
	user* search_curr_user(std::string username);
	std::vector <playlist*> get_intended_playlists(std::string curr_user);
	std::string get_playlist_songs(std::string curr_playlist_id);
	playlist* search_intended_playlist(std::string curr_playlist_id);
	std::string get_playlist_info(std::string playlist_id);
	std::string get_body_of_song(song* curr_song);

private:
	std::vector <user*> users;
	std::vector <song*> songs;
	user* user_logged_in;
	std::vector <playlist*> playlists;
	int playlists_num;
	filter_song* filtered_songs;
	bool has_filtered;
	recommended_songs* recommended_songs_system;
};





#endif
