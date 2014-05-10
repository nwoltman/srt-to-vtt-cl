#ifndef CONVERTER_H_
#define CONVERTER_H_

#include <string>

class Converter
{
public:
	Converter(int timeOffsetMs = 0, const std::string &outputDir = "", bool quiet = false);
	~Converter();

	/**
	 * Converts a single .srt file to a .vtt file.
	 *
	 * @param filepath The path the file to convert. Can be a full or relative path.
	 */
	void convertFile(std::string filepath);

	/**
	 * Converts all files in a directory, optionally converting files in subdirectories.
	 *
	 * @param dirpath The path the directory in which to search for .srt files to convert.
	 * @param recursive Set this to true to recursively search subdirectories for .srt files to convert. Defaults to false.
	 */
	void convertDirectory(std::string &dirpath, bool recursive = false);

private:
	void trimPath(std::string &path); // Trims any trailing slash ('/' or '\') from the path
	void print(std::string info);     // Prints information to the console

	int _timeOffsetMs;      // The timing offset in milliseconds
	std::string _outputDir; // The directory in which the converted .vtt files will be saved.
	bool _quiet;            // If true, prevents printing to the console
};

#endif