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
