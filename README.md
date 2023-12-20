# LZ77 Compression/Decompression Algorithm

## Introduction

I have implemented the LZ77 compression/decompression algorithm in C++ as my project assignment in college. I've included also files for testing purposes, such as: `input.txt`, `output.txt` and `decompressed.txt` to better visualise the compression/decompression process.

## How to use

A program is a command-line-parameters kind. It takes **always** 5 parameters:

- `-i input_file`: Input file for compression/decompression
- `-o output_file`: Output file for compression/decompression
- `-t mode`: c for compression, d for decompression
- `-n inputBufferSize`: Size of input buffer (max match length)
- `-k historyBufferSize`: Size of history buffer (search buffer)

## How it works

The algorithm works by replacing repeated occurrences of data with references to a single copy of that data existing earlier in the uncompressed data stream. The LZ77 algorithm operates on a buffer that slides through the input. The length of the buffer is the maximum distance to look back in the input for a match. The algorithm assumes that strings encountered earlier in the input stream are more likely to occur later in the input stream, and uses this assumption to decide which match to copy into the output stream.

## How to compile

```bash
g++ lz77.cpp main.cpp parameters.cpp functions.cpp -o lz77
```

If you compile this as such, you will get a `lz77.exe` executable file. You can run it by typing:

```bash
./lz77
```

## Example

#### Compression

``input.txt as [input file], output.txt as [output file]`` \
**It can be any file, not just .txt (e.g: jpg, png, bin, cpp, etc.)**
```bash
./lz77 -i input.txt -o output.txt -t c -n 10 -k 10
```

#### Decompression

``output.txt as [input file], decompressed.txt as [output file]``
```bash
./lz77 -i output.txt -o decompressed.txt -t d -n 10 -k 10
```

## Stars

If you like this project, please consider giving it a star. Thanks!

## Credits

The project is not under any license, but with human kindness, I would like to be credited if you use it in your project. Thank you!
