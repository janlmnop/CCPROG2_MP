#include <stdio.h>
#include <strings.h>
#include "definitions.h"

/**
 * Counts the number of BattlePets in competdium.txt
 * @param BP Array of BattlePet structures
 * @return The number of BattlePets in competdium.txt
 */
int countBattlePets (struct BattlePets BP[])
{
    FILE *fp; 
    int i=0;

    fp = fopen("competdium.txt", "r");

    if ((fp = fopen("competdium.txt", "r")) == NULL)
		printf("ERROR: %s does not exist.\n", "competdium.txt");

    while ((fscanf(fp, "%[^\n]\n%[^\n]\n%[^\n]\n%d\n\n", BP[i].battlepet, BP[i].elementalaffinity, BP[i].description, &BP[i].matchcount)) == 4)
        i++;

    fclose(fp);

    return i;
}

/**
 * Counts the number of players in players.txt
 * @param playerlist Array of PlayerTag structures
 * @return The number of players in players.txt
 */
int countPlayers (struct PlayerTag playerlist[])
{
    FILE *fp; 
    int i=0;

    fp = fopen("players.txt", "r");

    if ((fp = fopen("players.txt", "r")) == NULL)
		printf("ERROR: %s does not exist.\n", "players.txt");

    while ((fscanf(fp, "%[^\n]\n%d\n%d\n%d\n\n", playerlist[i].playername, &playerlist[i].wincount, &playerlist[i].losscount, &playerlist[i].drawcount)) == 4)
        i++;

    fclose(fp);
     
    return i;
}

/**
 * Option for the user to select from a list of existing players or to make a new one
 * @param playerlist Array of PlayerTag structures to display the existing players
 * @param player The current player
 * @pre playerlist contains existing players from prevous games
 */
void selectPlayer (struct PlayerTag playerlist[], struct PlayerTag player[])
{
    FILE *fp; 

    int option;
    int i=0;

    fp = fopen("players.txt", "r");
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
        printf("\nNew player username: ");
        scanf("%s", playerlist[option-1].playername);
        strcpy(player[0].playername, playerlist[option-1].playername);
        player[0].wincount = 0;
        player[0].losscount = 0;
        player[0].drawcount = 0;
        fprintf(fp, "%s\n%d\n%d\n%d\n\n", playerlist[option-1].playername, playerlist[option-1].wincount, playerlist[option-1].losscount, playerlist[option-1].drawcount);
        printf("\nGreetings, %s!\n", player[0].playername);
        fclose(fp);
    }
    else if (option < i+1 && option > 0) /* past players option */
    {
        printf("\nWelcome back, %s!\n", playerlist[option-1].playername);
        player[0] = playerlist[option-1];
    }
    else
        printf("Incorrect input. Try again.\n");
    
    fclose(fp);
}

/**
 * Displays a player's BattlePet roster
 * @param player The current player
 */
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

/**
 * Assigns BattlePet information (name, elemental affinity, description, & match count) to the players' roster
 * @param BP Array of BattlePet structures
 * @param player The current player
 * @pre player[0].roster.battlepet should exist in competdium.txt (list of BattlePets)
 */
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

/**
 * Loads a player's roster from a file
 * @param BP Array of BattlePet structures
 * @param currentplayer The current player
 * @param otherplayer The opposing player
 */
void loadSavedRoster (struct BattlePets BP[], struct PlayerTag currentplayer[], struct PlayerTag otherplayer[])
{
    String36 filename;
    FILE *fp;

    // look for the player's file
    strcpy(filename, "saved_roster/"); 
    strcat(filename, currentplayer[0].playername);
    strcat(filename, ".txt");

    fp = fopen(filename, "r");

    if ((fp = fopen(filename, "r")) == NULL)
    {
		printf("ERROR: %s does not exist.\n", filename);

        printf("\nCreating New Roster\n");
        createNewRoster(BP, currentplayer, otherplayer);
	}
    else
    {
        // scan player's file and get their BPs
        for (int i=0; i<3; i++)
        {
            for (int j=0; j<3; j++)
            {
                fscanf(fp, "%s", currentplayer[0].roster[i][j].battlepet);
            }
        }

        saveRosterInfo(BP, currentplayer);

        printf("\n[Match Roster]\n");
        displayRoster(currentplayer);

        fclose(fp);
    } 
}

/**
 * Checks whether a BattlePet has already been selected by the other player
 * @param selectedBP The index of the BattlePet the user wants to store in their roster
 * @param player The current player
 * @param BP Array of BattlePet structures
 * @pre BattlePet should be an existing BattlePet in competdium.txt
 */
int checkPetAvailability (int selectedBP, struct PlayerTag player[], struct BattlePets BP[])
{

    for (int i = 0; i <3; i++)
    {
        for (int j=0; j<3; j++)
        {
            if (strcmp(player[0].roster[i][j].battlepet, BP[selectedBP].battlepet) == 0)
                return 1;   /* returns 1 if the BP is already selected by the other player */
        }
    }
    return 0;   /* returns 0 if the BP is still available */
}

/**
 * Returns the index of the selected BattlePet
 * @param BP Array of BattlePet structures
 * @param selectedBP The index of the BattlePet the user wants to store in their roster
 * @return The index of the selected BattlePet based on competdium.txt
 */
int returnBPIndex (struct BattlePets BP[], int selectedBP)
{
    for (int i=0; i<countBattlePets(BP); i++)
    {
        if (strcmp(BP[i].battlepet, BP[selectedBP].battlepet) == 0)
            return i;
    }
    return -1;
}

