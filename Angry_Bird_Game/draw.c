#include "draw.h"
#include "gba.h"
#include <stdio.h>
#include "images/square.h"
#include "images/bird.h"
#include "images/gameover.h"
#include "images/winscreen.h"

// TA-TODO: Include any header files for images generated by nin10kit.
// Example for the provided garbage image:
// #include "images/garbage.h"

// TA-TODO: Add any draw/undraw functions for sub-elements of your app here.
// For example, for a snake game, you could have a drawSnake function
// or a drawFood function
//
// e.g.:
// static void drawSnake(Snake* snake);
// static void drawFood(Food* food);

// This function will be used to draw everything about the app
// including the background and whatnot.
void fullDrawAppState(AppState *state) {
    // TA-TODO: IMPLEMENT.
    if (state->gameOver == 1 && state->win == 1) {
        drawFullScreenImageDMA(winscreen);
    } else if (state->gameOver == 1) {
        drawFullScreenImageDMA(gameover);
    } else {
	    fillScreenDMA(WHITE);
	    for (int i = 0; i < birdMax; i++) {
	        if (state->birds[i].caught == 0) {
	            drawImageDMA(state->birds[i].x, state->birds[i].y, state->birds[i].width, state->birds[i].height, bird);
	        }
	    }
	    drawImageDMA(state->square.x, state->square.y, state->square.width, state->square.height, square);
	    drawString(5, 5, "score:", BLACK);
	    char scoreStr[3];
        sprintf(scoreStr, "%d", state->score);
        drawString(40, 5, scoreStr, BLACK);
        drawString(5, 15, "time:", BLACK);
        char timeStr[3];
        sprintf(timeStr, "%d", timeOver-state->timer);
        drawString(40, 15, timeStr, BLACK);
    }
}

// This function will be used to undraw (i.e. erase) things that might
// move in a frame. E.g. in a Snake game, erase the Snake, the food & the score.
void undrawAppState(AppState *state) {

    drawRectDMA(5, 5, 80, 30, WHITE);
    for (int i = 0; i < birdMax; i++) {
        if (state->birds[i].caught == 0) {
            drawRectDMA(state->birds[i].x, state->birds[i].y, state->birds[i].width, state->birds[i].height, WHITE);
        }
    }
    drawRectDMA(state->square.x, state->square.y, state->square.width, state->square.height, WHITE);

    
}

// This function will be used to draw things that might have moved in a frame.
// For example, in a Snake game, draw the snake, the food, the score.
void drawAppState(AppState *state) {
    // TA-TODO: IMPLEMENT.
    for (int i = 0; i < birdMax; i++) {
        if (state->birds[i].caught == 0) {
            drawImageDMA(state->birds[i].x, state->birds[i].y, state->birds[i].width, state->birds[i].height, bird);
        }
    }
    drawImageDMA(state->square.x, state->square.y, state->square.width, state->square.height, square);
    drawString(5, 5, "score:", BLACK);
    char scoreStr[3];
    sprintf(scoreStr, "%d", state->score);
    drawString(40, 5, scoreStr, BLACK);
    drawString(5, 15, "time:", BLACK);
    char timeStr[3];
    sprintf(timeStr, "%d", timeOver-state->timer);
    drawString(40, 15, timeStr, BLACK);
}
