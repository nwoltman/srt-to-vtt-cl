/**
 * @file Utils.h
 * Header file for the Utils (utilities) class.
 *
 * @author Nathan Woltman
 * @copyright 2014 Nathan Woltman
 * @license MIT https://github.com/woollybogger/srt-to-vtt-cl/blob/master/LICENSE.txt
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <string>


class Utils
{
public:
	/**
	 * Tells if the path is a directory.
	 *
	 * @param path The path string.
	 * @returns TRUE if the path exists and is a directory; else FALSE.
	 */
	static bool isDir(const std::string& path);

	/**
	 * Strips characters from the end of a string.
	 *
	 * @param s The input string.
	 * @param c The character to be removed from the end of the string (removed continuously until the string no longer ends with this character).
	 * @returns A reference to the input string.
	 */
	static std::string& rtrim(std::string& s, char c);

	/**
	 * Replace all occurrences of the search string with the replacement string.
	 *
	 * @param subject The string being searched and replaced on.
	 * @param search The string being searched for to be replaced.
	 * @param replace The replacement string.
	 * @returns A reference to the input string (subject).
	 */
	static std::string& str_replace(std::string& subject, std::string search, std::string replace);
};

#endif
