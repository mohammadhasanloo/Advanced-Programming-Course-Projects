#include "utunes.hpp"

using namespace std;



utunes::utunes(int _playlists_num, user* _user_logged_in, bool _has_filtered)
{
	user_logged_in = _user_logged_in;
	playlists_num = _playlists_num;
	has_filtered = _has_filtered;
	filtered_songs = new filter_song();
	recommended_songs_system = nullptr;
}

utunes::~utunes()
{
	filter_song* pre = filtered_songs;
	filtered_songs = nullptr;
	delete pre;

	for (int i = 0; i < users.size(); i++)
	{
		user* pre = users[i];
		users[i] = nullptr;
		delete pre;
	}

	for (int i = 0; i < songs.size(); i++)
	{
		song* pre = songs[i];
		songs[i] = nullptr;
		delete pre;
	}

	for (int i = 0; i < playlists.size(); i++)
	{
		playlist* pre = playlists[i];
		playlists[i] = nullptr;
		delete pre;
	}
}

void utunes::read_files(const vector <string>& separated_lines,  map <string, int> column)
{
	string new_link, new_id, new_artist, new_release_year, new_title;
	for (int i = 0; i < separated_lines.size(); i++)
	{
		if (i == column[LINK])
			new_link = separated_lines[i];
		if (i == column[ID])
			new_id = separated_lines[i];
		if (i == column[ARTIST])
			new_artist = separated_lines[i];
		if (i == column[RELEASE_YEAR])
			new_release_year = separated_lines[i];
		if (i == column[TITLE])
			new_title = separated_lines[i];
	}

	songs.push_back(new song(new_id, new_title, new_artist, new_release_year, new_link, 0, 0, 0));
}

bool utunes::has_repetitious_username(string new_username)
{
	for (int i = 0; i < users.size(); i++)
	{
		if (users[i]->get_username() == new_username)
			return true;
	}
	return false;
}

song* utunes::search_intended_song(string new_liked_song)
{
	for (int i = 0; i < songs.size(); i++)
	{
		if (songs[i]->get_id() == new_liked_song)
			return songs[i];
	}
	return nullptr;
}

void utunes::read_liked_songs_files(const vector <string>& separated_lines, map <string, int> column)
{
	string new_username, new_email, new_password, new_liked_song;
	
	for (int i = 0; i < separated_lines.size(); i++)
	{
		if (i == column[LIKED_SONGS_ORDER])
			new_liked_song = separated_lines[i];

		if (i == column[PASSWORD])
			new_password = separated_lines[i];

		if (i == column[EMAIL])
			new_email = separated_lines[i];

		if (i == column[USERNAME])
			new_username = separated_lines[i];
	}

	if (!has_repetitious_username(new_username))
		users.push_back(new user(new_email, new_username, new_password));

	for (int i = 0; i < users.size(); i++)
	{
		song* curr_song=search_intended_song(new_liked_song);
		if (users[i]->get_username() == new_username)
			users[i]->add_new_liked_song_to_user(curr_song);
	}
}

void utunes::check_sign_up_errors(string username, string email, string password)
{
	for (int i = 0; i < users.size(); i++)
		users[i]->check_sign_up_errors(email, username, password);
}

void utunes::add_new_user(string username, string email, string password)
{
	logout_user();

	users.push_back(new user(email, username, password));

	user_logged_in = users.back();
}

string utunes::get_body_of_song(song* curr_song)
{
	string body;
	body+="<a href='song?id=";
	body+=curr_song->get_id();
	body+= "'target='_self'>";
	body+=curr_song->get_song_info();
	body+= + "</a><br>";
	return body;	
}

string utunes::get_songs()
{
	if(has_filtered)
	{
		vector <song*> intended_songs = filtered_songs->get_intended_songs(songs);
		sort_by_id(intended_songs);
		string body;
		for(int i=0;i<intended_songs.size();i++)
			body+=get_body_of_song(intended_songs[i]);

		return body;	
	}
	else
	{
		sort_by_id(songs);
		string body;
		for(int i=0;i<songs.size();i++)
			body+=get_body_of_song(songs[i]);

		return body;
	}
}

playlist* utunes::search_intended_playlist(string curr_playlist_id)
{
	for(int i=0;i<playlists.size();i++)
	{
		if(curr_playlist_id==to_string(playlists[i]->get_playlist_id()))
		return playlists[i];
	}
	return nullptr;
}

