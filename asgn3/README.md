# Assignment 3 - Getting Your Affairs in Order- README

## Program Description
This program is a library consisting of 4 sorting functions. The sorting functions are as follows: Insertion Sort, Shell Sort, Quick Sort, and Heap Sort. Each one accomplishes the same purpose of ordering an array but each accomplishes this task in different ways. It also includes options to change variables of the sorting algorithms including RNG seeds, array length, and the number of sorted elements that are displayed.

## Program Compiling
To compile the complete program, input:
>*make all*

Following this the library will be compiled and generated into multiple executable binaries, but the one used to run the library is sorting.

## How to run this program

After following the compiling structions given above, input:
>./sorting

With no arguments, the library will automatically output a help message that includes information on what the library does and how to run the different functions available inside.

## Known bugs
With no arguments, the library is meant to automatically output a help message that includes information on what the library does and how to run the different functions available inside.

Unfortunately, with this bug that message does not appear by default. So as an alternative, the help message will be listed below:

SYNOPSIS

   A library of sorting algorithms.

USAGE

   ./sorting [-aeisqr:n:p:h] [-r seed] [-n length] [-p elements]

OPTIONS

  -a   Runs all sorting algorithms.

  -e   Runs heap sort algorithm.
 
  -i   Runs insertion sort algorithm.
 
  -s   Runs shell sort algorithm.
 
  -q   Runs quicksort algorithm.
 
  -r   Sets RNG seed. Default is 13371453.
 
  -n   Sets array length. Default is 100.
 
  -p   Sets number of elements to print. Default is 100.
 
  -h   Display program synopsis and usage.
