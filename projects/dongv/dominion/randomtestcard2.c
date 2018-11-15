/*
 * randomtestcard2.c
 * smithy: +3 card
	
 */

/*
 * Include the following lines in your makefile:
 *
 * randomtestcard2: randomtestcard2.c dominion.o rngs.o
 *      gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"

int main(){
    int i;
    int newCards = 3;
    int discarded = 1;
    int shuffledCards = 0;
   
    int k[10] = {adventurer, feast, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room};

    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

for (i = 0; i < 3200000; i++){
    int seed = 1000;                //random seed 1000
    int numPlayers = rand()%3+2;    //number of players could be 2-4
    int handpos = rand()%20;         //randomize handpos, player's intial hand is 5
	
    struct gameState G, testG;
	
    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);// copy the game state to a test case
    int thisPlayer = whoseTurn(&testG);	    //current player
    testG.handCount[thisPlayer]=rand()%20;;
    testG.deckCount[thisPlayer]=rand()%500;;
    testG.numActions=rand()%20;
    memcpy(&testG, &G, sizeof(struct gameState));
    rf_smithy(&testG, handpos);             //run refactored smithy card instead of cardeffect
    //cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
    //printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
    //printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
    //printf("number of players = %d, hand position = %d\n", numPlayers, handpos);
    assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
    assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards);
}
    
    printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
return 0;
}