string utunes::get_playlist_songs(string curr_playlist_id)
{
	playlist* curr_playlist=search_intended_playlist(curr_playlist_id);

	return curr_playlist->get_songs_of_playlist();
}

void utunes::login_user(string input_username, string input_pass)
{
	logout_user();

	for (int i = 0; i < users.size(); i++)
	{
		if (users[i]->get_username() == input_username)
		{
			users[i]->check_password_maching(input_pass);
			user_logged_in = users[i];
			return;
		}
	}
	throw Server::Exception("bad request");
}

string utunes::get_playlist_info(string playlist_id)
{
	playlist* curr_playlist=search_intended_playlist(playlist_id);
	string body;
	body+="<table id='t01'> <tr> <th> Playlist Name </th> <th> Type Of Ownership </th> </tr>";
	body+=curr_playlist->get_curr_playlist_info();
	body+="</table> <br>";

	return body;
}

string utunes::get_curr_song_info(string song_id)
{
	song* curr_song=search_curr_song(song_id);
	string body;
	bool has_user_liked=user_logged_in->check_liked_curr_song(curr_song);
	body+="<table id='t01'> <tr> <th> Song Name </th> <th> Artist </th> <th> Year Release </th> <th> Num of Likes </th> <th> Num of Playlists </th> <th>  </th> <th>  </th> </tr>";
	body+=curr_song->get_curr_song_info(has_user_liked);
	body+="</table> <br>";
	body+="<table id='t01'> <tr> <th> Song Name </th> <th> Artist </th> <th> Year Release </th> <th> Confidence </th> <th> Link </th> </tr>";
	body+="<h2> Recommnded Songs </h2>";
	body+=get_recommeded_songs(COUNT_OF_RECOMMENDED_SONGS);
	body+="</table>";

	return body;
}

string utunes::get_liked_songs(string username)
{
	string body;

	user* curr_user=search_curr_user(username);
	body = curr_user->show_liked_songs();

	return body;
}

user* utunes::search_curr_user(string username)
{
	for(int i=0;i<users.size();i++)
	{
		if(username==users[i]->get_username())
		return users[i];
	}
	return nullptr;
}

vector <playlist*> utunes::get_intended_playlists(string curr_user)
{
	vector <playlist*> intended_playlists;

	for(int i=0;i<playlists.size();i++)
	{
		if(playlists[i]->get_username_of_playlist() == curr_user)
			intended_playlists.push_back(playlists[i]);
	}

	return intended_playlists;
}

string utunes::show_playlists(string username)
{
	string body;

	vector <playlist*> users_playlists= get_intended_playlists(username);

	for(int i=0;i<users_playlists.size();i++)
	{
		body+="<br> <a href='currplaylist?id=";
		body+=to_string(users_playlists[i]->get_playlist_id());
		body+= "'target='_self'>";
		body+=users_playlists[i]->get_playlist_info();
		body+= + "</a><br>";
	}

	return body;
}

song* utunes::search_curr_song(string song_id)
{
	for(int i=0;i<songs.size();i++)
	{
		if(songs[i]->get_id() == song_id)
			return songs[i];
	}
	return nullptr;
}

void utunes::logout_user()
{
	filter_song* pre = filtered_songs;
	filtered_songs = nullptr;
	delete pre;

	filtered_songs = new filter_song();

	if(user_logged_in!=nullptr)
		user_logged_in = nullptr;

	has_filtered = false;
}

void utunes::sort_by_id(vector <song*> curr_song)
{
	for (int i = 0; i < curr_song.size(); i++)
	{
		for (int j = i + 1; j < curr_song.size(); j++)
		{
			if (curr_song[i]->get_id() > curr_song[j]->get_id())
				swap(curr_song[i], curr_song[j]);
		}
	}
}

void utunes::get_all_songs_info()
{
	if (!has_filtered)
	{
		sort_by_id(songs);

		for (int i = 0; i < songs.size(); i++)
			songs[i]->show_song_info();
	}
	else
	{
		vector <song*> intended_songs = filtered_songs->get_intended_songs(songs);

		sort_by_id(intended_songs);

		for (int i = 0; i < intended_songs.size(); i++)
			intended_songs[i]->show_song_info();
	}
}

void utunes::check_is_existed_song(string liked_song_id)
{
	bool is_song_existed = false;
	for (int i = 0; i < songs.size(); i++)
	{
		if (songs[i]->get_id() == liked_song_id)
			is_song_existed = true;
	}
	if (!is_song_existed)
		throw Server::Exception("Not Found");
}

