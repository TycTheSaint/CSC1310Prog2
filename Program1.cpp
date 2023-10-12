/*
	Title:  Program1.cpp
	Author:  Tyce Webster & Isaac Essex
    Course: CSC 1310-001
	Date:  9/16/2023
    Due: 9/18/2023
	Purpose: Format an interactive user menu that allows the user to create
    and modify a video game library where they can save and load games from 
    a file, add or remove games from the library, and display all of the
    library's games a list for easy reading

*/
//Header files
#include "VideoGameLibrary.h"

//Main function
int main()
{
    //Variables used
    int input, num;
    char filename[100];

    cout << "How many video games can your library hold?\n"; //Asks user for amount of games held
    cin >> num; 

    //Check for valid input
    while(num <= 0)
    {
        cout << "Your library should at least hold one game :/\n";
        cout << "How many video games can your library hold?\n";
        cin >> num;
    }

    //Create our Library. We refer to and modify this library for the 
    //remainder of the program.
    VideoGameLibrary* videoGameLibrary = new VideoGameLibrary(num);

    do
    {
        //Basic user menu
        cout << "\nWhat would you like to do?\n";
        cout << "1.  Load video games from file.\n";
        cout << "2.  Save video games to a file.\n";
        cout << "3.  Add a video game.\n";
        cout << "4.  Remove a video game.\n";
        cout << "5.  Display all video games.\n";
        cout << "6.  Remove ALL video games from this Library and end program.\n";
        cout << "CHOOSE 1-6:  ";
        cin >> input;

        //Check for valid input
        while(input < 1 || input > 6)
        {
            cout << "\nThat is not a valid choice.\n";
            cout << "CHOOSE 1-6:  ";
            cin >> input;
        }

        //Read input
        switch(input)
        {
            case 1:
                    cout << "\n\nWhat is the name of the file? (example.txt):  ";
                    cin >> filename;
                    videoGameLibrary->loadVideoGamesFromFile(filename); //Calls loadVideoGamesFromFile function
                    break;

            case 2:
                    cout << "\n\nWhat do you want to name the file? (example.txt):  ";
                    cin >> filename;
                    videoGameLibrary->saveToFile(filename); //Calls saveToFile function
                    break;

            case 3:
                    videoGameLibrary->addVideoGameToArray(); //Calls addVideoGameToArray function
                    break;

            case 4:
                    videoGameLibrary->removeVideoGameFromArray(); //Calls removeVideoGameFromArray function
                    break;

            case 5:
                    videoGameLibrary->displayVideoGames(); //Calls displayVideoGames functions
                    break;

        }
    
    //Repeat until user is finished
    } while (input != 6);

    //Formatting
    cout<<endl;

    //Deallocate pointers
    delete videoGameLibrary;

    cout << "\n\nGOODBYE!";
    
    return 0;
}