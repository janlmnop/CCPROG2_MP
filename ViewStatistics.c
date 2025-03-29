#include <stdio.h>
#include <strings.h>

#ifndef countPlayers
#define countPlayers

#ifndef countBattlePets
#define countBattlePets

void DisplayTopPlayers (struct PlayerTag playerlist[]) {
	
	FILE *fp;
	
	int i;
	int j;
	int temp;
	countPlayers(playerlist);
	
	fp = fopen("players.txt", "r");
	
	if ((fp = fopen("players.txt", "r")) == NULL)
				printf("ERROR: %s does not exist.\n", "players.txt");
	
	fscanf(fp, "%[^\n]\n%d\n%d\n%d\n\n", playerlist[i].playername, &playerlist[i].wincount, %playerlist[i].losscount, &playerlist[i].drawcount);
	
	for (i = 0; i < countPlayers - 1; i++) {
		for (j = i + 1; j < countPlayers; j++) {
			if (playerlist[i].wincount < playerlist[j].wincount || (playerlist[i].wincount == playerlist[j].wincount && playerlist[i].losscount > playerlist[j].losscount) ||
				(playerlist[i].wincount == playerlist[j].wincount && playerlist[i].losscount == playerlist[j].losscount && playerlist[i].drawcount > playerlist[j].drawcount) ||
				(playerlist[i].wincount == playerlist[j].wincount && playerlist[i].losscount == playerlist[j].losscount && playerlist[i].drawcount == playerlist[j].drawcount && strcmp(playerlist[i].playername, playerlist[j].playername) > 0)) {
					temp = playerlist[i];
					playerlist[i] = playerlist[j];
					playerlist[j] = temp;
				}
		}
	}
	
	printf("Top 5 Players\n");
	
	for (i = 0; i < countPlayers; i++) {
		printf("[%d] %s (W: %d, L: %d, D: %d\n)", i+1, playerlist[i].playername, playerlist[i].wincount, playerlist[i].losscount, playerlist[i].drawcount);
	}	
	
	fclose(fp);
}

void DisplayTopBattlePets (struct BattlePets BP[]) {
	
	FILE &fp;
	int i, j;
	int temp;
	countBattlePets (BP);
	
	fp = fopen("competdium.txt", "r");
	
	if ((ffp = fopen("competdium.txt", "r")) == NULL)
				printf("ERROR: %s does not exist.\n", "competdium.txt");
	fscanf(fp, "%[^\n]\n%[^\n]\n%[^\n]\n%d\n\n", BP[i].battlepet, BP[i].elementalaffinity, BP[i].description, &BP[i].matchcount);
	
	for (i = 0; i < countBattlePets - 1; i++) {
		for (j = i + 1; j < countBattlePets; j++) {
			if (BP[i].matchcount < BP[j].matchcount || (BP[i].matchcount == BP[j].matchcount && strcmp(BP[i].battlepet, BP[j].battlepet) > 0)) {
				temp = BP[i];
				BP[i] = BP[j];
				BP[j] = temp;
			}
		}
	}
	
	printf("Top 5 Battlepets\n");
	for (i = 0; i < countBattlePets; i++) {
		printf("[%d] %s (%d matches)", i+1, BP[i].battlepet, BP[i].matchcount);
	}
	
	fclose(fp);
}
