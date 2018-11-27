/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 * 
 *  Unit test of fullDeckCount function
	the function returns a count of the specified card in the deck + hand + discard
 *
 * unittest4: unittest4.c dominion.o rngs.o
 *      gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
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
	int maxDeck = 500;
    int seed = 1000;
    int numPlayer = 2;  //assume there are 2 players 
    int i, j; 
	//initialize 10 kingdom cards for game
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;

    printf ("TESTING fullDeckCount():\n");
        
#if (PRINT_TEST == 1)
        printf("Test count of card for full deck\n");
#endif
        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        initializeGame(numPlayer, k, seed, &G); 	// initialize a new game	
		for (j = 0; j < 10; j++){					//get count of each kingdom card
			int count = 0;							//initial count
			for (i = 0; i < maxDeck; i++){			//max search value = 500 for max deck
					if (G.hand[0][i] == k[j]) count++;		//check hand for card
					if (G.deck[0][i] == k[j]) count++;		//check deck for card
					if (G.discard[0][i] == k[j]) count++;	//check discard for card
			}  
			assert(fullDeckCount(0, k[j], &G) == count);    //function and compare to count
		}
							
#if (PRINT_TEST == 1)
                printf("Passed check for count of 10 kingdom cards\n");
#endif
                
#if (PRINT_TEST == 1)
                printf("Test: check player 1 for estate card\n");
#endif
        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        initializeGame(numPlayer, k, seed, &G); // initialize a new game	
		int count = 0;							    //initial count
			for (i = 0; i < maxDeck; i++){			//max search value = 500 for max deck
					if (G.hand[1][i] == estate) count++;	  //check hand for card
					if (G.deck[1][i] == estate) count++;      //check deck for card
					if (G.discard[1][i] == estate) count++;	  //check discard for card
			}  
			assert(fullDeckCount(1, estate, &G) == count);    //function and compare to count
		
#if (PRINT_TEST == 1)
                printf("Passed check for player 1, estate card\n");
#endif

    printf("All tests passed!\n");

    return 0;
}
