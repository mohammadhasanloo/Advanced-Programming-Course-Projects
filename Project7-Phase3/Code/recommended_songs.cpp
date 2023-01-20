#include "recommended_songs.hpp"


using namespace std;



recommended_songs::recommended_songs(vector <user*> _users, user* _user_logged_in, vector <song*> _songs, int _count)
{
	users = _users;
	user_logged_in = _user_logged_in;
	songs = _songs;
	count = _count;
}

bool recommended_songs::check_user_liked_curr_song(song* curr_song,user* curr_user)
{
	return curr_user->check_liked_curr_song(curr_song);
}

vector <bool> recommended_songs::make_list_of_liked_songs(user* curr_user)
{
	vector <bool> liked_songs;

	for (int i = 0; i < songs.size(); i++)
	{
		if (check_user_liked_curr_song(songs[i], curr_user))
			liked_songs.push_back(true);
		else
			liked_songs.push_back(false);
	}

	return liked_songs;
}

double recommended_songs::calculate_similarity_between_users(int user1, int user2, const vector <vector <bool>>& users_and_songs_matrix)
{
	double similarity_songs_num = 0;

	for (int i = 0; i < songs.size(); i++)
	{
		if ((users_and_songs_matrix[user1][i] == users_and_songs_matrix[user2][i]) && (users_and_songs_matrix[user1][i]==true))
			similarity_songs_num++;
	}

	return (similarity_songs_num / songs.size()) * 100;
}

vector <double> recommended_songs::make_list_of_front_side_users(int user1, const vector <vector <bool>>& users_and_songs_matrix)
{
	vector <double> similarity_user1_and_user2;

	for (int i = 0; i < users.size(); i++)
		similarity_user1_and_user2.push_back(calculate_similarity_between_users(user1, i, users_and_songs_matrix));

	return similarity_user1_and_user2;
}

int recommended_songs::find_logged_in_user()
{
	for (int i = 0; i < users.size(); i++)
	{
		if (users[i] == user_logged_in)
			return i;
	}
}

vector <pair <double, user*>> recommended_songs::make_pairs_of_users_similarity(int logged_in_user_num,
	const vector <double>& users_similarity_matrix)
{
	vector <pair <double, user*>> similarity_percent;

	for (int i = 0; i < users.size(); i++)
	{
		pair <double, user*> curr_similarity_percent;
		if (i != logged_in_user_num)
		{
			curr_similarity_percent.first = users_similarity_matrix[i];
			curr_similarity_percent.second = users[i];
			similarity_percent.push_back(curr_similarity_percent);
		}
	}
	return similarity_percent;
}

void recommended_songs::print_users_similarity(const vector <pair <double, user*>> &similarity_percent)
{
	for (int i = 0; ((i < count) && (i != similarity_percent.size())); i++)
		cout << setprecision(PRECISION_NUMBER) << fixed << similarity_percent[i].first << "% " <<
		similarity_percent[i].second->get_username() << endl;
}

bool recommended_songs::has_swap_condition(pair <double, user*> pre, pair <double, user*> curr)
{
	if (pre.first < curr.first)
		return true;

	if (pre.first == curr.first && pre.second->get_username() > curr.second->get_username())
		return true;

	return false;
}

vector <pair <double, user*>> recommended_songs::sort_similarity_percent(vector <pair <double, user*>> similarity_percent)
{
	for (int i = 0; i < similarity_percent.size(); i++) 
		for (int j = i + 1; j < similarity_percent.size(); j++)
			if (has_swap_condition(similarity_percent[i], similarity_percent[j])) swap(similarity_percent[i], similarity_percent[j]);

	return similarity_percent;
}

vector <pair <double, user*>> recommended_songs::make_other_users_similarity_percent(int logged_in_user_num, const vector <double> & users_similarity_matrix)
{
	vector <pair <double, user*>> similarity_percent= make_pairs_of_users_similarity(logged_in_user_num, users_similarity_matrix);

	similarity_percent = sort_similarity_percent(similarity_percent);

	return similarity_percent;
}

