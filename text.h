/*
	Title:  text.h
	Author:  Tyce Webster & Isaac Essex
    Course: CSC 1310-001
	Date:  9/16/2023
    Due: 9/18/2023
	Purpose: Include nescessary libraries, declare member variables, 
    and declare member functions for the Text Class.
*/

//Header libraries
#ifndef TEXT_H
#define TEXT_H

//Libraries used
#include <iostream>
#include <cstring>
using namespace std;

//Text class
class Text
{
    private: //Private member variables
        char* textArray; //pointer to a constant character array
        int textLength;
    public: //Public member functions
        Text(const char* c); //Constructor
        ~Text(); //Deconstructor
        void displayText();
        const char* getText() const; //Accessor function
        int getLength() const; //Accessor function
};

#endif