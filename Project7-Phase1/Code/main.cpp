#include <iostream>
#include "command_handle.hpp"

using namespace std;


int main(int argc,char* argv[])
{
	command_handle new_program = command_handle(false);
	new_program.run(argv[1]);
	return 0;
}
