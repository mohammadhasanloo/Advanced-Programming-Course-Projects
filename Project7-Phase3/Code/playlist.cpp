#include "playlist.hpp"

using namespace std;


playlist::playlist(string _playlist_name, int _playlist_id, user* _playlist_user, bool _is_private_playlist)
{
	playlist_name = _playlist_name;
	playlist_id = _playlist_id;
	playlist_user = _playlist_user;
	is_private_playlist = _is_private_playlist;
}

bool playlist::show_a_user_playlists_name(bool can_show_private_playlist)
{
	if (!can_show_private_playlist && is_private_playlist)
		return false;

	if (is_private_playlist)
		cout << playlist_id << " " << playlist_name << " " << "private" << endl;
	else
		cout << playlist_id << " " << playlist_name << " " << "public" << endl;

	return true;
}

void playlist::add_song_to_playlist(song* curr_song)
{
	for(int i=0;i<playlist_songs.size();i++)
	{
		if(curr_song==playlist_songs[i])
			throw Server::Exception("Bad Request");
	}
	playlist_songs.push_back(curr_song);
}

void playlist::check_access_to_playlist()
{
	if (is_private_playlist)
		throw permission_denied();
}

void playlist::sort_by_id()
{
	for (int i = 0; i < playlist_songs.size(); i++)
	{
		for (int j = i + 1; j < playlist_songs.size(); j++)
		{
			if (playlist_songs[i]->get_id() > playlist_songs[j]->get_id())
				swap(playlist_songs[i], playlist_songs[j]);
		}
	}
}

void playlist::show_songs_of_playlist()
{
	if (playlist_songs.size() <= 0)
		throw empty_err();

	sort_by_id();

	for (int i = 0; i < playlist_songs.size(); i++)
		playlist_songs[i]->show_song_info();
}

void playlist::delete_song_from_playlist(string curr_song_id)
{
	for (int i = 0; i < playlist_songs.size(); i++)
	{
		if (curr_song_id == playlist_songs[i]->get_id())
		{
			playlist_songs[i]->remove_playlist_song_num();
			playlist_songs.erase(playlist_songs.begin() + i);
			return;
		}
	}
}

string playlist::get_songs_of_playlist()
{
	string body;
	for(int i=0;i<playlist_songs.size();i++)
	{
		body+="<a href='song?id=";
		body+=playlist_songs[i]->get_id();
		body+= "'target='_self'>";
		body+=playlist_songs[i]->get_song_info();
		body+= + "</a>";
		body+="<a href='deletesongfromplaylist?songid=";
		body+=playlist_songs[i]->get_id();
		body+="&playlistid=";
		body+=to_string(playlist_id);
		body+= "'target='_self'> DELETE </a> <br>";
	}
	return body;
}

string playlist::get_curr_playlist_info()
{
	string info;
	info += "<tr> <td>" + playlist_name + "</td> <td>";
	if(is_private_playlist)
		info+="Private </td> </tr> <br><br>";
	else
		info+="Public </td> </tr> <br><br>";
		
	return info;
}

string playlist::get_playlist_info()
{
	string info;
	
	info += to_string(playlist_id) + "." + playlist_name + "<br>";
	if(is_private_playlist)
		info+= "Private";
	else
		info+= "Public";
	info+="<br><br>";

	return info;
}