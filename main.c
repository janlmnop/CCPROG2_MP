#include <stdio.h>
#include <strings.h>
#include "selectBattle.c"
#include "selectComPetDium.c"

//DEFINITIIONs
#define MAX_USERS 50
#define MAX_BATTLEPETS 60

typedef char String36[37];
typedef char String30[31];
typedef char String240[241];


//STRUCTURES
struct Player
{
    String36 username;  //player username
    String36 roster[9]; //array of arrays
};



/**
* Description : Displays the main menu
* Author/s : Daguiso, Janelle Ann F.
*            
* Section : S27B
* Last Modified : Feb. 7, 2025
* Acknowledgments : N/A
*/
void displayMainMenu()
{
    printf("\nMain Menu\n");
    printf("[1] Battle!\n");
    printf("[2] ComPetDium\n");
    printf("[3] View Statistics\n");
    printf("[0] Exit\n");
}


//selectBattle placeholder

//selectComPetDium placeholder

/*
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
* Author/s : Daguiso, Janelle Ann F.
*            
* Section : S27B
* Last Modified : Feb. 9, 2025
* Acknowledgments : N/A
*/
void selectExit(int *quitflag)
{
    char option;

    printf("\nDo you wish to proceed? (y/n): ");
    scanf(" %c", &option);

    if (option == 'Y' || option == 'y')
    {
        printf("Farewell, player!");
        *quitflag = 1;
    }
    else if (option == 'N' || option == 'n')
    {
        printf("Awesome!");
    }
}





int main () {
    //variable declarations
    int menuinput;
    int quitflag = 0;
    int BPtotal = 16;   /* 16 initially */
   

    //program proper
    do {
        displayMainMenu();
        printf("\n>> ");
        scanf("%d", &menuinput);

        switch(menuinput)
        {
            case 1: selectBattle(); break;

            case 2: selectComPetDium(&BPtotal); break;

            case 3: selectViewStatistics(); break;

            case 0: selectExit(&quitflag); break;

            default: printf("Incorrect input. Try again.\n");
        }
        printf("\n");
    } while (quitflag != 1);

    return 0;
}




// notes: 
//   - functions marked done can still be improved visually, but they should work already
//   - don't forget to call functions in main
//   - follow conventions; basically, make it look pretty haha
//   - there's a lot of functions so the code looks clean

// I - in progress
// D - done (needs minor improvements)
// X - done (completely)

/*
   FUNCTIONS (ideally) 
    [ ] selectBattle 
        [I] selectPlayer
        [ ] loadBattlePetRoster
        [ ] selectBattlePetRoster
        [ ] displayBattlePetRoster
        [ ] compareBattlePets -> this is the BattlePets, fight!
        [ ] showMatchResults
        [ ] promptUserPlayAgain
    [D] selectComPetDium
        [D] viewBattlePets
        [D] addBattlePet
        [D] editBattlePet
        [D] deleteBattlePet
        [D] saveRoster
    [ ] selectViewStatistics
        [ ]displayTop5Players
        [ ] displayTop5BattlePets
        [ ] countPlayerWins -> could just be a pointer that increments
        [ ] countBattlePetAppearance -> could just be a pointer that increments
    [X] selectExit
*/
