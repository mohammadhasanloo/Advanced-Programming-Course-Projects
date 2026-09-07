#include "command_handle.hpp"

using namespace std;

command_handle::command_handle()
{
	new_utunes = new utunes(FIRST_PLAYLISTS_NUM,nullptr,false);
}

command_handle::~command_handle()
{
	utunes* pre = new_utunes;
	new_utunes = nullptr;
	delete pre;
}

vector <string> command_handle::seperate_strings(string one_line, char character)
{
	stringstream current(one_line);
	vector <string> result;

	while (current.good())
	{
		string substr;
		getline(current, substr, character);
		result.push_back(substr);
	}
	return result;
}

map <string, int> command_handle::save_column(const vector <string>& curr_separated_lines)
{
	map <string, int> column;

	for (size_t i = 0; i < curr_separated_lines.size(); i++)
		column[curr_separated_lines[i]] = i;
		
	return column;
}

void command_handle::save_songs_in_program(char songs_list[])
{
	ifstream input_file_csv(songs_list);
	string one_line;
	getline(input_file_csv, one_line);

	vector <string> separated_line = seperate_strings(one_line, SEPARATOR_CHAR_CSV);
	map <string, int> column = save_column(separated_line);

	while (getline(input_file_csv, one_line))
	{
		vector <string> separated_lines = seperate_strings(one_line, SEPARATOR_CHAR_CSV);
		new_utunes->read_files(separated_lines, column);
	}
}

void command_handle::save_liked_songs_in_program(char liked_songs_list[])
{
	ifstream input_file_csv(liked_songs_list);
	string one_line;
	getline(input_file_csv, one_line);

	vector <string> separated_line = seperate_strings(one_line, SEPARATOR_CHAR_CSV);
	map <string, int> column = save_column(separated_line);

	while (getline(input_file_csv, one_line))
	{
		vector <string> separated_lines = seperate_strings(one_line, SEPARATOR_CHAR_CSV);
		new_utunes->read_liked_songs_files(separated_lines, column);
	}
}






std::string page_head(const std::string& title)
{
	return "<!DOCTYPE html><html lang='en'><head>"
	       "<meta charset='utf-8'>"
	       "<meta name='viewport' content='width=device-width, initial-scale=1'>"
	       "<title>" + title + " - uTunes</title>"
	       "<link rel='stylesheet' href='/styles.css'>"
	       "</head><body>"
	       "<header class='masthead'><div class='inner'>"
	       "<a class='wordmark' href='/home'>uTunes</a>"
	       "<nav>"
	       "<a href='/home'>Songs</a>"
	       "<a href='/likedsongs'>Liked</a>"
	       "<a href='/playlists'>Playlists</a>"
	       "<a href='/login'>Log out</a>"
	       "</nav>"
	       "</div></header><main>";
}

std::string page_foot()
{
	return "</main></body></html>";
}

Response* signup_handler::callback(Request* req)
{
	string username=req->getBodyParam("username");
	string email=req->getBodyParam("email");
	string password=req->getBodyParam("password");

	if(password=="" || username=="" || email=="")
		throw Server::Exception("Empty");

	new_utunes->check_sign_up_errors(username, email, password);
	new_utunes->add_new_user(username, email, password);

	Response* res=Response::redirect("/home");
	res->setSessionId(username);
	return res;
}

Response* login_handler::callback(Request* req)
{
	string username=req->getBodyParam("username");
	string password=req->getBodyParam("password");

	new_utunes->login_user(username, password);

	Response* res=Response::redirect("/home");
	res->setSessionId(username);
	return res;
}

string home_handler::add_filter_html()
{
	string body;
	ifstream input_file_csv("pages/Filter.html");
	string one_line;
	while(getline(input_file_csv, one_line))
		body+=one_line;

	return body;	
}

