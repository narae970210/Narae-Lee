#include "logic.h"
#include <stdio.h>
#include <stdlib.h>

void initializeAppState(AppState *appState) {
    // TA-TODO: Initialize everything that's part of this AppState struct here.
    // Suppose the struct contains random values, make sure everything gets
    // the value it should have when the app begins.
    appState->init = 1;
    appState->gameOver = 0;
    appState->reset = 0;
    appState->score = 0;
    appState->win = 0;
    
    //square = 8x8
    appState->square.x = 120;
    appState->square.y = 80;
    appState->square.left = 0;
    appState->square.right = 0;
    appState->square.high = 0;
    appState->square.low = 0;
    appState->square.width = squareWidth;
    appState->square.height = squareHeight;
    appState->timer = 0;


    for (int i = 0; i < birdMax; i++) {
        appState->birds[i].width = birdWidth;
        appState->birds[i].height = birdHeight;
        appState->birds[i].caught = 1;
    }
}

static void generateBirds(AppState* oldState, AppState* newState) {
    for (int i = 0; i < birdMax; i++) {
        if (oldState->birds[i].caught == 1) {
            newState->birds[i].x = randint(0, WIDTH-birdWidth-1);
            newState->birds[i].y = randint(0, HEIGHT-birdHeight-1);
            newState->birds[i].xDir = (-1) + (randint(0, 1) * 2);
            newState->birds[i].yDir = (-1) + (randint(0, 1) * 2);
            newState->birds[i].caught = 0;
            break;
        }
    }
}

static void moveBirds(AppState* oldState, AppState* newState) {
    for (int i = 0; i < birdMax; i++) {
        if (!oldState->birds[i].caught) {
            if (oldState->birds[i].x + oldState->birds[i].width + oldState->birds[i].xDir < WIDTH-1 && oldState->birds[i].x + oldState->birds[i].xDir > 0) {
                newState->birds[i].x = oldState->birds[i].x + oldState->birds[i].xDir;
            } else {
                newState->birds[i].xDir = oldState->birds[i].xDir * (-1);
            }
            if (oldState->birds[i].y + oldState->birds[i].height + oldState->birds[i].yDir < HEIGHT-1 && oldState->birds[i].y + oldState->birds[i].yDir > 0) {
                newState->birds[i].y = oldState->birds[i].y + oldState->birds[i].yDir;
            } else {
                newState->birds[i].yDir = oldState->birds[i].yDir * (-1);
            }
        }
    }
}

static int birdCaught(Bird* bird, Square* square) {
    int birdLeft = bird->x - squareWidth;
    if (birdLeft < 0) {
        birdLeft = 0;
    }
    int birdRight = bird->x + birdWidth + squareWidth;
    if (birdRight >= WIDTH) {
        birdRight = WIDTH - 1;
    }
    int birdLow = bird->y - squareHeight;
    if (birdLow < 0) {
        birdLow = 0;
    }
    int birdHigh = bird->y + birdHeight + squareHeight;
    if (birdHigh >= HEIGHT) {
        birdHigh = HEIGHT - 1;
    }

    int squareLeft = square->x;
    int squareRight = square->x + squareWidth;
    int squareLow = square->y;
    int squareHigh = square->y + squareHeight;

    if (squareLeft >= birdLeft && squareRight <= birdRight && squareLow >= birdLow && squareHigh <= birdHigh) {
        return 1;
    }
    return 0;
}

static void deleteBird(AppState* oldState, AppState* newState) {
    for (int i = 0; i < birdMax; i++) {
        if (oldState->birds[i].caught == 0) {
            if (birdCaught(&oldState->birds[i], &oldState->square)) {
                newState->birds[i].caught = 1;
                newState->score++;
                if (oldState->score >= winScore) {
                    newState->gameOver = 1;
                    newState->win = 1;
                }
            }
        }
    }
}

static void timerIncrement(AppState* oldState, AppState* newState) {
    newState->timer = oldState->timer + 1;
    if (newState->timer >= timeOver) {
        newState->gameOver = 1;
    }
}


// TA-TODO: Add any process functions for sub-elements of your app here.
// For example, for a snake game, you could have a processSnake function
// or a createRandomFood function or a processFoods function.
//
// e.g.:
// static Snake processSnake(Snake* currentSnake);
// static void generateRandomFoods(AppState* currentAppState, AppState* nextAppState);

// This function processes your current app state and returns the new (i.e. next)
// state of your application.
AppState processAppState(AppState *currentAppState, u32 keysPressedBefore, u32 keysPressedNow) {
    /* TA-TODO: Do all of your app processing here. This function gets called
     * every frame.
     *
     * To check for key presses, use the KEY_JUST_PRESSED macro for cases where
     * you want to detect each key press once, or the KEY_DOWN macro for checking
     * if a button is still down.
     *
     * To count time, suppose that the GameBoy runs at a fixed FPS (60fps) and
     * that VBlank is processed once per frame. Use the vBlankCounter variable
     * and the modulus % operator to do things once every (n) frames. Note that
     * you want to process button every frame regardless (otherwise you will
     * miss inputs.)
     *
     * Do not do any drawing here.
     *
     * TA-TODO: VERY IMPORTANT! READ THIS PART.
     * You need to perform all calculations on the currentAppState passed to you,
     * and perform all state updates on the nextAppState state which we define below
     * and return at the end of the function. YOU SHOULD NOT MODIFY THE CURRENTSTATE.
     * Modifying the currentAppState will mean the undraw function will not be able
     * to undraw it later.
     */

    AppState nextAppState = *currentAppState;
    Square *square = &(nextAppState.square);

    if (vBlankCounter % 60 == 0) {
        generateBirds(currentAppState, &nextAppState);
        timerIncrement(currentAppState, &nextAppState);
    }

    if (KEY_JUST_PRESSED(BUTTON_RIGHT, keysPressedNow, keysPressedBefore)) {
        if (square -> x < WIDTH-square->width-1) {
            square -> x++;
            square -> right = 1;
        }
    }
    if (KEY_JUST_PRESSED(BUTTON_LEFT, keysPressedNow, keysPressedBefore)) {
        if (square -> x > 0) {
            square -> x--;
            square -> left = 1;
        }
    }
    if (KEY_JUST_PRESSED(BUTTON_UP, keysPressedNow, keysPressedBefore)) {
        if (square -> y > 0) {
            square -> y--;
            square -> high = 1;
        }
    }
    if (KEY_JUST_PRESSED(BUTTON_DOWN, keysPressedNow, keysPressedBefore)) {
        if (square -> y < HEIGHT-square->height-1) {
            square -> y++;
            square -> low = 1;
        }
    }
    if (KEY_JUST_PRESSED(BUTTON_B, keysPressedNow, keysPressedBefore)) {
        deleteBird(currentAppState, &nextAppState);
    }
    moveBirds(currentAppState, &nextAppState);

    return nextAppState;
}
