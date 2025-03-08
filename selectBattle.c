#include <stdio.h>
#include <strings.h>
#include "definitions.h"


// countBattlePets | reference: [^\n]
int countBattlePets (struct BattlePets BP[])
{
    FILE *fp; 
    int i=0;

    fp = fopen("competdium.txt", "r");

    if ((fp = fopen("competdium.txt", "r")) == NULL)
		fprintf(stderr, "ERROR: %s does not exist.\n", "competdium.txt");

    while ((fscanf(fp, "%[^\n]\n%[^\n]\n%[^\n]\n%d\n\n", BP[i].battlepet, BP[i].elementalaffinity, BP[i].description, &BP[i].matchcount)) == 4)
        i++;

    return i;

    fclose(fp);
}

// countPlayers
int countPlayers (struct PlayerTag playerlist[])
{
    FILE *fp; 
    int i=0;

    fp = fopen("players.txt", "r");

    if ((fp = fopen("players.txt", "r")) == NULL)
		fprintf(stderr, "ERROR: %s does not exist.\n", "players.txt");

    while ((fscanf(fp, "%[^\n]\n%d\n%d\n%d\n\n", playerlist[i].playername, &playerlist[i].wincount, &playerlist[i].losscount, &playerlist[i].drawcount)) == 4)
        i++;

    return i;

    fclose(fp);
}

// selectPlayer | reference: [^\n]
void selectPlayer (struct PlayerTag playerlist[], struct PlayerTag player[])
{
    FILE *fp; 

    int option;
    int i=0;

    // displays current list of players from players.txt
    fp = fopen("players.txt", "r");
    if ((fp = fopen("players.txt", "r")) == NULL)
		fprintf(stderr, "ERROR: %s does not exist.\n", "players.txt");

    while ((fscanf(fp, "%[^\n]\n%d\n%d\n%d\n\n", playerlist[i].playername, &playerlist[i].wincount, &playerlist[i].losscount, &playerlist[i].drawcount)) == 4)
    {
        fprintf(stdout, "[%d] %s\n", i+1, playerlist[i].playername);
        i++;
    }
    printf("[%d] <New Player>\n", i+1);

    // player selection
    printf("\n>> ");
    scanf("%d", &option); /* new player option */
    if (option == i+1)
    {
        fp = fopen("players.txt", "a");
        fprintf(stdout, "\nNew player username: ");
        fscanf(fp, "%s", playerlist[option-1].playername);
        playerlist[option-1].wincount = 0;
        playerlist[option-1].losscount = 0;
        playerlist[option-1].drawcount = 0;
        fprintf(fp, "%s\n%d\n%d\n%d\n\n", playerlist[option-1].playername, playerlist[option-1].wincount, playerlist[option-1].losscount, playerlist[option-1].drawcount);
        printf("\nGreetings, %s!\n", playerlist[option-1].playername);
        fclose(fp);
    }
    else if (option < i+1) /* past players option */
    {
        printf("\nWelcome back, %s!\n", playerlist[option-1].playername);
        player[0] = playerlist[option-1];
    }
    else
        printf("Incorrect input. Try again.\n");
   
    fclose(fp);
}

// displayRoster
void displayRoster (struct PlayerTag player[])
{
    printf("\tC#0\t\tC#1\t\tC#2\n");
    for (int i=0; i<3; i++)
    {
      printf("R#%d", i);
      for (int j=0; j<3; j++)
      {
        if (strlen(player[0].roster[i][j].battlepet)<6)     /* formatting purposes */
            printf("\t[%s]\t", player[0].roster[i][j].battlepet);
        else 
            printf("\t[%s]", player[0].roster[i][j].battlepet);
      }
      printf("\n");
    }
}

