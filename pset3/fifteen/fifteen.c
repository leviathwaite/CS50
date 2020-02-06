/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements the Game of Fifteen (generalized to d x d).
 *
 * Usage: ./fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [MIN,MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements the Game of Fifteen (generalized to d x d).
 *
 * Usage: ./fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [MIN,MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */

#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// board's minimal dimension
#define MIN 3

// board's maximal dimension
#define MAX 9

// define color
#define ANSI_COLOR_GREEN   "\x1b[42m"
#define ANSI_COLOR_RESET   "\x1b[0m"

// board, whereby board[i][j] represents row i and column j
int board[MAX][MAX];

// starting location of blank
int blankLocC;
int blankLocR;

// used to store available moves
int moves[4];

// board's dimension
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void save(void);
void updateMoves();

int main(int argc, string argv[])
{
    // greet player
    greet();

    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < MIN || d > MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            MIN, MIN, MAX, MAX);
        return 2;
    }

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // saves the current state of the board (for testing)
        save();

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep for animation's sake
        usleep(500000);
    }

    // that's all folks
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
    printf("GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1,
 * (i.e., fills board with values but does not actually print them),
 * whereby board[i][j] represents row i and column j.
 */
void init(void)
{
    //setup game board, -1 value applied to extra spaces
    int counter = d * d;
    for(int i = 0; i < MAX; i++)
    {
        for(int j = 0; j < MAX; j++)
        {
            if(i < d && j < d)
            {
                counter--;
                board[i][j] = counter;
            }
        }
    } 
    
     // if odd swap 1 & 2
    if((d * d - 1) % 2 == 1)
    {
        board[d - 1][d - 2] = 2;
        board[d - 1][d - 3] = 1;
    } 
    
    // store blank location, cloumn and row
    blankLocC = d - 1;
    blankLocR = d - 1;
    
    // calculate available moves
    updateMoves();
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++)
        {
            if(board[i][j] != 0)
            {
                for(int k = 0; k < 4; k++)
                {
                    if(board[i][j] == moves[k])
                    {
                       printf(ANSI_COLOR_GREEN); 
                    }
                }
                
                printf("%2d ", board[i][j]);
                printf(ANSI_COLOR_RESET);
            }
            else
            {
                printf(" _ ");
            }
        }
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    //TODO make swap function and constant for up, down. left, right
    if(tile > 0)
    {
        // up
        if(tile == moves[0])
        {
            board[blankLocR][blankLocC] = tile;
            
            // move blank up
            blankLocR--;
            board[blankLocR][blankLocC] = 0;
            updateMoves();
            return true;
        }
        // down
        if(tile == moves[1])
        {
            board[blankLocR][blankLocC] = tile;
        
            // move blank down
            blankLocR++;
            board[blankLocR][blankLocC] = 0;
            updateMoves();
            return true;
        }
        // left
        if(tile == moves[2])
        {
            board[blankLocR][blankLocC] = tile;
        
            // move blank left
            blankLocC--;
            board[blankLocR][blankLocC] = 0;
            updateMoves();
            return true;
        }
        // right
        if(tile == moves[3])
        {
            board[blankLocR][blankLocC] = tile;
        
            // move blank right
            blankLocC++;
            board[blankLocR][blankLocC] = 0;
            updateMoves();
            return true;
        }

    }
        return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
   // simple check before full check
    if(board[0][0] == 1 && board[d - 1][d - 1] == 0)
    {
        //printf("simple win passed\n");
        
        int prevSpace = 1;
        for(int i = 0; i < d; i++)
        {
            for(int j = 0; j < d; j++)
            {
                if(prevSpace != board[i][j])
                {
                    if(board[i][j] == 0)
                    {
                        return true;
                    }
                        //printf("win failed, %i != %i\n", board[i][j], prevSpace);
                        return false;
                }
                //printf("win passed, %i == %i\n", board[i][j], prevSpace);
                prevSpace++;
            }
        }
        //printf("returning true\n");
        return true;
    } 
    //printf("return false\n");
    return false;
}

/**
 * Saves the current state of the board to disk (for testing).
 */
void save(void)
{
    // log
    const string log = "log.txt";

    // delete existing log, if any, before first save
    static bool saved = false;
    if (!saved)
    {
        unlink(log);
        saved = true;
    }

    // open log
    FILE* p = fopen(log, "a");
    if (p == NULL)
    {
        return;
    }

    // log board
    fprintf(p, "{");
    for (int i = 0; i < d; i++)
    {
        fprintf(p, "{");
        for (int j = 0; j < d; j++)
        {
            fprintf(p, "%i", board[i][j]);
            if (j < d - 1)
            {
                fprintf(p, ",");
            }
        }
        fprintf(p, "}");
        if (i < d - 1)
        {
            fprintf(p, ",");
        }
    }
    fprintf(p, "}\n");

    // close log
    fclose(p);
}

void updateMoves()
{
    // up
    if(blankLocR - 1 >= 0)
    {
        moves[0] = board[blankLocR - 1][blankLocC];
    }
    else
    {
        moves[0] = -1;
    }
    // down
    if(blankLocR + 1 < d)
    {
        moves[1] = board[blankLocR + 1][blankLocC];
    }
    else
    {
        moves[1] = -1;
    }

    //left
    if(blankLocC - 1 >= 0)
    {
    moves[2] = board[blankLocR][blankLocC - 1];
    }
    else
    {
        moves[2] = -1;
    }
    //right
    if(blankLocC + 1 < d)
    {
    moves[3] = board[blankLocR][blankLocC + 1];
    }
    else
    {
        moves[3] = -1;
    }
    
    for(int i = 0; i < 4; i++)
    {
        // printf("moves %i = %i\n", i, moves[i]);
    }
}
