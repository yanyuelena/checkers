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