// saveRosterInfo | structure to structure assignment (i.e. player's roster <- BP info)
void saveRosterInfo (struct BattlePets BP[], struct PlayerTag player[])
{
    int i=0, j, x, y;
    FILE *fp;

    fp = fopen("competdium.txt", "r");

    while ((fscanf(fp, "%[^\n]\n%[^\n]\n%[^\n]\n%d\n\n", BP[i].battlepet, BP[i].elementalaffinity, BP[i].description, &BP[i].matchcount)) == 4)
        i++;

    for (j=0; j<i; j++)
    {
        for (x=0; x<3; x++)
        {
            for (y=0; y<3; y++)
            {
                if (strcmp(BP[j].battlepet, player[0].roster[x][y].battlepet) == 0)
                    player[0].roster[x][y] = BP[j];
            }
        }
    }
    fclose(fp);
}

// loadSavedRoster
void loadSavedRoster (struct BattlePets BP[], struct PlayerTag player[])
{
    String36 filename;
    FILE *fp;

    // look for the player's file
    strcpy(filename, "saved_roster/"); 
    strcat(filename, player[0].playername);
    strcat(filename, ".txt");

    fp = fopen(filename, "r");

    if ((fp = fopen(filename, "r")) == NULL) {
		fprintf(stderr, "ERROR: %s does not exist.\n", filename);
	}

    // scan player's file and get their BPs
    for (int i=0; i<3; i++)
    {
        for (int j=0; j<3; j++)
        {
            fscanf(fp, "%s", player[0].roster[i][j].battlepet);
        }
    }

    saveRosterInfo(BP, player);

    printf("\n[Match Roster]\n");
    displayRoster(player);

    fclose(fp);
}

// checkPetAvailability
int checkPetAvailability (String36 BattlePet, struct PlayerTag player[])
{
    for (int i = 0; i <3; i++)
    {
        for (int j=0; j<3; j++)
        {
            if (strcmp(BattlePet, player[0].roster[i][j].battlepet) == 0)
                return 1;   /* returns 1 if the BP is already selected by the other player */
        }
    }
    return 0;   /* returns 0 if the BP is still available */
}

// returnBPIndex
int returnBPIndex (struct BattlePets BP[], String36 name)
{
    for (int i=0; i<countBattlePets(BP); i++)
    {
        if (strcmp(BP[i].battlepet, name) == 0)
            return i;
    }
    return -1;
}

// returnPlayerIndex
int returnPlayerIndex (struct PlayerTag playerlist[], String36 name)
{
    for (int i=0; i<countPlayers(playerlist); i++)
    {
        if (strcmp(playerlist[i].playername, name) == 0)
            return i;
    }
    return -1;
}

// createNewRoster | reference [^\n]
void createNewRoster (struct BattlePets BP[], struct PlayerTag currentplayer[], struct PlayerTag otherplayer[])
{
    int i=0, j, x, y;
    int flag[16] = {0}; /* initializes array elements to 0 */
    String36 name;
    FILE *fp;

    // show grid where BattlePets will go
    displayRoster(currentplayer);

    // read BattlePets from a file
    fp = fopen("competdium.txt", "r");

    while ((fscanf(fp, "%[^\n]\n%[^\n]\n%[^\n]\n%d\n\n", BP[i].battlepet, BP[i].elementalaffinity, BP[i].description, &BP[i].matchcount)) == 4)
        i++;

    // check whether the BattlePet has been selected by otherplayer
    for (j = 0; j<i; j++)
    {
        for (x=0; x<3; x++)
        {
            for (y=0; y<3; y++)
            {
                if (strcmp(otherplayer[0].roster[x][y].battlepet, BP[j].battlepet) == 0)
                    flag[j] = 1;
            }
        }
    }

    // display available battle pets
    printf("\n[Available BattlePets]\n");
    for (j = 0; j < i; j++) 
    {
        if (flag[j] == 1) 
            printf("[x] %s\n", BP[j].battlepet);
        else
            printf("[%d] %s\n", j + 1, BP[j].battlepet);
    }

    // let user make a roster
    printf("\n[Create Roster]\n");
    for (x=0; x<3; x++)
    {
        for (y=0; y<3; y++)
        {
            do {
                printf("[%d][%d]: ", x, y);
                scanf("%s", name);
    
                if (checkPetAvailability(name, otherplayer))
                    printf("This BattlePet has already been selected!\n");
    
            } while (checkPetAvailability(name, otherplayer));

            strcpy(currentplayer[0].roster[x][y].battlepet, name);
            currentplayer[0].roster[x][y] = BP[returnBPIndex(BP, name)];
        }
    }

    // display thisplayer's final roster
    printf("\n[Player's Final Roster]\n");
    displayRoster(currentplayer);

    fclose(fp);
}

