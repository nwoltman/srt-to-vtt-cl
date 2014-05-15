/**
 * @file Utils.cpp
 * Implementation for the Utils (utilities) class.
 *
 * @author Nathan Woltman
 * @copyright 2014 Nathan Woltman
 * @license MIT https://github.com/woollybogger/srt-to-vtt-cl/blob/master/LICENSE.txt
 */

#if defined(_WIN32) || defined(WIN32)
#include <Windows.h>
#else
#include <sys/stat.h>
#endif

#include <dirent.h>
#include "Utils.h"

using namespace std;


bool Utils::isDir(const string& path)
{
#if defined(_WIN32) || defined(WIN32)
	DWORD ftype = GetFileAttributesA(path.c_str());
	if (ftype == FILE_ATTRIBUTE_DIRECTORY)
		return true;
#else
	struct stat st;
	if (stat(path.c_str(), &st) == 0 && (st.st_mode & S_IFDIR))
		return true;
#endif

	return false;
}

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
