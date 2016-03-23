Replaces duplicities in text
============================

## Description
Replaces duplicities in common text for better readability.
- Text: lazy fox jumps over jumps over the brown dog
- is replaced with: lazy fox jumps over the brown dog

## Prerequisities:
- Linux, Mac OS X or cygwin

### Automake build
- Installed g++, make, automake, autoconf and boost
- Example of necessary packages for Ubuntu/Debian:
```
apt-get install build-essential g++ autoconf automake \
pkg-config libtool libboost-dev autoconf-archive \
libboost-program-options-dev libboost-system-dev \
libboost-filesystem-dev
```

### cmake build
- Installed g++, cmake and boost
- Example of necessary packages for Ubuntu/Debian:
```
apt-get install build-essential g++ cmake libboost-dev \
autoconf-archive libboost-program-options-dev \
libboost-system-dev libboost-filesystem-dev
```

## How to build it

### Automake
```
./autogen
make
```

### cmake
```
cmake .
make
```

## How to test it
```
./test.sh
```

## Usage
```
./replace --help
Search in the text file for all word or sentence
duplicities, removes them and saves the text to
output file

Usage: replace [options] <input file> <output file>
Allowed options:
  --help                      Print usage
  -p [ --print-duplicities ]  Enables print of duplicities to stdout
  -s [ --separators ] arg     Set separators. Default value is $' \n'
  --input-file arg            Path to input file - mandatory argument
  --output-file arg           Path to output file - mandatory argument
```

## Limitations
The text file is loaded into memory so trying to process files bigger then is amount of your workstation memory can cause program failure or significant slow down of you OS.

The text file must have Linux new line format (for Windows "\r\n" it probably won't work). To convert to linux format you can use utility dos2unix.
