/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 * 
 *  Unit test of numHandCards function
	the function returns the number of cards in the player's hand
	the maximum hand size is 5
 *
 * unittest2: unittest2.c dominion.o rngs.o
 *      gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set PRINT_TEST to 0 to remove printfs from output
#define PRINT_TEST 1

int main() {
    int seed = 1000;
    int numPlayer = 2;  //assume there are 2 players 
    int i; 
	int maxHand = 5;
	int HC[maxHand];
	//initialize 10 kingdom cards for game
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;

    printf ("TESTING numHandCards():\n");
        
#if (PRINT_TEST == 1)
                printf("Test player 0 for num of cards in hand\n");
#endif
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                initializeGame(numPlayer, k, seed, &G); // initialize a new game
				G.whoseTurn = 0;						 	//set whoseTurn to 0
				for (i = 0; i < maxHand; i++){   
					G.handCount[0] = i;				  //set number of cards in hand to equal i
					HC[i] = numHandCards(&G);		  //use numHandCards function to return count of given card
					assert(G.handCount[0] == HC[i]);  //check if the number of cards are correct
				}
#if (PRINT_TEST == 1)
                printf("Passed check for count of cards in player 0's hand\n");
#endif
                
#if (PRINT_TEST == 1)
                printf("Test player 1 for num of cards in hand\n");
#endif
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                initializeGame(numPlayer, k, seed, &G); // initialize a new game
				G.whoseTurn = 1;						 	//set whoseTurn to 1
				for (i = 0; i < maxHand; i++){   
					G.handCount[1] = i;			      //set number of cards in hand to equal i
					HC[i] = numHandCards(&G);		  //use numHandCards function to return count of given card
					assert(G.handCount[1] == HC[i]);  //check if the number of cards are correct
				}
#if (PRINT_TEST == 1)
                printf("Passed check for count of cards in player 1's hand\n");
#endif

    printf("All tests passed!\n");

    return 0;
}
