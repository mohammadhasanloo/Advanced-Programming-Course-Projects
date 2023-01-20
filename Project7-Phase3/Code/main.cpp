#include <iostream>
#include "command_handle.hpp"

using namespace std;

const int SONGS_INPUT_NUM=1;
const int LIKED_SONGS_INPUT_NUM=2;


int main(int argc, char* argv[])
{
	command_handle new_program = command_handle();
	new_program.run(argv[SONGS_INPUT_NUM], argv[LIKED_SONGS_INPUT_NUM]);
	return 0;
}
