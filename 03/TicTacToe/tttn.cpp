// NxN tic-tac-toes
#include <iostream>
#include <cmath>
using namespace std;

// Terminal command: g++ -g -Wall tttn.cpp -0 tttn

// The following 3 functions are helper functions to convert
// between 1D and 2D array indices.  The grid itself is stored
// as a 1D array.  However, for printing, checking who won,
// etc. it may be easier to write loops that generate separate
// row/column indices (i.e. treating the array like a 2D array).
// The functions below should be written using the hints in the
// writeup for performing the appropriate arithmetic conversion
// between 1D- and 2D-indices, and can then be called in any
// of the other functions when wanting to convert one to the other.

/**
 * Helper function - Given the grid array and its dimension
 *    as well as a particular row (r) and column (c), this
 *    function performs the arithmetic to convert r and c
 *    to a 1D index and returns that character in the grid.
 *    For example, for dim = 3 and r = 2, c = 1, this function
 *    should compute the corresponding index: 7 and return
 *    grid[7].
 *
 *    Generate row/column
 *    indices and want to access that element in the grid.
 *    Pass the row/column indices as r and c, respectively.
 *
 */
char getEntryAtRC(char grid[], int dim, int r, int c);

/**
 * Helper function - Given a 1D index returns the row
 * that corresponds to this 1D index.  Use this in
 * conjunction with idxToCol() anytime, Convert 1D index to 2D indices.
 */
int idxToRow(int idx, int dim);

/**
 * Helper function - Given a 1D index returns the column
 * that corresponds to this 1D index.  Use this in
 * conjunction with idxToRow() anytime Convert 1D index to 2D indices.
 */
int idxToCol(int idx, int dim);

/** Should print the tic-tac-toe board in a nice grid
 *  format as shown below:
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O'
 *         (the letter oh), or '?'.
 */
void printTTT(char grid[], int dim);

/**
 * Should check if any player has won the game yet.
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O', or '?'
 *
 * Return value:
 *   Should return 1 if 'X' has won, 2 if 'O' has won, or 0 (zero)
 *   if the game is still undecided.
 *
 */
int checkForWinner(char grid[], int dim);

/**
 * Should check if there is no possible way any player can win.
 * More specifically, if there does not exist a row, column,
 * or diagonal that can still have 3 of a kind, then the game
 * will be a draw.
 *
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O', or '?'
 *
 * Return value:
 *   Return true if no player can win given the current
 *   game state, false otherwise.
 */
bool checkForDraw(char grid[], int dim);

char getEntryAtRC(char grid[], int dim, int r, int c)
{
    int gridIdx = 0; //variable that helps manage index of gird array
    for (int i = 0; i < dim; i++)// i = row
    {
        for (int j = 0; j < dim; j++)// j = col
        {
            if (i == r && j == c)
            {
                return grid[gridIdx];
            }
            gridIdx += 1;
        }
    }
}

int idxToRow(int idx, int dim)
{
    int idxcount = 0; //variable that helps count index
    for (int i = 0; i < dim; i++)// i = row
    {
        for (int j = 0; j < dim; j++)// j = col
        {
            if (idxcount == idx)
            {
                return i;
            }
            idxcount++;
        }
    }
}

int idxToCol(int idx, int dim)
{
    int idxcount = 0; 
    for (int i = 0; i < dim; i++)// i = row
    {
        for (int j = 0; j < dim; j++)// j = col
        {
            if (idxcount == idx)
            {
                return j;
                break;
            }
            idxcount++;
        }
    }
}

void printTTT(char grid[], int dim)
{
    int gridIdx = 0; 
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            cout << " " << grid[gridIdx];
            if (j != dim - 1)
            {
                cout << " |";
            }
            else
            {
                cout << " ";
            }
            gridIdx++;
        }
        if (i != dim - 1)
        {
            cout << endl;
            for (int i = 0; i < 4 * dim - 1; i++)
            {
                cout << "-";
            }
            cout << endl;
        }
    }
}

