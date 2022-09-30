#include "user.hpp"



using namespace std;



user::user(string _email, string _username, string _password)
{
	username = _username;
	email = _email;
	password = _password;
}

void user::check_sign_up_errors(string new_email, string new_username, string new_password)
{
	if (new_email == email || new_username==username)
		throw bad_request();
}

void user::check_password_maching(string input_pass)
{
	if (input_pass != password)
		throw bad_request();
}

void user::check_repetitious_like(string liked_song_id)
{
	for (int i = 0; i < liked_songs.size(); i++)
	{
		if (liked_song_id == liked_songs[i]->get_id())
			throw bad_request();
	}
}

void user::add_new_liked_song(song* new_liked_song)
{
	liked_songs.push_back(new_liked_song);
}

void user::sort_by_id()
{
	for (int i = 0; i < liked_songs.size(); i++)
	{
		for (int j = i + 1; j < liked_songs.size(); j++)
		{
			if (liked_songs[i]->get_id() > liked_songs[j]->get_id())
				swap(liked_songs[i], liked_songs[j]);
		}
	}
}

void user::show_liked_songs()
{
	if (liked_songs.size() <= 0)
		throw empty_err();

	sort_by_id();

	for (int i = 0; i < liked_songs.size(); i++)
		liked_songs[i]->show_song_info();
}

void user::delete_liked_song(string curr_song_id)
{
	for (int i = 0; i < liked_songs.size(); i++)
	{
		if (liked_songs[i]->get_id() == curr_song_id)
		{
			liked_songs[i]->remove_liked_song_num();
			liked_songs.erase(liked_songs.begin() + i);
			return;
		}
	}
	throw bad_request();
}