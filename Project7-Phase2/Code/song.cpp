#include "song.hpp"

using namespace std;


song::song(string _song_id, string _song_title, string _song_artist, string _song_release_year, string _song_link,
	int _num_of_likes, int _num_of_comments, int _num_of_playlists)
{
	song_id = _song_id;
	song_title = _song_title;
	song_artist = _song_artist;
	song_release_year = _song_release_year;
	song_link = _song_link;
	num_of_likes = _num_of_likes;
	num_of_comments = _num_of_comments;
	num_of_playlists = _num_of_playlists;
}

song::~song()
{
	for (int i = 0; i < comments.size(); i++)
	{
		comment* pre = comments[i];
		comments[i] = nullptr;
		delete pre;
	}
}

void song::show_song_info()
{
	cout << song_id << " " << song_title << " " << song_artist << " " << song_release_year << endl;
}

void song::show_one_song_info()
{
	cout << song_id << endl;
	cout << song_title << endl;
	cout << song_artist << endl;
	cout << song_release_year << endl;
	cout << "#likes: " << to_string(num_of_likes) << endl;
	cout << "#comments: " << to_string(num_of_comments) << endl;
	cout << "#playlists: " << to_string(num_of_playlists) << endl;
}

void song::add_liked_song_num()
{
	num_of_likes++;
}

void song::remove_liked_song_num()
{
	num_of_likes--;
}

void song::add_comment_to_song(string new_time, string new_comment, string curr_username)
{
	comments.push_back(new comment(new_comment, curr_username, new_time));
	num_of_comments++;
}

void song::sort_comments_by_time(int pre,int curr)
{
	if (comments[pre]->get_time_commented() > comments[curr]->get_time_commented())
		swap(comments[pre], comments[curr]);

	else if (comments[pre]->get_time_commented() == comments[curr]->get_time_commented())
	{
		if (comments[pre]->get_user_commented() > comments[curr]->get_user_commented())
			swap(comments[pre], comments[curr]);
	}
}

void song::sort_comments()
{
	for (int i = 0; i < comments.size(); i++)
	{
		for (int j = i + 1; j < comments.size(); j++)
			sort_comments_by_time(i, j);
	}
}

void song::show_comments()
{
	if (comments.size() <= 0)
		throw empty_err();

	sort_comments();

	for (int i = 0; i < comments.size(); i++)
		comments[i]->show_comments();
}

void song::add_playlist_to_song()
{
	num_of_playlists++;
}

void song::remove_playlist_song_num()
{
	num_of_playlists--;
}

bool song::check_year_conditions(string curr_min_year, string curr_max_year)
{
	if (song_release_year >= curr_min_year && song_release_year <= curr_max_year)
		return true;
	return false;
}

bool song::check_like_conditions(string curr_min_like, string curr_max_like)
{
	if (num_of_likes >= stoi(curr_min_like) && num_of_likes <= stoi(curr_max_like))
		return true;
	return false;
}

bool song::check_artist_name_conditions(string curr_intended_artist)
{
	if (curr_intended_artist == song_artist)
		return true;
	return false;
}

void song::write_some_info()
{
	cout << song_title << " " << song_artist << " " << song_release_year << endl;
}