int checkForWinner(char grid[], int dim)
{
    // returns 0 when O Player wins
    // returns 1 when X Player wins

    //Check for winner in row
    for (int i = 0; i < dim; i++)// i = row
    {
        int OwinRow = 0;
        int XwinRow = 0;
        for (int j = 0; j < dim; j++)// j = col
        {
            if (getEntryAtRC(grid, dim, i, j) == 'O')
            {
                OwinRow += 1;
            }
            else if (getEntryAtRC(grid, dim, i, j) == 'X')
            {
                XwinRow += 1;
            }
        }
        if (OwinRow == dim)
        {
            return 0;
        }
        else if (XwinRow == dim)
        {
            return 1;
        }
    }

    //Check for winner in Column
    for (int i = 0; i < dim; i++)// i = col
    {
        int OwinCol = 0;
        int XwinCol = 0;
        for (int j = 0; j < dim; j++) // j = row
        {
            if (getEntryAtRC(grid, dim, j, i) == 'O')
            {
                OwinCol += 1;
            }
            else if (getEntryAtRC(grid, dim, j, i) == 'X')
            {
                XwinCol += 1;
            }
        }
        if (OwinCol == dim)
        {
            return 0;
        }
        else if (XwinCol == dim)
        {
            return 1;
        }
    }

    //Check for winner in Diagonal from left top to right bottom, Diagonal 1
    int OwinD1 = 0;
    int XwinD1 = 0;
    for (int i = 0; i <= dim - 1; i++)// i = row & column
    {
        if (getEntryAtRC(grid, dim, i, i) == 'O')
        {
            OwinD1 += 1;
        }
        else if (getEntryAtRC(grid, dim, i, i) == 'X')
        {
            XwinD1 += 1;
        }
    }
    if (OwinD1 == dim)
    {
        return 0;
    }
    else if (XwinD1 == dim)
    {
        return 1;
    }

    //Check for winner in Diagonal from right top to left bottom, Diagonal 2
    int colIdx = dim - 1;
    int OwinD2 = 0;
    int XwinD2 = 0;
    for (int i = 0; i < dim; i++)// i = row
    {
        if (getEntryAtRC(grid, dim, i, colIdx) == 'O')
        {
            OwinD2 += 1;
        }
        else if (getEntryAtRC(grid, dim, i, colIdx) == 'X')
        {
            XwinD2 += 1;
        }
        if (colIdx > 0)
        {
            colIdx--;
        }
        else if (colIdx == 0)
        {
            if (OwinD2 == dim)
            {
                return 0;
            }
            else if (XwinD2 == dim)
            {
                return 1;
            }
        }
    }
}

bool checkForDraw(char grid[], int dim)
{
    // returns 0 when X and O player draw

    //Check for Draw in row
    bool DrawResult = false;//use for determine whether it is draw

    for (int i = 0; i < dim; i++)// i = row
    {
        int ODrawRow = 0;
        int XDrawRow = 0;
        for (int j = 0; j < dim; j++)// j = col
        {
            if (getEntryAtRC(grid, dim, i, j) == 'O')
            {
                ODrawRow += 1;
            }
            else if (getEntryAtRC(grid, dim, i, j) == 'X')
            {
                XDrawRow += 1;
            }
        }
        if (ODrawRow >= 1 && XDrawRow >= 1)
        {
            DrawResult = true;
        }
        else
        {
            return false;
        }
    }

   //Check for Draw in row
    for (int i = 0; i < dim; i++)// i = col
    {
        int ODrawCol = 0;
        int XDrawCol = 0;
        for (int j = 0; j < dim; j++) // j = row
        {
            if (getEntryAtRC(grid, dim, j, i) == 'O')
            {
                ODrawCol += 1;
            }
            else if (getEntryAtRC(grid, dim, j, i) == 'X')
            {
                XDrawCol += 1;
            }
        }
        if (ODrawCol >= 1 && XDrawCol >= 1)
        {
            DrawResult = true;
        }
        else
        {
            return false;
        }
    }

    //Check for Draw in Diagonal 1
    // i = row & columnd diagonal right top to left bottom has same value
    // when we consider its array index.
    int ODrawD1 = 0;
    int XDrawD1 = 0;
    for (int i = 0; i < dim; i++)
    {
        if (getEntryAtRC(grid, dim, i, i) == 'O')
        {
            ODrawD1 += 1;
        }
        else if (getEntryAtRC(grid, dim, i, i) == 'X')
        {
            XDrawD1 += 1;
        }
    }
    if (ODrawD1 >= 1 && XDrawD1 >= 1)
    {
        DrawResult = true;
    }
    else
    {
        return false;
    }

    //Check for Draw in Diagonal 2
    int colIdx = dim - 1; //colIdx is the right end of the column
    int ODrawD2 = 0;
    int XDrawD2 = 0;
    for (int i = 0; i < dim; i++)// i = row
    {
        if (getEntryAtRC(grid, dim, i, colIdx) == 'O')
        {
            ODrawD2 += 1;
        }
        else if (getEntryAtRC(grid, dim, i, colIdx) == 'X')
        {
            XDrawD2 += 1;
        }
        if (colIdx > 0)
        {
            colIdx--;
        }
        else
        {
            if (ODrawD2 >= 1 && XDrawD2 >= 1)
            {
                DrawResult = true;
            }
            else
            {
                return false;
            }
        }
    }
    return DrawResult;
}

