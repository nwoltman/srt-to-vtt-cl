/**
 * @file Utils.cpp
 * Implementation for the Utils (utilities) class.
 *
 * @author Nathan Woltman
 * @copyright 2014-2016 Nathan Woltman
 * @license MIT https://github.com/nwoltman/srt-to-vtt-cl/blob/master/LICENSE.txt
 */

#include "Utils.h"
#include <codecvt>
#include <stdexcept>
#include <iostream>

#if defined(_WIN32) || defined(WIN32)
#include <Windows.h>
#else
#include <dirent.h>
#include <sys/stat.h>
#endif

using namespace std;

#define FILE_TEST_SIZE 4096 // 4 kb


void Utils::openFile(const string& filepath, wifstream& stream, bool verbose)
{
    unsigned char buffer[FILE_TEST_SIZE];
    const unsigned long long fileLength = getFileSize(filepath);
    const size_t bytes = fileLength < FILE_TEST_SIZE ? (size_t)fileLength : FILE_TEST_SIZE;
    ifstream fin(filepath, ifstream::binary);
    fin.read((char*)buffer, bytes);
    fin.close();

    AutoIt::TextEncodingDetect encodingDetector;
    AutoIt::TextEncodingDetect::Encoding encoding = encodingDetector.DetectEncoding(buffer, bytes);
    if (verbose) {
        dumpEncodingType(encoding);
    }
    switch (encoding) {
        // UTF-16
        case AutoIt::TextEncodingDetect::UTF16_LE_BOM:
        case AutoIt::TextEncodingDetect::UTF16_LE_NOBOM:
        case AutoIt::TextEncodingDetect::UTF16_BE_BOM:
        case AutoIt::TextEncodingDetect::UTF16_BE_NOBOM:
        #if defined(_WIN32) || defined(WIN32) // Windows
            stream.open(filepath, ios::binary);
            stream.imbue(locale(fin.getloc(), new codecvt_utf16<wchar_t, 0x10ffff, consume_header>));
            break;
        #else
            throw runtime_error("Converting UTF-16 encoded files is not supported on your platform.");
        #endif

        case AutoIt::TextEncodingDetect::UTF8_BOM:
        case AutoIt::TextEncodingDetect::UTF8_NOBOM:
            stream.open(filepath);
            stream.imbue(locale(fin.getloc(), new codecvt_utf8<wchar_t, 0x10ffff, consume_header>));
            break;

            // ASCII, ANSI, none
        default:
            stream.open(filepath);
            stream.imbue(locale(fin.getloc(), new codecvt<wchar_t, char, mbstate_t>));
            break;
    }
}

unsigned long long Utils::getFileSize(const string& filepath)
{
    ifstream fin(filepath, ifstream::ate | ifstream::binary);
    return fin.tellg();
}

void Utils::dumpEncodingType(AutoIt::TextEncodingDetect::Encoding encoding)
{
    switch (encoding) {
        case AutoIt::TextEncodingDetect::None:
            cout << "No";
            break;
        case AutoIt::TextEncodingDetect::ANSI:
            cout << "ANSI";
            break;
        case AutoIt::TextEncodingDetect::ASCII:
            cout << "ASCII";
            break;
        case AutoIt::TextEncodingDetect::UTF8_BOM:
            cout << "UTF8_BOM";
            break;
        case AutoIt::TextEncodingDetect::UTF8_NOBOM:
            cout << "UTF8_NOBOM";
            break;
        case AutoIt::TextEncodingDetect::UTF16_LE_BOM:
            cout << "UTF16_LE_BOM";
            break;
        case AutoIt::TextEncodingDetect::UTF16_LE_NOBOM:
            cout << "UTF16_LE_NOBOM";
            break;
        case AutoIt::TextEncodingDetect::UTF16_BE_BOM:
            cout << "UTF16_BE_BOM";
            break;
        case AutoIt::TextEncodingDetect::UTF16_BE_NOBOM:
            cout << "UTF16_BE_NOBOM";
            break;
    }
    cout << " text encoding detected ...";
}

bool Utils::isDir(const string& path)
{
#if defined(_WIN32) || defined(WIN32)
    DWORD ftype = GetFileAttributesA(path.c_str());
    if (ftype & FILE_ATTRIBUTE_DIRECTORY)
        return true;
#else
    struct stat st;
    if (stat(path.c_str(), &st) == 0 && (st.st_mode & S_IFDIR))
        return true;
#endif

    return false;
}

void Utils::makeDir(const string& path)
{
    int res = system(("mkdir \"" + path + "\"").c_str());
    if (res != 0) {
        throw runtime_error("Failed to create directory \"" + path + "\" with status: " + to_string(res));
    }
}

bool Utils::pathExists(const string& path)
{
#if defined(_WIN32) || defined(WIN32)
    DWORD ftype = GetFileAttributesA(path.c_str());
    if (ftype != INVALID_FILE_ATTRIBUTES)
        return true;
#else
    struct stat st;
    if (stat(path.c_str(), &st) == 0 && (st.st_mode & S_IFDIR || st.st_mode & S_IFREG))
        return true;
#endif

    return false;
}

void Utils::rtrim(string& s, const char c)
{
    while (!s.empty() && s.back() == c)
    {
        s.pop_back();
    }
}

void Utils::rtrim(wstring& s, const wchar_t c)
{
    while (!s.empty() && s.back() == c)
    {
        s.pop_back();
    }
}

wstring& Utils::wstr_replace(wstring& subject, wstring search, wstring replace)
{
    for (;;)
    {
        size_t index = subject.find_first_of(search);
        if (index == wstring::npos) break;
        subject.replace(index, search.length(), replace);
    }

    return subject;
}
