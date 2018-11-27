/*
 * randomtestcard1.c
 * village card: +2 actions and +1 card
	
 */

/*
 * Include the following lines in your makefile:
 * randomtestcard1: randomtestcard1.c dominion.o rngs.o
 *      gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "village"

int main() {
    int i;
    int shuffledCards = 0;
    int newCards = 1;
    int newActions = 2;
    int discarded = 1;

    int k[10] = {adventurer, feast, village, minion, mine, cutpurse,
            sea_hag, tribute, smithy, council_room};

    printf("-----------------Random Testing Card: %s ----------------\n", TESTCARD);

// copy the game state to a test case
for (i = 0; i < 3200000; i++){
    int seed = 1000;                    //random seed 1000
    int handpos = rand()%20;           //randomize handpos, max hand is 500
    int numPlayers = rand()%3+2;	//number of players could be 2-4
    struct gameState G, testG;
	
    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);
    //cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);
    int thisPlayer = whoseTurn(&testG);	    //current player
    testG.handCount[thisPlayer]=rand()%20;;
    testG.deckCount[thisPlayer]=rand()%500;;
    testG.numActions=rand()%20;
    memcpy(&testG, &G, sizeof(struct gameState));
    villageFunction(thisPlayer, &testG, handpos);
    //printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
    //printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
    //printf("action count = %d, expected = %d\n", testG.numActions, G.numActions + newActions);
    //printf("number of players = %d, hand position = %d\n", numPlayers, handpos);
    assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
    assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards);
    assert(testG.numActions == G.numActions + newActions);
}
    printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

    return 0;
}


