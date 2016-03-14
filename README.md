# Replaces duplicities in text
==============================

## Description
Replaces duplicities in common text for better readability.
- Text: lazy fox jumps over jumps over the brown dog
- is replaced with: lazy fox jumps over the brown dog

## Prerequisities:
- Linux, Mac OS X or cygwin
- Installed g++ make and boost

## How to build it
```
./configure
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