int main()
{
    // This array holds the actual board/grid of X and Os. It is sized
    // for the biggest possible case (11x11). Should only
    // use dim^2 entries (i.e. if dim=3, only use 9 entries: 0 to 8)
    char tttdata[121];

    // dim stands for dimension and is the side length of the
    // tic-tac-toe board i.e. dim x dim (3x3 or 5x5).
    int dim;
    // Get the dimension from the user
    cout << "Enter the dimensions for your board: ";
    cin >> dim;

    int dim_sq = dim * dim;

    for (int i = 0; i < dim_sq; i++)
    {
        tttdata[i] = '?';
    }

    // Print one of these messages when the game is over
    // and before you quit
    const char xwins_msg[] = "X player wins!";
    const char owins_msg[] = "O player wins!";
    const char draw_msg[] = "Draw...game over!";

    bool done = false;
    // char player = 'X';
    // Show the initial starting board
    printTTT(tttdata, dim);

    bool XTurn = true; // bool variable to determine the turn between O and X 

    while (!done)
    {
        //**********************************************************
        // Get the current player's input (i.e. the location they want to
        // choose to place their mark [X or O]) and update the tttdata array.
        // Be sure to follow the requirements defined in the guide/writeup
        // for quitting immediately if the user input is out-of-bounds
        // (i.e. not in the range 0 to dim_sq-1) as well as continuing to
        // prompt for an input if the user chooses locations that have already
        // been chosen (already marked with an X or O).
        //**********************************************************

        if (XTurn == true) // It's player X's turn
        {
            int XInput;
            cout << endl;
            cout << "Player X enter your square choice [0-" << dim_sq - 1 << "]" << endl;
            cin >> XInput;
            if (XInput > (dim_sq - 1))
            {
                cout << "The input is out of boundaries." << endl;
                done = true;
                break;
            }
            else if (tttdata[XInput] == 'O' || tttdata[XInput] == 'X')
            {
                cout << "This spot has already been taken";
                continue;
            }
            else
            {
                tttdata[XInput] = 'X';
                XTurn = false;
            }
        }
        else // It's player O's turn used XTurn
        {
            int OInput;
            cout << endl;
            cout << "Player O enter your square choice [0-" << dim_sq - 1 << "]" << endl;
            cin >> OInput;
            if (OInput > (dim_sq - 1))
            {
                cout << "The input is out of boundaries." << endl;
                done = true;
                break;
            }
            else if (tttdata[OInput] == 'O' || tttdata[OInput] == 'X')
            {
                cout << "This spot has already been taken";
                continue;
            }
            else
            {
                tttdata[OInput] = 'O';
                XTurn = true;
            }
        }

        // Show the updated board if the user eventually chose a valid location
        // (i.e. quit the loop and program by now without any
        //  other output message if the user chosen an out-of-bounds input).
        printTTT(tttdata, dim);

        //**********************************************************
        // Complete the body of the while loop to process the input that was just
        //  received to check for a winner or draw and update other status, as
        //  needed.
        //
        // To match our automated checkers' expected output, must output
        // one of the messages defined above using *one* of the cout commands
        // (under the appropriate condition) below:
        //   cout << xwins_msg << endl;  OR
        //   cout << owins_msg << endl;  OR
        //   cout << draw_msg << endl;
        //
        // Note: Our automated checkers will examine a specific number of lines
        //  at the end of the program's output and expect to see the updated board
        //  and game status message.  You may certainly add some debug print
        //  statements during development but they will need to be removed to
        //  pass the automated checks.
        //**********************************************************
        if (checkForWinner(tttdata, dim) == 0)
        {
            cout << endl;
            cout << owins_msg << endl;
            done = true;
        }
        else if (checkForWinner(tttdata, dim) == 1)
        {
            cout << endl;
            cout << xwins_msg << endl;
            done = true;
        }
        else if (checkForDraw(tttdata, dim) == true)
        {
            cout << endl;
            cout << draw_msg << endl;
            done = true;
        }
    } // end while
  return 0;
}