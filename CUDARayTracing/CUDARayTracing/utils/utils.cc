#include "utils.h"

string current_path_string_windows() 
{
	char buff[MAX_PATH];
	GetModuleFileName(NULL, buff, MAX_PATH);
	string::size_type position = string(buff).find_last_of("\\/");
	cout << "current working directory: " << string(buff).substr(0, position) << '\n';
	return string(buff).substr(0, position);
}