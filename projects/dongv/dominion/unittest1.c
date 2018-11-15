/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 * 
 *  Unit test of supply count function
	the function returns the number of cards left for a given card
	When the game was initialize, a certain amount is available.
 *
 * unittest1: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
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
	int sC[10];
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;

    printf ("TESTING supplyCount():\n");
        
#if (PRINT_TEST == 1)
                printf("Test each kingdom card for supply count\n");
#endif
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                initializeGame(numPlayer, k, seed, &G); // initialize a new game
				for (i = 0; i < 10; i++){   
					G.supplyCount[k[i]] = i;
					sC[i] = supplyCount(k[i], &G);		  //use supplyCount function to return count of given card
					assert(G.supplyCount[k[i]] == sC[i]); // check if the number of cards are correct
				}
#if (PRINT_TEST == 1)
                printf("Passed check for count of 10 kingdom cards\n");
#endif
                
#if (PRINT_TEST == 1)
                printf("Test of each Victory card for supply count\n");
#endif
				memset(&G, 23, sizeof(struct gameState));   // clear the game state
                initializeGame(numPlayer, k, seed, &G); // initialize a new game
                assert(G.supplyCount[estate] == supplyCount(estate, &G));    // check estate card count = 8 for 2 players
				assert(G.supplyCount[duchy] == supplyCount(duchy, &G));      // check duchy card count = 8 
				assert(G.supplyCount[province] == supplyCount(province, &G));// check province card count = 8
#if (PRINT_TEST == 1)
                printf("Passed check Victory cards\n");
#endif

    printf("All tests passed!\n");

    return 0;
}
