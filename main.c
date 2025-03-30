/**
* Description : BattlePets! is a game where two players' rosters compete against each other based on their elemental affinities.
* Author/s : Daguiso, Janelle Ann
*            Mariano, Janyka Rochelle
* Section : S27B
* Last Modified : Mar. 30, 2025
* Acknowledgments : https://cplusplus.com/reference/cstdio/scanf/
*/

#include <stdio.h>
#include <strings.h>
#include "definitions.h"
#include "selectBattle.c"
#include "selectComPetDium.c"
#include "ViewStatistics.c"


/**
 * Displays the main menu options
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
 * Prompts the user to exit the program
 * @param quitflag Indicates whether the program should terminate: 0 to continue, 1 to exit
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
        printf("Awesome!");
    else
        printf(">:(\n");
}


int main () {
    int menuinput;
    int quitflag = 0;
   

    do {
        displayMainMenu();
        printf("\n>> ");
        scanf("%d", &menuinput);

        switch(menuinput)
        {
            case 1: Battle(); break;

            case 2: ComPetDium(); break;

            case 3: ViewStats(); break;

            case 0: selectExit(&quitflag); break;

            default: printf("Incorrect input. Try again.\n");
        }
        printf("\n");
    } while (quitflag != 1);

    return 0;
}

/** 
 * This is to certify that this project is my/our own work, based on my/our personal
 * efforts in studying and applying the concepts learned. I/We have constructed the
 * functions and their respective algorithms and corresponding code by myself/ourselves.
 * The program was run, tested, and debugged by my/our own efforts. I/We further certify
 * that I/We have not copied in part or whole or otherwise plagiarized the work of
 * other students and/or persons.asm
 * 
 * Daguiso, Janelle Ann 12305782
 * Mariano, Janyka Rochelle 12307653
*/
