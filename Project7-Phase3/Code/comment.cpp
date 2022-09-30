#include "comment.hpp"


using namespace std;



comment::comment(string _comment_text,string _user_commented,string _time_commented)
{
	comment_text = _comment_text;
	user_commented = _user_commented;
	time_commented = _time_commented;
}

void comment::show_comments()
{
	cout << time_commented << " " << user_commented << ": " << comment_text << endl;
}

