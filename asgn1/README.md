
# Assignment 1 - Pass the Pigs - README

## Program Description

This program runs a version of the dice game Pass the Pigs, by David Moffat.  This simplified form of the game is played with n number of players, ranging from two to ten players. Arranged in what can be visualized as a circle, the players roll the dice, or the pig, in an effort to earn points. Whenever the pig lands on its side, the next player’s turn commences. The first player to reach 100 points wins the game. 

## Program Compiling

To compile the program into an executable file, input the following command:  
>*make all*.  

Following this an executable binary file, titled "pig" will be generated in the directory.

## How to run this program

After following the compiling instructions above, input the following command:  
>*./pig*.   

The program will proceed to begin and you will be asked to input a valid number of players, followed by a valid seed number for the random number generator.

## Known bugs

When a string is inputted, the error message for an invalid number of players is outputted but not the error message for an invalid seed. The program still proceeds as normal despite this.
