#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void saveGame(char board[][10], int boardSize, int currentPlayer);
// bool checkWinning();
// void switchPlayer(int &currentPlayer);
// bool checkEndPoint();
void movementLogic(int currentPlayer, char board[][10], int boardSize);

int main() {
    int currentPlayer = 1;
    int boardSize = 0;
    bool validSize = false;
    bool savedFile = false;
    char board[10][10];

    string sizeChoice;
    string gameChoice;

    cout << "Menu (Enter 'X' to exit game):" << endl;
    cout << "1. Load saved game" << endl;
    cout << "2. Start new game" << endl;
    cin >> gameChoice;

    while(gameChoice == "1" || gameChoice == "2" || gameChoice == "x" || gameChoice == "X")
    {
        // Exit
        if(gameChoice == "x" || gameChoice == "X")
        {
            return 0;
        }

        // Load Game
        if(gameChoice == "1")
        {
            ifstream file("savegame.txt");

            if(file)
            {
                savedFile = true;

                file >> boardSize;
                file >> currentPlayer;

                for(int row = 0; row < boardSize; row++)
                {
                    for(int col = 0; col < boardSize; col++)
                    {
                        file >> board[row][col];
                    }
                }

                file.close();


                cout << "Saved game loaded!" << endl;
                cout << "Continue previous game!" << endl;
                cout << "Board Size: " << boardSize << endl;
                cout << "Current Player: " << currentPlayer << endl;
            }
            else
            {
                cout << "No saved game found!" << endl;
                cout << "Let's start a new game!" << endl;

                gameChoice = "2";
            }
        }

        // New Game
        if(gameChoice == "2")
        {
            validSize = false;

            while(!validSize)
            {
                cout << "\nEnter your desired board size (1-5)" << endl;
                cout << "(Enter X to exit game)" << endl;
                cout << "1. 6x6 board" << endl;
                cout << "2. 7x7 board" << endl;
                cout << "3. 8x8 board" << endl;
                cout << "4. 9x9 board" << endl;
                cout << "5. 10x10 board" << endl;
                cin >> sizeChoice;

                if(sizeChoice == "X" || sizeChoice == "x")
                {
                    return 0;
                }

                switch(sizeChoice[0])
                {
                    case '1':
                        boardSize = 6;
                        validSize = true;
                        break;

                    case '2':
                        boardSize = 7;
                        validSize = true;
                        break;

                    case '3':
                        boardSize = 8;
                        validSize = true;
                        break;

                    case '4':
                        boardSize = 9;
                        validSize = true;
                        break;

                    case '5':
                        boardSize = 10;
                        validSize = true;
                        break;

                    default:
                        cout << "Please enter a valid number." << endl;
                }
            }

            currentPlayer = 1;
        }

        bool doubleMove = false;

        movementLogic(currentPlayer, board, boardSize);

        if(/* piece == PIECE1 */ false && !doubleMove)
        {
            cout << "Double Move Activated!"
                 << endl;

            doubleMove = true;

        movementLogic(currentPlayer, board, boardSize);
        }

        /* if(checkEndPoint())
        {
            // Superpower selection logic here
        }

        if(checkWinning())
        {
            cout << "Game Over! Player " << currentPlayer << " wins!" << endl;

            return 0;
        }
        else
        {
            switchPlayer(currentPlayer);
        }

        break;
    }
    */
        return 0;
    }
}


void saveGame(char board[][10],
              int boardSize,
              int currentPlayer)
{
    ofstream saveFile("savegame.txt");

    if(!saveFile)
    {
        cout << "Error saving file!" << endl;
        return;
    }

    saveFile << boardSize << endl;
    saveFile << currentPlayer << endl;

    for(int row = 0; row < boardSize; row++)
    {
        for(int col = 0; col < boardSize; col++)
        {
            saveFile << board[row][col] << " ";
        }

        saveFile << endl;
    }

    saveFile.close();

    cout << "Game saved" << endl;
}

void movementLogic(int currentPlayer, char board[][10], int boardSize) {
    string fromCoord, toCoord;
    bool invalidMove = false;

    while (!invalidMove) {
        cout << "Player " << currentPlayer << " to move!" << endl;
        cout << "Enter the coordinate of the piece that you would like to move (eg. D4)" << endl <<
                "(Enter S to save and X to exit)" << endl;
        cin >> fromCoord;

        if (fromCoord == "x" || fromCoord == "X") {
            exit(0);
        }
        else if (fromCoord == "s" || fromCoord == "S") {
            saveGame(board, boardSize, currentPlayer);
            continue;
        }
        // else if （to check whether the piece belongs to currentPlayer
    }
}