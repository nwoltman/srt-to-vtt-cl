#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <tclap/CmdLine.h>
using namespace std;

int main(int argc, char* argv[])
{
	try {
		//Initialze the tclap command line parser
		TCLAP::CmdLine cmd(string("`srt-vtt` converts SubRip subtitles to the WebVTT subtitle format.\n")
				+ "If called without any arguments, all .srt files in the current directory will be converted and left within the current directory.\n"
				+ "Written by Nathan Woltman and distributed under the MIT license.",
			' ', "0.0.1");

		//Define arguements
		TCLAP::UnlabeledValueArg<string> inputArg("input",
			"File to convert or direcotry containing files to convert (to convert files in a directory and it's subdirectories, include the -r switch.",
			false, ".", "string");
		cmd.add(inputArg);

		TCLAP::ValueArg<int> offsetArg("t", "offset",
			"Timing offset in milliseconds. Can be any integer between " + to_string(INT_MAX) + " and " + to_string(INT_MIN) + ".",
			false, 0, "integer");
		cmd.add(offsetArg);

		TCLAP::ValueArg<string> dirArg("o", "output-dir",
			"The path to a directory where all output VTT files will be saved.",
			false, "", "string");
		cmd.add(dirArg);

		TCLAP::SwitchArg recursiveArg("r", "recursive", string()
			+ "If the input is a directory, this flag indicates its subdirectories will be searched recursively for .srt files to convert."
			+ " This flag is ignored if the input is a file.");
		cmd.add(recursiveArg);

		//Parse the argv array.
		cmd.parse(argc, argv);

		//Get the value parsed by each arg.
		string input = inputArg.getValue();
		int offset = offsetArg.getValue();
		string dir = dirArg.getValue();
		bool recursive = recursiveArg.getValue();

		//Debugging
		cout << "Input is: " << input << endl;
		cout << "Offset time is: " << offset << endl;
		cout << "Output directory is: " << dir << endl;
		cout << "Recursive? - " << recursive << endl;
	}
	catch (TCLAP::ArgException &e) {
		cerr << "error: " << e.error() << " for arg " << e.argId() << endl;
	}

	getchar();
	return 0;
}