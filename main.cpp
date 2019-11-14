#include <iostream>
#include <fstream>
using std::cout;
using std::endl;
using std::ifstream;
using std::ostream;
using std::ofstream;
#include "RulesList.h"

void PrintBoard( ostream &, int[][10] );
bool Solve( int[][10], RulesList & );
int tryToPut( int, int, int, int[][10], RulesList & );

ofstream fout( "output.txt" );

int main()
{
    int board[10][10];
    char orient;
    int numSpaces, numRules, tempX, tempY, sum, len;
    RulesList myRules;
    char place;

    ifstream fin( "board2.txt" );

    if( !fin )
    {
        cout << "Couldn't open board." << endl;
        return -1;
    }
    // set board to blanks
    for( int i = 0; i < 10; i++ )
    {
        for( int j = 0; j < 10; j++ )
        {
            board[i][j] = -1;
        }
    }
    // populate the spaces
    for( int i = 0; i < 10; i++ )
    {
        for( int j = 0; j < 10; j++ )
        {
            fin >> place;
            board[i][j] = place == 'x' ? -1 : 0;
        }
    }
    cout << "Starting board:\n" <<endl;
    PrintBoard( cout, board );
    cout << endl;
    // acquire all rules
    fin >> numRules;
    for( int i = 0; i < numRules; i++ )
    {
        fin >> orient >> sum >> tempY >> tempX >> len;
        myRules.addRule( orient, sum, tempY, tempX, len );
    }
    // attempt to solve the board

    if( Solve( board, myRules ) )
    {
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
        << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "Solved Board:\n" << endl;
        PrintBoard( cout, board );
    }
    else
    {
        cout << "No solution" << endl;
        return 1;
    }

    return 0;
}

/*
    First call: call function to try to place {1,2,...9} to slot 0,0.
                go through while loop and as long as board doesn't bust and
                board isn't solved, iterate through and try the next # (up to 9)
                At the end, if board is not solved, return false

    Recursive call:
    If given position is off the board completely, return Non-Bust fail (3).
    I want to try to place the given element in the given slot in the array.
    If the slot contains -1, then go ahead and pass the same parameters to a new
    recursive call, but to the next slot in the board.

    If placing given number causes a bust or repeat in its row or column, it
    should return bust (2).

    O/W, check its row to see if the row is filled. If it is, it should find
    it's appropriate row rule and check if that rule is satisfied, (functions in
    rules to find xRule and yRule by index would be helpful). If filled but does
    not satisfy the relevant rule, return false.

    If the row is satisfied it should then check if its column
    is filled. If the column is filled, it should check the rules list for
    it's appropriate rule and check if the column rule is satisfied. If it is
    not, return false.

    If both the row and column are filled and rule is satisfied, or if the board
    is not empty, seek the next valid position and try to put {1,2....9} there.
    If any of the calls succeed, return true. If any bust, return false. If
    non-bust fail, try next element.

    If all elements from {1,2,..9} fail, return non-bust fail.
*/

bool Solve( int board[][10], RulesList & myRules )
{
    /*
    call function to try to place {1,2,...9} to slot 0,0.
    go through while loop and as long as board doesn't bust and
    board isn't solved, iterate through and try the next # (up to 9)
    At the end, if board is not solved, return false
    */
    int returnVal = 0;
    int i = 1;
    while( i <= 9 && returnVal != 1 && returnVal != 2 )
    {
        returnVal = tryToPut( i, 0, 0, board, myRules );
        i++;
    }
    return returnVal == 1;
}
/*
    CODES:
    1 - Success!
    2 - Bust Fail!
    3 - Non-bust Fail!
    4 - Finished board

    If given position is off the board completely, return success!
    I want to try to place the given element in the given slot in the array.
    If the slot contains -1, then go ahead and pass the same parameters to a new
    recursive call, but to the next slot in the board.

    If placing given number causes a bust or repeat in its row or column, it
    should return bust (2).

    O/W, check its row to see if the row is filled. If it is, it should find
    it's appropriate row rule and check if that rule is satisfied, (functions in
    rules to find xRule and yRule by index would be helpful). If filled but does
    not satisfy the relevant rule, return false.

    If the row is satisfied it should then check if its column
    is filled. If the column is filled, it should check the rules list for
    it's appropriate rule and check if the column rule is satisfied. If it is
    not, return false.

    If both the row and column are filled and rule is satisfied, or if the board
    is not empty, seek the next valid position and try to put {1,2....9} there.
    If any of the calls succeed, return true. If any bust, return false. If
    non-bust fail, try next element.

    If all elements from {1,2,..9} fail, return non-bust fail.
    */
