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

string song::show_song_info()
{
	string body;

		body+= "<a href='song?id=";
		body+= song_id;
		body+= "'target='_self'>";
		body+= get_song_info();
		body+= + "</a><br>";
		body+= "<a href='unlike?id=";
		body+= song_id;
		body+= "&address=likedsongs";
		body+= "'target='_self'>";
		body+= "Unlike";
		body+= "</a><br><br>";

	return body;
}

string song::get_song_info()
{
	string info;
	info += song_id + "." + song_title + "<br>" + song_artist + "<br>" + song_release_year + "<br><br>";
	return info;
}

string song::get_curr_song_info(bool has_user_liked)
{
	string body;

	body += "<tr><td>" + song_title + "</td> <td>" + song_artist + "</td> <td>" + song_release_year + "</td> <td>"
	 + to_string(num_of_likes) +  "</td> <td>" + to_string(num_of_playlists) + "</td> <td>";

	 if(has_user_liked)
	 {
		 body+="<a href='unlike?address=song";
		 body+="&id=";
		 body+=song_id;
		 body+="'>Unlike</a>";
	 }
	 else
	 {
		 body+="<a href='like?address=song";
		 body+="&id=";
		 body+=song_id;
		 body+="'>Like</a>";;
	 }
	 body+="</td> <td>";

	 body+="<audio controls> <source src='";
	 body+=song_link;
	 body+="'type='audio/mpeg'> </audio>";
	 	 
	body +="</td> </tr> <br> ";
	return body;
}

string song::get_recommended_song_info()
{
	string body;
	body += "<tr> <td>" + song_title + "</td> <td>" + song_artist + "</td> <td>" + song_release_year + "</td>";
	return body;
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
