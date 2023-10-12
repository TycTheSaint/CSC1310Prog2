/*
	Title:  VideoGameLibrary.cpp
	Author:  Tyce Webster & Isaac Essex
    Course: CSC 1310-001
	Date:  9/16/2023
    Due: 9/18/2023
	Purpose:  Create a video game library that creates, stores, and displays 
    user data. Functions for the VideoGameLibrary Class are also defined here.
*/
//Header files
#include "VideoGameLibrary.h"
#include "VideoGame.h"

//Constructor that is called when a VideoGameLibrary object is created and it creates a library of video games
VideoGameLibrary::VideoGameLibrary(int max) //Function parameters
{
    maxGames = max;
    numGames = 0;
    //Dynamically allocate videoGamesArray to VideoGame objects based of the size of maxGames
    videoGamesArray = new VideoGame*[maxGames];
}

//Deconstructor that releases the dynamically created individual video games and the array
VideoGameLibrary::~VideoGameLibrary()
{
    //For loop iterates through each item of videoGamesArray and deletes each individual item
    for(int i = 0; i < numGames; i++)
    {
        delete videoGamesArray[i];
    }
    //Deletes videoGamesArray array memory
    delete [] videoGamesArray;

    cout << "VideoGameLibrary destructor: Released memory for each game in the video game array and the array itself." << endl;
}

//resizeVideoGamesArray function is called when array size of addVideoGameToArray function is not big enough to hold new data
void VideoGameLibrary::resizeVideoGamesArray()
{
    int max = maxGames * 2; //Doubles the size of max variable
    //Prints new resized variable
    cout << "\nResizing videoGamesArray from " << maxGames << " to " << max << ".";
    //Dynamically allocates newArry to new size of max
    VideoGame** newArry = new VideoGame*[max];
    //For-loop that iterates through the new set of the array moves the data of videoGamesArray
    for(int i = 0; i < numGames; i++)
    {
        newArry[i] = videoGamesArray[i];
    }
    
    delete [] videoGamesArray; //Releases data from videoGamesArray
    videoGamesArray = newArry;
    maxGames = max;
}

//addVideoGameToArray function that called when user needs to add a single video game to the library
void VideoGameLibrary::addVideoGameToArray()
{
    //Variables used
    char temp[100]; //Temp character array that has a size of 100 characters
    Text* title;
    Text* dev;
    Text* pub;
    int y;

    //Recieve user input
    cout << "\nVideo Game TITLE:  ";
    cin.ignore();
    cin.getline(temp, 100); //Gets title
    title = new Text(temp); //Sets title to the new Text object

    cout << "\nVideo Game DEVELOPER:  ";
    cin.getline(temp, 100); //Gets developer
    dev = new Text(temp); //Sets dev to the new Text object 

    cout << "\nVideo Game PUBLISHER:  ";
    cin.getline(temp, 100); //Gets publisher
    pub = new Text(temp); //Sets pub to the new Text object 

    cout << "\nVideo Game YEAR:  ";
    cin >> y; //Gets release year

    //creates VideoGame from new video game data and sends it to VideoGame constructor
    VideoGame* game = new VideoGame(title, dev, pub, y);

    //adds to library
    videoGamesArray[numGames] = game;

    //check array size
    if(numGames==maxGames){
        resizeVideoGamesArray();
    }

    numGames++; //Increments numGames
}

//displayVideoGames function that prints video games in library to the screen
void VideoGameLibrary::displayVideoGames()
{
    //For-loop iterates through videoGamesArray and prints them to the screen
    for(int i = 0; i < numGames; i++)
    {
        cout<<"\n\n"<<right<<setw(25)<<" "<<"--------Video Game "<<i+1<<"--------";
        videoGamesArray[i]->printVideoGameDetails();
    }
}

//displayVideoGameTitles function that prints the title of the games if the user wants to remove a game
void VideoGameLibrary::displayVideoGameTitles()
{
    Text* gameTitle;

    //Iterates through videoGamesArray and displays video game titles onto the screen
    for(int i = 0; i < numGames; i++) 
    {
        cout<<"\nVideo Game "<<i+1<<": ";
        gameTitle = videoGamesArray[i]->getVideoGameTitle();
        gameTitle->displayText();
    }
}

