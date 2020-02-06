//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// center of screen
#define CENTER_WIDTH WIDTH / 2
#define CENTER_HEIGHT HEIGHT / 2

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// dimensions of paddle
#define PADDLE_WIDTH 64
#define PADDLE_HEIGHT 12
#define PADDLE_Y 536

// constants for bricks
#define BRICK_STARTING_Y 64
#define BRICK_HEIGHT 12
#define BRICK_SPACING 4
#define BRICK_WIDTH (WIDTH - (BRICK_SPACING * 11)) / 10

// constants for ball
#define BALL_SIZE 25
#define BALL_SPEED 3

// constants for pause
#define TRUE 1
#define FALSE 0

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(int argc, string argv[])
{
    // make god mode for testing
    int godMode = FALSE;
    if (argc == 2)
    {
    //if(strcmp(getType(object), "GRect") == 0)
       if(strcmp(argv[1], "god"))
       {
        godMode = TRUE;
       }   
    }
    
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    // ball location tracking variables
    int ballX = CENTER_WIDTH - (BALL_SIZE / 2);
    int ballY = CENTER_HEIGHT - (BALL_SIZE / 2);
    // ball speed variables
    int rand = (int) (drand48() * BALL_SPEED);
    
    // stops ball from having no angle
    if(rand == 0) 
    {
        rand = 1;
    }
    
    int ballSpeedX = rand;
    int ballSpeedY = BALL_SPEED;
    
    // pause boolean
    int paused = TRUE;
    
     
        // add paddle
        add(window, paddle);
        
         // add ball
        add(window, ball);
        
        // add score label
        add(window, label);
        
        // wait for mouse click to start
        waitForClick();

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
       
        // update score label
        updateScoreboard(window, label, points);
        
     
        // check for mouse event
        GEvent event = getNextEvent(MOUSE_EVENT);
       
        if(godMode == FALSE)
        {
            // if we heard one
            if (event != NULL)
            {
                // if the event was movement
                if (getEventType(event) == MOUSE_MOVED)
                {
                    // paddle follows x of cursor
                    double paddleX = getX(event) - getWidth(paddle) / 2;
                
                    // keep paddle in the window
                    if(paddleX < 0)
                    {
                        paddleX = 0;
                    }
                
                    if(paddleX + PADDLE_WIDTH > WIDTH)
                    {
                        paddleX = WIDTH - (PADDLE_WIDTH);
                    }
                    // set paddle to updated location
                    setLocation(paddle, paddleX, PADDLE_Y);
                }
            }
       }else
       {
            // if godMode enabled, paddle's x matches ball's x
             setLocation(paddle, ballX - ((PADDLE_WIDTH / 2) - (BALL_SIZE / 2)), PADDLE_Y);
       }
       
       
        
        // bouncing and moving ball on x
        if(ballX < 0)
        {
            ballX = 0;
            ballSpeedX = -ballSpeedX;
        }
        if(ballX + BALL_SIZE > WIDTH)
        {
            ballX = WIDTH - BALL_SIZE;
            ballSpeedX = -ballSpeedX;
        }
        
        // update ball x position
        ballX += ballSpeedX;
        
        // bouncing and moving ball on y
       
        if(ballY < 0)
        {
            ballY = 0;
            ballSpeedY = -ballSpeedY;
        }
        
        // ball went passed paddle 
        if(ballY + BALL_SIZE > HEIGHT)
        {
            ballY = HEIGHT - BALL_SIZE;
            ballSpeedY = -ballSpeedY;
            lives--;
            
            
            // reset ball location and angle
            rand = (int) (drand48() * BALL_SPEED);
            ballX = CENTER_WIDTH - (BALL_SIZE / 2);
            ballY = CENTER_HEIGHT - (BALL_SIZE / 2);
            setLocation(ball, ballX, ballY);
           
            // wait for mouse click to continue
            waitForClick();
        }
        
        // update ball y position
        ballY += ballSpeedY;        
        
        setLocation(ball, ballX, ballY);
        
        // ball linger before moving again
        pause(10);
        
        // handle collisions with ball
        GObject object = detectCollision(window, ball);
        
        
        if(object == paddle)
        {
            // stop ball from gettin stuck in paddle
            if(ballY < PADDLE_Y)
            {
                ballY = PADDLE_Y - BALL_SIZE;
                // reverse y directoin for bounce effect
                ballSpeedY = -ballSpeedY;
            }
            else
            {
            // normal bounce of paddle
                ballY = PADDLE_Y - BALL_SIZE;
                ballSpeedX = -ballSpeedX;
                ballSpeedY = -ballSpeedY;
            }
        }
        // if ball collides with block
        else if(strcmp(getType(object), "GRect") == 0)
        {
            // remove block
            removeGWindow(window, object);
            // reverse y direction for bounce
            ballSpeedY = -ballSpeedY;
            
            // add score
            points++;
            if(points >= 50)
            {
                bricks = 0;
                ballSpeedY = 0;
                ballSpeedX = 0;
                updateScoreboard(window, label, points);
                // reset ball to center
                ballX = CENTER_WIDTH - (BALL_SIZE / 2);
                ballY = CENTER_HEIGHT - (BALL_SIZE / 2);
                setLocation(ball, ballX, ballY);
            }
            
        }
       
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // x & y for brick locations
    int x = BRICK_SPACING + (BRICK_SPACING / 2);
    int y = BRICK_STARTING_Y;

    // setup rows
    for(int i = 0; i < ROWS; i++)
    {
        //setup cols
        for(int j = 0; j < COLS; j++)
        {
            // create a new brick
            GRect tempBrick = newGRect(0, 0, BRICK_WIDTH, BRICK_HEIGHT);
            // set color for each row
            switch(i)
            {
                case 0:
                    setColor(tempBrick, "RED");
                    break;
                case 1:
                    setColor(tempBrick, "ORANGE");
                    break;
                case 2:
                    setColor(tempBrick, "YELLOW");
                    break;
                case 3:
                    setColor(tempBrick, "GREEN");
                    break;    
                case 4:
                    setColor(tempBrick, "CYAN");
                    break; 
            }
            
            // set fill to true
            setFilled(tempBrick, true);
            // set location
            setLocation(tempBrick, x, y);
            // add to window
            add(window, tempBrick);
            // move x to right for the next in row
            x += BRICK_WIDTH + BRICK_SPACING;
        }
        // move x back to start for new row
        x = BRICK_SPACING + (BRICK_SPACING / 2);
        // move down for next row
        y += BRICK_HEIGHT + BRICK_SPACING;
    }
    
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
            // create ball
            GOval ball = newGOval(0, 0, BALL_SIZE, BALL_SIZE);
            // set color
            setColor(ball, "BLACK");
            // set fill to true
            setFilled(ball, true);
            // set location
            setLocation(ball, CENTER_WIDTH - (BALL_SIZE / 2), CENTER_HEIGHT - (BALL_SIZE / 2));       
            // return ball
            return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // init paddle using constants
    GRect paddle = newGRect(0, 0, PADDLE_WIDTH, PADDLE_HEIGHT);
    // set color
    setColor(paddle, "BLACK");
    // set fill to true
    setFilled(paddle, true);
    // set starting location
    setLocation(paddle, (WIDTH - PADDLE_WIDTH) / 2, PADDLE_Y); 
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel("");
    setFont(label, "SansSerif-36");
    setColor(label, "BLUE");
    add(window, label);
    
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
