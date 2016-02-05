/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// current position
struct coord {
    int row;
    int column;
};

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
struct coord findPosition(int tile);
struct coord findEndPosition(int tile);
bool move(int tile);
bool move_space(char direction);
void align (int tile);
void move_vertical(int tile, char direction);
void move_horizontal(int tile, char direction);
void move_diagonal(int tile, int direction);
void move_to_end_pos(int tile);
void god_mode(void);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }
        
        // prompt for move
        printf("Tile to move: ");
        string tileInput = GetString();
        
        // quit if user inputs 0 (for testing)
        if (strcmp(tileInput, "GOD") == 0)
        {
            god_mode();
        }
        else
        {
            int tile = atoi(tileInput);
            if (tile == 0)
            {
                break;
            }
    
            // log move (for testing)
            fprintf(file, "%i\n", tile);
            fflush(file);
    
            // move if possible, else report illegality
            if (!move(tile))
            {
                printf("\nIllegal move.\n");
                usleep(50000);
            }
        }

        // sleep thread for animation's sake
        usleep(50000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(200000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    // Get Total number of spaces
    int total = d * d;
    
    // Add tiles to board
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            // Decrement value by one and assign to array
            board[i][j] = --total;
        }
    }
    
    // Swap 2 and 1 if even number of spaces
    if ((d * d) % 2 == 0)
    {
        board[d - 1][d - 3] = 1;
        board[d - 1][d - 2] = 2;
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // Loop through board array
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            // Print line instead of zero
            if (board[i][j] == 0)
            {
                printf("  _");
            }
            else 
            {
                printf("%3i", board[i][j]);
            }
        }
        
        printf("\n\n");
    }
}

/**
 * loop through board to find position of tile you are looking for
 */
struct coord findPosition(int tile)
{
    struct coord position;
    
    // Search board for row, and column
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == tile)
            {
                position.row = i;
                position.column = j;
            }
        }
    }
    
    return position;
}

/**
 * Find the position the tile should be at
 */
struct coord findEndPosition(int tile)
{
    struct coord position;
    
    // Get row and column based on d
    position.row = (tile - 1) / d;
    position.column = (tile - 1) % d;
    
    return position;
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // Check if valid tile
    if (tile > d * d - 1 || tile < 1) 
    {
        return false;
    }
    
    // Search board for row, and column
    struct coord position = findPosition(tile);
    int row = position.row, column = position.column;
    
    // Check nearby spaces
    if (row - 1 >= 0 && board[row - 1][column] == 0)
    {
        board[row - 1][column] = board[row][column];
        board[row][column] = 0;
        return true;
    }
    else if (row + 1 < d && board[row + 1][column] == 0)
    {
        board[row + 1][column] = board[row][column];
        board[row][column] = 0;
        return true;
    }
    else if (column - 1 >= 0 && board[row][column - 1] == 0)
    {
        board[row][column - 1] = board[row][column];
        board[row][column] = 0;
        return true;
    }
    else if (column + 1 < d && board[row][column + 1] == 0)
    {
        board[row][column + 1] = board[row][column];
        board[row][column] = 0;
        return true;
    }
    
    return false;
}

/**
 * move space tile in some direction
 */
bool move_space(char direction)
{
    bool success;
    struct coord space = findPosition(0);
    
    // Utilize the move function to move space tile
    if (direction == 'u')
    {
        success = move(board[space.row - 1][space.column]);
    }
    else if (direction == 'd')
    {
        success = move(board[space.row + 1][space.column]);
    }
    else if (direction == 'l')
    {
        success = move(board[space.row][space.column - 1]);
    }
    else if (direction == 'r')
    {
        success = move(board[space.row][space.column + 1]);
    }
    else {
        success = false;
    }
    
    if (success == true)
    {
        // clear the screen
        clear();
    
        // draw the current state of the board
        draw();
        
        // sleep thread for animation's sake
        usleep(50000);
    }
    
    return success;
}

/**
 * Move space tile to right of tile you want
 */
