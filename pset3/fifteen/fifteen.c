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
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// board free space position, (x,y) position
int r;
int c;

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(int dim);
void draw(int dim);
bool move(int tile, int dim);
void swap(int tile, int row, int col);    // parameters are tile, and row/col position of free space
bool won(int dim);

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
    init(d);

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw(d);

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
        if (won(d))
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile, d))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
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
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(int d)
{
int max = d * d - 1;
int n = max;
printf("Debug: max: %d", max);

    // points to free space
    r = d - 1;
    c = d - 1;
    
    // Assign values to array
    for(int rows = 0; rows < d; rows++) {
        for(int cols = 0; cols < d; cols++) {
            board[rows][cols] = n;
            n--;
        }
    }
    // If dimension is odd, swap 1 and 2
    if(max % 2 != 0) {
        board[r][c-2] = 1;
        board[r][c-1] = 2;
    }
    return;
}

/**
 * Prints the board in its current state.
 */
void draw(int d)
{
    for(int rows = 0; rows < d; rows++) {
        for(int cols = 0; cols < d; cols++) {
            if(board[rows][cols] == 0) {
                printf("  _");
                continue;
            }
            printf(" %2d", board[rows][cols]);
        }
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile, int d)
{
int max = d * d - 1;    
    
    // If tile exists
    if(tile > 0 && tile <= max) {
        
        // Up
        if(r - 1 >= 0) {     // if in bounds
            if(board[r-1][c] == tile) {
                swap(tile, r - 1, c);
                r--;
                return true;
            }
        }
        
        // Down
        if(r + 1 <= d - 1) { // if in bounds
            if(board[r+1][c] == tile) {
                swap(tile, r + 1, c);
                r++;
                return true;
            }
        }
        
        // Left
        if(c - 1 >= 0) {     // if in bounds
            if(board[r][c-1] == tile) {
                swap(tile, r, c - 1);
                c--;
                return true;
            }
        }
        
        // Right
        if(c + 1 <= d - 1) { // if in bounds
            if(board[r][c+1] == tile) {
                swap(tile, r, c + 1);
                c++;
                return true;
            }
        }
    }
    
    return false;
}

/**
 * Swaps free space tile with tile specified
 */
void swap(int tile, int t_row, int t_col)
{
    board[t_row][t_col] = 0;
    board[r][c] = tile;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(d)
{
int val = 1;

    for(int rows = 0; rows < d; rows++) {       // [0,0],[0,1]...[d-1,d-1]
        for(int cols = 0; cols < d; cols++) {
            
            if(board[rows][cols] == val) {
                val++;
            }
            else if(rows == d-1 && cols == d-1 && board[rows][cols] == 0) {
                    return true;
            }
            else {
                    return false;
            }
        }
    }
    return false;
}