Response* home_handler::callback(Request*)
{
	Response* res=new Response;

	res->setHeader("Content-Type", "text/html");
	string body;
	body += page_head("Songs");
  	body += "<div class='panel'>" + add_filter_html() + "</div>";
	body += "<h1>Songs</h1>";
	body += "<div class='songs'>" + new_utunes->get_songs() + "</div>";
  	body += page_foot();
  	res->setBody(body);

	return res;
}

Response* song_handler::callback(Request* req)
{
	Response* res=new Response;
	res->setHeader("Content-Type", "text/html");
	string song_id=req->getQueryParam("id");

	string body;
	body += page_head("Song");
  	body += "<h2>Song info</h2>";
	body += new_utunes->get_curr_song_info(song_id);  
  	body += page_foot();
  	res->setBody(body);

	return res;
}

Response* liked_songs_handler::callback(Request* req)
{
	Response* res=new Response;
	res->setHeader("Content-Type", "text/html");
	string username=req->getSessionId();
	if(!new_utunes->is_known_user(username))
		return Response::redirect("/login");

	string body;
	body += page_head("Liked songs");
  	body += "<h1>Your Favourite Songs</h1>";
	body += new_utunes->get_liked_songs(username);  
  	body += page_foot();
  	res->setBody(body);

	return res;
}

Response* playlists_handler::callback(Request* req)
{
	Response* res=new Response;
	res->setHeader("Content-Type", "text/html");
	string username=req->getSessionId();
	if(!new_utunes->is_known_user(username))
		return Response::redirect("/login");

	string body;
	body += page_head("Playlists");
  	body += "<h1>Your Playlists</h1>";
	body += new_utunes->show_playlists(username);
	body += "<div class='actions'>"
	        "<a class='button primary' href='/createplaylist'>New playlist</a>"
	        "</div>";
  	body += page_foot();
  	res->setBody(body);

	return res;
}

Response* create_playlist_handler::callback(Request* req)
{
	string username=req->getSessionId();
	if(!new_utunes->is_known_user(username))
		return Response::redirect("/login");
	string playlist_name=req->getBodyParam("name");
	string public_or_private=req->getBodyParam("publicorprivate");

	if(playlist_name=="")
		throw Server::Exception("Empty");

	if (public_or_private==PRIVATE)
		new_utunes->make_new_playlist(playlist_name, true);

	else if (public_or_private == PUBLIC)
		new_utunes->make_new_playlist(playlist_name, false);


	Response* res=Response::redirect("/playlists");
	return res;
}

Response* curr_playlist_handler::callback(Request* req)
{
	string username=req->getSessionId();
	if(!new_utunes->is_known_user(username))
		return Response::redirect("/login");

	Response* res=new Response;
	res->setHeader("Content-Type", "text/html");
	string playlist_id=req->getQueryParam("id");

	string body;
	body += page_head("Playlist");
  	body += "<h2>Playlist's Songs info</h2>";
	body += new_utunes->get_playlist_info(playlist_id);
	body += "<br> <br>";
	body += new_utunes->get_playlist_songs(playlist_id);
	body += "<br> <div style='background-color: rgb(207, 71, 30); padding: 1%; max-width: 300px; border-radius: 3px; margin: auto; '>  <form action='addsong?playlistid=";  
	body += playlist_id;
	body += "' method='post'> <p>Add Song To Your Playlist</p>  <input name='songid' type='text' placeholder='Song Id' style='display:block; margin: auto; margin-bottom: 10px; padding: 5px; width: 94%;' />   <button type='submit' style='display:block; width: 100%; padding: 7px;'>Add Song</button>  </form>  </div> ";  
  	body += page_foot();
  	res->setBody(body);

	return res;
}

Response* unlike_handler::callback(Request* req)
{
	string username=req->getSessionId();
	if(!new_utunes->is_known_user(username))
		return Response::redirect("/login");
	string song_id=req->getQueryParam("id");
	string address="/" + req->getQueryParam("address");

	if(address=="/song")
		address += "?id=" + song_id;

	new_utunes->delete_liked_song(song_id, username);

	Response* res=Response::redirect(address);
	return res;
}

