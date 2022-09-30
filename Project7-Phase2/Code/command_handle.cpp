#include "command_handle.hpp"

using namespace std;

command_handle::command_handle(bool _has_logged_in)
{
	new_utunes = new utunes(FIRST_PLAYLISTS_NUM,nullptr,false);
	has_logged_in = _has_logged_in;
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

	for (int i = 0; i < curr_separated_lines.size(); i++)
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



void command_handle::GET_songs_functions()
{
	if (!has_logged_in)
		throw permission_denied();

	if (separated_input.size() == GET_ALL_SONGS_NUM_INPUT)
		new_utunes->get_all_songs_info();

	else if (separated_input.size() == GET_ONE_SONGS_NUM_INPUT)
	{
		if (separated_input[FIRST_INPUT_FUN] != ID)
			throw bad_request();

		new_utunes->get_one_song_info(separated_input[ID_SONG_NUM_GET_SONGS]);
	}
	else
		throw bad_request();
}

void command_handle::GET_likes_errors()
{
	if (!has_logged_in)
		throw permission_denied();

	if (separated_input.size() != GET_LIKES_SIZE)
		throw bad_request();
}

void command_handle::GET_likes_function()
{
	GET_likes_errors();

	new_utunes->show_liked_songs();
}

void command_handle::GET_users_errors()
{
	if (!has_logged_in)
		throw permission_denied();

	if (separated_input.size() != GET_USERS_SIZE)
		throw bad_request();
}

void command_handle::GET_users_function()
{
	GET_users_errors();

	new_utunes->write_usernames();
}

void command_handle::GET_comments_errors()
{
	if (!has_logged_in)
		throw permission_denied();

	if (separated_input.size() != GET_COMMENTS_SIZE)
		throw bad_request();

	if (separated_input[FIRST_INPUT_FUN] != SONG_ID)
		throw bad_request();
}

void command_handle::GET_comments_function()
{
	GET_comments_errors();

	new_utunes->show_comments(separated_input[GET_COMMENT_SONG_ID]);
}

void command_handle::GET_playlists_errors()
{
	if (!has_logged_in)
		throw permission_denied();

	if (separated_input.size() != GET_PLAYLISTS_SIZE)
		throw bad_request();

	if (separated_input[FIRST_INPUT_FUN] != USERNAME)
		throw bad_request();
}

void command_handle::GET_playlists_function()
{
	GET_playlists_errors();

	new_utunes->show_a_user_playlists_name(separated_input[GET_PLAYLISTS_USERNAME]);
}

void command_handle::GET_playlists_songs_errors()
{
	if (!has_logged_in)
		throw permission_denied();

	if (separated_input.size() != GET_PLAYLISTS_SONGS_SIZE)
		throw bad_request();

	if (separated_input[FIRST_INPUT_FUN] != PLAYLIST_ID)
		throw bad_request();
}

void command_handle::GET_playlists_songs_function()
{
	GET_playlists_songs_errors();

	new_utunes->show_songs_of_playlist(separated_input[FIRST_INPUT]);
}

void command_handle::GET_similar_users_errors()
{
	if (!has_logged_in)
		throw permission_denied();

	if (separated_input.size() != GET_SIMILAR_USERS_SIZE)
		throw bad_request();

	if (separated_input[FIRST_INPUT_FUN] != COUNT)
		throw bad_request();

	if (stoi(separated_input[FIRST_INPUT]) <= 0)
		throw bad_request();
}

void command_handle::GET_similar_users_function()
{
	GET_similar_users_errors();

	new_utunes->get_similar_users(stoi(separated_input[FIRST_INPUT]));
}

void command_handle::GET_recommeded_errors()
{
	if (!has_logged_in)
		throw permission_denied();

	if (separated_input.size() != GET_RECOMMEDED_SIZE)
		throw bad_request();

	if (separated_input[FIRST_INPUT_FUN] != COUNT)
		throw bad_request();

	if (stoi(separated_input[FIRST_INPUT]) <= 0)
		throw bad_request();
}

void command_handle::GET_recommeded_function()
{
	GET_recommeded_errors();

	new_utunes->get_recommeded_songs(stoi(separated_input[FIRST_INPUT]));
}

void command_handle::GET_functions()
{
	if (separated_input[FUN_NUM_INPUT] == SONGS)
		GET_songs_functions();

	else if (separated_input[FUN_NUM_INPUT] == LIKES)
		GET_likes_function();

	else if (separated_input[FUN_NUM_INPUT] == USERS)
		GET_users_function();

	else if (separated_input[FUN_NUM_INPUT] == COMMENTS)
		GET_comments_function();

	else if (separated_input[FUN_NUM_INPUT] == PLAYLISTS)
		GET_playlists_function();

	else if (separated_input[FUN_NUM_INPUT] == PLAYLISTS_SONGS)
		GET_playlists_songs_function();

	else if (separated_input[FUN_NUM_INPUT] == SIMILAR_USERS)
		GET_similar_users_function();

	else if (separated_input[FUN_NUM_INPUT] == RECOMMENDED)
		GET_recommeded_function();

	else
		throw not_found();
}



void command_handle::POST_signup_errors()
{
	if (has_logged_in)
		throw permission_denied();

	if (separated_input.size() != POST_SIGNUP_SIZE)
		throw bad_request();

	if (separated_input[FIRST_INPUT_FUN] != EMAIL || separated_input[SECOND_INPUT_FUN] != USERNAME
		|| separated_input[THIRD_INPUT_FUN] != PASSWORD)
		throw bad_request();
}

void command_handle::POST_signup_function()
{
	POST_signup_errors();

	new_utunes->check_sign_up_errors(separated_input);
	new_utunes->add_new_user(separated_input);
	has_logged_in = true;
}

void command_handle::POST_login_errors()
{
	if (has_logged_in)
		throw permission_denied();

	if (separated_input.size() != POST_LOGIN_SIZE)
		throw bad_request();

	if (separated_input[FIRST_INPUT_FUN] != EMAIL || separated_input[SECOND_INPUT_FUN] != PASSWORD)
		throw bad_request();
}

void command_handle::POST_login_function()
{
	POST_login_errors();

	new_utunes->login_user(separated_input[EMAIL_NUM_LOGIN], separated_input[PASS_NUM_LOGIN]);
	has_logged_in = true;
}

void command_handle::POST_logout_errors()
{
	if (!has_logged_in)
		throw permission_denied();

	if (separated_input.size() != POST_LOGOUT_SIZE)
		throw bad_request();
}

void command_handle::POST_logout_function()
{
	POST_logout_errors();

	new_utunes->logout_user();
	has_logged_in = false;
}

void command_handle::POST_likes_errors()
{
	if (!has_logged_in)
		throw permission_denied();

	if (separated_input.size() != POST_LIKES_SIZE)
		throw bad_request();

	if (separated_input[FIRST_INPUT_FUN] != ID)
		throw bad_request();
}

void command_handle::POST_likes_function()
{
	POST_likes_errors();

	new_utunes->like_a_song(separated_input[ID_SONG_NUM_POST_LIKES]);
}

void command_handle::POST_comments_errors()
{
	if (!has_logged_in)
		throw permission_denied();

	if (separated_input.size() != POST_COMMENTS_SIZE)
		throw bad_request();

	if (separated_input[FIRST_INPUT_FUN] != SONG_ID || separated_input[SECOND_INPUT_FUN] != TIME || separated_input[THIRD_INPUT_FUN] != COMMENT)
		throw bad_request();
}

void command_handle::POST_comments_function()
{
	POST_comments_errors();

	new_utunes->add_comment_to_song(separated_input[POST_COMMENT_SONG_ID],
		separated_input[POST_COMMENT_TIME], separated_input[POST_COMMENT_COMMENT]);
}

void command_handle::POST_playlists_errors()
{
	if (!has_logged_in)
		throw permission_denied();

	if (separated_input.size() != POST_PLAYLISTS_SIZE)
		throw bad_request();
}

void command_handle::POST_playlists_function()
{
	POST_playlists_errors();

	if (separated_input[POST_PLAYLISTS_PRIVACY] == PRIVATE)
		new_utunes->make_new_playlist(separated_input[POST_PLAYLISTS_NAME], true);

	else if (separated_input[POST_PLAYLISTS_PRIVACY] == PUBLIC)
		new_utunes->make_new_playlist(separated_input[POST_PLAYLISTS_NAME], false);

	else
		throw bad_request();
}

void command_handle::POST_playlists_songs_errors()
{
	if (!has_logged_in)
		throw permission_denied();

	if (separated_input.size() != POST_PLAYLISTS_SONGS_SIZE)
		throw bad_request();

	if (separated_input[FIRST_INPUT_FUN] != PLAYLIST_ID || separated_input[SECOND_INPUT_FUN] != SONG_ID)
		throw bad_request();
}

void command_handle::POST_playlists_songs_function()
{
	POST_playlists_songs_errors();

	new_utunes->add_song_to_playlist(separated_input[POST_PLAYLISTS_SONGS_PLAYLIST_ID], separated_input[POST_PLAYLISTS_SONGS_SONG_ID]);
}

void command_handle::POST_artist_filter()
{
	string curr_artist;
	for (int i = START_ARTIST_FILTER_STRING; i < separated_input.size(); i++)
	{
		curr_artist += separated_input[i];
		if (i != (separated_input.size() - 1))
			curr_artist += " ";
	}

	new_utunes->filter_with_artist(curr_artist);
}

void command_handle::POST_filters_errors()
{
	if (!has_logged_in)
		throw permission_denied();

	if (separated_input.size() <= TYPE_OF_FILTER)
		throw bad_request();

	if (separated_input[TYPE_OF_FILTER] == MIN_YEAR && separated_input.size() != POST_FILTERS_YEAR_SIZE)
		throw bad_request();

	else if (separated_input[TYPE_OF_FILTER] == MIN_LIKE && separated_input.size() != POST_FILTERS_LIKE_SIZE)
		throw bad_request();

	else if (separated_input[TYPE_OF_FILTER] == ARTIST && separated_input.size() < POST_FILTERS_ARTIST_SIZE)
		throw bad_request();
}

void command_handle::POST_filters_function()
{
	POST_filters_errors();

	if (separated_input[TYPE_OF_FILTER] == ARTIST)
		POST_artist_filter();

	else if (separated_input[TYPE_OF_FILTER] == MIN_YEAR)
	{
		if (separated_input[SECOND_INPUT_FUN] != MAX_YEAR)
			throw bad_request();

		new_utunes->filter_with_year(separated_input[FIRST_INPUT], separated_input[SECOND_INPUT]);
	}
	else if (separated_input[TYPE_OF_FILTER] == MIN_LIKE)
	{
		if (separated_input[SECOND_INPUT_FUN] != MAX_LIKE)
			throw bad_request();

		new_utunes->filter_with_like(separated_input[FIRST_INPUT], separated_input[SECOND_INPUT]);
	}
	else
		throw bad_request();
}

void command_handle::POST_functions()
{
	if (separated_input[FUN_NUM_INPUT] == SIGNUP)
	{
		POST_signup_function();
		cout << OK << endl;
	}

	else if (separated_input[FUN_NUM_INPUT] == LOGIN)
	{
		POST_login_function();
		cout << OK << endl;
	}

	else if (separated_input[FUN_NUM_INPUT] == LOGOUT)
	{
		POST_logout_function();
		cout << OK << endl;
	}

	else if (separated_input[FUN_NUM_INPUT] == LIKES)
	{
		POST_likes_function();
		cout << OK << endl;
	}

	else if (separated_input[FUN_NUM_INPUT] == COMMENTS)
	{
		POST_comments_function();
		cout << OK << endl;
	}

	else if (separated_input[FUN_NUM_INPUT] == PLAYLISTS_SONGS)
	{
		POST_playlists_songs_function();
		cout << OK << endl;
	}

	else if (separated_input[FUN_NUM_INPUT] == FILTERS)
	{
		POST_filters_function();
		cout << OK << endl;
	}

	else if (separated_input[FUN_NUM_INPUT] == PLAYLISTS)
		POST_playlists_function();

	else
		throw not_found();

}




void command_handle::DELETE_likes_errors()
{
	if (!has_logged_in)
		throw permission_denied();

	if (separated_input.size() != DELETE_LIKE_SIZE)
		throw bad_request();

	if (separated_input[DELETE_LIKE_ID_LOC] != ID)
		throw bad_request();
}

void command_handle::DELETE_likes_fuction()
{
	DELETE_likes_errors();

	new_utunes->delete_liked_song(separated_input[ID_SONG_NUM_DEL_LIKES]);
}

void command_handle::DELETE_playlists_songs_errors()
{
	if (!has_logged_in)
		throw permission_denied();

	if (separated_input.size() != DELETE_PLAYLISTS_SONGS_SIZE)
		throw bad_request();

	if ((separated_input[FIRST_INPUT_FUN] != PLAYLIST_ID) || (separated_input[SECOND_INPUT_FUN] != SONG_ID))
		throw bad_request();
}

void command_handle::DELETE_playlists_songs_function()
{
	DELETE_playlists_songs_errors();

	new_utunes->delete_song_from_playlist(separated_input[FIRST_INPUT],separated_input[SECOND_INPUT]);
}

void command_handle::DELETE_filters_errors()
{
	if (!has_logged_in)
		throw permission_denied();

	if (separated_input.size() != DELETE_FILTERS_SIZE)
		throw bad_request();
}

void command_handle::DELETE_filters_function()
{
	DELETE_filters_errors();

	new_utunes->delete_filters();
}

void command_handle::DELETE_functions()
{
	if (separated_input[FUN_NUM_INPUT] == LIKES)
	{
		DELETE_likes_fuction();
		cout << OK << endl;
	}
	else if (separated_input[FUN_NUM_INPUT] == PLAYLISTS_SONGS)
	{
		DELETE_playlists_songs_function();
		cout << OK << endl;
	}
	else if (separated_input[FUN_NUM_INPUT] == FILTERS)
	{
		DELETE_filters_function();
		cout << OK << endl;
	}
	else
		throw not_found();
}



void command_handle::check_first_input_errors()
{
	if ((separated_input.size() <= 1) || (separated_input.size()==3))
		throw bad_request();

	if (separated_input.size() > 3)
	{
		if (separated_input[QUESTION_MARK_LOC] != QUESTION_MARK)
			throw bad_request();
	}
}

void command_handle::run(char songs_list[], char liked_songs_list[])
{
	save_songs_in_program(songs_list);

	save_liked_songs_in_program(liked_songs_list);

	string input;
	while (getline(cin, input))
	{
		separated_input = seperate_strings(input, SEPARATOR_CHAR);
		try
		{
			check_first_input_errors();

			if (separated_input[POST_GET_DEL_NUM_INPUT] == GET)
				GET_functions();

			else if (separated_input[POST_GET_DEL_NUM_INPUT] == POST)
				POST_functions();

			else if (separated_input[POST_GET_DEL_NUM_INPUT] == DELETE)
				DELETE_functions();

			else
				throw bad_request();
		}
		catch (exception& errors)
		{
			cout << errors.what() << endl;
		}
	}
}