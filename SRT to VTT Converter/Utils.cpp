#include "Utils.h"

using namespace std;


string& Utils::rtrim(std::string& s, char c)
{
	while (s.length() && s.back() == c) {
		s.pop_back();
	}
	return s;
}

std::string& Utils::str_replace(std::string& subject, std::string search, std::string replace)
{
	size_t index;
	while ((index = subject.find_first_of(search)) != string::npos)
	{
		subject.replace(index, search.length(), replace);
	}
	return subject;
}