Response* add_song_to_playlist::callback(Request* req)
{
	string song_id=req->getBodyParam("songid");
	string playlist_id=req->getQueryParam("playlistid");

	
	new_utunes->add_song_to_playlist(playlist_id, song_id);


	Response* res=Response::redirect("/currplaylist?id=" + playlist_id);
	return res;
}

Response* delete_song_from_playlist::callback(Request* req)
{
	string song_id=req->getQueryParam("songid");
	string playlist_id=req->getQueryParam("playlistid");

	new_utunes->delete_song_from_playlist(playlist_id,song_id);

	Response* res=Response::redirect("/currplaylist?id=" + playlist_id);
	return res;
}

Response* like_handler::callback(Request* req)
{
	string song_id=req->getQueryParam("id");
	string address="/" + req->getQueryParam("address");

	if(address=="/song")
		address += "?id=" + song_id;

	new_utunes->like_a_song(song_id);

	Response* res=Response::redirect(address);
	return res;
}

void filter_handler::year_filter_fun(string min_year, string max_year)
{
	if(min_year=="" || max_year=="")
		throw Server::Exception("Empty");

	new_utunes->filter_with_year(min_year, max_year);
}

void filter_handler::like_filter_fun(string min_like, string max_like)
{
	if(min_like=="" || max_like=="")
		throw Server::Exception("Empty");

	new_utunes->filter_with_like(min_like, max_like);
}

void filter_handler::artist_filter_fun(string artist_name)
{
	if(artist_name=="")
		throw Server::Exception("Empty");

	new_utunes->filter_with_artist(artist_name);
}

void filter_handler::delete_filters()
{
	new_utunes->delete_filters();
}

Response* filter_handler::callback(Request* req)
{
	string filter_type=req->getQueryParam("type");

	if(filter_type==YEAR)
		year_filter_fun(req->getBodyParam("minyear"), req->getBodyParam("maxyear"));

	if(filter_type==LIKE)
		like_filter_fun(req->getBodyParam("minlike"), req->getBodyParam("maxlike"));

	if(filter_type==ARTIST)	
		artist_filter_fun(req->getBodyParam("artistname"));

	if(filter_type==DELETE)	
		delete_filters();

	Response* res=Response::redirect("/home");
	return res;
}




void command_handle::run(char songs_list[], char liked_songs_list[])
{
	save_songs_in_program(songs_list);

	save_liked_songs_in_program(liked_songs_list);

	try
	{
	MyServer server(PORT_NUM);
	server.get("/styles.css", new ShowPage("static/styles.css"));
	server.get("/signup", new ShowPage("pages/Signup.html"));
	server.post("/signup", new signup_handler(new_utunes));
	server.get("/login", new ShowPage("pages/login.html"));
	server.post("/login", new login_handler(new_utunes));
	server.get("/home", new home_handler(new_utunes));
	server.get("/song", new song_handler(new_utunes));
	server.get("/likedsongs", new liked_songs_handler(new_utunes));
	server.get("/playlists", new playlists_handler(new_utunes));
	server.get("/createplaylist", new ShowPage("pages/createplaylist.html"));
	server.post("/createplaylist", new create_playlist_handler(new_utunes));
	server.get("/currplaylist", new curr_playlist_handler(new_utunes));
	server.get("/unlike", new unlike_handler(new_utunes));
	server.post("/addsong", new add_song_to_playlist(new_utunes));
	server.get("/deletesongfromplaylist", new delete_song_from_playlist(new_utunes));
	server.get("/like", new like_handler(new_utunes));
	server.post("/filter", new filter_handler(new_utunes));

	server.run();
	}
	catch (Server::Exception e)
	{
		cout << e.getMessage() << endl;
	}
}