// displayChallengers
void displayChallengers (struct PlayerTag player1[], struct PlayerTag player2[])
{
    printf("\n[Challengers]\n");
    for (int i=0; i<3; i++)
    {
        for (int j=0; j<3; j++)
        {
            printf("[%d][%d]: %s vs. %s\n", i, j, player1[0].roster[i][j].battlepet, player2[0].roster[i][j].battlepet);
        }
    }
}

// compareElementalAffinities: tests wins and loss cases
void compareElementalAffinities (struct BattlePets BP[], char results[3][3], struct PlayerTag player1[], struct PlayerTag player2[])
{
    FILE *fp;
    int i=0, j;

    fp = fopen("competdium.txt", "r");

    while ((fscanf(fp, "%[^\n]\n%[^\n]\n%[^\n]\n%d\n\n", BP[i].battlepet, BP[i].elementalaffinity, BP[i].description, &BP[i].matchcount)) == 4)
        i++;

    for (i=0; i<3; i++)
    {
        for (j=0; j<3; j++)
        {
            // check player1 wins
            if ((strcmp(player1[0].roster[i][j].elementalaffinity, "Fire") == 0 && 
                (strcmp(player2[0].roster[i][j].elementalaffinity, "Grass") == 0 ||
                 strcmp(player2[0].roster[i][j].elementalaffinity, "Earth") == 0 || 
                 strcmp(player2[0].roster[i][j].elementalaffinity, "Ice") == 0)) ||

                (strcmp(player1[0].roster[i][j].elementalaffinity, "Water") == 0 && 
                (strcmp(player2[0].roster[i][j].elementalaffinity, "Fire") == 0 ||
                 strcmp(player2[0].roster[i][j].elementalaffinity, "Electric") == 0 || 
                 strcmp(player2[0].roster[i][j].elementalaffinity, "Metal") == 0)) ||

                (strcmp(player1[0].roster[i][j].elementalaffinity, "Grass") == 0 && 
                (strcmp(player2[0].roster[i][j].elementalaffinity, "Water") == 0 ||
                 strcmp(player2[0].roster[i][j].elementalaffinity, "Earth") == 0 ||
                 strcmp(player2[0].roster[i][j].elementalaffinity, "Electric") == 0)) ||

                (strcmp(player1[0].roster[i][j].elementalaffinity, "Earth") == 0 && 
                (strcmp(player2[0].roster[i][j].elementalaffinity, "Air") == 0 ||
                 strcmp(player2[0].roster[i][j].elementalaffinity, "Metal") == 0)) ||

                (strcmp(player1[0].roster[i][j].elementalaffinity, "Air") == 0 && 
                (strcmp(player2[0].roster[i][j].elementalaffinity, "Grass") == 0 ||
                 strcmp(player2[0].roster[i][j].elementalaffinity, "Electric") == 0)) ||

                (strcmp(player1[0].roster[i][j].elementalaffinity, "Electric") == 0 && 
                (strcmp(player2[0].roster[i][j].elementalaffinity, "Earth") == 0 ||
                 strcmp(player2[0].roster[i][j].elementalaffinity, "Metal") == 0)) ||

                (strcmp(player1[0].roster[i][j].elementalaffinity, "Ice") == 0 && 
                (strcmp(player2[0].roster[i][j].elementalaffinity, "Water") == 0 ||
                 strcmp(player2[0].roster[i][j].elementalaffinity, "Grass") == 0 ||
                 strcmp(player2[0].roster[i][j].elementalaffinity, "Air") == 0 ||
                 strcmp(player2[0].roster[i][j].elementalaffinity, "Electric") == 0)) ||

                (strcmp(player1[0].roster[i][j].elementalaffinity, "Metal") == 0 && 
                (strcmp(player2[0].roster[i][j].elementalaffinity, "Fire") == 0 ||
                 strcmp(player2[0].roster[i][j].elementalaffinity, "Air") == 0 ||
                 strcmp(player2[0].roster[i][j].elementalaffinity, "Ice") == 0)))    
                {
                    results[i][j] = '1';
                }

            // check player2 wins
            else if ((strcmp(player1[0].roster[i][j].elementalaffinity, "Fire") == 0 &&
                    (strcmp(player2[0].roster[i][j].elementalaffinity, "Water") == 0 ||
                     strcmp(player2[0].roster[i][j].elementalaffinity, "Metal") == 0)) ||
                    
                    (strcmp(player1[0].roster[i][j].elementalaffinity, "Water") == 0 &&
                    (strcmp(player2[0].roster[i][j].elementalaffinity, "Grass") == 0 ||
                     strcmp(player2[0].roster[i][j].elementalaffinity, "Ice") == 0)) ||
    
                    (strcmp(player1[0].roster[i][j].elementalaffinity, "Grass") == 0 && 
                    (strcmp(player2[0].roster[i][j].elementalaffinity, "Fire") == 0 ||
                     strcmp(player2[0].roster[i][j].elementalaffinity, "Air") == 0 ||
                     strcmp(player2[0].roster[i][j].elementalaffinity, "Ice") == 0)) ||
                     
                    (strcmp(player1[0].roster[i][j].elementalaffinity, "Earth") == 0 && 
                    (strcmp(player2[0].roster[i][j].elementalaffinity, "Fire") == 0 ||
                     strcmp(player2[0].roster[i][j].elementalaffinity, "Grass") == 0 ||
                     strcmp(player2[0].roster[i][j].elementalaffinity, "Electric") == 0)) ||
                    
                    (strcmp(player1[0].roster[i][j].elementalaffinity, "Air") == 0 &&
                    (strcmp(player2[0].roster[i][j].elementalaffinity, "Earth") == 0 ||
                     strcmp(player2[0].roster[i][j].elementalaffinity, "Ice") == 0 ||
                     strcmp(player2[0].roster[i][j].elementalaffinity, "Metal") == 0)) ||
                    
                    (strcmp(player1[0].roster[i][j].elementalaffinity, "Electric") == 0 && 
                    (strcmp(player2[0].roster[i][j].elementalaffinity, "Water") == 0 ||
                     strcmp(player2[0].roster[i][j].elementalaffinity, "Grass") == 0 ||
                     strcmp(player2[0].roster[i][j].elementalaffinity, "Air") == 0 ||
                     strcmp(player2[0].roster[i][j].elementalaffinity, "Ice") == 0)) ||
                    
                    (strcmp(player1[0].roster[i][j].elementalaffinity, "Ice") == 0 &&
                    (strcmp(player2[0].roster[i][j].elementalaffinity, "Fire") == 0 ||
                     strcmp(player2[0].roster[i][j].elementalaffinity, "Metal") == 0)) ||
                    
                    (strcmp(player1[0].roster[i][j].elementalaffinity, "Metal") == 0 && 
                    (strcmp(player2[0].roster[i][j].elementalaffinity, "Water") == 0 ||
                     strcmp(player2[0].roster[i][j].elementalaffinity, "Earth") == 0 ||
                     strcmp(player2[0].roster[i][j].elementalaffinity, "Electric") == 0)))
                {
                    results[i][j] = '2';
                }

            // draw cases
            else
                results[i][j] = 'D';
        } 
    }
    fclose(fp);
}

