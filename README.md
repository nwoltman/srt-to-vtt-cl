SRT to VTT Command Line
=============

A command line application that converts subtitle files from SubRib (.srt) format to WebVTT (.vtt) format.

## Binaries

* [Windows](https://raw.githubusercontent.com/woollybogger/srt-to-vtt-cl/master/bin/Windows/srt-vtt.exe "Download the 32-bit Windows binary file")
* [Mac OS X](https://raw.githubusercontent.com/woollybogger/srt-to-vtt-cl/master/bin/Mac-OSX/srt-vtt "Download the OS X binary file")

## Usage

For the most basic usage, simply put the binary file in the same directory as the .srt files you want to convert and run the converter. This will convert all files in that directory and save them with the .vtt extension.

For more advanced usage, see below:

```
srt-vtt [-q] [-r] [-o <string>] [-t <integer>] [--] [--version] [-h] <string>

  -q,  --quiet
    Prevents details about the conversion from being printed to the console.

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

**Note: Linux requires GCC v5.1 or greater**

```sh
cd SRT_to_VTT
make
```

### Windows

+ Open the Visual Studio solution
+ If in *Debug* mode change to *Release* mode
+ Press `Ctrl+Shift+B` or go to `Build -> Build Solution`