void recommended_songs::similar_users_function()
{
	vector <vector <bool>> users_and_songs_matrix;
	vector <vector <double>> users_similarity_matrix;

	for (int i = 0; i < users.size(); i++)
		users_and_songs_matrix.push_back(make_list_of_liked_songs(users[i]));

	for (int i = 0; i < users.size(); i++)
		users_similarity_matrix.push_back(make_list_of_front_side_users(i, users_and_songs_matrix));

	int logged_in_user_num=find_logged_in_user();

	vector <pair <double, user*>> similarity_percent=make_other_users_similarity_percent(logged_in_user_num,
		users_similarity_matrix[logged_in_user_num]);

	print_users_similarity(similarity_percent);
}

pair <song*, double> recommended_songs::calculate_confidence_one_by_one(int logged_in_user_num, int curr_song,
	const vector <double>& users_similarity_matrix,const vector < vector <bool>>& users_and_songs_matrix)
{
	pair <song*, double> song_confidence;
	song_confidence.first = songs[curr_song];
	double confidence = 0;

	for (int i = 0; i < users.size(); i++)
	{
		if (users_and_songs_matrix[i][curr_song] && (i != logged_in_user_num))
			confidence += users_similarity_matrix[i];
	}
	song_confidence.second = confidence / (users.size() - 1);

	return song_confidence;
}

bool recommended_songs::check_swap(pair <song*, double> pre, pair <song*, double> curr)
{
	if (pre.second < curr.second)
		return true;

	if (pre.second == curr.second && pre.first->get_id() > curr.first->get_id())
		return true;

	return false;
}

vector <pair <song*, double>> recommended_songs::sort_recommended_songs(vector <pair <song*, double>> confidence)
{
	for (int i = 0; i < confidence.size(); i++)
		for (int j = i + 1; j < confidence.size(); j++)
			if (check_swap(confidence[i], confidence[j])) swap(confidence[i], confidence[j]);

	return confidence;
}

bool recommended_songs::is_song_liked(song* curr_song)
{
	return user_logged_in->is_song_liked(curr_song);
}

vector <pair <song*, double>> recommended_songs::calculate_confidence(int logged_in_user_num, const vector <double>& users_similarity_matrix,
	const vector <vector <bool>> &users_and_songs_matrix)
{
	vector <pair <song*, double>> confidence;

	for (int i = 0; i < songs.size(); i++)
	{
		if(!is_song_liked(songs[i]))
		confidence.push_back(calculate_confidence_one_by_one(logged_in_user_num, i, users_similarity_matrix, users_and_songs_matrix));
	}

	confidence = sort_recommended_songs(confidence);

	return confidence;
}

string recommended_songs::print_recommended_songs(const vector <pair <song*, double>>& songs_confidence)
{
	string body;
	for(int i = 0; ((i < count) && (i != songs_confidence.size())); i++)
	{
		body+=songs_confidence[i].first->get_recommended_song_info() + "<td>" + to_string(songs_confidence[i].second) + " % </td> <td>";
		body+="<a href='song?id=";
		body+=songs_confidence[i].first->get_id();
		body+="'> Link </a> </td> </tr> <br>";
	}
	return body;
}

string recommended_songs::recommeded_songs_function()
{
	vector <vector <bool>> users_and_songs_matrix;
	vector <vector <double>> users_similarity_matrix;

	for (int i = 0; i < users.size(); i++)
		users_and_songs_matrix.push_back(make_list_of_liked_songs(users[i]));

	for (int i = 0; i < users.size(); i++)
		users_similarity_matrix.push_back(make_list_of_front_side_users(i, users_and_songs_matrix));

	int logged_in_user_num = find_logged_in_user();

	vector <pair <song*, double>> songs_confidence=calculate_confidence(logged_in_user_num,
		users_similarity_matrix[logged_in_user_num], users_and_songs_matrix);

	string body=print_recommended_songs(songs_confidence);

	return body;
}