// countWins 
void countWins (char results[3][3], int *ones, int *twos)
{
    for (int i=0; i<3; i++)
    {
        for (int j=0; j<3; j++)
        {
            if (results[i][j] == '1')
                (*ones)++;
            else if (results[i][j] == '2')
                (*twos)++;
        }
    }
}

// checkTicTacToeWin
int checkTicTacToeWin (char results[3][3], struct PlayerTag player[]) 
{
    // check rows and columns
    for (int i = 0; i < 3; i++)
    {
        if ((results[i][0] == '1' && results[i][1] == '1' && results[i][2] == '1') ||
            (results[0][i] == '1' && results[1][i] == '1' && results[2][i] == '1')) {
            return 1; /* player1 lucky win */
        }
    }
    for (int i = 0; i < 3; i++) 
    {
        if ((results[i][0] == '2' && results[i][1] == '2' && results[i][2] == '2') ||
            (results[0][i] == '2' && results[1][i] == '2' && results[2][i] == '2')) {
            return 2; /* player2 lucky win */
        }
    }
    // check diagonally
    if ((results[0][0] == '1' && results[1][1] == '1' && results[2][2] == '1') ||
        (results[0][2] == '1' && results[1][1] == '1' && results[2][0] == '1'))
        return 1;

    if ((results[0][0] == '2' && results[1][1] == '2' && results[2][2] == '2') ||
        (results[0][2] == '2' && results[1][1] == '2' && results[2][0] == '2'))
        return 1;

    return 0;
}