int tryToPut( int guess, int y, int x, int board[][10], RulesList & myRules )
{
    Rule xRule, yRule;
    int curSumX = 0, curSumY = 0, i = 0;
    bool uniqX = true, uniqY = true, filled = true;

    if( x + y > 18 )
    {
        return 1;
    }
    if( board[y][x] == -1 )
    {
        return x <= 9 ? tryToPut( guess, y, x + 1, board, myRules )
                      : tryToPut( guess, y + 1, 0, board, myRules );
    }
    board[y][x] = guess;
    // find relevant x and y rules

    xRule = myRules.findRule( 'h', y, x );
    yRule = myRules.findRule( 'v', y, x );


    // check if bust or repeat in row
    for( i = xRule.startX, curSumX = 0, uniqX = true;
    i < xRule.startX + xRule.length; i++ )
    {
        curSumX += board[y][i];

        if( guess == board[y][i] && i != x )
        {
            uniqX = false;
        }

    }
    // if x bust, return bust
    if( curSumX > xRule.sum )
    {
        board[y][x] = 0;
        return 2;
    }
    // check if bust or repeat in column
    for( i = yRule.startY, curSumY = 0, uniqY = true;
    i < yRule.startY + yRule.length; i++ )
    {
        curSumY += board[i][x];
        if( guess == board[i][x] && i != y )
        {
            uniqY = false;
        }
    }
    // if bust, return bust
    if( curSumY > yRule.sum )
    {
        board[y][x] = 0;
        return 2;
    }
    // if either x or y is not unique, return non-bust fail
    if( ! ( uniqY && uniqX ) )
    {
        board[y][x] = 0;
        return 3;
    }
    // check if row is filled
    filled = x == xRule.startX + xRule.length - 1;
    // if row filled, ensure rule is satisfied
    if( filled && curSumX != xRule.sum )
    {
        board[y][x] = 0;
        return 3;
    }
    // check if column is filled
    filled = y == yRule.startY + yRule.length - 1;
    // if column filled, ensure rule is satisfied
    if( filled && curSumY != yRule.sum )
    {
        board[y][x] = 0;
        return 3;
    }
    // try to place {1,2,...9} in next available slot and return result
    int returnVal = 0, nextX, nextY;
    // find next position
    if( x + 1 > 9 ) // next position is off side of board, try next piece
    {
        nextY = y + 1;
        nextX = 0;
    }
    else
    {
        nextY = y;
        nextX = x + 1;
    }

    // set i for while loop
    i = 1;
    while( i <= 9 && returnVal != 1 && returnVal != 2 )
    {
        returnVal = tryToPut( i, nextY, nextX, board, myRules );
        i++;
    }
    if( returnVal != 1 )
    {
        board[y][x] = 0;
    }
    return returnVal != 2 ? returnVal : 3;
}

void PrintBoard( ostream & out, int board[][10] )
{
    for( int i = 0; i < 10; i++ )
    {
        for( int j = 0; j < 10; j++ )
        {
            if( board[i][j] == -1 )
            {
                out << 'x' << '\t';
            }
            else
            {
                out << board[i][j] << '\t';
            }
        }
        out << endl;
    }
    return;
}