//loadVideoGamesFromFile function that allows user to read data from file and add video games to video game library
void VideoGameLibrary::loadVideoGamesFromFile(char* fileName) //Function paramters
{
    //Variables used
    ifstream inFile;
    char temp[100];
    int numGamesFromFile = 0, y;
    Text* title;
    Text* dev;
    Text* pub;
    VideoGame* constructObj;

    inFile.open(fileName); //Opens file
    
    if(inFile.good())
    {
        inFile.getline(temp, 100);
        //While-loop that goes through title, developer, publisher, and year of video game and adds them to a file
        while(!inFile.eof())
        {
            title = new Text(temp); //Sets temp to title variable
            inFile.getline(temp, 100);
            dev = new Text(temp); //Sets temp to dev variable
            inFile.getline(temp, 100);
            pub = new Text(temp); //Sets temp to pub variable
            inFile >> y;
            inFile.ignore();

            constructObj = new VideoGame(title, dev, pub, y); //Sends data to VideoGame constructor

            //Calls resizeVideoGamesArray function if numGames is equal to the maxGames variable
            if(numGames == maxGames)
            {
                resizeVideoGamesArray();
            }

            videoGamesArray[numGames] = constructObj; //Sets the videoGamesArray to new constructObj object

            numGames++; //Increments numGames

            cout << endl;
            title->displayText(); //Displays title to screen 
            cout << " was added successfully.";

            inFile.getline(temp, 100); //Reads next title of video game if needed
            numGamesFromFile++;
        }

        cout << "\n\n" << numGamesFromFile << " video games were read from the file and added to your VideoGame library.\n";
    }
    else
    {
        cout << "\nSorry, I was unable to open the file.\n";
    }
    
}

//removeVideoGameFromArray function that removes one video game from library if user wants 
void VideoGameLibrary::removeVideoGameFromArray()
{
    //Variables used
    int choice, indexRemoved, elementChange;
    Text* gameTitle;

    //Checks if there is less than or equal to one game in library
    if(numGames <= 1)
    {
        cout << "There must at least be one game in your library.\n";
    }

    cout << "\n\nChoose from the following video games to remove:\n";
    displayVideoGameTitles(); //Prints all video game titles
    cout << "\nChoose a video game to remove between 1 & " << numGames << ":  ";
    cin >> choice; //User inputs what game they want to remove

    //Checks that user inputed valid choice
    while(choice < 1 || choice > numGames)
    {
        cout << "\nInvalid choice, please choose between 1 & " << numGames << ":  ";
        cin >> choice;
    }

    indexRemoved = choice - 1; 
    gameTitle = videoGamesArray[indexRemoved]->getVideoGameTitle(); //Removes index of the item deleted of the videoGamesArray

    cout << "\n\nThe video game \"";
    gameTitle->displayText();
    cout << "\" has been successfully deleted.\n\n";

    //Releases memory of that video game from videoGamesArray
    delete videoGamesArray[indexRemoved];

    elementChange = numGames - 1;

    //For-loop moves each element of the array to replace the removed element
    for(int i = indexRemoved; i < elementChange; i++)
    {
        videoGamesArray[i] = videoGamesArray[i + 1];
    }

    videoGamesArray[elementChange] = NULL; //Sets last item of array to a null pointer

    numGames--; //Decrements numGames
}

//saveToFile function that prints all data from video game library to a file
void VideoGameLibrary::saveToFile(char* fileName) //Function paramters 
{
    //Variables used 
    ofstream outFile;

    outFile.open(fileName); //Opens file 

    //For-loop iterates through videoGamesArray and prints data to a file through the printVideoGameDetailsToFile function
    for(int i = 0; i < numGames; i++)
    {
        videoGamesArray[i]->printVideoGameDetailsToFile(outFile);
    }

    outFile.close(); //Closes file

    cout << "\nAll video games in your library have been printed to " << fileName << endl;
}