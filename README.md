# Lexical-Analyzer
A scanner which takes PL/0 code and checks for errors

Andrea Wormus
This program serves as a compiler for the PL/0 language. A lexical analyzer is implemented and used to identify errorsas well as output the source code, a lexeme table, and a list of lexemes used in the source code. 

This code reads in an input file containing PL/0 code, converts the code into tokens and identifies errors.
The program is written in C and compiled on the Eustis environment.
In order to compile and run your C programs in UNIX machine do as follow:
  To compile:
     gcc –o <runfile> <sourcefile.c>
  To Run:
    ./<runfile>
  Note the period and forward slash before the name of the executable file.
  Example: suppose your c program is named "vmhw1.c". To compile your source code you type in:
     gcc -o test vmhw1.c
  The "-o test" part of the command creates an executable file called "test". (The "-o" stands for
  "output".)
  If you left off the "-o test", the executable would be in a file called "a.out" by default.
  Then to run it you have to type in:
     ./test
