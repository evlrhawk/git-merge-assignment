/***********************************************************************
* Program:
*    Project 13, Sudoku 
*    Brother Comeau, CS124
* Author:
*    Thomas Burr
* Summary: 
*    This program will read a sudou game from a file, and display onto
*    the screen. Then, it will allow the player to edit the game board
*    , redisplay it, and save and quit the game.
*
*    Estimated:  0.0 hrs   
*    Actual:     0.0 hrs
*      Please describe briefly what was the most difficult part.
**********************************************************************/
#include <fstream>
#include <cstdlib>
#include <iostream>
using namespace std;

/**********************************************************************
 * Prompts user for a filename
 *********************************************************************/
void getFilename(char filename[])
{
   cout << "Where is your board located? ";
   cin >> filename;
}

/**********************************************************************
 * Reads content of file into 2D array
 *********************************************************************/
void readFile(char filename[], int board[][9])
{
   ifstream fin(filename);

   if (fin.fail())
      return;

   for (int row = 0; row < 9; row++)
   {
      for (int column = 0; column < 9; column++)
      {
         fin >> board[row][column];
      }
   }

   fin.close();

}

/**********************************************************************
 * Displays instruction to screen
 *********************************************************************/
void displayMenu()
{
   cout << "Options:\n"
        << "   ?  Show these instructions\n"
        << "   D  Display the board\n"
        << "   E  Edit one square\n"
        << "   S  Show the possible values for a square\n"
        << "   Q  Save and Quit\n"
        << endl;
}

/**********************************************************************
 * Displays game board to screen
 *********************************************************************/
void displayBoard(int board[][9])
{
   int count = 0;
   cout << "   A B C D E F G H I\n";
   for (int row = 0; row < 9; row++)
   {
      count++;
      cout << count << "  ";

      for (int column = 0; column < 9; column++)
      {         
         if (column == 2 || column == 5 || column == 8)
         {
            if (board[row][column] == 0)
               cout << " ";
            else
               cout << board[row][column];
         }
         else
         {
            if (board[row][column] == 0)
               cout << "  ";
            else 
               cout << board[row][column] << " ";
         }
         if (column  == 2 || column == 5)
            cout << "|";
      }

      cout << endl;
      if (row == 2 || row == 5)
         cout << "   -----+-----+-----\n";
      
   }
   cout << endl;
}

/**********************************************************************
 * Prompts user for file to save game to
 *********************************************************************/
void getEndFilename(char filename[])
{
   cout << "What file would you like to write your board to: ";
   cin >> filename;
}

/**********************************************************************
 * Saves game to new file
 *********************************************************************/
void saveGame(char filename[], int board[][9])
{
   int count = 0;
   
   ofstream fout(filename);
   
   if (fout.fail())
      return;
   
   for (int row = 0; row < 9; row++)
   {
      for (int column = 0; column < 9; column++)
      { 
         fout << board[row][column] << " ";
         if (count % 8 == 0)
         {
            fout << endl;
         }
         count++;
      }
   }
   
   fout.close();

   cout << "Board written successfully\n";
   return;

}

/**********************************************************************
 * Computes possible values for a given square
 *********************************************************************/
int computeValues(int board[][9], int row, int column
                  , bool possibilities[])
{
   for (int i = 0; i < 9; i++)
   {
      
      if (board[i][column] > 0)
      {
         possibilities[board[i][column] - 1] = false;
      }
   }
   
   for (int j = 0; j < 9; j++)
   {
      
      if (board[row][j] > 0)
      {
         possibilities[board[row][j] - 1] = false;
      }
   }
   
   int newRow = (row / 3) * 3;
   int newColumn = (column / 3) * 3;
   
   
   if (board[newRow][newColumn] > 0)
      possibilities[board[newRow][newColumn] - 1] = false;

   
   if (board[newRow + 1][newColumn] > 0)
      possibilities[board[newRow + 1][newColumn] - 1] = false;

   
   if (board[newRow + 2][newColumn] > 0 )
      possibilities[board[newRow + 2][newColumn] - 1] = false;
   
   
   if (board[newRow][newColumn + 1] > 0)
      possibilities[board[newRow][newColumn + 1] - 1] = false;
   
   
   if (board[newRow][newColumn + 2] > 0)
      possibilities[board[newRow][newColumn + 2] - 1] = false;
   
   
   if (board[newRow + 1][newColumn + 1] > 0)
      possibilities[board[newRow + 1][newColumn + 1] - 1] = false;

   
   if (board[newRow + 1][newColumn + 2] > 0)
      possibilities[board[newRow + 1][newColumn + 2] - 1] = false;

   
   if (board[newRow + 2][newColumn + 1] > 0)
      possibilities[board[newRow + 2][newColumn + 1] - 1] = false;

   
   if (board[newRow + 2][newColumn + 2] > 0)
      possibilities[board[newRow + 2][newColumn + 2] - 1] = false;

}

