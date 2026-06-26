#include <iostream>
#include <fstream>
#include <string>

using namespace std;


void saveGame(char **board, int boardSize, int currentPlayer);
// bool checkWinning();
void switchPlayer(int &currentPlayer);
// bool checkEndPoint();
bool validFromCoord(string fromCoord, char **board, int boardSize, string col_string, int &fromRow, int &fromCol, int currentPlayer);
bool validToCoord(string toCoord, char **board, int boardSize, string col_string, int &toRow, int &toCol, int currentPlayer);
void movementLogic(int currentPlayer, char **board, int boardSize);

int main() {
    int currentPlayer = 1;
    int boardSize = 0;
    bool validSize = false;
    bool savedFile = false;
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
                        if (temp == '.') {
                            board[row][col] = ' '; // Convert '.' placeholder back to a clean blank tile
                        } else {
                            board[row][col] = temp; // Assign 'X' or 'O' directly to the board
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


        // New Game
        if(gameChoice == "2")
        {
            validSize = false;

            while(!validSize)
            {
                cout << "Enter your desired board size (1-5)" << endl;
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

            // O pieces at top
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

            // X pieces at bottom
            for(int row = boardSize - 2;
                row < boardSize;
                row++)
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

        bool gameOver = false;

        while (!gameOver) {
            // Display board
            cout << endl;

            for(int row = 0; row < boardSize; row++)
            {
                cout << " ";

                for(int i = 0; i < boardSize * 4 + 1; i++)
                {
                    cout << "-";
                }

                cout << endl;

                cout << "|";

                for(int col = 0; col < boardSize; col++)
                {
                    cout << " " << board[row][col] << " |";
                }

                cout << " " << char('A' + row) << endl;
            }

            cout << " ";

            for(int i = 0; i < boardSize * 4 + 1; i++)
            {
                cout << "-";
            }

            cout << endl;

            cout << " ";

            for(int col = 1; col <= boardSize; col++)
            {
                cout << " " << col << "  ";
            }

            cout << endl << endl;

            movementLogic(currentPlayer, board, boardSize);
            // check has anyone win the game
            // if not then switch to the next player
            switchPlayer(currentPlayer);
        }
        // Free dynamic memory
        if(board != NULL)
        {
            for(int row = 0; row < boardSize; row++)
            {
                delete[] board[row];
            }

            delete[] board;
        }
        return 0;
    }
}







void switchPlayer(int &currentPlayer)
{
    if (currentPlayer == 1)
        currentPlayer = 2;
    else
        currentPlayer = 1;
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
bool validFromCoord(string fromCoord, char **board, int boardSize, string col_string, int &fromRow, int &fromCol, int currentPlayer) {

    if (fromCoord == "x" || fromCoord == "X" ) {
        exit(0);
    }
    else if (fromCoord == "s" || fromCoord == "S") {
        saveGame(board, boardSize, currentPlayer);
        return false;
    }

    char row_char = toupper(fromCoord[0]);
    fromRow = row_char - 'A';

    if (fromCoord.length() == 2) {
        col_string = fromCoord[1];
    }
    else if (fromCoord.length() == 3) {
        col_string = fromCoord[1];
        col_string += fromCoord[2];
    }
    else {
        cout << "Invalid coordinate! Please enter a valid coordinate." << endl;
        return false;
    }

    if (col_string == "1") {
        fromCol = 0;
    }
    else if (col_string == "2") {
        fromCol = 1;
    }
    else if (col_string == "3") {
        fromCol = 2;
    }
    else if (col_string == "4") {
        fromCol = 3;
    }
    else if (col_string == "5") {
        fromCol = 4;
    }
    else if (col_string == "6") {
        fromCol = 5;
    }
    else if (col_string == "7") {
        fromCol = 6;
    }
    else if (col_string == "8") {
        fromCol = 7;
    }
    else if (col_string == "9") {
        fromCol = 8;
    }
    else if (col_string == "10") {
        fromCol = 9;
    }
    else {
        cout << "Invalid column number! Please enter a number between 1 and 10." << endl;
        return false;
    }

    // check if currentPlayer moving their own piece
    char playerPiece;

    if (currentPlayer == 1) {
        playerPiece = 'o'; //when the piece reaches endPoint it will become capital letter
        // need to consider this in the future
    } else {
        playerPiece = 'x';
    }

    // check if is the piece on the board
    if (fromRow < 0 || fromRow > boardSize-1 || fromCol < 0 || fromCol > boardSize-1) {
        cout << "Invalid! That space is off the board. Try again." << endl;
        return false;
    }

    // check if is the coordinate consist any piece
    if (board[fromRow][fromCol] == ' ') {
        cout << "Invalid! There is no piece there. Try again." << endl;
        return false;
    }

    if (board[fromRow][fromCol] != playerPiece) {
        cout << "Invalid! That piece does not belong to you. Try again." << endl;
        return false;
    }

    cout << "Valid piece selected at " << row_char << col_string << "!" << endl;
    return true;
}

bool validToCoord(string toCoord, char **board, int boardSize, string col_string, int &toRow, int &toCol, int currentPlayer) {

    if (toCoord == "x" || toCoord == "X") {
        exit(0);
    }
    else if (toCoord == "s" || toCoord == "S") {
        saveGame(board, boardSize, currentPlayer);
        return false;
    }

    char row_char = toupper(toCoord[0]);
    toRow = row_char - 'A';

    col_string = "";

    if (toCoord.length() == 2) {
        col_string = toCoord[1];
    }
    else if (toCoord.length() == 3) {
        col_string = toCoord[1];
        col_string += toCoord[2];
    }
    else {
        cout << "Invalid coordinate! Please enter a valid coordinate." << endl;
        return false;
    }

    if (col_string == "1") {
        toCol = 0;
    }
    else if (col_string == "2") {
        toCol = 1;
    }
    else if (col_string == "3") {
        toCol = 2;
    }
    else if (col_string == "4") {
        toCol = 3;
    }
    else if (col_string == "5") {
        toCol = 4;
    }
    else if (col_string == "6") {
        toCol = 5;
    }
    else if (col_string == "7") {
        toCol = 6;
    }
    else if (col_string == "8") {
        toCol = 7;
    }
    else if (col_string == "9") {
        toCol = 8;
    }
    else if (col_string == "10") {
        toCol = 9;
    }
    else {
        cout << "Invalid column number! Please enter a number between 1 and 10." << endl;
        return false;
    }

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

void movementLogic(int currentPlayer, char **board, int boardSize) {
    string fromCoord, toCoord, col_string = "";
    int fromRow, toRow, fromCol, toCol;

    cout << "Player " << currentPlayer << " to move!" << endl;
    if (currentPlayer == 1) {
        cout << "Your piece is 'o'" << endl;
    }
    else {
        cout << "Your piece is 'x'" << endl;
    }

    bool successMove = false;

    do {
        cout << "Enter the coordinate of the piece that you would like to move (eg. D4)" << endl <<
                "(Enter S to save and X to exit)" << endl;
        cout << "From which coordinate (Please enter the coordinate without any spacing): ";
        cin >> fromCoord;
        if (validFromCoord(fromCoord, board, boardSize, col_string, fromRow, fromCol, currentPlayer) == false) {
            continue;
        }
        cout << "Enter the destination coordinate (eg. D4)" << endl <<
                "(Enter S to save and X to exit)" << endl;
        cout << "To which coordinate (Please enter the coordinate without any spacing): ";
        cin >> toCoord;
        if (validToCoord(toCoord, board, boardSize, col_string, toRow, toCol, currentPlayer) == false) {
            continue;
        }

        bool validDiagonal = false, isJump = false;
        int middleRow = 0, middleCol = 0;

        if (currentPlayer == 1) {
            // normal moving 1 step
            if (toRow == fromRow +1) {
                if (toCol == fromCol +1 || toCol == fromCol -1 ) {
                    validDiagonal = true;
                }
            }
                else if (toRow == fromRow + 2) {
                if (toCol == fromCol + 2 || toCol == fromCol - 2) {
                    // Find the coordinate of the piece we are jumping over
                    middleRow = fromRow + 1;
                    if (toCol == fromCol + 2) {
                        middleCol = fromCol + 1;
                    } // Jumped right
                    else {
                        middleCol = fromCol - 1;
                    }                      // Jumped left

                    // Check if the middle piece belongs to the OPPONENT
                    if (board[middleRow][middleCol] == 'x' || board[middleRow][middleCol] == 'X') {
                        validDiagonal = true;
                        isJump = true; // We successfully ate someone!
                    } else {
                        cout << "Invalid! You can only jump over an opponent's piece." << endl;
                        continue;
                    }
                }
            }
        }

        // --- PLAYER 2 ('x') MOVES UP (Row - 1 or Row - 2) ---
        else if (currentPlayer == 2) {

            // Rule 1: Normal 1-Step Move
            if (toRow == fromRow - 1) {
                if (toCol == fromCol + 1 || toCol == fromCol - 1) {
                    validDiagonal = true;
                }
            }
            // Rule 2: 2-Step Jump (Eating)
            else if (toRow == fromRow - 2) {
                if (toCol == fromCol + 2 || toCol == fromCol - 2) {

                    // Find the coordinate of the piece we are jumping over
                    middleRow = fromRow - 1;
                    if (toCol == fromCol + 2) { middleCol = fromCol + 1; } // Jumped right
                    else { middleCol = fromCol - 1; }                      // Jumped left

                    // Check if the middle piece belongs to the OPPONENT
                    if (board[middleRow][middleCol] == 'o' || board[middleRow][middleCol] == 'O') {
                        validDiagonal = true;
                        isJump = true;
                    } else {
                        cout << "Invalid! You can only jump over an opponent's piece." << endl;
                        continue;
                    }
                }
            }
        }

        // If it wasn't a 1-step or a valid 2-step jump, reject it
        if (validDiagonal == false) {
            cout << "Invalid move! You must move diagonally forward, or jump an opponent." << endl;
            continue;
        }

        board[toRow][toCol] = board[fromRow][fromCol];
        board[fromRow][fromCol] = ' ';

        successMove = true;

    } while (successMove == false);

    if (successMove) {
        // Display board
        cout << "Player " << currentPlayer << " moved from " << fromCoord << " to " << toCoord << endl;

        // --- DISPLAY BOARD BLOCK ---
        cout << endl;
        for(int row = 0; row < boardSize; row++)
        {
            cout << " ";
            for(int i = 0; i < boardSize * 4 + 1; i++) {
                cout << "-";
            }
            cout << endl;
            cout << "|";

            for(int col = 0; col < boardSize; col++) {
                cout << " " << board[row][col] << " |";
            }
            cout << " " << char('A' + row) << endl;
        }

        cout << " ";
        for(int i = 0; i < boardSize * 4 + 1; i++) {
            cout << "-";
        }
        cout << endl;
        cout << " ";

        for(int col = 1; col <= boardSize; col++) {
            cout << " " << col << "  ";
        }
        cout << endl << endl;
    }
}

