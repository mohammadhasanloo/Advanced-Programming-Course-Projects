#ifndef COMMENT_H
#define COMMENT_H

#include <iostream>



class comment
{
public:
	comment(std::string _comment_text, std::string _user_commented, std::string _time_commented);
	std::string get_time_commented() { return time_commented; }
	std::string get_user_commented() { return user_commented; }
	void show_comments();

private:
	std::string comment_text;
	std::string user_commented;
	std::string time_commented;

};




#endif