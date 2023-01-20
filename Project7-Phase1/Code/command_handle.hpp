#ifndef COMMAND_HANDLE_H
#define COMMAND_HANDLE_H


#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include "utunes.hpp"
#include "not_found.hpp"
#include "bad_request.hpp"
#include "permission_denied.hpp"


const char SEPARATOR_CHAR_CSV = ',';
const char SEPARATOR_CHAR = ' ';
const std::string OK= "OK";
const std::string GET = "GET";
const std::string POST = "POST";
const std::string DELETE = "DELETE";
const std::string QUESTION_MARK = "?";
const std::string SIGNUP = "signup";
const std::string LOGIN = "login";
const std::string LOGOUT = "logout";
const std::string USERNAME = "username";
const std::string EMAIL = "email";
const std::string PASSWORD = "password";
const std::string TIME = "time";
const std::string SONGS = "songs";
const std::string LIKES = "likes";
const std::string USERS = "users";
const std::string COMMENT = "comment";
const std::string COMMENTS = "comments";
const std::string PLAYLISTS = "playlists";
const std::string PRIVATE = "private";
const std::string PUBLIC = "public";
const std::string PLAYLISTS_SONGS = "playlists_songs";
const std::string FILTERS = "filters";
const std::string MIN_YEAR = "min_year";
const std::string MAX_YEAR = "max_year";
const std::string MIN_LIKE = "min_like";
const std::string MAX_LIKE = "max_like";
const std::string PLAYLIST_ID = "playlist_id";
const std::string SONG_ID = "song_id";

const int POST_GET_DEL_NUM_INPUT = 0;
const int FUN_NUM_INPUT = 1;
const int QUESTION_MARK_LOC = 2;
const int EMAIL_NUM_LOGIN = 4;
const int PASS_NUM_LOGIN = 6;
const int GET_ALL_SONGS_NUM_INPUT = 2;
const int GET_ONE_SONGS_NUM_INPUT = 5;
const int POST_COMMENT_SONG_ID = 4;
const int POST_COMMENT_TIME = 6;
const int POST_COMMENT_COMMENT = 8;
const int ID_SONG_NUM_GET_SONGS = 4;
const int ID_SONG_NUM_POST_LIKES = 4;
const int ID_SONG_NUM_DEL_LIKES = 4;
const int GET_COMMENT_SONG_ID = 4;
const int FIRST_PLAYLISTS_NUM = 1;
const int POST_PLAYLISTS_NAME = 4;
const int POST_PLAYLISTS_PRIVACY = 6;
const int GET_PLAYLISTS_USERNAME = 4;
const int POST_PLAYLISTS_SONGS_PLAYLIST_ID = 4;
const int POST_PLAYLISTS_SONGS_SONG_ID = 6;
const int DELETE_LIKE_ID_LOC = 3;
const int START_ARTIST_FILTER_STRING = 4;
const int TYPE_OF_FILTER = 3;
const int FIRST_INPUT_FUN = 3;
const int FIRST_INPUT = 4;
const int SECOND_INPUT_FUN = 5;
const int SECOND_INPUT = 6;
const int THIRD_INPUT_FUN = 7;
const int THIRD_INPUT = 8;


const int DELETE_LIKE_SIZE = 5;
const int DELETE_PLAYLISTS_SONGS_SIZE = 7;
const int DELETE_FILTERS_SIZE = 2;
const int GET_PLAYLISTS_SONGS_SIZE = 5;
const int GET_PLAYLISTS_SIZE = 5;
const int GET_COMMENTS_SIZE = 5;
const int GET_USERS_SIZE = 2;
const int GET_LIKES_SIZE = 2;
const int POST_SIGNUP_SIZE = 9;
const int POST_LOGIN_SIZE = 7;
const int POST_LOGOUT_SIZE = 2;
const int POST_LIKES_SIZE = 5;
const int POST_COMMENTS_SIZE = 9;
const int POST_PLAYLISTS_SIZE = 7;
const int POST_PLAYLISTS_SONGS_SIZE = 7;
const int POST_FILTERS_ARTIST_SIZE = 5;
const int POST_FILTERS_YEAR_SIZE = 7;
const int POST_FILTERS_LIKE_SIZE = 7;



class command_handle
{
public:
	command_handle(bool _has_logged_in);
	~command_handle();
	void run(char songs_list[]);
	std::vector<std::string> seperate_strings(std::string oneline, char character);
	std::map<std::string, int> savecolumn(const std::vector <std::string>& separatedline);
	void save_songs_in_program(char songs_list[]);
	void GET_functions();
	void POST_functions();
	void POST_signup_function();
	void POST_login_function();
	void POST_logout_function();
	void GET_songs_functions();
	void POST_likes_function();
	void GET_likes_function();
	void DELETE_functions();
	void DELETE_likes_fuction();
	void GET_users_function();
	void POST_comments_function();
	void GET_comments_function();
	void POST_playlists_function();
	void GET_playlists_function();
	void POST_playlists_songs_function();
	void GET_playlists_songs_function();
	void DELETE_playlists_songs_function();
	void POST_filters_function();
	void DELETE_filters_function();
	void check_first_input_errors();
	void DELETE_filters_errors();
	void DELETE_playlists_songs_errors();
	void DELETE_likes_errors();
	void GET_playlists_songs_errors();
	void GET_playlists_errors();
	void GET_comments_errors();
	void GET_users_errors();
	void GET_likes_errors();
	void POST_signup_errors();
	void POST_login_errors();
	void POST_logout_errors();
	void POST_likes_errors();
	void POST_comments_errors();
	void POST_playlists_errors();
	void POST_playlists_songs_errors();
	void POST_artist_filter();
	void POST_filters_errors();

private:
	utunes* new_utunes;
	std::vector <std::string> separated_input;
	bool has_logged_in;
};




#endif 
