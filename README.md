# SRT to VTT Command Line

[![Build Status](https://github.com/nwoltman/srt-to-vtt-cl/actions/workflows/ci.yml/badge.svg?branch=master)](https://github.com/nwoltman/srt-to-vtt-cl/actions?query=branch%3Amaster)

A command line tool that converts subtitle files from SubRib (.srt) format to WebVTT (.vtt) format.

If you'd rather use a GUI than the command line, check out the [SRT to VTT Converter](https://github.com/nwoltman/srt-to-vtt-converter).

## Binaries

* [Windows](https://github.com/nwoltman/srt-to-vtt-cl/raw/master/bin/Windows/srt-vtt.exe "Download the 32-bit Windows binary file")
* [Mac OS X](https://github.com/nwoltman/srt-to-vtt-cl/raw/master/bin/Mac-OSX/srt-vtt "Download the OS X binary file")
* Linux - [build instructions](#build)

## Usage

For the most basic usage, simply put the binary file in the same directory as the .srt files you want to convert and run the converter. This will convert all files in that directory and save them with the .vtt extension.

For more advanced usage, see below:

```
srt-vtt  [-q] [-v] [-r] [-o <string>] [-t <integer>] [--] [--version] [-h] <string>

  -q,  --quiet
    Prevents details about the conversion from being printed to the console.
    Overrides --verbose.

  -v,  --verbose
    Indicates that details about the conversion should be printed to the console.

  -r,  --recursive
    If the input is a directory, this flag indicates its subdirectories will be searched
    recursively for .srt files to convert. This flag is ignored if the input path is a
    file.

  -o <string>,  --output-dir <string>
    The path to a directory where all output VTT files will be saved.

  -t <integer>,  --offset <integer>
    Timing offset in milliseconds. Can be any integer between 2147483647 and -2147483648.

  --,  --ignore_rest
    Ignores the rest of the labeled arguments following this flag.

  --version
    Displays version information and exits.

  -h,  --help
    Displays usage information and exits.

  <string>
    Path to a file to convert or directory containing files to convert (to convert files
    in a directory and it's subdirectories, include the -r switch).

  If called without any arguments, all .srt files in the current directory will be
  converted and saved within the current directory.
```

## Build

### OS X / Linux

**Compiler requirements: Clang v3.4+ or GCC v5.1+**

```sh
git clone https://github.com/nwoltman/srt-to-vtt-cl.git
cd srt-to-vtt-cl
make
```

The built binary will be located in `bin/Mac-OSX` on OS X and `bin/<uname -s>/<uname -m>` on Linux
(i.e. on Ubuntu: `bin/Linux/x86_64`)

### Windows

+ Open the Visual Studio solution
+ If in *Debug* mode, change to *Release* mode
+ Press `Ctrl+Shift+B` or in the menu `Build -> Build Solution`

## Test

```sh
make
make test
```
