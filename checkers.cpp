#include <iostream>
using namespace std;

int main() {

displayBoard();

    return 0;
}


void displayBoard()
{
    int size;
    char board[10][10];

    cout << "Enter board size (6 - 10): ";
    cin >> size;

    while(size < 6 || size > 10)
    {
        cout << "Invalid board size!" << endl;
        cout << "Please enter a number between 6 and 10: ";
        cin >> size;
    }

    // Initialize board
    for(int row = 0; row < size; row++)
    {
        for(int col = 0; col < size; col++)
        {
            board[row][col] = ' ';
        }
    }

    // Place O pieces (top 2 rows)
    for(int row = 0; row < 2; row++)
    {
        for(int col = 0; col < size; col++)
        {
            if((row + col) % 2 == 0)
            {
                board[row][col] = 'O';
            }
        }
    }

    // Place X pieces (bottom 2 rows)
    for(int row = size - 2; row < size; row++)
    {
        for(int col = 0; col < size; col++)
        {
            if((row + col) % 2 == 1)
            {
                board[row][col] = 'X';
            }
        }
    }

    cout << endl;

    // Display board
    for(int row = 0; row < size; row++)
    {
        cout << " ";

        for(int i = 0; i < size * 4 + 1; i++)
        {
            cout << "-";
        }

        cout << endl;

        cout << "|";

        for(int col = 0; col < size; col++)
        {
            cout << " " << board[row][col] << " |";
        }

        cout << " " << char('A' + row) << endl;
    }

    // Bottom border
    cout << " ";

    for(int i = 0; i < size * 4 + 1; i++)
    {
        cout << "-";
    }

    cout << endl;

    // Column numbers
    cout << " ";

    for(int col = 1; col <= size; col++)
    {
        cout << " " << col << "  ";
    }

    cout << endl;
}
#include <iostream>
using namespace std;

void displayBoard()
{
    int size;
    char board[10][10];

    cout << "Enter board size (6 - 10): ";
    cin >> size;

    while(size < 6 || size > 10)
    {
        cout << "Invalid board size!" << endl;
        cout << "Please enter a number between 6 and 10: ";
        cin >> size;
    }

    // Initialize board
    for(int row = 0; row < size; row++)
    {
        for(int col = 0; col < size; col++)
        {
            board[row][col] = ' ';
        }
    }

    // Place O pieces (top 2 rows)
    for(int row = 0; row < 2; row++)
    {
        for(int col = 0; col < size; col++)
        {
            if((row + col) % 2 == 0)
            {
                board[row][col] = 'O';
            }
        }
    }

    // Place X pieces (bottom 2 rows)
    for(int row = size - 2; row < size; row++)
    {
        for(int col = 0; col < size; col++)
        {
            if((row + col) % 2 == 1)
            {
                board[row][col] = 'X';
            }
        }
    }

    cout << endl;

    // Display board
    for(int row = 0; row < size; row++)
    {
        cout << " ";

        for(int i = 0; i < size * 4 + 1; i++)
        {
            cout << "-";
        }

        cout << endl;

        cout << "|";

        for(int col = 0; col < size; col++)
        {
            cout << " " << board[row][col] << " |";
        }

        cout << " " << char('A' + row) << endl;
    }

    // Bottom border
    cout << " ";

    for(int i = 0; i < size * 4 + 1; i++)
    {
        cout << "-";
    }

    cout << endl;

    // Column numbers
    cout << " ";

    for(int col = 1; col <= size; col++)
    {
        cout << " " << col << "  ";
    }

    cout << endl;

return 0;
}
