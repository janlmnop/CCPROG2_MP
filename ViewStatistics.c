/**********************************************************************************************************************
 * Description   : This file includes the View Statistcs portion of the program, where players can see the Top 5 Players
 * 				   based on wins and the Top 5 BattlePets based on appearances in matches.
 * Author/s      : Mariano, Janyka Rochelle
 * 				   
 * Section       : S27B
 * Last Modified : Mar. 29, 2025
***********************************************************************************************************************/

#ifndef ViewStatistics
#define ViewStatistics

#include <stdio.h>
#include <strings.h>
#include "definitions.h"


/**
 * Displays the View Statistics menu options
 */
void displayViewStatisticsOptions ()
{
	printf("\nView Statistics Menu\n");
    printf("[1] Top 5 Players\n");
    printf("[2] Top 5 BattlePets\n");
}

/**
 * Displays the Top 5 Players based on most wincounts, least losscounts, and draws.
 * @param playerlist Array of PlayerTag structures
 */
void DisplayTopPlayers (struct PlayerTag playerlist[]) {
	
	FILE *fp;
	
	int i;
	int j;
	int k=0;
	struct PlayerTag temp;
	
	fp = fopen("players.txt", "r");
	
	if ((fp = fopen("players.txt", "r")) == NULL)
				printf("ERROR: %s does not exist.\n", "players.txt");
	
	while (fscanf(fp, "%[^\n]\n%d\n%d\n%d\n\n", playerlist[k].playername, &playerlist[k].wincount, &playerlist[k].losscount, &playerlist[k].drawcount) == 4)
		k++;

	

	for (i = 0; i < k-1; i++) {
		for (j = i + 1; j < k; j++) {
			if (playerlist[i].wincount < playerlist[j].wincount || (playerlist[i].wincount == playerlist[j].wincount && playerlist[i].losscount > playerlist[j].losscount) ||
				(playerlist[i].wincount == playerlist[j].wincount && playerlist[i].losscount == playerlist[j].losscount && playerlist[i].drawcount > playerlist[j].drawcount) ||
				(playerlist[i].wincount == playerlist[j].wincount && playerlist[i].losscount == playerlist[j].losscount && playerlist[i].drawcount == playerlist[j].drawcount && strcmp(playerlist[i].playername, playerlist[j].playername) > 0)) {
					temp = playerlist[i];
					playerlist[i] = playerlist[j];
					playerlist[j] = temp;
				}
		}
	}
	
	for (i = 0; i < 5; i++) {
		printf("[%d] %s (W: %d, L: %d, D: %d)\n", i+1, playerlist[i].playername, playerlist[i].wincount, playerlist[i].losscount, playerlist[i].drawcount);
	}	
	
	fclose(fp);
}

/**
 * Displays the Top 5 BattlePets based on appearances in matches
 * @param BP Array of BattlePet structures
 */
void DisplayTopBattlePets (struct BattlePets BP[]) {
	
	FILE *fp;
	int i, j, k=0;
	struct BattlePets temp;
	countBattlePets (BP);
	
	fp = fopen("competdium.txt", "r");
	
	if ((fp = fopen("competdium.txt", "r")) == NULL)
				printf("ERROR: %s does not exist.\n", "competdium.txt");
	while (fscanf(fp, "%[^\n]\n%[^\n]\n%[^\n]\n%d\n\n", BP[k].battlepet, BP[k].elementalaffinity, BP[k].description, &BP[k].matchcount) == 4)
		k++;
	
	for (i = 0; i < k - 1; i++) {
		for (j = i + 1; j < k; j++) {
			if (BP[i].matchcount < BP[j].matchcount || (BP[i].matchcount == BP[j].matchcount && strcmp(BP[i].battlepet, BP[j].battlepet) > 0)) {
				temp = BP[i];
				BP[i] = BP[j];
				BP[j] = temp;
			}
		}
	}
	
	for (i = 0; i < 5; i++) {
		printf("[%d] %s (%d matches)\n", i+1, BP[i].battlepet, BP[i].matchcount);
	}
	
	fclose(fp);
}



/**
 * Main function executed when the player selects 'View Statistics'
 */
void ViewStats ()
{
	struct BattlePets BP[MAX_BATTLEPETS];
	struct PlayerTag playerlist[MAX_USERS];
	int ViewStatsInput;

	printf("\n -- Battle! --\n");

	displayViewStatisticsOptions();
    printf("\n>> ");
    scanf("%d", &ViewStatsInput);

	switch(ViewStatsInput)
    {
        case 1: DisplayTopPlayers(playerlist); break;

        case 2: DisplayTopBattlePets(BP); break;

        default: printf("Incorrect input. Try again.\n");
    }
    printf("\n");
}
	

#endif // ViewStatistics
