#include <iostream>
#include "command_handle.hpp"

using namespace std;

const int SONGS_INPUT_NUM=1;
const int LIKED_SONGS_INPUT_NUM=2;
const int REQUIRED_ARGUMENTS=3;


int main(int argc, char* argv[])
{
	if (argc < REQUIRED_ARGUMENTS)
	{
		cerr << "usage: utunes-server <songs.csv> <liked_songs.csv>" << endl;
		return 1;
	}

	command_handle new_program = command_handle();
	new_program.run(argv[SONGS_INPUT_NUM], argv[LIKED_SONGS_INPUT_NUM]);
	return 0;
}
