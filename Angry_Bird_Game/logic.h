#ifndef LOGIC_H
#define LOGIC_H

#include "gba.h"

#define squareWidth 8
#define squareHeight 8
#define birdWidth 30
#define birdHeight 20
#define winScore 20
#define timeOver 40
#define birdMax 6

typedef struct {
    int x;
    int y;
    int left;
    int right;
    int high;
    int low;
    int width;
    int height;

} Square;

typedef struct {
    int x;
    int y;
    int width;
    int height;
    int caught;
    int xDir;
    int yDir;
} Bird;

typedef struct {
    // Store whether or not the game is over in this member:
    int init, gameOver, reset;
    int score, win;
    Bird birds[birdMax];
    Square square;
    int timer;

} AppState;


/*
* TA-TODO: Add any additional structs that you need for your app.
*
* For example, for a Snake game, one could be:
*
* typedef struct {
*   int heading;
*   int length;
*   int x;
*   int y;
* } Snake;
*
*/

// This function can initialize an unused AppState struct.
void initializeAppState(AppState *appState);
// void generateRandomFoods(AppState* currentAppState, AppState* nextAppState);
// This function will be used to process app frames.
AppState processAppState(AppState *currentAppState, u32 keysPressedBefore, u32 keysPressedNow);

// If you have anything else you need accessible from outside the logic.c
// file, you can add them here. You likely won't.

#endif
