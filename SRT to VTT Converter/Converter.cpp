#include <dirent.h>
#include <iostream>
#include "Converter.h"

#if defined(_WIN32) || defined(WIN32)
#define DIR_SEPARATOR "\\"
#else
#define DIR_SEPARATOR "/"
#endif

using namespace std;

Converter::Converter(int timeOffsetMs, const std::string &outputDir, bool quiet)
{
	_timeOffsetMs = timeOffsetMs;
	_outputDir = outputDir;
	trimPath(_outputDir);
	_quiet = quiet;
}

Converter::~Converter()
{
}

void Converter::convertFile(std::string filepath)
{
	print("Converting file: " + filepath);
}

void Converter::convertDirectory(std::string &dirpath, bool recursive)
{
	trimPath(dirpath);
	print("Searching for files to convert in: " + dirpath);

	DIR *dir;
	struct dirent *ent;

	if ((dir = opendir(dirpath.c_str())) == NULL) {
		cerr << "Could not read directory \"" << dirpath << "\"" << endl;
		return;
	}

	//Loop through all items in the directory
	while ((ent = readdir(dir)) != NULL)
	{
		string item = ent->d_name;
		string ext = item.substr(item.find_last_of(".") + 1);
		switch (ent->d_type) {
			case DT_LNK:
			case DT_REG:
				//If the file is a .srt file, convert it
				if (ext == "srt" || ext == "SRT") {
					convertFile(dirpath + DIR_SEPARATOR + item);
				}
				break;

			case DT_DIR:
				//If recursive, search subdirectories
				if (recursive && item != "." && item != "..") {
					convertDirectory(dirpath + DIR_SEPARATOR + item, recursive);
				}
				break;

			default:
				/* Ignore device entries */
				/*NOP*/;
		}
	}
	closedir(dir);
}

void Converter::trimPath(string &path)
{
	while (path.length() && (path.back() == '/' || path.back() == '\\')) {
		path.pop_back();
	}
}

void Converter::print(string info)
{
	if (!_quiet) {
		cout << info << endl;
	}
}