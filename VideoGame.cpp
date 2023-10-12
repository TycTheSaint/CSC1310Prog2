/*
	Title:  VideoGame.cpp
	Author:  Tyce Webster & Isaac Essex
    Course: CSC 1310-001
	Date:  9/16/2023
    Due: 9/18/2023
	Purpose:  Create an object that is conceptualized as a video game. This
    oject stores information about the game's title, developer, publisher,
    and year of release. This .cpp also defines functions associated with 
    the VideoGame class.
*/

//Header files
#include "VideoGame.h"
#include "text.h"

//Constructor that is called when all video games information is known and will create new information
VideoGame::VideoGame(Text* title, Text* developer, Text* publisher, int year) //Function parameters
{
    this->title = title; //Initializes the Text* title variable to private variavble of VideoGame title
    this->developer = developer; //Initializes the Text* developer variable to private variavble of VideoGame developer
    this->publisher = publisher; //Initializes the Text* publisher variable to private variavble of VideoGame publisher
    this->year = year; //Initializes the year variable to private variable of VideoGame year
}

//Deconstructor that releases dynamically allocated text arrays in VideoGame class
VideoGame::~VideoGame()
{
    //Releases memory for the video game title, developer, and publisher
    delete title;
    delete developer;
    delete publisher;

    cout << "VideoGame destructor: Released memory for VideoGame object." << endl;
}

//printVideoGameDetails function that prints all the video game information to screen
void VideoGame::printVideoGameDetails()
{
    cout<<"\n\n"<<right<<setw(23)<<"Game Title:"<<left<<"   ";
    title->displayText(); //Prints game title
    cout<<"\n\n"<<right<<setw(23)<<"Developer:"<<left<<"   ";
    developer->displayText(); //Prints game developer
    cout<<"\n\n"<<right<<setw(23)<<"Publisher:"<<left<<"   ";
    publisher->displayText(); //Prints game publisher
    cout<<"\n\n"<<right<<setw(23)<<"Year Released:"<<left<<"   ";
    cout<<year<<endl; //Prints game release year
}

//printVideoGameDetailsToFile function that prints all of video game information to a file
void VideoGame::printVideoGameDetailsToFile(ofstream &outFile) //Function parameters
{
    char temp[100]; //Sets temp character array to a max of 100 characters

    strncpy(temp, title->getText(), 100); //Sets title to the temp character array
    outFile << temp << endl; //Prints title to file
    strncpy(temp, developer->getText(), 100); //Sets developer to the temp character array
    outFile << temp << endl; //Prints developer to file
    strncpy(temp, publisher->getText(), 100); //Sets publisher to the temp character array
    outFile << temp << endl; //Prints publisher to file
    outFile << year; //Prints release year to file
}

//Accessor function that gets data for the title of video game
Text* VideoGame::getVideoGameTitle() const
{
    return title; //Returns video game title to a pointer of a Text object
}