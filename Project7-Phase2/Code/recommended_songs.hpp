#ifndef RECOMMENDED_SONGS_H
#define RECOMMENDED_SONGS_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "user.hpp"
#include "song.hpp"


const int PRECISION_NUMBER = 2;

class recommended_songs
{
public:
	recommended_songs(std::vector <user*> _users, user* _user_logged_in, std::vector <song*> _songs, int _count);
	void similar_users_function();
	void recommeded_songs_function();
	std::vector <bool> make_list_of_liked_songs(user* curr_user);
	bool check_user_liked_curr_song(song* curr_song, user* curr_user);
	std::vector <double> make_list_of_front_side_users(int user1, const std::vector <std::vector <bool>>& users_and_songs_matrix);
	double calculate_similarity_between_users(int user1, int user2, const std::vector <std::vector <bool>>& users_and_songs_matrix);
	int find_logged_in_user();
	std::vector <std::pair <double, user*>> make_other_users_similarity_percent(int logged_in_user_num,
		const std::vector <double>& users_similarity_matrix);
	std::vector <std::pair <double, user*>> make_pairs_of_users_similarity(int logged_in_user_num,
		const std::vector <double>& users_similarity_matrix);
	std::vector <std::pair <double, user*>> sort_similarity_percent(std::vector <std::pair <double, user*>> similarity_percent);
	bool has_swap_condition(std::pair <double, user*> pre, std::pair <double, user*> curr);
	void print_users_similarity(const std::vector <std::pair <double, user*>>& similarity_percent);
	std::vector <std::pair <song*, double>> calculate_confidence(int logged_in_user_num, const std::vector <double>& users_similarity_matrix,
		const std::vector <std::vector <bool>>& users_and_songs_matrix);
	std::pair <song*, double> calculate_confidence_one_by_one(int logged_in_user_num, int curr_song,
		const std::vector <double>& users_similarity_matrix, const std::vector <std::vector<bool>>& users_and_songs_matrix);
	bool check_swap(std::pair <song*, double> pre, std::pair <song*, double> curr);
	std::vector <std::pair <song*, double>> sort_recommended_songs(std::vector <std::pair <song*, double>> confidence);
	void print_recommended_songs(const std::vector <std::pair <song*, double>>& songs_confidence);
	bool is_song_liked(song* curr_song);

private:
	user* user_logged_in;
	std::vector <user*> users;
	std::vector <song*> songs;
	int count;
};


#endif