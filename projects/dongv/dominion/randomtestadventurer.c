/*
 * randomtestadventurer.c
 */

/*
 * Include the following lines in your makefile:
 *
 * randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
 *      gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

int main() {
    int i;
    int newCards = 2;
    int discarded = 0;
    //int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int shuffledCards;
    int k[10] = {adventurer, feast, village, minion, mine, cutpurse,
    sea_hag, tribute, smithy, council_room};

printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	
for (i = 0; i < 3200000; i++){
    struct gameState G, testG;
    int seed = 1000;                            //random seed 1000
    int numPlayers = rand()%2+2;		//number of players could be 2-4
    int handpos = rand()%20;                     //randomize handpos, player's initial hand is 5
    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);
    // copy the game state to a test case
    int thisPlayer = whoseTurn(&testG);	    //current player
    testG.handCount[thisPlayer]=rand()%20;;
    testG.deckCount[thisPlayer]=rand()%500;;
    testG.numActions=rand()%20;

    memcpy(&testG, &G, sizeof(struct gameState));
    //cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
    shuffledCards = rf_adventurer(&testG, handpos); 
    //printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
    //printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards - shuffledCards);
    //printf("discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]+shuffledCards);
    //printf("number of players = %d, hand position = %d\n", numPlayers, handpos);
    assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
    assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards - shuffledCards);
    assert(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] + shuffledCards);
}
    printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

return 0;
}


