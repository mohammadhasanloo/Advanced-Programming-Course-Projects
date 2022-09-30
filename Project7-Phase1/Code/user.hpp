#ifndef USER_H
#define USER_H

#include <iostream>
#include <vector>
#include "song.hpp"
#include "bad_request.hpp"
#include "empty.hpp"


class user
{
public:
	user(std::string _email, std::string _username, std::string _password);
	void check_sign_up_errors(std::string new_email, std::string new_username, std::string new_password);
	std::string get_email() { return email; }
	void check_password_maching(std::string input_pass);
	void check_repetitious_like(std::string liked_song_id);
	void add_new_liked_song(song* new_liked_song);
	void show_liked_songs();
	void sort_by_id();
	void delete_liked_song(std::string curr_song_id);
	std::string get_username() { return username; }

private:
	std::string email;
	std::string username;
	std::string password;
	std::vector <song*> liked_songs;

};



#endif