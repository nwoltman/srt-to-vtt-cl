#ifndef UTILS_H_
#define UTILS_H_

#include <string>


class Utils
{
public:
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