/**********************************************************************
 * Displays possible values for a given square
 *********************************************************************/
void displayPossibleValues(int board[][9], int row, int column
                           , char coordinates[])
{
   bool possibilities[9];

   for (int j = 0; j < 9; j++)
   {
      possibilities[j] = true;
   }
      
   computeValues(board, row, column, possibilities);
   cout << "The possible values for '" << coordinates << "' are: ";

   int count = 0;
   for (int l = 0; l < 9; l++)
   {
      if (possibilities[l] == true)
         count++;
   }
   int commas = 0;
   for (int i = 0; i < 9; i++)
   {
      if (possibilities[i] == true)
      {
         commas++;
         if (commas != count)
         {
            cout << i + 1 << ", ";
         }
         else
            cout << i + 1;
      }
   }
   cout << endl;
}

/**********************************************************************
 * Prompts user for coordinates of game square
 *********************************************************************/
void getCoordinates(int &row, int &column, char coordinates[])
{
   cout << "What are the coordinates of the square: ";
   cin >> coordinates;

   if (islower(coordinates[0]))
      coordinates[0] = toupper(coordinates[0]);

   if (coordinates[0] == 'A')
      column = 0;
   else if (coordinates[0] == 'B')
      column = 1;
   else if (coordinates[0] == 'C')
      column = 2;
   else if (coordinates[0] == 'D')
      column = 3;
   else if (coordinates[0] == 'E')
      column = 4;
   else if (coordinates[0] == 'F')
      column = 5;
   else if (coordinates[0] == 'G')
      column = 6;
   else if (coordinates[0] == 'H')
      column = 7;
   else if (coordinates[0] == 'I')
      column = 8;

   for (int j = 1; j < 2; j++)
   {
      char *temp = &coordinates[j];
      row = atoi(temp) - 1;
   }
}

/**********************************************************************
 * Edits one square of game board
 *********************************************************************/
void editGame(int board[][9], int row, int column, char coordinates[])
{
   bool possibilities[9];

   for (int j = 0; j < 9; j++)
   {
      possibilities[j] = true;
   }
    
   int value = 0;
   if (board[row][column] != 0)
      cout << "ERROR: Square '" << coordinates << "' is filled\n";
   else
   {
      cout << "What is the value at '" << coordinates << "': ";
      cin >> value;
      computeValues(board, row, column, possibilities);
            
      if (possibilities[value - 1] == false)
      {
         cout << "ERROR: Value '" << value
              << "' in square '" << coordinates << "' is invalid\n";
      }
      else
      {
         board[row][column] = value; 
      }
   }
}

/**********************************************************************
 * Allows user to interact with game
 *********************************************************************/
void interact(char filename[], int board[][9])
{
   char coordinates[2];
   int row = 0;
   int column = 0;
   char command = 0;
   do
   {
      cout << "> ";
      cin >> command;
      if (islower(command))
         command = toupper(command);
      switch (command)
      {
         case '?':
            displayMenu();
            cout << endl;
            break;
         case 'D':
            displayBoard(board);
            break;
         case 'E':
            getCoordinates(row, column, coordinates);
            editGame(board, row, column, coordinates);
            cout << endl;
            break;
         case 'S':
            getCoordinates(row, column, coordinates);
            displayPossibleValues(board, row, column, coordinates);
            cout << endl;
            break;
         case 'Q':
            getEndFilename(filename);
            saveGame(filename, board);
            break;
      }
   }
   while (command != 'Q');
}

/**********************************************************************
 * Calls other functions to run program
 *********************************************************************/
int main()
{
   char filename[32];
   int board[9][9];
   
   for (int i = 0; i < 9; i++)
   {
      for (int j = 0; j < 9; j++)
      {
         board[i][j] = 0;
      }
   }
  
   getFilename(filename);
   readFile(filename, board);
   displayMenu();
   displayBoard(board);
   interact(filename, board);
   return 0;
}
