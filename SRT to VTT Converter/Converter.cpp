/**
 * @file Converter.cpp
 * Implementation for the Converter class.
 *
 * @author Nathan Woltman
 * @copyright 2014 Nathan Woltman
 * @license MIT https://github.com/woollybogger/srt-to-vtt-cl/blob/master/LICENSE.txt
 */

#include <codecvt>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <regex>
#include "Converter.h"
#include "Utils.h"

#if defined(_WIN32) || defined(WIN32)
#define DIR_SEPARATOR "\\"
#else
#define DIR_SEPARATOR "/"
#endif

using namespace std;

Converter::Converter(int timeOffsetMs, const std::string& outputDir, bool quiet)
{
	_timeOffsetMs = timeOffsetMs;
	_outputDir = outputDir;
	_quiet = quiet;

	//Strip trailing slashes from the output directory's path
	Utils::rtrim(_outputDir, '/');
	Utils::rtrim(_outputDir, '\\');
}

void Converter::convertDirectory(std::string& dirpath, bool recursive)
{
	//Strip trailing slashes from the directory's path
	Utils::rtrim(dirpath, '/');
	Utils::rtrim(dirpath, '\\');

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
					string subdir = dirpath + DIR_SEPARATOR + item;
					convertDirectory(subdir, recursive);
				}
				break;

			default:
				/* Ignore device entries */
				/*NOP*/;
		}
	}
	closedir(dir);
}

void Converter::convertFile(std::string filepath)
{
	//Determine path of the output file
	string outpath = regex_replace(filepath, regex("\\.srt$", regex_constants::icase), string("")) + ".vtt";

	if (!_outputDir.empty()) { //The user specified an output directory
		if (!Utils::isDir(_outputDir)) {
			print("Creating directory: " + _outputDir);
			system(string("mkdir \"" + _outputDir + "\"").c_str());
		}
		outpath = _outputDir + DIR_SEPARATOR + outpath.substr(outpath.find_last_of(DIR_SEPARATOR) + 1);
	}

	print("Converting file: " + filepath + " => " + outpath);
	
	try {
		regex rgxDialogNumber("\\d+");
		regex rgxTimeFrame("(\\d\\d:\\d\\d:\\d\\d,\\d{3}) --> (\\d\\d:\\d\\d:\\d\\d,\\d{3})");

		ifstream infile(filepath);
		skipBom(infile); //In case file starts with BOM

		ofstream outfile(outpath);

		//Write mandatory starting for the WebVTT file
		outfile << "WEBVTT" << endl << endl;

		string sLine;
		while (getline(infile, sLine))
		{
			//Ignore dialog number lines
			if (regex_match(sLine, rgxDialogNumber))
				continue;

			smatch match;
			regex_match(sLine, match, rgxTimeFrame);
			if (!match.empty()) {
				if (_timeOffsetMs != 0) {
					//Extract the times in milliseconds from the time frame line
					long msStartTime = timeStringToMs(match[1]);
					long msEndTime = timeStringToMs(match[2]);

					//Modify the time with the offset, making sure the time gets set to 0 if it is going to be negative
					msStartTime += _timeOffsetMs;
					msEndTime += _timeOffsetMs;
					if (msStartTime < 0) msStartTime = 0;
					if (msEndTime < 0) msEndTime = 0;

					//Construct the new time frame line
					sLine = msToVttTimeString(msStartTime) + " --> " + msToVttTimeString(msEndTime);
				}
				else {
					//Simply replace the commas in the time with a period
					sLine = Utils::str_replace(sLine, ",", ".");
				}
			}
			else {
				//HTMl encode the text so it is displayed properly by browsers
				sLine = htmlEncodeUtf8(sLine);
			}

			outfile << sLine << endl; //Output the line to the new file
		}

		infile.close();
		outfile.close();

		print("Done!");
	}
	catch (exception &e) {
		cerr << "An error occurred converting \"" << filepath << "\":" << endl << e.what() << endl;
	}
}

void Converter::skipBom(istream & in)
{
	const char bom[3] = { (char)0xEF, (char)0xBB, (char)0xBF };
	char test[3] = { 0 };
	in.read(test, 3);
	if (*test != *bom) {
		in.seekg(0);
	}
}

string Converter::htmlEncodeUtf8(const std::string& str)
{
	//Convert the string to a wstring
	wstring wstr = wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(str);
	
	//The string doesn't have any UTF-8 characters if both strings have the same length
	if (str.length() == wstr.length())
		return str;

	//HTML-encode the UTF-8 characters in the ASCII range
	for (size_t i = 0; i < wstr.length(); i++)
	{
		if (wstr[i] >= 160 && wstr[i] <= 255) {
			wstring replacement = L"&#" + to_wstring((int)wstr[i]) + L";";
			wstr.replace(i, 1, replacement);
			i += replacement.length() - 1;
		}
	}

	//Convert back to string and return
	return wstring_convert<codecvt_utf8<wchar_t>, wchar_t>().to_bytes(wstr);
}

long Converter::timeStringToMs(const std::string& time)
{
	//Time format: hh:mm:ss,### (where # = ms)
	int hours = stoi(time.substr(0, 2));
	int minutes = stoi(time.substr(3, 2));
	int seconds = stoi(time.substr(6, 2));
	int milliseconds = stoi(time.substr(9));

	return hours*3600000 + minutes*60000 + seconds*1000 + milliseconds;
}

std::string Converter::msToVttTimeString(long ms)
{
	int hours = ms/3600000;
	ms -= hours*3600000;

	int minutes = ms/60000;
	ms -= minutes*60000;

	int seconds = ms/1000;
	ms -= seconds*1000;

	return (hours < 10 ? "0" : "") + to_string(hours)
		+ ":" + (minutes < 10 ? "0" : "") + to_string(minutes)
		+ ":" + (seconds < 10 ? "0" : "") + to_string(seconds)
		+ "." + (ms < 100 ? "0" : "") + (ms < 10 ? "0" : "") + to_string(ms);
}

void Converter::print(string info)
{
	if (!_quiet) {
		cout << info << endl;
	}
}
