/**
 * @file main.cpp
 * Main file for the SRT to VTT Converter. Processes command line options.
 *
 * @version 1.0.1
 * @author Nathan Woltman
 * @copyright 2014 Nathan Woltman
 * @license MIT https://github.com/woollybogger/srt-to-vtt-cl/blob/master/LICENSE.txt
 */

#include <iostream>
#include <limits.h>
#include <string>
#include <tclap/CmdLine.h>
#include "Converter.h"
#include "Utils.h"

using namespace std;


int main(int argc, char* argv[])
{
	try {
		//Initialze the tclap command line parser
		TCLAP::CmdLine cmd(string("`srt-vtt` converts SubRip subtitles to the WebVTT subtitle format.\n")
				+ "If called without any arguments, all .srt files in the current directory will be converted and left within the current directory.\n"
				+ "Written by Nathan Woltman and distributed under the MIT license.",
			' ', "1.0.1");

		//Define arguements
		TCLAP::UnlabeledValueArg<string> inputArg("input",
			"Path to a file to convert or directory containing files to convert (to convert files in a directory and it's subdirectories, include the -r switch).",
			false, ".", "string");
		cmd.add(inputArg);

		TCLAP::ValueArg<int> offsetArg("t", "offset",
			"Timing offset in milliseconds. Can be any integer between " + to_string(INT_MAX) + " and " + to_string(INT_MIN) + ".",
			false, 0, "integer");
		cmd.add(offsetArg);

		TCLAP::ValueArg<string> outputArg("o", "output-dir",
			"The path to a directory where all output VTT files will be saved.",
			false, "", "string");
		cmd.add(outputArg);

		TCLAP::SwitchArg recursiveArg("r", "recursive", string()
			+ "If the input is a directory, this flag indicates its subdirectories will be searched recursively for .srt files to convert."
			+ " This flag is ignored if the input path is a file.");
		cmd.add(recursiveArg);

		TCLAP::SwitchArg quietArg("q", "quiet", "Prevents details about the conversion from being printed to the console.");
		cmd.add(quietArg);

		//Parse the argv array
		cmd.parse(argc, argv);

		//Get the value parsed by each arg
		string input = inputArg.getValue();
		int timeOffset = offsetArg.getValue();
		string outputDir = outputArg.getValue();
		bool recursive = recursiveArg.getValue();
		bool quiet = quietArg.getValue();

		//Convert
		Converter converter(timeOffset, outputDir, quiet);
		if (Utils::isDir(input)) {
			converter.convertDirectory(input, recursive);
		}
		else if (Utils::pathExists(input)) {
			converter.convertFile(input);
		}
		else {
			cout << "The input path does not exist!" << endl;
		}
	}
	catch (TCLAP::ArgException &e) {
		cerr << "error: " << e.error() << " for arg " << e.argId() << endl;
	}

	return 0;
}