void align (int tile)
{
    // finds space
    struct coord space = findPosition(0);
    
    // finds tile
    struct coord tilePos = findPosition(tile);
    
    // Check if tile on right
    int side = 1;
    if (tilePos.column == d - 1)
    {
        side = -1;
    }
    
    // Make sure tile is not in same column
    if (space.column == tilePos.column)
    {
        if (side == -1)
        {
            move_space('l');
        }
        else {
            move_space('r');
        }
    }
    
    // moves space to same row as tile
    while (space.row != tilePos.row)
    {
        // If lower on board move up
        if (space.row > tilePos.row)
        {
            move_space('u');
        }
        // Else move down
        else
        {
            move_space('d');
        }
        
        space = findPosition(0);
        tilePos = findPosition(tile);
    }
    
    // Moves space to right of tile
    while (space.column != tilePos.column + side)
    {
        // If right of tile, move left
        if (space.column > tilePos.column + side)
        {
            move_space('l');
        }
        // Else move right
        else
        {
            move_space('r');
        }
        
        space = findPosition(0);
        tilePos = findPosition(tile);
    }
}

/**
 * Move tile vertically
 */
void move_vertical(int tile, char direction)
{
    // finds tile
    struct coord tilePos = findPosition(tile);
    
    // figure out which side the space should be on
    char side = 'l';
    if (tilePos.column == d - 1)
    {
        side = 'r';
    }

    align(tile);
    move_space(direction);
    move_space(side);
    move(tile);
}

/**
 * Move tile horizontally
 */
void move_horizontal(int tile, char direction)
{
    // finds tile
    struct coord tilePos = findPosition(tile);
    
    // figure out which side the space should be on
    char side1 = 'u', side2 = 'd';
    if (tilePos.row == 0)
    {
        side1 = 'd';
        side2 = 'u';
    }
    
    align(tile);
    move_space(side1);
    move_space(direction);
    move_space(direction);
    move_space(side2);
    move(tile);
}

/**
 * Move tile diagonally
 */
void move_diagonal(int tile, int direction)
{
    // finds tile
    struct coord tilePos = findPosition(tile);
    
    switch (direction)
    {
        // Move tile to upper left
        case 1:
            if (tilePos.row - 1 >= 0 && tilePos.column - 1 >= 0)
            {
                move_vertical(tile, 'u');
                move_horizontal(tile, 'l');
            }
            break;
            
        // Move tile to upper right
        case 2:
            if (tilePos.row - 1 >= 0 && tilePos.column + 1 < d)
            {
                move_vertical(tile, 'u');
                move_horizontal(tile, 'r');
            }
            break;
            
        // Move tile to lower left
        case 3:
            if (tilePos.row + 1 < d && tilePos.column - 1 >= 0)
            {
                move_vertical(tile, 'd');
                move_horizontal(tile, 'l');
            }
            break;
        
        // Move tile to lower right
        case 4:
            if (tilePos.row + 1 < d && tilePos.column + 1 < d)
            {
                move_vertical(tile, 'd');
                move_horizontal(tile, 'r');
            }
            break;
        
        default:
            break;
    }
}

/**
 * Move tile to it's final position
 */
void move_to_end_pos(int tile)
{
     // finds tile and end position
    struct coord tilePos = findPosition(tile);
    struct coord endTilePos = findEndPosition(tile);
    
    // Direction to head
    char rowDir = (endTilePos.row - tilePos.row > 0) ? 'd' : 'u';
    char columnDir = (endTilePos.column - tilePos.column > 0) ? 'r' : 'l';
    
    int diagDir = 1;
    if (rowDir == 'u' && columnDir == 'r')
    {
        diagDir = 2;
    }
    else if (rowDir == 'd' && columnDir == 'l')
    {
        diagDir = 3;
    }
    else if (rowDir == 'd' && columnDir == 'r')
    {
        diagDir = 1;
    }
    
    // Move to either same row or column
    while (tilePos.row != endTilePos.row && tilePos.column != endTilePos.column)
    {
        move_diagonal(tile, diagDir);
        tilePos = findPosition(tile);
    }
    
    // Move to correct row
    while (tilePos.row != endTilePos.row)
    {
        move_vertical(tile, rowDir);
        tilePos = findPosition(tile);
    }
    
    // Move to correct column
    while (tilePos.column != endTilePos.column)
    {
        move_horizontal(tile, columnDir);
        tilePos = findPosition(tile);
    }
}

/**
 * God mode
 */
void god_mode(void)
{
    // Get total tiles
    //int total = d * d;
    
    // Loop through tiles
    for (int i = 1; i < 3; i++)
    {
        move_to_end_pos(i);
    }
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    // Set counter
    int counter = 0;
    
    // Check each tile to ensure it's in order
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            // Check if last spot and if not correct value
            if (++counter != (d * d) && board[i][j] != counter)
            {
                return false;
            }
        }
    }
    
    return true;
}