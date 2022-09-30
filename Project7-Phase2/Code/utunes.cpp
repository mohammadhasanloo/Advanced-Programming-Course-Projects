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

void utunes::check_sign_up_errors(const vector <string>& seperated_input)
{
	for (int i = 0; i < users.size(); i++)
		users[i]->check_sign_up_errors(seperated_input[EMAIL_NUM_SIGNUP],
			seperated_input[USER_NUM_SIGNUP], seperated_input[PASS_NUM_SIGNUP]);
}

void utunes::add_new_user(const vector <string>& seperated_input)
{
	users.push_back(new user(seperated_input[EMAIL_NUM_SIGNUP],
		seperated_input[USER_NUM_SIGNUP], seperated_input[PASS_NUM_SIGNUP]));

	user_logged_in = users.back();
}

void utunes::login_user(string input_email, string input_pass)
{
	for (int i = 0; i < users.size(); i++)
	{
		if (users[i]->get_email() == input_email)
		{
			users[i]->check_password_maching(input_pass);
			user_logged_in = users[i];
			return;
		}
	}
	throw bad_request();
}

void utunes::logout_user()
{
	filter_song* pre = filtered_songs;
	filtered_songs = nullptr;
	delete pre;
	filtered_songs = new filter_song();
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
	if (songs.size() <= 0)
		throw empty_err();

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

void utunes::get_one_song_info(string request_id)
{
	for (int i = 0; i < songs.size(); i++)
	{
		if (request_id == songs[i]->get_id())
		{
			songs[i]->show_one_song_info();
			return;
		}
	}
	throw not_found();
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
		throw not_found();
}

void utunes::like_a_song(string liked_song_id)
{
	check_is_existed_song(liked_song_id);
	user_logged_in->check_repetitious_like(liked_song_id);

	for (int i = 0; i < songs.size(); i++)
	{
		if (songs[i]->get_id() == liked_song_id)
		{
			user_logged_in->add_new_liked_song(songs[i]);
			songs[i]->add_liked_song_num();
			break;
		}
	}
}

void utunes::show_liked_songs()
{
	user_logged_in->show_liked_songs();
}

void utunes::delete_liked_song(string curr_song_id)
{
	user_logged_in->delete_liked_song(curr_song_id);
}

void utunes::write_usernames()
{
	if (users.size() <= 1)
		throw empty_err();

	vector <string> usernames;
	for (int i = 0; i < users.size(); i++)
	{
		if (users[i] != user_logged_in)
			usernames.push_back(users[i]->get_username());
	}

	sort(usernames.begin(),usernames.end());
	for (int i = 0; i < usernames.size(); i++)
		cout << usernames[i] << endl;
}

void utunes::add_comment_to_song(string new_song_id, string new_time, string new_comment)
{
	for (int i = 0; i < songs.size(); i++)
	{
		if (songs[i]->get_id() == new_song_id)
		{
			songs[i]->add_comment_to_song(new_time, new_comment, user_logged_in->get_username());
			return;
		}
	}
	throw not_found();
}

void utunes::show_comments(string curr_song_id)
{
	for (int i = 0; i < songs.size(); i++)
	{
		if (songs[i]->get_id() == curr_song_id)
		{
			songs[i]->show_comments();
			return;
		}
	}
	throw not_found();
}

void utunes::make_new_playlist(string new_playlist_name, bool new_is_private)
{
	playlists.push_back(new playlist(new_playlist_name, playlists_num, user_logged_in, new_is_private));
	cout << playlists_num << endl;
	playlists_num++;
}

void utunes::show_a_user_playlists_name(string curr_username)
{
	bool has_anything_to_show = false;

	for (int i = 0; i < playlists.size(); i++)
	{
		if ((playlists[i]->get_username_of_playlist() == curr_username) && (curr_username == user_logged_in->get_username()))
		{
			bool is_show = playlists[i]->show_a_user_playlists_name(true);
			if (is_show)
				has_anything_to_show = true;
		}

		else if ((playlists[i]->get_username_of_playlist() == curr_username) && (curr_username != user_logged_in->get_username()))
		{
			bool is_show = playlists[i]->show_a_user_playlists_name(false);
			if (is_show)
				has_anything_to_show = true;
		}
	}
	if (!has_anything_to_show)
		throw empty_err();
}

void utunes::search_curr_playlist(song* curr_song, string curr_playlist_id)
{
	for (int j = 0; j < playlists.size(); j++)
	{
		if (playlists[j]->get_playlist_id() == stoi(curr_playlist_id))
		{
			if (user_logged_in->get_username() != playlists[j]->get_username_of_playlist())
				throw permission_denied();

			playlists[j]->add_song_to_playlist(curr_song);
			curr_song->add_playlist_to_song();
			return;
		}
	}
	throw not_found();
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
	throw not_found();
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
	throw not_found();
}

void utunes::delete_song_from_playlist(string curr_playlist_id, string curr_song_id)
{
	for (int i = 0; i < playlists.size(); i++)
	{
		if (stoi(curr_playlist_id) == playlists[i]->get_playlist_id())
		{
			if (playlists[i]->get_username_of_playlist() != user_logged_in->get_username())
				throw permission_denied();

			playlists[i]->delete_song_from_playlist(curr_song_id);
			return;
		}
	}
	throw not_found();
}

void utunes::filter_with_artist(string curr_artist)
{
	filtered_songs->add_artist_filter(curr_artist);
	has_filtered = true;
}

void utunes::check_positive_num_errors(string curr_min_year, string curr_max_year)
{
	if ((stoi(curr_max_year) < stoi(curr_min_year)) || stoi(curr_min_year) < 0 || stoi(curr_max_year) < 0)
		throw bad_request();
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

void utunes::get_recommeded_songs(int count)
{
	recommended_songs_system = new recommended_songs(users, user_logged_in, songs, count);

	recommended_songs_system->recommeded_songs_function();

	recommended_songs* pre = recommended_songs_system;
	recommended_songs_system = nullptr;
	delete pre;
}