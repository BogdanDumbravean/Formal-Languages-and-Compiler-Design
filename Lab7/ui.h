#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "domain.h"

class Reader{
private:
    // Reads a line from stream and returns elements split by whitespaces in a vector
    // Input: fin - stream from which to read
    // Output: - Vector of elements from the next line, that were split by whitespace
    // Preconditions: Choose the proper template  
    template <class T>
    vector<T> readVector(ifstream& fin);
public:
    FA fa;

    // Reads the FA from a file
    // Input: filename - name of the file with the elements of the FA
    // Preconditions: File is orderd as specified in the documentation
    // Postconditions: private variable "fa" will be populated with the read data
    void read(string filename);
};

class UI {
private:
    FA fa;
    Solver s;

    // Prints possible commands that can be given by user 
    // Output: - prints all comands in console
    void printCommands();

    // Prints elements of a vector in console
    // Input: v - vector to be printed
    // Output: - prints all elements of the vector in console
    template <class T>
    void printVector(vector<T> v);

    // Processes command given by user
    // Input: command - number of command
    // Output: prints to the console the output of the command 
    void parseCommand(int command);
public:
    UI(FA _fa, Solver _s) : fa(_fa), s(_s) {}

    // Starts the program and prints to the console the available commands
    // Output: prints to the console the possible commands
    void start();
};