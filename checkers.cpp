// *********************************************************
// Program: checkers.cpp
// Course: CCP6114 Programming Fundamentals
// Lecture Class: TC2L
// Tutorial Class: TT8L
// Trimester: 2610
// Information : 261UC250RK | LEE YANYU ELENA | lee.yanyu.elena1@student.mmu.edu.my | +60 11-6435 1727
// *********************************************************
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


void saveGame(char **board, int boardSize, int currentPlayer);
void switchPlayer(int &currentPlayer);
bool checkEndPoint(char **board, int boardSize, int toRow, int toCol, int currentPlayer);
bool validFromCoord(string fromCoord, char **board, int boardSize, string col_string, int &fromRow, int &fromCol, int currentPlayer);
bool validToCoord(string toCoord, char **board, int boardSize, string col_string, int &toRow, int &toCol, int currentPlayer);
void movementLogic(int currentPlayer, char **board, int boardSize);
bool gameOver = false;
bool winningCondition(char **board, int boardSize);

int main()
{
    int currentPlayer = 1;
    int boardSize = 0;
    char **board = NULL;
    string sizeChoice;
    string gameChoice;

    cout << "Menu (Enter 'X' to exit game):" << endl;
    cout << "1. Load saved game" << endl;
    cout << "2. Start new game" << endl;
    cout << "Choice: ";
    cin >> gameChoice;

    while(gameChoice != "1" && gameChoice != "2" && gameChoice != "x" && gameChoice != "X")
    {
        cout << "Invalid choice! Please enter 1, 2 or X." << endl;
        cout << "Choice: ";
        cin >> gameChoice;
    }

    // exit
    if(gameChoice == "x" || gameChoice == "X")
    {
        return 0;
    }

    // load game
    if(gameChoice == "1")
    {
        ifstream file("savegame.txt");
        if(file)
        {
            file >> boardSize;
            file >> currentPlayer;

            // Allocate memory for the board
            board = new char*[boardSize];
            for(int row = 0; row < boardSize; row++)
            {
                board[row] = new char[boardSize];
            }

            // Read the board normally using standard streams
            for(int row = 0; row < boardSize; row++)
            {
                for(int col = 0; col < boardSize; col++)
                {
                    char temp;
                    file >> temp; // Read the next character, automatically skipping whitespace dividers

                    // Convert placeholder back into a standard space
                    if (temp == '.')
                    {
                        board[row][col] = ' ';
                    }

                    else
                    {
                        board[row][col] = temp;
                    }
                }
            }

            file.close();

            cout << "Saved game loaded!" << endl;
            cout << "Continue previous game!" << endl;
        }
        else
        {
            cout << "No saved game found!" << endl;
            cout << "Let's start a new game!" << endl;

            gameChoice = "2";
        }
    }

    // New game
    if(gameChoice == "2")
    {
        bool validSize = false;

        while(!validSize)
        {
            cout <<"\nWelcome to Checkers Game!" << endl;
            cout << "1. 6x6 board" << endl;
            cout << "2. 7x7 board" << endl;
            cout << "3. 8x8 board" << endl;
            cout << "4. 9x9 board" << endl;
            cout << "5. 10x10 board" << endl;
            cout << "(Enter X to exit game)" << endl;
            cout << "Enter your desired board size (1-5): ";
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

        board = new char*[boardSize];

        for(int row = 0; row < boardSize; row++)
        {
            board[row] = new char[boardSize];
        }

        for(int row = 0; row < boardSize; row++)
        {
            for(int col = 0; col < boardSize; col++)
            {
                board[row][col] = ' ';
            }
        }

        // O pieces (Player 1) on top
        for(int row = 0; row < 2; row++)
        {
            for(int col = 0; col < boardSize; col++)
            {
                if((row + col) % 2 == 0)
                {
                    board[row][col] = 'o';
                }
            }
        }

        // x pieces (Player 2) on bottom
        for(int row = boardSize - 2; row < boardSize; row++)
        {
            for(int col = 0; col < boardSize; col++)
            {
                if((row + col) % 2 == 0)
                {
                    board[row][col] = 'x';
                }
            }
        }

        currentPlayer = 1;
    }

    while (!gameOver)
    {
        // Display board everytime when game still running
        cout << endl;
        for(int row = 0; row < boardSize; row++)
        {
            cout << " ";
            for(int i = 0; i < boardSize * 4 + 1; i++) cout << "-";
            cout << endl << "|";

            for(int col = 0; col < boardSize; col++)
            {
                char visualPiece = board[row][col];

                // to maintain superpower pieces as 'O' and 'X' for visual clarity, while keeping their original values
                if (visualPiece == 'R' || visualPiece == 'B') 
                {
                    visualPiece = 'O';
                }
                if (visualPiece == 'P' || visualPiece == 'V')
                {
                    visualPiece = 'X';
                }

                cout << " " << visualPiece << " |";
            }
            cout << " " << char('A' + row) << endl;
        }
        cout << " ";
        for(int i = 0; i < boardSize * 4 + 1; i++) cout << "-";
        cout << endl << " ";
        for(int col = 1; col <= boardSize; col++) cout << " " << col << "  ";
        cout << endl << endl;

        if (winningCondition(board, boardSize)) break;

        movementLogic(currentPlayer, board, boardSize);

        switchPlayer(currentPlayer);
    }

    if (board != NULL)
    {
        for(int row = 0; row < boardSize; row++) {
            delete[] board[row];
        }
        delete[] board;
    }
    return 0;
}

bool winningCondition(char **board, int boardSize)
{
    bool hasO = false;
    bool hasX = false;

    for (int row = 0; row < boardSize; row++) {
        for (int col = 0; col < boardSize; col++)
        {
            if (board[row][col] == 'o' || board[row][col] == 'O' || board[row][col] == 'R' || board[row][col] == 'B')
            {
                hasO = true;
            }
            if (board[row][col] == 'x' || board[row][col] == 'X' || board[row][col] == 'V' || board[row][col] == 'P')
            {
                hasX = true;
            }
        }
    }
    
    if (!hasO)
    {
        cout <<"\n ===================================================" << endl;
        cout <<   "          CONGRATULATIONS! PLAYER 2 WINS!!         " << endl;
        cout <<" ===================================================" << endl;
        gameOver = true;
        return true;
    }
    
    if (!hasX)
    {
        cout <<"\n ===================================================" << endl;
        cout <<   "          CONGRATULATIONS! PLAYER 1 WINS!!         " << endl;
        cout <<" ===================================================" << endl;
        gameOver = true;
        return true;
    }
    return false;
}


void switchPlayer(int &currentPlayer)
{
    if (currentPlayer == 1)
    {
        currentPlayer = 2;
    }
    else
    {
        currentPlayer = 1;
    }
}

bool checkEndPoint(char **board, int boardSize, int toRow, int toCol, int currentPlayer)
{
    // Check if within board range
    if (toRow < 0 || toRow >= boardSize || toCol < 0 || toCol >= boardSize) return false;

    // Player 1 Upgrades (Reaches Bottom Row)
    if (currentPlayer == 1 && toRow == boardSize - 1 && board[toRow][toCol] == 'o')
    {
        cout << "\n*** Player 1 reached the endpoint! Choose your King's Superpower: ***" << endl;
        cout << "1. Double Move (Move this King twice every single turn)" << endl;
        cout << "2. Reverse Capture (If captured, both pieces explode)" << endl;
        cout << "3. Boomerang Capture (Stays in spot during captures)" << endl;
        cout << "Power (1-3): ";
        string power;
        cin >> power;

        while (power != "1" && power != "2" && power != "3") 
        {
            cout << "Invalid choice! Please enter a valid number (1, 2, or 3): ";
            cin >> power;
        }

        if (power == "2")
        {
            board[toRow][toCol] = 'R';
            cout << "\nUpgraded to REVERSE CAPTURE KING ('O')!" << endl;
        }
        else if (power == "3")
        {
            board[toRow][toCol] = 'B';
            cout << "\nUpgraded to BOOMERANG KING ('O')!" << endl;
        }
        else
        {
            board[toRow][toCol] = 'O';
            cout << "\nUpgraded to DOUBLE MOVE KING ('O')! Power activates next turn." << endl;
        }
        return true;
    }
    // Player 2 Upgrades (Reaches Top Row)
    else if (currentPlayer == 2 && toRow == 0 && board[toRow][toCol] == 'x')
    {
        cout << "\n*** Player 2 reached the endpoint! Choose your King's Superpower: ***" << endl;
        cout << "1. Double Move (Move this King twice every single turn)" << endl;
        cout << "2. Reverse Capture (If captured, both pieces explode)" << endl;
        cout << "3. Boomerang Capture (Stays in spot during captures)" << endl;
        cout << "Power (1-3): ";
        string power;
        cin >> power;

        while (power != "1" && power != "2" && power != "3") 
        {
            cout << "Invalid choice! Please enter a valid number (1, 2, or 3): ";
            cin >> power;
        }

        if (power == "2")
        {
            board[toRow][toCol] = 'P';
            cout << "\nUpgraded to REVERSE CAPTURE KING ('X')!" << endl;
        }
        else if (power == "3")
        {
            board[toRow][toCol] = 'V';
            cout << "\nUpgraded to BOOMERANG KING ('X')!" << endl;
        }
        else
        {
            board[toRow][toCol] = 'X';
            cout << "\nUpgraded to DOUBLE MOVE KING ('X')! Power activates next turn." << endl;
        }
        return true;
    }
    return false;
}

void saveGame(char **board, int boardSize, int currentPlayer)
{
    ofstream file("savegame.txt");

    if(!file)
    {
        cout << "Error! Cannot save game." << endl;
        return;
    }

    // Save metadata
    file << boardSize << endl;
    file << currentPlayer << endl;

    // Save board contents (substituting spaces with periods)
    for(int row = 0; row < boardSize; row++)
    {
        for(int col = 0; col < boardSize; col++)
        {
            if (board[row][col] == ' ') {
                file << '.' << " ";
            } else {
                file << board[row][col] << " "; // Write 'X' or 'O' separated by a space
            }
        }
        file << endl;
    }

    file.close();
    cout << "Game saved successfully!" << endl;
}

    // check if it's a valid move, function to be called in movementLogic
bool validFromCoord(string fromCoord, char **board, int boardSize, string col_string, int &fromRow, int &fromCol, int currentPlayer)
{
    if (fromCoord == "x" || fromCoord == "X" )
    {
        exit(0);
    }
    else if (fromCoord == "s" || fromCoord == "S")
    {
        saveGame(board, boardSize, currentPlayer);
        return false;
    }

    char row_char = toupper(fromCoord[0]);
    fromRow = row_char - 'A';

    if (fromCoord.length() == 2)
    {
        col_string = fromCoord[1];
    }
    else if (fromCoord.length() == 3)
    {
        col_string = fromCoord[1];
        col_string += fromCoord[2];
    }
    else
    {
        cout << "Invalid coordinate! Please enter a valid coordinate." << endl;
        return false;
    }

    if (col_string == "1")       fromCol = 0;
    else if (col_string == "2")  fromCol = 1;
    else if (col_string == "3")  fromCol = 2;
    else if (col_string == "4")  fromCol = 3;
    else if (col_string == "5")  fromCol = 4;
    else if (col_string == "6")  fromCol = 5;
    else if (col_string == "7")  fromCol = 6;
    else if (col_string == "8")  fromCol = 7;
    else if (col_string == "9")  fromCol = 8;
    else if (col_string == "10") fromCol = 9;
    else return false;

    // check if is the piece on the board
    if (fromRow < 0 || fromRow > boardSize-1 || fromCol < 0 || fromCol > boardSize-1)
    {
        cout << "Invalid! That space is off the board. Try again." << endl;
        return false;
    }

    char currentPiece = board[fromRow][fromCol];
    // check if is the coordinate consist any piece
    if (currentPiece == ' ')
    {
        cout << "Invalid! There is no piece there. Try again." << endl;
        return false;
    }

    bool ownsPiece = false;

    if (currentPlayer == 1)
    {
        if (currentPiece == 'o' || currentPiece == 'O' || currentPiece == 'R' || currentPiece == 'B')
        {
            ownsPiece = true;
        }
    }
    else if (currentPlayer == 2)
    {
        if (currentPiece == 'x' || currentPiece == 'X' || currentPiece == 'P' || currentPiece == 'V')
        {
            ownsPiece = true;
        }
    }

    if (!ownsPiece)
    {
        cout << "Invalid! That piece does not belong to you. Try again." << endl;
        return false;
    }

    // valid piece selected message
    if (currentPiece == 'O' || currentPiece == 'X')
    {
        cout << "Selected a [DOUBLE MOVE KING] at " << row_char << col_string << "!" << endl;
    }
    else if (currentPiece == 'R' || currentPiece == 'P')
    {
        cout << "Selected a [REVERSE CAPTURE KING] at " << row_char << col_string << "!" << endl;
    }
    else if (currentPiece == 'B' || currentPiece == 'V')
    {
        cout << "Selected a [BOOMERANG KING] at " << row_char << col_string << "!" << endl;
    }
    else
    {
        cout << "Valid piece selected at " << row_char << col_string << "!" << endl;
    }
    
    return true;
}

bool validToCoord(string toCoord, char **board, int boardSize, string col_string, int &toRow, int &toCol, int currentPlayer)
{
    if (toCoord == "x" || toCoord == "X")
    {
        exit(0);
    }
    else if (toCoord == "s" || toCoord == "S")
    {
        saveGame(board, boardSize, currentPlayer);
        return false;
    }

    char row_char = toupper(toCoord[0]);
    toRow = row_char - 'A';

    col_string = "";

    if (toCoord.length() == 2)
    {
        col_string = toCoord[1];
    }
    else if (toCoord.length() == 3)
    {
        col_string = toCoord[1];
        col_string += toCoord[2];
    }
    else
    {
        cout << "Invalid coordinate! Please enter a valid coordinate." << endl;
        return false;
    }

    if (col_string == "1")       toCol = 0;
    else if (col_string == "2")  toCol = 1;
    else if (col_string == "3")  toCol = 2;
    else if (col_string == "4")  toCol = 3;
    else if (col_string == "5")  toCol = 4;
    else if (col_string == "6")  toCol = 5;
    else if (col_string == "7")  toCol = 6;
    else if (col_string == "8")  toCol = 7;
    else if (col_string == "9")  toCol = 8;
    else if (col_string == "10") toCol = 9;
    else return false;

    // check if the destination is on the board
    if (toRow < 0 || toRow > boardSize-1 || toCol < 0 || toCol > boardSize-1) {
        cout << "Invalid! That space is off the board. Try again." << endl;
        return false;
    }

    // check if is the destination is occupied or empty
    if (board[toRow][toCol] != ' ') {
        cout << "Invalid! It's occupied! Try again." << endl;
        return false;
    }

    return true;
}

void movementLogic(int currentPlayer, char **board, int boardSize)
{
    string fromCoord, toCoord, col_string = "";
    int fromRow, toRow, fromCol, toCol;
    bool successMove = false;
    bool isDoubleMove = false; // for double move king

    cout << "Player " << currentPlayer << "'s turn! ";
    if (currentPlayer == 1)
    {
        cout << "Your piece is 'o'" << endl;
    }
    else {
        cout << "Your piece is 'x'" << endl;
    }

    do {
        cout << "\nEnter the coordinate of the piece to move without spaces(e.g. D4)." << endl
             << "[Enter 'S' to save, or 'X' to exit]" << endl;
        cout << "From  : ";
        cin >> fromCoord;
        if (!validFromCoord(fromCoord, board, boardSize, col_string, fromRow, fromCol, currentPlayer))
        {   
            continue;
        }

        cout << "To    : ";
        cin >> toCoord;
        if (!validToCoord(toCoord, board, boardSize, col_string, toRow, toCol, currentPlayer))
        {
            continue;
        }

        bool validDiagonal = false, isJump = false;
        int middleRow = 0, middleCol = 0;

        // simplify board[fromRow][fromCol] to currentPiece for easier to read
        char currentPiece = board[fromRow][fromCol];
        bool isKing = (currentPiece == 'O' || currentPiece == 'R' || currentPiece == 'B' || currentPiece == 'X' || currentPiece == 'P' || currentPiece == 'V');

        // For double move king
        if (currentPiece == 'O' || currentPiece == 'X')
        {
            isDoubleMove = true;
        }

        if (currentPlayer == 1)
        {
            if (toRow == fromRow + 1 || (isKing && toRow == fromRow - 1)) // moving 1 step
            {
                if (toCol == fromCol + 1 || toCol == fromCol - 1)
                {
                    validDiagonal = true;
                }
            }
            else if (toRow == fromRow + 2) // normal piece jump over oponent piece
            {
                middleRow = fromRow + 1; middleCol = (fromCol + toCol) / 2;
                char mid = board[middleRow][middleCol];
                if (mid == 'x' || mid == 'X' || mid == 'P' || mid == 'V')
                {
                    validDiagonal = true;
                    isJump = true;
                }
            }
            else if (isKing && toRow == fromRow - 2) // king piece jump over oponent piece
            {
                middleRow = fromRow - 1; middleCol = (fromCol + toCol) / 2;
                char mid = board[middleRow][middleCol];
                if (mid == 'x' || mid == 'X' || mid == 'P' || mid == 'V')
                {
                    validDiagonal = true;
                    isJump = true;
                }
                else
                {
                    cout << "Invalid! You can only jump over an opponent piece." << endl;
                    continue;
                }
            }
        }
        else if (currentPlayer == 2) 
        {
            if (toRow == fromRow - 1 || (isKing && toRow == fromRow + 1)) // moving 1 step
            {
                if (toCol == fromCol + 1 || toCol == fromCol - 1)
                {
                    validDiagonal = true;
                }
            }
            else if (toRow == fromRow - 2) // normal piece jump over oponent piece
            {
                middleRow = fromRow - 1; middleCol = (fromCol + toCol) / 2;
                char mid = board[middleRow][middleCol];
                if (mid == 'o' || mid == 'O' || mid == 'R' || mid == 'B')
                {
                    validDiagonal = true;
                    isJump = true;
                }
                else
                {
                    cout << "Invalid! You can only jump over an opponent piece." << endl;
                    continue;
                }
            }
            else if (isKing && toRow == fromRow + 2) // king piece jump over oponent piece
            {
                middleRow = fromRow + 1; middleCol = (fromCol + toCol) / 2;
                char mid = board[middleRow][middleCol];
                if (mid == 'o' || mid == 'O' || mid == 'R' || mid == 'B')
                {
                    validDiagonal = true;
                    isJump = true;
                }
                else
                {
                    cout << "Invalid! You can only jump over an opponent piece." << endl;
                    continue;
                }
            }
        }

        if (!validDiagonal)
        { 
            cout << "Invalid move! You must move diagonally forward, or jump over an opponent." << endl;
            continue;
        }

        board[toRow][toCol] = board[fromRow][fromCol];
        board[fromRow][fromCol] = ' ';

        if (isJump)
        {
            char victim = board[middleRow][middleCol];
            board[middleRow][middleCol] = ' ';
            cout << "\n*** Player " << currentPlayer << " captured an opponent's piece! ***" << endl;

            // reverse capture
            if (victim == 'R' || victim == 'P') {
                cout << "\n*** REVERSE CAPTURE! The captured King destroys the attacker! ***" << endl;
                board[toRow][toCol] = ' ';
                toRow = -1;
            }
            // boomerang capture
            else if (currentPiece == 'B' || currentPiece == 'V')
            {
                cout << "\n*** BOOMERANG CAPTURE! King snaps back to original spot! ***" << endl;
                board[fromRow][fromCol] = board[toRow][toCol];
                board[toRow][toCol] = ' ';
                toRow = fromRow; toCol = fromCol;
            }
            else // combo capture (Omnidirectional Edition)
            {
                int currentRound = 1; // elimination ++
                bool continousJump = true; // jump check
                int currentRow = toRow, currentCol = toCol;

                while (continousJump) 
                {
                    // Assume we won't find a continuous jump this round
                    continousJump = false; 

                    int directionCols[2] = {currentCol - 2, currentCol + 2};

                    // Loop through checking Left (-2) and Right (+2) columns
                    for (int i = 0; i < 2; i++) 
                    {
                        int nextCol = directionCols[i];

                        if (currentPlayer == 1) 
                        {
                            // check standard forward jump (Downwards: +2 rows)
                            int nextRow = currentRow + 2;
                            if (nextRow >= 0 && nextRow < boardSize && nextCol >= 0 && nextCol < boardSize) 
                            {
                                if (board[nextRow][nextCol] == ' ') 
                                {
                                    int nextMidRow = currentRow + 1;
                                    int nextMidCol = (currentCol + nextCol) / 2;
                                    char target = board[nextMidRow][nextMidCol];

                                    if (target == 'x' || target == 'X' || target == 'P' || target == 'V') 
                                    {
                                        board[nextRow][nextCol] = board[currentRow][currentCol];
                                        board[currentRow][currentCol] = ' ';
                                        board[nextMidRow][nextMidCol] = ' ';

                                        currentRound++; // elimination ++
                                        currentRow = nextRow;
                                        currentCol = nextCol;
                                        toRow = nextRow; // Update landing anchors for promotion checks
                                        toCol = nextCol;
                                        continousJump = true; // Loop check passes!
                                        break; // Break the inner loop to restart scanning from new spot
                                    }
                                }
                            }

                            // check backward jump (Upwards: -2 rows) only for KING pieces
                            if (continousJump == false && isKing) 
                            {
                                nextRow = currentRow - 2;
                                if (nextRow >= 0 && nextRow < boardSize && nextCol >= 0 && nextCol < boardSize) 
                                {
                                    if (board[nextRow][nextCol] == ' ') 
                                    {
                                        int nextMidRow = currentRow - 1;
                                        int nextMidCol = (currentCol + nextCol) / 2;
                                        char target = board[nextMidRow][nextMidCol];

                                        if (target == 'x' || target == 'X' || target == 'P' || target == 'V') 
                                        {
                                            board[nextRow][nextCol] = board[currentRow][currentCol];
                                            board[currentRow][currentCol] = ' ';
                                            board[nextMidRow][nextMidCol] = ' ';

                                            currentRound++; // elimination ++
                                            currentRow = nextRow;
                                            currentCol = nextCol;
                                            toRow = nextRow;
                                            toCol = nextCol;
                                            continousJump = true;
                                            break;
                                        }
                                    }
                                }
                            }
                        }

                        else if (currentPlayer == 2) 
                        {
                            // check standard forward jump (Upwards: -2 rows)
                            int nextRow = currentRow - 2;
                            if (nextRow >= 0 && nextRow < boardSize && nextCol >= 0 && nextCol < boardSize) 
                            {
                                if (board[nextRow][nextCol] == ' ') 
                                {
                                    int nextMidRow = currentRow - 1;
                                    int nextMidCol = (currentCol + nextCol) / 2;
                                    char target = board[nextMidRow][nextMidCol];

                                    if (target == 'o' || target == 'O' || target == 'R' || target == 'B') 
                                    {
                                        board[nextRow][nextCol] = board[currentRow][currentCol];
                                        board[currentRow][currentCol] = ' ';
                                        board[nextMidRow][nextMidCol] = ' ';

                                        currentRound++; // elimination ++
                                        currentRow = nextRow;
                                        currentCol = nextCol;
                                        toRow = nextRow;
                                        toCol = nextCol;
                                        continousJump = true;
                                        break;
                                    }
                                }
                            }

                            // check backward jump (Downwards: +2 rows) only for KING pieces
                            if (continousJump == false && isKing) 
                            {
                                nextRow = currentRow + 2;
                                if (nextRow >= 0 && nextRow < boardSize && nextCol >= 0 && nextCol < boardSize) 
                                {
                                    if (board[nextRow][nextCol] == ' ') 
                                    {
                                        int nextMidRow = currentRow + 1;
                                        int nextMidCol = (currentCol + nextCol) / 2;
                                        char target = board[nextMidRow][nextMidCol];

                                        if (target == 'o' || target == 'O' || target == 'R' || target == 'B') 
                                        {
                                            board[nextRow][nextCol] = board[currentRow][currentCol];
                                            board[currentRow][currentCol] = ' ';
                                            board[nextMidRow][nextMidCol] = ' ';

                                            currentRound++; // elimination ++
                                            currentRow = nextRow;
                                            currentCol = nextCol;
                                            toRow = nextRow;
                                            toCol = nextCol;
                                            continousJump = true;
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                if (currentRound > 1) cout << "Chain-capture sequence running! Total captures: " << currentRound << endl;
            }
        }
        successMove = true;
    } while (!successMove);

    // double move king
    if (isDoubleMove && toRow != -1 && !gameOver)
    {

        for(int r = 0; r < boardSize; r++)
        {
            cout << " ";
            for(int i = 0; i < boardSize * 4 + 1; i++) cout << "-";
            cout << endl << "|";
            for(int c = 0; c < boardSize; c++) {
                char visualPiece = board[r][c];
                if (visualPiece == 'R' || visualPiece == 'B') visualPiece = 'O';
                if (visualPiece == 'P' || visualPiece == 'V') visualPiece = 'X';
                cout << " " << visualPiece << " |";
            }
            cout << " " << char('A' + r) << endl;
        }
        cout << " ";
        for(int i = 0; i < boardSize * 4 + 1; i++) cout << "-";
        cout << endl << " ";
        for(int c = 1; c <= boardSize; c++) cout << " " << c << "  ";
        cout << endl << endl;

        // second move starts from first move's destination
        int secondFromRow = toRow;
        int secondFromCol = toCol;
        int secondToRow, secondToCol;
        bool validSecondMove = false;

        cout << "*** DOUBLE MOVE ACTIVE AT " << char('A' + secondFromRow) << (secondFromCol + 1) << "! ***" << endl;

        do {
            cout << "To (Second Move Destination): ";
            cin >> toCoord;
            if (!validToCoord(toCoord, board, boardSize, col_string, secondToRow, secondToCol, currentPlayer))
            {
                continue;
            }

            bool validDiagonal = false, isJump = false;
            int middleRow = 0, middleCol = 0;

            // Verified King boundary rules across all 4 quadrants
            if (secondToRow == secondFromRow + 1 || secondToRow == secondFromRow - 1) {
                if (secondToCol == secondFromCol + 1 || secondToCol == secondFromCol - 1) validDiagonal = true;
            }
            else if (secondToRow == secondFromRow + 2 || secondToRow == secondFromRow - 2) {
                if (secondToCol == secondFromCol + 2 || secondToCol == secondFromCol - 2) {
                    middleRow = (secondFromRow + secondToRow) / 2;
                    middleCol = (secondFromCol + secondToCol) / 2;
                    char mid = board[middleRow][middleCol];

                    if (currentPlayer == 1 && (mid == 'x' || mid == 'X' || mid == 'P' || mid == 'V'))
                    { 
                        validDiagonal = true;
                        isJump = true;
                    }
                    else if (currentPlayer == 2 && (mid == 'o' || mid == 'O' || mid == 'R' || mid == 'B'))
                    { 
                        validDiagonal = true;
                        isJump = true;
                    }
                }
            }

            if (!validDiagonal) {
                cout << "Invalid move vector! King must move diagonally 1 step or jump 2 steps over an opponent." << endl;
                continue;
            }

            board[secondToRow][secondToCol] = board[secondFromRow][secondFromCol];
            board[secondFromRow][secondFromCol] = ' ';

            if (isJump)
            {
                char victim = board[middleRow][middleCol];
                board[middleRow][middleCol] = ' ';
                cout << "\n*** Player " << currentPlayer << " captured an opponent's piece on Second Move! ***" << endl;

                // reverse capture
                if (victim == 'R' || victim == 'P')
                {
                    cout << "\n***  REVERSE CAPTURE! The captured King destroys the attacker! ***" << endl;
                    board[secondToRow][secondToCol] = ' ';
                    secondToRow = -1;
                }
            
                else // combo capture for second move (Cleaned King Edition)
                {
                    int currentRound = 1; // elimination ++
                    bool continousJump = true; // jump check
                    int currentRow = secondToRow, currentCol = secondToCol; // Locked to second move coordinates

                    while (continousJump) 
                    {
                        // Assume we won't find a jump this round
                        continousJump = false; 

                        int directionCols[2] = {currentCol - 2, currentCol + 2};

                        // Loop through checking Left (-2) and Right (+2) columns
                        for (int i = 0; i < 2; i++) 
                        {
                            int nextCol = directionCols[i];

                            if (currentPlayer == 1) 
                            {
                                // check forward jump (Downwards: +2 rows)
                                int nextRow = currentRow + 2;
                                if (nextRow >= 0 && nextRow < boardSize && nextCol >= 0 && nextCol < boardSize) 
                                {
                                    if (board[nextRow][nextCol] == ' ') 
                                    {
                                        int nextMidRow = currentRow + 1;
                                        int nextMidCol = (currentCol + nextCol) / 2;
                                        char target = board[nextMidRow][nextMidCol];

                                        if (target == 'x' || target == 'X' || target == 'P' || target == 'V') 
                                        {
                                            board[nextRow][nextCol] = board[currentRow][currentCol];
                                            board[currentRow][currentCol] = ' ';
                                            board[nextMidRow][nextMidCol] = ' ';

                                            currentRound++; 
                                            currentRow = nextRow;
                                            currentCol = nextCol;
                                            secondToRow = nextRow; 
                                            secondToCol = nextCol;
                                            continousJump = true; 
                                            break; 
                                        }
                                    }
                                }

                                // check backward jump (Upwards: -2 rows) for double move king
                                nextRow = currentRow - 2;
                                if (nextRow >= 0 && nextRow < boardSize && nextCol >= 0 && nextCol < boardSize) 
                                {
                                    if (board[nextRow][nextCol] == ' ') 
                                    {
                                        int nextMidRow = currentRow - 1;
                                        int nextMidCol = (currentCol + nextCol) / 2;
                                        char target = board[nextMidRow][nextMidCol];

                                        if (target == 'x' || target == 'X' || target == 'P' || target == 'V') 
                                        {
                                            board[nextRow][nextCol] = board[currentRow][currentCol];
                                            board[currentRow][currentCol] = ' ';
                                            board[nextMidRow][nextMidCol] = ' ';

                                            currentRound++; 
                                            currentRow = nextRow;
                                            currentCol = nextCol;
                                            secondToRow = nextRow; 
                                            secondToCol = nextCol;
                                            continousJump = true;
                                            break;
                                        }
                                    }
                                }
                            }

                            else if (currentPlayer == 2) 
                            {
                                // check forward jump (Upwards: -2 rows)
                                int nextRow = currentRow - 2;
                                if (nextRow >= 0 && nextRow < boardSize && nextCol >= 0 && nextCol < boardSize) 
                                {
                                    if (board[nextRow][nextCol] == ' ') 
                                    {
                                        int nextMidRow = currentRow - 1;
                                        int nextMidCol = (currentCol + nextCol) / 2;
                                        char target = board[nextMidRow][nextMidCol];

                                        if (target == 'o' || target == 'O' || target == 'R' || target == 'B') 
                                        {
                                            board[nextRow][nextCol] = board[currentRow][currentCol];
                                            board[currentRow][currentCol] = ' ';
                                            board[nextMidRow][nextMidCol] = ' ';

                                            currentRound++; 
                                            currentRow = nextRow;
                                            currentCol = nextCol;
                                            secondToRow = nextRow; 
                                            secondToCol = nextCol;
                                            continousJump = true;
                                            break;
                                        }
                                    }
                                }

                                // check backward jump (Downwards: +2 rows) for double move king
                                nextRow = currentRow + 2;
                                if (nextRow >= 0 && nextRow < boardSize && nextCol >= 0 && nextCol < boardSize) 
                                {
                                    if (board[nextRow][nextCol] == ' ') 
                                    {
                                        int nextMidRow = currentRow + 1;
                                        int nextMidCol = (currentCol + nextCol) / 2;
                                        char target = board[nextMidRow][nextMidCol];

                                        if (target == 'o' || target == 'O' || target == 'R' || target == 'B') 
                                        {
                                            board[nextRow][nextCol] = board[currentRow][currentCol];
                                            board[currentRow][currentCol] = ' ';
                                            board[nextMidRow][nextMidCol] = ' ';

                                            currentRound++; 
                                            currentRow = nextRow;
                                            currentCol = nextCol;
                                            secondToRow = nextRow; 
                                            secondToCol = nextCol;
                                            continousJump = true;
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    
                    if (currentRound > 1) cout << "Chain-capture sequence running on Second Move! Total captures: " << currentRound << endl;
                }
            }

            // Lock final tracking targets for potential endgame checks
            toRow = secondToRow;
            toCol = secondToCol;
            validSecondMove = true;
        } while (!validSecondMove);
    }

    checkEndPoint(board, boardSize, toRow, toCol, currentPlayer);
}