/**
 * Returns the index of the player
 * @param playerlist Array of PlayerTag structures
 * @param name The name of the player
 * @return The index of the player
 * @pre name exists in players.txt
 */
int returnPlayerIndex (struct PlayerTag playerlist[], String36 name)
{
    for (int i=0; i<countPlayers(playerlist); i++)
    {
        if (strcmp(playerlist[i].playername, name) == 0)
            return i;
    }
    return -1;
}

/**
 * Option to create a new BattlePet roster for the current game
 * @param BP Array of BattlePet structures
 * @param currentplayer The current player
 * @param otherplayer The opposing player (used to compare if the currentplayer's chosen BattlePet has already been selected)
 */
void createNewRoster (struct BattlePets BP[], struct PlayerTag currentplayer[], struct PlayerTag otherplayer[])
{
    int i=0, j, x, y;
    int flag[16] = {0}; /* initializes array elements to 0 */
    int selectedBP;
    FILE *fp;

    // show grid where BattlePets will go
    displayRoster(currentplayer);

    // read BattlePets from a file
    fp = fopen("competdium.txt", "r");

    while ((fscanf(fp, "%[^\n]\n%[^\n]\n%[^\n]\n%d\n\n", BP[i].battlepet, BP[i].elementalaffinity, BP[i].description, &BP[i].matchcount)) == 4)
        i++;

    // check whether the BattlePet has been selected by otherplayer
    for (j=0; j<i; j++)
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
            printf("[%d] %s\n", j+1, BP[j].battlepet);
    }

    // let user make a roster
    printf("\n[Create Roster]\n");
    for (x=0; x<3; x++)
    {
        for (y=0; y<3; y++)
        {
            do {
                printf("[%d][%d]: ", x, y);
                scanf("%d", &selectedBP);
    
                selectedBP -= 1;
                if (checkPetAvailability(selectedBP, otherplayer, BP))
                    printf("This BattlePet has already been selected!\n");
                else if (selectedBP <= 0 || selectedBP >= i)
                    printf("Incorrect input. Try again.\n");
    
            } while (checkPetAvailability(selectedBP, otherplayer, BP));

            strcpy(currentplayer[0].roster[x][y].battlepet, BP[selectedBP].battlepet);
            currentplayer[0].roster[x][y] = BP[selectedBP];
        }
    }

    // display thisplayer's final roster
    printf("\n[Player's Final Roster]\n");
    displayRoster(currentplayer);

    fclose(fp);
}

/**
 * Displays which BattlePet goes against each other in each player's roster
 * @param player1 Player 1
 * @param player2 Player 2
 */
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

/**
 * Compares the elemental affinities of the BattlePets in each player's roster and stores the results in a 1D array
 * @param BP Array of BattlePet structures
 * @param results 2D array of characters to store match results
 * @param player1 Player 1
 * @param player2 Player 2 
 */
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

/**
 * Counts the occurence of 1s and 2s in results to determine a winner
 * @param results 2D array of characters to store match results
 * @param ones Adress that stores the occurence of 1s in results
 * @param twos Adress that stores the occurence of 2s in results
 */
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

/**
 * Checks whether a lucky win can be declared based on results
 * @param results 2D array of characters to store match results
 * @return 1 if player1 wins based on Tic-Tac-Toe rules
 * @return 2 if player2 wins based on Tic-Tac-Toe rules
 * @return 0 if there is no Tic-Tac-Toe pattern detected
 */
int checkTicTacToeWin (char results[3][3]) 
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
        return 2;

    return 0;
}

/**
 * Shows the match results and saves them to a file
 * @param playerlist Array of PlayerTag structures
 * @param BP Array of BattlePet structures
 * @param player1 Player 1
 * @param player2 Player 2
 */
void showMatchResults (struct PlayerTag playerlist[], struct BattlePets BP[], struct PlayerTag player1[], struct PlayerTag player2[])
{
    int i, j;
    int ones=0, twos=0; /* counter for player 1 and 2 wins */
    int luckywinflag=0; /* lucky win indicator */
    int p1index = returnPlayerIndex(playerlist, player1[0].playername); /* player1's index simplified */
    int p2index = returnPlayerIndex(playerlist, player2[0].playername); /* player2's index simplified */
    char results[3][3]= {0}; /* char array that stores match results */
    int matchnum;          /* number of matches -> for incrementing */
    char matchcount[3];    /* number of matches -> for renaming files */
    String36 winner;       /* stores winning player's name */
    String36 typeofwin;    /* stores the type of win */
    String36 filename;     /* filename where match results are stored */
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

    // determine lucky win if any
    luckywinflag = checkTicTacToeWin(results);

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
    fp = fopen("players.txt", "w");
    while ((fscanf(fp, "%[^\n]\n%d\n%d\n%d\n\n", playerlist[i].playername, &playerlist[i].wincount, &playerlist[i].losscount, &playerlist[i].drawcount)) == 4)
        i++;

    for (int m=0; m<i+1; m++)
    {
        fprintf(fp, "%s\n%d\n%d\n%d\n\n", playerlist[m].playername, playerlist[m].wincount, playerlist[m].losscount, playerlist[m].drawcount);
    } 
    fclose(fp);

    // determine the name of the results file
    fp = fopen("results/match_count.txt", "r");
    fscanf(fp, "%s", matchcount);
    strcpy(filename, "results/match_"); 
    strcat(filename, matchcount);
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
 * Main function executed when the player selects 'Battle!'; leads to the game proper.
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
        case 1: loadSavedRoster(BP, player1, player2); break;
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
        case 1: loadSavedRoster(BP, player2, player1); break;
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
