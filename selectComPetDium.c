#include <stdio.h>
#include <strings.h>

#define MAX_BATTLEPETS 60

struct BattlePets
{
    String30 battlepet;         //BattlePet's name
    String30 elementalaffinity; //BattlePet's elemental affinity
    String240 description;      //BattlePet short description
    int matchcount;             //number of times the BattlePet has appeared in matches
};

// selectComPetDium menu options
void displayComPetDiumOptions ()
{
    printf("\nComPetDium Menu\n");
    printf("[1] View BattlePets\n");
    printf("[2] Add BattlePet\n");
    printf("[3] Edit BattlePet\n");
    printf("[4] Delete BattlePet\n");
    printf("[5] Save Roster\n");
}

// scan current selection of battlepets -> this will come from the competdium.txt + the added/edited pets 
void populateBattlePetList (struct BattlePets BP[], int *BPtotal)
{
    int i, len;
    int lastcharflag = 0;
    char lastchar[2];
    String30 word;

    for (i=0; i<(*BPtotal); i++)
    {
        scanf("%s", BP[i].battlepet);
        scanf("%s", BP[i].elementalaffinity);
        //scans the description
        do{
            scanf("%s", word);
      
            //checks whether the last word of the sentence was reached
            len = strlen(word);
            lastchar[0] = word[len-1];
            lastchar[1] = '\0';
            if (strcmp(lastchar, ".") == 0)
              lastcharflag++;

            strcat(BP[i].description, word);
            //adds a space between words
            if (lastcharflag != 1)
                strcat(BP[0].description, " ");

          } while (lastcharflag != 1);
        scanf("%d", &BP[i].matchcount);
    }
}

// viewBattlePets
void viewBattlePets (struct BattlePets BP[], int *BPtotal)
{
    int i;

    printf("\n-- View BattlePets --\n");

    for (i=0; i<(*BPtotal); i++)
    {
        printf("[%d]", i+1);
        printf("\nName: %s\n", BP[i].battlepet);
        printf("Elemental Affinity: %s\n", BP[i].elementalaffinity);
        printf("Description: %s\n", BP[i].description);
        printf("\n");
    }
}

// addBattlePet
void addBattlePet (struct BattlePets BP[], int *BPtotal)
{
    int len;
    int lastcharflag = 0;
    char lastchar[2];
    String30 word;

    printf("\n-- Add BattlePet --\n");

    printf("\nName: "); 
    scanf("%s", BP[*BPtotal].battlepet);
    printf("Elemental Affinity: ");
    scanf("%s", BP[*BPtotal].elementalaffinity);
    printf("Description: ");
    do{
        scanf("%s", word);
        len = strlen(word);
        lastchar[0] = word[len-1];
        lastchar[1] = '\0';
        if (strcmp(lastchar, ".") == 0)
          lastcharflag++;

        strcat(BP[*BPtotal].description, word);
        if (lastcharflag != 1)
            strcat(BP[*BPtotal].description, " ");

      } while (lastcharflag != 1);

    (*BPtotal)++;

    //update competdium.txt
}

// editBattlePet
void editBattlePet (struct BattlePets BP[])
{
    int option;
    int len;
    int lastcharflag = 0;
    char lastchar[2];
    String30 word;

    printf("\n-- Edit BattlePet --\n");

    printf("\nWhich BattlePet would you like to edit? (input a number): ");
    scanf("%d", &option);
    printf("\nEdit: %s\n", BP[option - 1].battlepet);

    printf("\nNew Name: "); 
    scanf("%s", BP[option - 1].battlepet);
    printf("New Elemental Affinity: ");
    scanf("%s", BP[option - 1].elementalaffinity);
    printf("New Description: ");
    strcpy(BP[option - 1].description, "");
    do{
        scanf("%s", word);
        len = strlen(word);
        lastchar[0] = word[len-1];
        lastchar[1] = '\0';
        if (strcmp(lastchar, ".") == 0)
          lastcharflag++;

        strcat(BP[option - 1].description, word);
        if (lastcharflag != 1)
            strcat(BP[option - 1].description, " ");

      } while (lastcharflag != 1);  
}

// deleteBattlePet
void deleteBattlePet (struct BattlePets BP[], int *BPtotal)
{
    int i, deletedBP;
    char option;

    printf("\n-- Delete BattlePet --\n");

    printf("\nWhich BattlePet would you like to delete? (input a number): ");
    scanf("%d", &deletedBP);

    //prompt user if they are sure before deletion
    printf("\nDo you wish to delete %s completely? (y/n): ", BP[deletedBP - 1].battlepet);
    scanf(" %c", &option);

    if (option == 'Y' || option == 'y')
    {
        printf("\n%s has been deleted.\n", BP[deletedBP-1].battlepet);

        for (i=deletedBP-1; i<(*BPtotal); i++)
        {
            strcpy(BP[i].battlepet, BP[i+1].battlepet);
            strcpy(BP[i].elementalaffinity, BP[i+1].elementalaffinity);
            strcpy(BP[i].description, BP[i+1].description);
        }
        (*BPtotal)--;
    }
    else if (option == 'N' || option == 'n')
    {
        printf("Awesome!");
    }

}

// display board
void displayBoard (String36 Board[][3])
{
    int i, j;

    printf("\tC#0\t\tC#1\t\tC#2\n");
    for (i=0; i<3; i++)
    {
      printf("R#%d", i);
      for (j=0; j<3; j++)
      {
        if (strlen(Board[i][j])<6)
        {
          printf("\t[%s]\t", Board[i][j]);
        }
        else
          printf("\t[%s]", Board[i][j]);
      }
      printf("\n");
    }
}

// saveRoster
void saveRoster ()
{
    int i, j;
    String36 Board[3][3];

    printf("\n-- Save Roster --\n");

    //ask for username -> loop through list of players

    //initialize board
    for (i=0; i<3; i++)
    {
      for (j=0; j<3; j++)
        {
          strcpy(Board[i][j], "insert here");
        }
    }

    displayBoard(Board);

    //take user input
    printf("\nInsert BattlePets\n");

    for (i=0; i<3; i++)
    {
      for (j=0; j<3; j++)
        {
          printf("[%d][%d]: ", i, j);
          scanf("%s", Board[i][j]);
        }
    }

    printf("\n");
    displayBoard(Board);

    //save to saved_roster/<player_name>.txt
}

/**
* Description : Select ComPetDium; Players can view, add, edit, and delete BattlePets, and save them to their roster
* Author/s : Daguiso, Janelle Ann F.
*            
* Section : S27B
* Last Modified : Feb. 22, 2025
* Acknowledgments : N/A
*/
void selectComPetDium(int *BPtotal)
{
    struct BattlePets BP[MAX_BATTLEPETS];
    int competdiuminput;

    printf("\n -- ComPetDium --\n");

    displayComPetDiumOptions();
    // populateBattlePetList(Initial); //this should come from a file initially
    printf("\n>> ");
    scanf("%d", &competdiuminput);

    switch(competdiuminput)
    {
        case 1: viewBattlePets(BP, BPtotal); break;

        case 2: addBattlePet(BP, BPtotal); break;

        case 3: editBattlePet(BP); break;

        case 4: deleteBattlePet(BP, BPtotal); break;

        case 5: saveRoster(); break;

        default: printf("Incorrect input. Try again.\n");
    }
    printf("\n");

}