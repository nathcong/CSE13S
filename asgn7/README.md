# Assignment 7 - The Great Firewall of Santa Cruz - README

## Program Description
This program is a library that reads an input and scans for words that are in a premade list of "banned" words or a premade list of alternative words to use in place of other words. Depending on what is detected the program reacts accordingly with an appropriate message that describes the word crime that takes place and what words were detected that were part of the lists. The implementations included in this library include a bloom filter, binary search trees, a hash table, nodes, and bit vectors.

## Program Compiling
To compile the complete program, input:
>*make*

Following this the library will be compiled and generated into multiple executable binaries, but the executable used to run the library is banhammer.

## How to run this program

SYNOPSIS

  A word filtering program for the GPRSC.
  Filters out and reports bad words parsed from stdin.

USAGE

  ./keygen [-hst:f:] [-t size] [-f size]

OPTIONS

  -v          Print statistics.
  
  -h         Program help message.
  
  -t size    Hash table size. Default size is 2 ^ 16.
  
  -f size    Bloom filter size. Default size is 2 ^ 20.

## Known bugs
banhammer.c does not print the words in an appropriate form, most liekly due to logical errors in printing the binary search trees and nodes, which were used for debugging.
