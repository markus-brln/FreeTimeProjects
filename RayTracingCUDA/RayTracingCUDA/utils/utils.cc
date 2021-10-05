#include "utils.h"

string current_path_string()
{
	// std::cout << "Current path is " << FileSys::current_path() << '\n'; // (1)
	// FileSys::current_path(FileSys::temp_directory_path()); // (3)
	// std::cout << "Current path is " << FileSys::current_path() << '\n';
	return filesystem::current_path().u8string();
}