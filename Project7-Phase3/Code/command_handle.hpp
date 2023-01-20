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
#include "my_server.hpp"
#include "server/server.hpp"


const char SEPARATOR_CHAR_CSV = ',';
const char SEPARATOR_CHAR = ' ';
const int FIRST_PLAYLISTS_NUM = 1;
const int PORT_NUM=5030;
const std::string table_design_blue = " <head> <style> table { width:100%; }table, th, td { border: 1px solid black; border-collapse: collapse; } th, td { padding: 15px; text-align: left;} #t01 tr:nth-child(even) { background-color: #eee; } #t01 tr:nth-child(odd) { background-color: #fff; } #t01 th { background-color: Blue; color: white; } </style> </head> ";
const std::string table_design_red = " <head> <style> table { width:100%; }table, th, td { border: 1px solid black; border-collapse: collapse; } th, td { padding: 15px; text-align: left;} #t01 tr:nth-child(even) { background-color: #eee; } #t01 tr:nth-child(odd) { background-color: #fff; } #t01 th { background-color: Red; color: white; } </style> </head> ";
const std::string PRIVATE = "private";
const std::string PUBLIC = "public";
const std::string YEAR="year";
const std::string LIKE="like";
const std::string DELETE="delete";





class login_handler : public RequestHandler
 {
public:	
  login_handler(utunes* _new_utunes) { 
	 new_utunes= _new_utunes;
	 }

  Response *callback(Request *);

private:
	utunes* new_utunes;
};

class signup_handler : public RequestHandler
 {
public:	
  signup_handler(utunes* _new_utunes) { 
	 new_utunes= _new_utunes;
	 }

  Response *callback(Request *);

private:
	utunes* new_utunes;
};

class home_handler : public RequestHandler
 {
public:	
  home_handler(utunes* _new_utunes) { 
	 new_utunes= _new_utunes;
	 }

  Response *callback(Request *);
  std::string add_filter_html();

private:
	utunes* new_utunes;
};

class song_handler : public RequestHandler
 {
public:	
  song_handler(utunes* _new_utunes) { 
	 new_utunes= _new_utunes;
	 }

  Response *callback(Request *);

private:
	utunes* new_utunes;
};

class liked_songs_handler : public RequestHandler
{
public:	
  liked_songs_handler(utunes* _new_utunes) { 
	 new_utunes= _new_utunes;
	 }

  Response *callback(Request *);

private:
	utunes* new_utunes;
};

class playlists_handler : public RequestHandler
{
public:	
  playlists_handler(utunes* _new_utunes) { 
	 new_utunes= _new_utunes;
	 }

  Response *callback(Request *);

private:
	utunes* new_utunes;
};

class create_playlist_handler : public RequestHandler
{
public:	
  create_playlist_handler(utunes* _new_utunes) { 
	 new_utunes= _new_utunes;
	 }

  Response *callback(Request *);

private:
	utunes* new_utunes;
};

class curr_playlist_handler : public RequestHandler
{
public:	
  curr_playlist_handler(utunes* _new_utunes) { 
	 new_utunes= _new_utunes;
	 }

  Response *callback(Request *);

private:
	utunes* new_utunes;
};

class unlike_handler : public RequestHandler
{
public:	
  unlike_handler(utunes* _new_utunes) { 
	 new_utunes= _new_utunes;
	 }

  Response *callback(Request *);

private:
	utunes* new_utunes;
};

class add_song_to_playlist : public RequestHandler
{
public:	
  add_song_to_playlist(utunes* _new_utunes) { 
	 new_utunes= _new_utunes;
	 }

  Response *callback(Request *);

private:
	utunes* new_utunes;
};

class delete_song_from_playlist : public RequestHandler
{
public:	
  delete_song_from_playlist(utunes* _new_utunes) { 
	 new_utunes= _new_utunes;
	 }

  Response *callback(Request *);

private:
	utunes* new_utunes;
};

class like_handler : public RequestHandler
{
public:	
  like_handler(utunes* _new_utunes) { 
	 new_utunes= _new_utunes;
	 }

  Response *callback(Request *);

private:
	utunes* new_utunes;
};

class filter_handler : public RequestHandler
{
public:	
  filter_handler(utunes* _new_utunes) { 
	 new_utunes= _new_utunes;
	 }

  Response *callback(Request *);
  void year_filter_fun(std::string min_year, std::string max_year);
  void like_filter_fun(std::string min_like, std::string max_like);
  void artist_filter_fun(std::string artist_name);
  void delete_filters();

private:
	utunes* new_utunes;
};


class command_handle
{
public:
	command_handle();
	~command_handle();
	void run(char songs_list[], char liked_songs_list[]);
	std::vector<std::string> seperate_strings(std::string oneline, char character);
	std::map<std::string, int> save_column(const std::vector <std::string>& separatedline);
	void save_songs_in_program(char songs_list[]);
	void save_liked_songs_in_program(char liked_songs_list[]);

private:
	utunes* new_utunes;
};




#endif 
