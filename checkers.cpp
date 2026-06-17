#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

int main()
{

int currentPlayer = 1;
string choice;
int boardSize;
bool validSize = false;
bool savedFile;
char board [10][10];

void saveGame;
void checkWinning;
void switchPlayer;
void checkEndPoint;

cout << "Menu ( Enter 'X' to exit game): "<<endl;
     << "1.Load saved game/n 2.Start new game"<< endl;
cin >> choice

while ( choice == 1 || choice == 2 || choice == 'x' || choice == 'X')
{
    if ( choice == 'x' || choice == 'X')
        return 0;
    else
    {
        if (choice == "1")
            {
                ifstream file("savegame.txt");
                
                if (file)
                {
                    file >> boardSize;
                    
                    for (int row = 0; row < boardSize; row++)
                    {
                        for (int col = 0; col < boardSize; col++)
                        {
                            file >> board[row][col];
                        }
                    }
                    file.close();
                    cout << "Saved game loaded!" << endl;
                }
                else
                {
                    cout << "No saved game found! Let's start a new game!" << endl;
                    choice = "2"; // Redirects to start a new game configuration
                }
            }
            
        else
        do
        {
         cout << "\nEnter your desired board size (1-5) (Enter 'X' to exit game):" << endl;
                    cout << "1. 6x6 board\n2. 7x7 board\n3. 8x8 board\n4. 9x9 board\n5. 10x10 board" << endl;
                    cout << "Board size: ";
                    cin >> boardSize;

                    // Handle exit inside the setup loop
                    if (boardSize == 'x' || boardSize == 'X')
                    {
                        return 0;
                    }

                    // --- SWITCH STATEMENT FOR DISPLAYING BOARD SIZE ---
                    switch (boardSize)
                    {
                        case '1':
                            cout << "Display 6x6 board" << endl;
                            boardSize = 6;
                            validSize = true;
                            break;
                        case '2':
                            cout << "Display 7x7 board" << endl;
                            boardSize = 7;
                            validSize = true;
                            break;
                        case '3':
                            cout << "Display 8x8 board" << endl;
                            boardSize = 8;
                            validSize = true;
                            break;
                        case '4':
                            cout << "Display 9x9 board" << endl;
                            boardSize = 9;
                            validSize = true;
                            break;
                        case '5':
                            cout << "Display 10x10 board" << endl;
                            boardSize = 10;
                            validSize = true;
                            break;
                        default:
                            cout << "Please enter a valid number (1-5)." << endl;
                            break; // validSize remains false, loop repeats
                    }
                }while (!validSize);
                
                currentPlayer = 1;
    }
            break; 
}
bool doubleMove = false;

movementLogic();

if (piece = 1 && !doubleMove)
    cout << "Double Move Activated!" << endl;
    doubleMove = true;
    movementLogic();
else
checkEndPoint();

if (checkEndPoint == true)
{
    if (piece == uppercase)
    {
        checkWinning();
    else
        validPower = false;
        //change piece into uppercase

        do{
            cout << "Choose your supperpowers(1-3): " <<endl;
            cout << "1.Double move\n2.Reverse Capture\n3.Boomerang Capture"<< endl;
            cin >> power;

            switch (power)
                    {
                        case '1':
                            //change uppercase piece to piece1
                            validPower = true;
                            break;
                        case '2':
                            //change uppercase piece to piece2
                            validPower = true;
                            break;
                        case '3':
                            //change uppercase piece to piece3
                            validPower = true;
                            break;
                        default:
                            cout << "Please enter a valid number." << endl;
                    }
           }while (!validPower);

        checkWinning();
     }
}

void saveGame (char board [][10], int size)
{
    ofstream saveFile ("savegame.txt");

    saveFile << size << endl;

    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            saveFile << board [row][col];
        }

        saveFile << endl;
    }

    saveFile.close();
    cout << "Game saved successfully!" << endl;

}

void checkWinning()
{

}

void switchPlayer()
{

}

void checkEndPoint()
{

}
