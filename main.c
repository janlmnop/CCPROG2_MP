#include <stdio.h>
#include <strings.h>

//DEFINITIIONs (tentative) 
#define MAX_USERS 50;
#define MAX_BATTLEPETS 60;

typedef char String36[37];
typedef char String30[31];
typedef char String240[241];


//STRUCTURES (tentative)
struct Player
{
    String36 username; //player username
    String36 roster[9]; //array of arrays
};

struct BattlePets
{
    String30 battlepet; //BattlePet's name
    int elementalaffinity; //BattlePet's elemental affinity
    String240 description; //BattlePet short description
};



/**
* Description : Displays the main menu
* Author/s : Daguiso, Janelle
*            Mariano, Janyka
* Section : S27B
* Last Modified : <date when last revision was made>
* Acknowledgments : <list of references used in the making of this project>
*/
void displayMainMenu()
{
    printf("\nMain Menu\n");
    printf("[1] Battle!\n");
    printf("[2] ComPetDium\n");
    printf("[3] View Statistics\n");
    printf("[0] Exit\n");
}


/**
* Description : Select Battle!; leads to game proper -> i'm not sure pa if it should return something; we prolly need one of those
* Author/s : 
*            
* Section : S27B
* Last Modified : <date when last revision was made>
* Acknowledgments : <list of references used in the making of this project>
*/
void selectBattle()
{
    printf("\n -- Battle! --\n");
}


/**
* Description : Select ComPetDium; Players can view, add, edit, and delete BattlePets, and save them to their roster
* Author/s : 
*            
* Section : S27B
* Last Modified : <date when last revision was made>
* Acknowledgments : <list of references used in the making of this project>
*/
void selectComPetDium()
{
    printf("\n -- ComPetDium --\n");
}

/**
* Description : Select View Statistics; Players can view the current leaderboard of players and BattlePets
* Author/s : 
*            
* Section : S27B
* Last Modified : <date when last revision was made>
* Acknowledgments : <list of references used in the making of this project>
*/
void selectViewStatistics()
{
    printf("\n -- View Statistics --\n");
}

/**
* Description : Select Exit; Quit game
* Author/s : Janelle Ann F. Daguiso
*            
* Section : S27B
* Last Modified : Feb. 9, 2025
* Acknowledgments : <list of references used in the making of this project>
*/
void selectExit(int *quitflag)
{
    char option;

    printf("\nDo you wish to proceed? (y/n): ");
    scanf(" %c", &option);

    if (option == 'Y' || option == 'y')
    {
        printf("Alright, byeeee");
        *quitflag = 1;
    }
    else if (option == 'N' || option == 'n')
    {
        printf("Yayyyy");
    }
}



// FUNCTIONS (tentative)
// syntax: verb_noun in camel-case
// notes: 
//   - functions marked done can still be improved visually, but they should work already
//   - don't forget to call functions in main
//   - follow conventions; basically, make it look pretty haha

//displayMainMenu <done>
    //selectBattle <in progress - Janelle>
        //selectPlayer <in progres - Janelle>
        //loadBattlePetRoster
        //selectBattlePetRoster 
        //displayBattlePetRoster
        //compareBattlePets -> this is the BattlePets, fight!
        //showMatchResults
        //promptUserPlayAgain
    //selectComPetDium
        //viewBattlePets
        //addBattlePet
        //editBattlePet
        //deleteBattlePet
        //saveRoster
    //selectViewStatistics
        //displayTop5Players
        //displayTop5BattlePets
        //countPlayerWins -> could just be a pointer that increments
        //countBattlePetAppearance -> could just be a pointer that increments
    //selectExit <done>


int main () {
    //variable declarations
    int menuinput;
    int quitflag = 0;


    //program proper
    do {
        displayMainMenu();
        printf("\n>> ");
        scanf("%d", &menuinput);

        switch(menuinput)
        {
            case 1: selectBattle(); break;

            case 2: selectComPetDium(); break;

            case 3: selectViewStatistics(); break;

            case 0: selectExit(&quitflag); break;

            default: printf("Incorrect input. Try again.\n");
        }
        printf("\n");
    } while (quitflag != 1);

    return 0;
}
