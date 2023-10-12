/*
	Title:  text.cpp
	Author:  Tyce Webster & Isaac Essex
    Course: CSC 1310-001
	Date:  9/16/2023
    Due: 9/18/2023
	Purpose: Create and store an array of characters because we're simply 
    too pretentious to use a string.
*/

//Header file
#include "text.h"

//Constructor that is called automatically when Text object is created, dynamically allocates a character array passed to function
Text::Text(const char* c) //Function parameters
{
    textLength = strlen(c); //Gets the length of the string passed to the function
    char* temp = new char[textLength + 1]; //Dynamically allocates new character string to size of string
    strcpy (temp, c); //Puts c into the new temp value
    this->textArray = temp; //Sets the textArray attribute to new temp cstring
}

//Deconstructor that releases the memory for the cstring pointed to by textArray
Text::~Text()
{
    //Releases dynamically allocated textArray
    delete [] textArray;

    cout << "Text destructor: Released memory for textArray.\n";
}

//displayText function that prints textArray to the screen
void Text::displayText()
{
        cout << textArray;
}

//Accessor function to get the data for the textArray
const char* Text::getText() const
{
    return textArray; //Returns a pointer to textArray
}

//Accessor function to get the length for textLength
int Text::getLength() const
{
    return textLength; //Returns the length of the string
}