# Assignment 5 - Huffman Coding - README

## Program Description
This program is a library that compresses and decompresses data using the Huffman coding algorithm. It contains implementations of a stack, a priority queue, a node graph, an input/output module, a huffman tree builder, and a code ADT that represents a stack of bits. With the two executable binaries, encode and decode, data can be compressed (encoded) and decompressed (decoded), all using the Huffman algorithm.

## Program Compiling
To compile the complete program, input:
>*make all*

Following this the library will be compiled and generated into multiple executable binaries, but the executables used to run the library are encode and decode.

## How to run this program

#### Encode

SYNOPSIS

A Huffman encoder.
Compresses a file using the Huffman coding algorithm.

USAGE

./encode [-hvi:o:] [-i infile] [-o outfile]

OPTIONS

-v	     Print compression statistics.
	
-h           Program help message.

-i *infile*  Input file to compress. Default is stdin.

-o *outfile* Output file with compressed data. Default is stdout.

#### Decode

SYNOPSIS

A Huffman decoder.
Decompresses a file using the Huffman coding algorithm.

USAGE

./encode [-hvi:o:] [-i infile] [-o outfile]

OPTIONS

-v           Print decompression statistics.

-h           Program help message.

-i *infile*  Input file to decompress. Default is stdin.

-o *outfile* Output file with decompressed data. Default is stdout.

