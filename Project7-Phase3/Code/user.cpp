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
		throw Server::Exception("bad request");
}

void user::check_password_maching(string input_pass)
{
	if (input_pass != password)
		throw Server::Exception("bad request");
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

string user::show_liked_songs()
{
	sort_by_id();

	string body;

	for (int i = 0; i < liked_songs.size(); i++)
		body += liked_songs[i]->show_song_info();

	return body;
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
}

void user::add_new_liked_song_to_user(song* new_liked_song)
{
	liked_songs.push_back(new_liked_song);
	new_liked_song->add_liked_song_num();
}

bool user::check_liked_curr_song(song* curr_song)
{
	for (int i = 0; i < liked_songs.size(); i++)
	{
		if (liked_songs[i] == curr_song)
			return true;
	}
	return false;
}

bool user::is_song_liked(song* curr_song)
{
	for (int i = 0; i < liked_songs.size(); i++)
	{
		if (curr_song == liked_songs[i])
			return true;
	}
	return false;
}