// showMatchResults: shows match results and saves them to a file
void showMatchResults (struct PlayerTag playerlist[], struct BattlePets BP[], struct PlayerTag player1[], struct PlayerTag player2[])
{
    int i, j;
    int ones=0, twos=0; /* counter for player 1 and 2 wins */
    int luckywinflag=0; /* lucky win indicator */
    int p1index = returnPlayerIndex(playerlist, player1[0].playername); /* player1's index simplified */
    int p2index = returnPlayerIndex(playerlist, player2[0].playername); /* player2's index simplified */
    char results[3][3]= {0}; /* char array that stores match results */
    int matchnum;       /* number of matches -> for incrementing */
    char matchcount;    /* number of matches -> to rename files */
    String36 winner;    /* stores winning player's name */
    String36 typeofwin; /* stores the type of win */
    String36 filename;  /* filename where match results are stored */
    FILE *fp; 

    compareElementalAffinities(BP, results, player1, player2);

    printf("\n[Match Results]\n");
    for (i=0; i<3; i++)
    {
        for (j=0; j<3; j++)
        {
            printf(" [%c]", results[i][j]);
        }
        printf("\n");
    }

    // count 1s and 2s
    countWins(results, &ones, &twos);

    // determine lucky win
    luckywinflag = checkTicTacToeWin(results, player1);

    //determine a winner
    if (luckywinflag == 1)
    {
        strcpy(winner, player1[0].playername);
        strcpy(typeofwin, "Lucky Win");
        printf("\nWinner: %s (Player 1) [Lucky Win]", player1[0].playername);
        playerlist[p1index].wincount +=1;
        playerlist[p2index].losscount +=1;
    }
    else if (luckywinflag == 2)
    {
        strcpy(winner, player2[0].playername);
        strcpy(typeofwin, "Lucky Win");
        printf("\nWinner: %s (Player 2) [Lucky Win]", player2[0].playername);
        playerlist[p2index].wincount +=1;
        playerlist[p1index].losscount +=1;
    }
    else if (ones > twos)
    {
        strcpy(winner, player1[0].playername);
        strcpy(typeofwin, "Majority Win");
        printf("\nWinner: %s (Player 1) [Majority Win]", player1[0].playername);
        playerlist[p1index].wincount +=1;
        playerlist[p2index].losscount +=1;
    }    
    else if (twos > ones)
    {
        strcpy(winner, player2[0].playername);
        strcpy(typeofwin, "Majority Win");
        printf("\nWinner: %s (Player 2) [Majority Win]", player2[0].playername);
        playerlist[p2index].wincount +=1;
        playerlist[p1index].losscount +=1;
    }
    else
    {
        strcpy(winner, "N/A");
        strcpy(typeofwin, "Draw");
        printf("\nWinner: N/A [Draw]");
        playerlist[p1index].drawcount +=1;
        playerlist[p2index].drawcount +=1;
    }
    printf("\n");

    // update the contents of players.txt based on results
    fp = fopen("players.txt", "wb");
    while ((fscanf(fp, "%[^\n]\n%d\n%d\n%d\n\n", playerlist[i].playername, &playerlist[i].wincount, &playerlist[i].losscount, &playerlist[i].drawcount)) == 4)
        i++;

    for (int m = 0; m < i; m++)
    {
        fprintf(fp, "%s\n%d\n%d\n%d\n\n", playerlist[m].playername, playerlist[m].wincount, playerlist[m].losscount, playerlist[m].drawcount);
    } 
    fclose(fp);

    // determine the name of the results file
    fp = fopen("results/match_count.txt", "r");
    fscanf(fp, " %c", &matchcount);
    strcpy(filename, "results/match_"); 
    strcat(filename, &matchcount);
    strcat(filename, ".txt");
    fclose(fp);

    // store match results to a file
    fp = fopen(filename, "w");
    fprintf(fp, "Player1: %s\n", player1[0].playername);
    fprintf(fp, "Player2: %s\n\n", player2[0].playername);
    fprintf(fp, "P1 Roster vs. P2 Roster\n");
    for (i=0; i<3; i++)
    {
        for (j=0; j<3; j++)
        {
            fprintf(fp, "%s vs. %s\n", player1[0].roster[i][j].battlepet, player2[0].roster[i][j].battlepet);
        }
    }
    fprintf(fp, "\nMatch Results\n");
    for (i=0; i<3; i++)
    {
        for (j=0; j<3; j++)
        {
            fprintf(fp, " %c", results[i][j]);
        }
        fprintf(fp, "\n");
    }
    fprintf(fp, "\nWinner: %s", winner);
    fprintf(fp, "\nType of Win: %s\n", typeofwin);

    // determine the match number
    fp = fopen("results/match_count.txt", "r");
    fscanf(fp, "%d\n", &matchnum);
    matchnum +=1;
    fclose(fp);

    // increment the match number
    fp = fopen("results/match_count.txt", "w");
    fprintf(fp, "%d\n", matchnum);
    fclose(fp);
}



