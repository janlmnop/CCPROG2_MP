#include <stdio.h>
#include <strings.h>


// DEFINITIONS
#define MAX_USERS 50
#define MAX_BATTLEPETS 60

typedef char String36[37];      //Player username
typedef char String30[31];      //BattlePet name and elemental affinity
typedef char String240[241];    //BattlePet description

// STRUCTURES
struct BattlePets
{
    String30 battlepet;         //BattlePet's name
    String30 elementalaffinity; //BattlePet's elemental affinity
    String240 description;      //BattlePet short description
    int matchcount;             //number of times the BattlePet has appeared in matches
};

struct PlayerTag
{
    String36 playername;            //player username
    int wincount;                   //player win count
    int losscount;                  //player loss count
    int drawcount;                  //player draw count
    struct BattlePets roster[3][3]; //array of arrays
};


// FUNCTION PROTOTYPES
/* selectBattle.c */
int countBattlePets (struct BattlePets BP[]);
int countPlayers (struct PlayerTag playerlist[]);
void selectPlayer (struct PlayerTag playerlist[], struct PlayerTag player[]);
void displayRoster (struct PlayerTag player[]);
void saveRosterInfo (struct BattlePets BP[], struct PlayerTag player[]);
void loadSavedRoster (struct BattlePets BP[], struct PlayerTag player[]);
int checkPetAvailability (String36 BattlePet, struct PlayerTag player[]);
int returnBPIndex (struct BattlePets BP[], String36 name);
int returnPlayerIndex (struct PlayerTag playerlist[], String36 name);
void createNewRoster (struct BattlePets BP[], struct PlayerTag currentplayer[], struct PlayerTag otherplayer[]);
void displayChallengers (struct PlayerTag player1[], struct PlayerTag player2[]);
void compareElementalAffinities (struct BattlePets BP[], char results[3][3], struct PlayerTag player1[], struct PlayerTag player2[]);
void countWins (char results[3][3], int *ones, int *twos);
void showMatchResults (struct PlayerTag playerlist[], struct BattlePets BP[], struct PlayerTag player1[], struct PlayerTag player2[]);

/* selectComPetDium.c */
void populateBattlePetList (struct BattlePets BP[], int *BPtotal);
void viewBattlePets (struct BattlePets BP[], int *BPtotal);
void addBattlePet (struct BattlePets BP[], int *BPtotal);
void editBattlePet (struct BattlePets BP[]);
void deleteBattlePet (struct BattlePets BP[], int *BPtotal);
void displayBoard (String36 Board[][3]);