void utunes::like_a_song(string liked_song_id)
{
	check_is_existed_song(liked_song_id);
	song* curr_song=search_curr_song(liked_song_id);

	user_logged_in->add_new_liked_song(curr_song);
	curr_song->add_liked_song_num();
}

void utunes::show_liked_songs()
{
	user_logged_in->show_liked_songs();
}

void utunes::delete_liked_song(string curr_song_id, string curr_username)
{
	user* curr_user = search_curr_user(curr_username);
	curr_user->delete_liked_song(curr_song_id);
}

void utunes::make_new_playlist(string new_playlist_name, bool new_is_private)
{
	playlists.push_back(new playlist(new_playlist_name, playlists_num, user_logged_in, new_is_private));
	playlists_num++;
}

void utunes::search_curr_playlist(song* curr_song, string curr_playlist_id)
{
	for (int j = 0; j < playlists.size(); j++)
	{
		if (playlists[j]->get_playlist_id() == stoi(curr_playlist_id))
		{
			if (user_logged_in->get_username() != playlists[j]->get_username_of_playlist())
				throw Server::Exception("Permission Denied");

			playlists[j]->add_song_to_playlist(curr_song);
			curr_song->add_playlist_to_song();
			return;
		}
	}
	throw Server::Exception("Not Found");
}

void utunes::add_song_to_playlist(string curr_playlist_id, string curr_song_id)
{
	for (int i = 0; i < songs.size(); i++)
	{
		if (curr_song_id == songs[i]->get_id())
		{
			search_curr_playlist(songs[i], curr_playlist_id);
			return;
		}
	}
	throw Server::Exception("Not Found");
}

void utunes::show_songs_of_playlist(string curr_playlist_id)
{
	for (int i = 0; i < playlists.size(); i++)
	{
		if (playlists[i]->get_playlist_id() == stoi(curr_playlist_id))
		{
			if (user_logged_in->get_username() != playlists[i]->get_username_of_playlist())
				playlists[i]->check_access_to_playlist();

			playlists[i]->show_songs_of_playlist();
			return;
		}
	}
	throw Server::Exception("Not Found");
}

void utunes::delete_song_from_playlist(string curr_playlist_id, string curr_song_id)
{
	for (int i = 0; i < playlists.size(); i++)
	{
		if (stoi(curr_playlist_id) == playlists[i]->get_playlist_id())
		{
			if (playlists[i]->get_username_of_playlist() != user_logged_in->get_username())
				throw Server::Exception("Permission Denied");

			playlists[i]->delete_song_from_playlist(curr_song_id);
			return;
		}
	}
	throw Server::Exception("Not Found");
}

void utunes::filter_with_artist(string curr_artist)
{
	filtered_songs->add_artist_filter(curr_artist);
	has_filtered = true;
}

void utunes::check_positive_num_errors(string curr_min_year, string curr_max_year)
{
	if ((stoi(curr_max_year) < stoi(curr_min_year)) || stoi(curr_min_year) < 0 || stoi(curr_max_year) < 0)
		throw Server::Exception("Bad Request");
}

void utunes::filter_with_year(string curr_min_year, string curr_max_year)
{
	check_positive_num_errors(curr_min_year, curr_max_year);

	filtered_songs->add_year_filter(curr_min_year, curr_max_year);
	has_filtered = true;
}

void utunes::filter_with_like(string curr_min_like, string curr_max_like)
{
	check_positive_num_errors(curr_min_like, curr_max_like);

	filtered_songs->add_like_filter(curr_min_like, curr_max_like);
	has_filtered = true;
}

void utunes::delete_filters()
{
	filtered_songs->delete_filters();
	has_filtered = false;
}

void utunes::get_similar_users(int count)
{
	recommended_songs_system = new recommended_songs(users, user_logged_in, songs, count);

	recommended_songs_system->similar_users_function();

	recommended_songs* pre = recommended_songs_system;
	recommended_songs_system = nullptr;
	delete pre;
}

string utunes::get_recommeded_songs(int count)
{
	recommended_songs_system = new recommended_songs(users, user_logged_in, songs, count);

	string body = recommended_songs_system->recommeded_songs_function();

	recommended_songs* pre = recommended_songs_system;
	recommended_songs_system = nullptr;
	delete pre;
	
	return body;
}