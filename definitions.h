/************************************************************************************************************************
 * Description   : This file is for declaring definitions, structures, and function prototypes used in the program.
 * Authors/s     : Daguiso, Janelle Ann F.
 * 
 * Section       : S27B
 * Last Modified : Mar. 24, 2025
*************************************************************************************************************************/

#include <stdio.h>
#include <strings.h>

#ifndef definitions
#define definitions

#define MAX_USERS 50            // Maximum number of Users / Players
#define MAX_BATTLEPETS 60       // Maximum number of BattlePets

typedef char String36[37];      // Player's username
typedef char String30[31];      // BattlePet name and elemental affinity
typedef char String240[241];    // BattlePet description


/**
 * Represents a BattlePet 
 */
struct BattlePets
{
    String30 battlepet;         // BattlePet's name
    String30 elementalaffinity; // BattlePet's elemental affinity
    String240 description;      // BattlePet's short description
    int matchcount;             // Number of times the BattlePet has appeared in matches
};

/**
 * Represents a Player
 */
struct PlayerTag
{
    String36 playername;            // Player's username
    int wincount;                   // Player's win count
    int losscount;                  // Player's loss count
    int drawcount;                  // Player's draw count
    struct BattlePets roster[3][3]; // Player's BattlePet roster
};


// FUNCTION PROTOTYPES
/* selectBattle.c */
int countBattlePets (struct BattlePets BP[]);
int countPlayers (struct PlayerTag playerlist[]);
void selectPlayer (struct PlayerTag playerlist[], struct PlayerTag player[]);
void displayRoster (struct PlayerTag player[]);
void saveRosterInfo (struct BattlePets BP[], struct PlayerTag player[]);
void loadSavedRoster (struct BattlePets BP[], struct PlayerTag currentplayer[], struct PlayerTag otherplayer[]);
int checkPetAvailability (int selectedBP, struct PlayerTag player[], struct BattlePets BP[]);
int returnBPIndex (struct BattlePets BP[], int selectedBP);
int returnPlayerIndex (struct PlayerTag playerlist[], String36 name);
void createNewRoster (struct BattlePets BP[], struct PlayerTag currentplayer[], struct PlayerTag otherplayer[]);
void displayChallengers (struct PlayerTag player1[], struct PlayerTag player2[]);
void compareElementalAffinities (struct BattlePets BP[], char results[3][3], struct PlayerTag player1[], struct PlayerTag player2[]);
void countWins (char results[3][3], int *ones, int *twos);
void showMatchResults (struct PlayerTag playerlist[], struct BattlePets BP[], struct PlayerTag player1[], struct PlayerTag player2[]);

/* selectComPetDium.c */
void viewBattlePets (struct BattlePets BP[]);
void addBattlePet (struct BattlePets BP[]);
void editBattlePet (struct BattlePets BP[]);
void deleteBattlePet (struct BattlePets BP[]);
void displayBoard (String36 Board[][3]);
void saveRoster (struct BattlePets BP[]);


#endif // definitions
