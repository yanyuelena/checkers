#include <iostream>
#include <fstream>
#include <string>

using namespace std;


void saveGame(char **board, int boardSize, int currentPlayer);
// bool checkWinning();
// void switchPlayer(int &currentPlayer);
// bool checkEndPoint();
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
                        file >> temp;

                        // Convert placeholder back into a standard space
                        if (temp == '.') {
                            board[row][col] = ' ';
                        } else {
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

        while(true)
        {
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

            break;
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
                file << board[row][col] << " ";
            }
        }
        file << endl;
    }

    file.close();
    cout << "Game saved successfully!" << endl;

// check if it's a valid move, function to be called in movementLogic (Elena's code is moved up here)
bool validMove(string fromCoord, string toCoord, char **board, int boardSize, string col_string, int &row, int &col, int currentPlayer) {
    char row_char = toupper(fromCoord[0]);
        row = row_char - 'A';
        col_string = ""; // from what i learn online it says that better assign it to empty string good practice wor
        
        if (fromCoord == "x" || fromCoord == "X" || toCoord == "x" || toCoord == "X") {
            exit(0);
        }
        else if (fromCoord == "s" || fromCoord == "S" || toCoord == "s" || toCoord == "S") {
            saveGame(board, boardSize, currentPlayer);
            return false;
        }

        if (fromCoord.length() == 2) {
            col_string = fromCoord[1];
        }
        else if (fromCoord.length() == 3) {
            col_string = fromCoord[1];
            col_string += fromCoord[2];
        }
        else if (toCoord.length() == 2) {
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
            col = 0;
        }
        else if (col_string == "2") {
            col = 1;
        }
        else if (col_string == "3") {
            col = 2;
        }
        else if (col_string == "4") {
            col = 3;
        }
        else if (col_string == "5") {
            col = 4;
        }
        else if (col_string == "6") {
            col = 5;
        }
        else if (col_string == "7") {
            col = 6;
        }
        else if (col_string == "8") {
            col = 7;
        }
        else if (col_string == "9") {
            col = 8;
        }
        else if (col_string == "10") {
            col = 9;
        }
        else {
            cout << "Invalid column number! Please enter a number between 1 and 10." << endl;
            return false;
        }

        // check if is the piece on the board
        if (row < 0 || row >= boardSize || col < 0 || col >= boardSize) {
            cout << "Invalid! That space is off the board. Try again." << endl;
            return false;
        }

        // check if is the coordinate consist any piece
        if (board[row][col] == ' ') {
            cout << "Invalid! There is no piece there. Try again." << endl;
            return false;
        }

        // check if currentPlayer moving their own piece
        char playerPiece;

        if (currentPlayer == 1) {
            playerPiece = 'o';
        } else {
            playerPiece = 'x';
        }

        if (board[row][col] != playerPiece) {
            cout << "Invalid! That piece does not belong to you. Try again." << endl;
            return false;
        }

        cout << "Valid piece selected at " << row_char << col_string << "!" << endl;
        return true;
}

void movementLogic(int currentPlayer, char **board, int boardSize) {
    string fromCoord, toCoord;
    // bool validMove = false;
    string col_string = "";
    int row = 0, col = 0;

    do {
        cout << "Player " << currentPlayer << " to move!" << endl;
        if (currentPlayer == 1) {
            cout << "Your piece is 'o'" << endl;
        }
        else {
            cout << "Your piece is 'x'" << endl;
        }
        cout << "Enter the coordinate of the piece that you would like to move (eg. D4)" << endl <<
                "(Enter S to save and X to exit)" << endl;
        cout << "From which coordinate: ";
        cin >> fromCoord;

/*      (this one can prob delete dy ah but im not sure so i leave here first)
        char row_char = toupper(fromCoord[0]);
        int row = row_char - 'A';
        string col_string = ""; // from what i learn online it says that better assign it to empty string good practice wor

        if (fromCoord.length() == 2) {
            col_string = fromCoord[1];
        }
        else if (fromCoord.length() == 3) {
            col_string = fromCoord[1];
            col_string += fromCoord[2];
        }
        else {
            cout << "Invalid coordinate! Please enter a valid coordinate." << endl;
            continue;
        }

        int col;

        if (col_string == "1") {
            col = 0;
        }
        else if (col_string == "2") {
            col = 1;
        }
        else if (col_string == "3") {
            col = 2;
        }
        else if (col_string == "4") {
            col = 3;
        }
        else if (col_string == "5") {
            col = 4;
        }
        else if (col_string == "6") {
            col = 5;
        }
        else if (col_string == "7") {
            col = 6;
        }
        else if (col_string == "8") {
            col = 7;
        }
        else if (col_string == "9") {
            col = 8;
        }
        else if (col_string == "10") {
            col = 9;
        }
        else {
            cout << "Invalid column number! Please enter a number between 1 and 10." << endl;
            continue;
        }

        // check if is the piece on the board
        if (row < 0 || row >= boardSize || col < 0 || col >= boardSize) {
            cout << "Invalid! That space is off the board. Try again." << endl;
            continue;
        }

        // check if is the coordinate consist any piece
        if (board[row][col] == ' ') {
            cout << "Invalid! There is no piece there. Try again." << endl;
            continue;
        }

        // check if currentPlayer moving their own piece
        char playerPiece;

        if (currentPlayer == 1) {
            playerPiece = 'o';
        } else {
            playerPiece = 'x';
        }

        if (board[row][col] != playerPiece) {
            cout << "Invalid! That piece does not belong to you. Try again." << endl;
            continue;
        }

        cout << "Valid piece selected at " << row_char << col_string << "!" << endl;
    */
       // validMove = true;
    } while (!validMove(fromCoord, toCoord, board, boardSize, col_string, row, col, currentPlayer));

    do {
        cout << "Player " << currentPlayer << " to move!" << endl;
        if (currentPlayer == 1) {
            cout << "Your piece is 'o'" << endl;
        }
        else {
            cout << "Your piece is 'x'" << endl;
        }
        cout << "Enter the destination coordinate (eg. D4)" << endl <<
                "(Enter S to save and X to exit)" << endl;
        cout << "To which coordinate: ";
        cin >> toCoord;
    } while (!validMove(fromCoord, toCoord, board, boardSize, col_string, row, col, currentPlayer));
}
