#ifndef _DOMINION_HELPERS_H
#define _DOMINION_HELPERS_H

#include "dominion.h"

int drawCard(int player, struct gameState *state);
int updateCoins(int player, struct gameState *state, int bonus);
int discardCard(int handPos, int currentPlayer, struct gameState *state, 
		int trashFlag);
int gainCard(int supplyPos, struct gameState *state, int toFlag, int player);
int getCost(int cardNumber);

//add refactored function for 5 cards including smithy and adventurer
int rf_remodel(int choice1, int choice2, struct gameState *state, int handPos);
int rf_smithy(struct gameState *state, int handPos);
int rf_village(struct gameState *state, int handPos);
int rf_adventurer(struct gameState *state, int handPos);
int rf_feast(int choice1,  struct gameState *state, int handPos);

int cardEffect(int card, int choice1, int choice2, int choice3, 
	       struct gameState *state, int handPos, int *bonus);

#endif