/**
* Description : Select Battle!; Leads to game proper
* Author/s : Daguiso, Janelle Ann F.
*            
* Section : S27B
* Last Modified : Mar. 8, 2025
* Acknowledgments : N/A
*/
void selectBattle()
{
    struct BattlePets BP[MAX_BATTLEPETS];
    struct PlayerTag playerlist[MAX_USERS];
    struct PlayerTag player1[1], player2[1];
    int option;

    printf("\n -- Battle! --\n");

    // Determine Players 1 & Select BattlePet Roster
    printf("\n[Select Player 1]\n");
    selectPlayer(playerlist, player1);

    printf("\n[Select Player 1 Roster]\n");
    printf("[1] Load saved roster\n");
    printf("[2] Create roster for this match\n");

    printf("\n>> ");
    scanf("%d", &option);
    switch (option)
    {
        case 1: loadSavedRoster(BP, player1); break;
        case 2: createNewRoster(BP, player1, player2); break;
        default: printf("Incorrect input. Try again.\n");
    }    


    // Determine Player 2 & Select BattlePet Roster
    printf("\n[Select Player 2]\n");
    selectPlayer(playerlist, player2);

    printf("\n[Select Player 2 Roster]\n");
    printf("[1] Load saved roster\n");
    printf("[2] Create roster for this match\n");

    printf("\n>> ");
    scanf("%d", &option);
    switch (option)
    {
        case 1: loadSavedRoster(BP, player2); break;
        case 2: createNewRoster(BP, player2, player1); break;
        default: printf("Incorrect input. Try again.\n");
    }  

    // BattlePets, Fight!
    printf("\n -- BattlePets, Fight! --\n");
    printf("\n%s (Player 1) vs. %s (Player 2)\n", player1[0].playername, player2[0].playername);
    displayChallengers(player1, player2);

    // Show Match Results
    showMatchResults(playerlist, BP, player1, player2);
}
