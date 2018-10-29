/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 * 
 *  Unit test of isGameOver function
	the function returns 0 if game is not over and returns 1 when game is over
	Game is over when province card count = 0 or the 3 cards has a supply count of 0
 *
 * unittest3: unittest3.c dominion.o rngs.o
 *      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
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
    int i, j; 
	j = 1;
	//initialize 10 kingdom cards for game
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;

    printf ("TESTING isGameOver():\n");
        
#if (PRINT_TEST == 1)
                printf("Test for supply count of province = 0\n");
#endif
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                initializeGame(numPlayer, k, seed, &G); // initialize a new game								
				for (i = 0; i < 2; i++){   
					G.supplyCount[province] = i; //set supply count of province card to equal i
					assert(isGameOver(&G) == j); //check if game is over, where j=1
					j--;					     //set j=0 for false when supplycount is not 0
				}
#if (PRINT_TEST == 1)
                printf("Passed check for province supply count at 0 or 1\n");
#endif
                
#if (PRINT_TEST == 1)
                printf("Test three supply pile are at 0\n");
#endif
				j = 1;
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                initializeGame(numPlayer, k, seed, &G);     // initialize a new game
				G.whoseTurn = 1;						 	// set whoseTurn to 1
				for (i = 0; i < 2; i++){   
					G.supplyCount[k[i]] = i; 	  //set supply count of kindom card to equal i (0 and 1)
					G.supplyCount[k[i+1]] = i;
					G.supplyCount[k[i+2]] = i;
					assert(isGameOver(&G) == j);  //check if game is over, j = 1 for true
					j--;						  //set j=0 for false when supplycount is not 0
				}
#if (PRINT_TEST == 1)
                printf("Passed check for three supply pile at 0 or 1\n");
#endif

    printf("All tests passed!\n");

    return 0;
}
