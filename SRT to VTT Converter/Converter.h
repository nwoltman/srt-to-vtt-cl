/**
 * @file Converter.h
 * Header file for the Convert class.
 *
 * @author Nathan Woltman
 * @copyright 2014 Nathan Woltman
 * @license MIT https://github.com/woollybogger/srt-to-vtt-cl/blob/master/LICENSE.txt
 */

#ifndef CONVERTER_H_
#define CONVERTER_H_

#include <string>


class Converter
{
public:
	/* Constructor */
	Converter(int timeOffsetMs = 0, const std::string& outputDir = "", bool quiet = false);

	/**
	 * Converts all files in a directory, optionally converting files in subdirectories.
	 *
	 * @param dirpath The path to the directory in which to search for .srt files to convert. Can be a full or relative path.
	 * @param recursive Set this to true to recursively search subdirectories for .srt files to convert. Defaults to false.
	 */
	void convertDirectory(std::string& dirpath, bool recursive = false);

	/**
	 * Converts a single .srt file to a .vtt file.
	 *
	 * @param filepath The path to the file to convert. Can be a full or relative path.
	 */
	void convertFile(std::string filepath);

private:
	void skipBom(std::istream& in);                     // Skips the istream past a byte order mark (BOM)
	std::string htmlEncodeUtf8(const std::string& str); // HTML-encodes UTF-8 characters so they display properly in browsers
	long timeStringToMs(const std::string& time);       // Converts a SubRip time string to milliseconds
	std::string msToVttTimeString(long ms);             // Converts milliseconds to a WebVTT-formatted time string
	void print(std::string info);                       // Prints information to the console

	int _timeOffsetMs;      // The timing offset in milliseconds
	std::string _outputDir; // The directory in which the converted .vtt files will be saved.
	bool _quiet;            // If true, prevents printing to the console
};

#endif
