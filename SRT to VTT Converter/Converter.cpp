#include "Converter.h"
using namespace std;

Converter::Converter(int timeOffsetMs, std::string outputDir = "", bool quiet = false)
{
	_timeOffsetMs = timeOffsetMs;
	_outputDir = outputDir;
	_quiet = quiet;
}

Converter::~Converter()
{
}

void Converter::convertFile(std::string filepath)
{

}

void Converter::convertDirectory(std::string dirpath, bool recursive = false)
{

}