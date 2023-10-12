/*
	Title:  VideoGameLibrary.h
	Author:  Tyce Webster & Isaac Essex
    Course: CSC 1310-001
	Date:  9/16/2023
    Due: 9/18/2023
	Purpose:  Include nescessary libraries, declare member variables, 
    and declare member functions for the VideoGameLibrary Class.
*/
//Header libraries
#ifndef VIDEOGAMELIBRARY_H
#define VIDEOGAMELIBRARY_H

//Libraries used
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
//Header file
#include "VideoGame.h"
using namespace std;

//VideoGameLibrary class
class VideoGameLibrary
{
    private: //Private member variables
        VideoGame** videoGamesArray; //Pointer to a array of pointers that points to individual VideoGame objects
        int maxGames;
        int numGames;
    public: //Public member functions
        VideoGameLibrary(int max); //Constructor
        ~VideoGameLibrary(); //Deconstructor
        void resizeVideoGamesArray();
        void addVideoGameToArray();
        void displayVideoGames();
        void displayVideoGameTitles();
        void loadVideoGamesFromFile(char* fileName);
        void removeVideoGameFromArray();
        void saveToFile(char* fileName);
};

#endif