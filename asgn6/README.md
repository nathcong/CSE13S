# Assignment 6 - Public Key Cryptography - README

## Program Description
This program is a library that conducts data encryption and decryption using the RSA algorithm. In addition, the library also contains an RSA public and private key generator that will generate unique RSA keys. The implementations included in this library include a random number generator, various number theory functions used in the RSA algorithm, and various functions used in or in conjunction with the RSA algorithm.

This library and the implementations within all use the GNU Multiple Precision Arithmetic Library. 

## Program Compiling
To compile the complete program, input:
>*make*

Following this the library will be compiled and generated into multiple executable binaries, but the executables used to run the library are keygen, encrypt, and decrypt.

## How to run this program

#### Encrypt

SYNOPSIS

Encrypts data using RSA encryption, decryption done by decrypt program.

USAGE

./encrypt [-hvi:o:n:] [-i infile] [-o outfile] [-n pbfile]

OPTIONS

-v           Enable verbose printing.

-h           Program help message.

-i infile    Input file with data to be encrypted. Default is stdin.

-o outfile   Output file with encrypted data. Default is stdout.

-n pbfile    Public key file. Default is rsa.pub.

#### Decrypt

SYNOPSIS

Decrypts data using RSA decryption, encryption done by encrypt program.

USAGE

./decrypt [-hvi:o:n:] [-i infile] [-o outfile] [-n pvfile]

OPTIONS

-v           Enable verbose printing.
  
-h           Program help message.

-i infile    Input file with data to be decrypted. Default is stdin.

-o outfile   Output file with decrypted data. Default is stdout.

-n pbfile    Private key file. Default is rsa.priv.

#### Key Generator

SYNOPSIS
  
Generates a pair of RSA public and private keys.

USAGE
  
./key [-hvb:i:n:d:s:] [-b bits] [-i iterations] [-n pbfile] [-d pvfile] [-s seed]

OPTIONS
  
-v              Enable verbose printing.
  
-h              Program help message.
  
-b bits        Bits needed for public modulus n.
  
-i iterations  Iterations to test primes. Default is 50.
  
-s seed        Random seed for RNG. Default is time since UNIX epoch.
  
-n pbfile       Public key file. Default is rsa.pub.
  
-d pvfile       Private key file. Default is rsa.priv.

