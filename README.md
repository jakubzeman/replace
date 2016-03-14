# Replaces duplicities in text
==============================

## Description
Replaces duplicities in common text for better readability.
- Text: lazy fox jumps over jumps over the brown dog
- is replaced with: lazy fox jumps over the brown dog

## Prerequisities:
- Linux, Mac OS X or cygwin
- Installed g++ make and boost
- Example of necessary packages for Ubuntu/Debian:
```
apt-get install build-essential g++ autoconf automake pkg-config libtool libboost-dev
```

## How to build it
```
./autogen
make
```

## How to test it
```
./test.sh
```

## Usage
```
./replace <path to input text file> <path to output file name>
```

## Limitations
The text file is loaded into memory so trying to process files bigger then is amount of your workstation memory can cause program failure or significant slow down of you OS.

The text file must have Linux new line format (for Windows "\r\n" it probably won't work). To convert to linux format you can use utility dos2unix.
