#include <stdio.h>
#include <strings.h>


#define MAX_USERS 50            // Maximum number of Users / Players
#define MAX_BATTLEPETS 60       // Maximum number of BattlePets

typedef char String36[37];      // Player's username
typedef char String30[31];      // BattlePet name and elemental affinity
typedef char String240[241];    // BattlePet description

/**
 * Represents a BattlePet 
 */
struct BattlePet
{
    String30 battlepet;         // BattlePet's name
    String30 elementalaffinity; // BattlePet's elemental affinity
    String240 description;      // BattlePet's short description
    int matchcount;             // Number of times the BattlePet has appeared in matches
};


/**
 * Displays ComPetDium menu options: view, add, edit, and delete BattlePet(s); save roster
 */
void displayComPetDiumOptions ()
{
    printf("\nComPetDium Menu\n");
    printf("[1] View BattlePets\n");
    printf("[2] Add BattlePet\n");
    printf("[3] Edit BattlePet\n");
    printf("[4] Delete BattlePet\n");
    printf("[5] Save Roster\n");
}

/**
 * Option to display the list of BattlePets in competdium.txt
 * @param BP Array of BattlePet structures
 */
void viewBattlePets (struct BattlePet BP[])
{
  FILE *fp;

  fp = fopen("competdium.txt", "r");

    int i=0, j;

    printf("\n-- View BattlePets --\n");

    if ((fp = fopen("competdium.txt", "r")) == NULL)
		fprintf(stderr, "ERROR: %s does not exist.\n", "competdium.txt");

    while ((fscanf(fp, "%[^\n]\n%[^\n]\n%[^\n]\n%d\n\n", BP[i].battlepet, BP[i].elementalaffinity, BP[i].description, &BP[i].matchcount)) == 4)
        i++;

    for (j=0; j<i; j++)
    {
        printf("[%d]", j+1);
        printf("\nName: %s\n", BP[j].battlepet);
        printf("Elemental Affinity: %s\n", BP[j].elementalaffinity);
        printf("Description: %s\n", BP[j].description);
        printf("\n");
    }

  fclose(fp);
}

/**
 * Option to add a BattlePet to the list of BattlePets in competdium.txt
 * @param BP Array of BattlePet structures
 */
void addBattlePet (struct BattlePet BP[])
{
    int i=0;
    int len;
    int okflag=0;
    int lastcharflag = 0;
    char lastchar[2];
    String30 ea;
    String30 word;
    FILE *fp;

    printf("\n-- Add BattlePet --\n");

    if ((fp = fopen("competdium.txt", "r")) == NULL)
		fprintf(stderr, "ERROR: %s does not exist.\n", "competdium.txt");

    while ((fscanf(fp, "%[^\n]\n%[^\n]\n%[^\n]\n%d\n\n", BP[i].battlepet, BP[i].elementalaffinity, BP[i].description, &BP[i].matchcount)) == 4)
        i++;
    
    fclose(fp);

    fp = fopen("competdium.txt", "a");
    printf("\nName: "); 
    scanf("%s", BP[i].battlepet);
    fprintf(fp, "%s\n", BP[i].battlepet);
    
    do {
      printf("Elemental Affinity: ");
      scanf("%s", ea);
      if (strcmp(ea, "Fire") == 0 || strcmp(ea, "Water") == 0 || strcmp(ea, "Grass") == 0 || strcmp(ea, "Earth") == 0 || 
           strcmp(ea, "Air") == 0 || strcmp(ea, "Electric") == 0 || strcmp(ea, "Ice") == 0 || strcmp(ea, "Metal") == 0)
          {
            strcpy(BP[i].elementalaffinity, ea);
            fprintf(fp, "%s\n", BP[i].elementalaffinity);
            okflag++;
          }
      else
        printf("Incorrect input. Try again.\n");
      
    } while (okflag != 1);

    printf("Description: ");
    do{
        scanf("%s", word);
        len = strlen(word);
        lastchar[0] = word[len-1];
        lastchar[1] = '\0';
        if (strcmp(lastchar, ".") == 0)
          lastcharflag++;

        strcat(BP[i].description, word);
        if (lastcharflag != 1)
            strcat(BP[i].description, " ");

      } while (lastcharflag != 1);
    fprintf(fp, "%s\n", BP[i].description);
    BP[i+1].matchcount = 0;
    fprintf(fp, "%d\n\n", BP[i].matchcount);

    fclose(fp);
}

/**
 * Option to edit an existing BattlePet in the list of BattlePets in competdium.txt
 * @param BP Array of BattlePet structures
 */
void editBattlePet (struct BattlePet BP[])
{
    int i = 0, j;
    int option;
    int len;
    int okflag = 0;
    int lastcharflag = 0;
    char lastchar[2];
    String30 ea;
    String30 word;
    FILE *fp;

    printf("\n-- Edit BattlePet --\n");

    if ((fp = fopen("competdium.txt", "r")) == NULL)
		  printf("ERROR: %s does not exist.\n", "competdium.txt");

    while ((fscanf(fp, "%[^\n]\n%[^\n]\n%[^\n]\n%d\n\n", BP[i].battlepet, BP[i].elementalaffinity, BP[i].description, &BP[i].matchcount)) == 4)
        i++;
    
    fclose(fp);

    printf("\nWhich BattlePet would you like to edit? (input a number): ");
    scanf("%d", &option);
    printf("\nEdit: %s\n", BP[option - 1].battlepet);
    printf("\nNew Name: "); 
    scanf("%s", BP[option - 1].battlepet);

    do {
      printf("New Elemental Affinity: ");
      scanf("%s", ea);
      if (strcmp(ea, "Fire") == 0 || strcmp(ea, "Water") == 0 || strcmp(ea, "Grass") == 0 || strcmp(ea, "Earth") == 0 || 
           strcmp(ea, "Air") == 0 || strcmp(ea, "Electric") == 0 || strcmp(ea, "Ice") == 0 || strcmp(ea, "Metal") == 0)
          {
            strcpy(BP[option - 1].elementalaffinity, ea);
            fprintf(fp, "%s\n", BP[option - 1].elementalaffinity);
            okflag++;
          }
      else
        printf("Incorrect input. Try again.\n");
      
    } while (okflag != 1);

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

    // print the new contents to the file
    fp = fopen("competdium.txt", "w");
    for (j=0; j<i; j++)
    {
      fprintf(fp, "%s\n", BP[j].battlepet);
      fprintf(fp, "%s\n", BP[j].elementalaffinity);
      fprintf(fp, "%s\n", BP[j].description);
      fprintf(fp, "%d\n\n", BP[j].matchcount);
    }
    fclose(fp);
}

/**
 * Option ot delete a BattlePet from the list of BattlePets in competdium.txt
 * @param BP Array of BattlePet structures
 */
void deleteBattlePet (struct BattlePet BP[])
{
    int j=0, i=0, deletedBP;
    char option;
    FILE *fp;

    printf("\n-- Delete BattlePet --\n");

    if ((fp = fopen("competdium.txt", "r")) == NULL)
		fprintf(stderr, "ERROR: %s does not exist.\n", "competdium.txt");

    while ((fscanf(fp, "%[^\n]\n%[^\n]\n%[^\n]\n%d\n\n", BP[i].battlepet, BP[i].elementalaffinity, BP[i].description, &BP[i].matchcount)) == 4)
        i++;
    
    fclose(fp);

    printf("\nWhich BattlePet would you like to delete? (input a number): ");
    scanf("%d", &deletedBP);

    //prompt user if they are sure before deletion
    printf("\nDo you wish to delete %s completely? (y/n): ", BP[deletedBP - 1].battlepet);
    scanf(" %c", &option);

    if (option == 'Y' || option == 'y')
    {
      printf("\n%s has been deleted.\n", BP[deletedBP-1].battlepet);

      for (j=deletedBP-1; j<i; j++)
      {
        strcpy(BP[j].battlepet, BP[j+1].battlepet);
        strcpy(BP[j].elementalaffinity, BP[j+1].elementalaffinity);
        strcpy(BP[j].description, BP[j+1].description);
        BP[j].matchcount = 0;
      }
      fp = fopen("competdium.txt", "w");
      for (j=0; j<i-1; j++)
      {
        fprintf(fp, "%s\n", BP[j].battlepet);
        fprintf(fp, "%s\n", BP[j].elementalaffinity);
        fprintf(fp, "%s\n", BP[j].description);
        fprintf(fp, "%d\n\n", BP[j].matchcount);
      }
      fclose(fp);
    }
    else if (option == 'N' || option == 'n')
    {
        printf("Awesome!");
    }
}

/**
 * Displays a player's 3x3 roster
 * @param Board 2D array of strings the stores a player's roster information
 */
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

/**
 * Option for a user to create and save a 3x3 roster
 * @param BP Array of BattlePet structures
 */
void saveRoster (struct BattlePet BP[])
{
    int i, j, x=0, y;
    int okflag=0;
    int found=0;
    String36 Board[3][3];
    String36 playername;
    String36 filename;
    String36 selection;

    FILE *fp;

    printf("\n-- Save Roster --\n");

    printf("Enter player name: ");
    scanf("%s", playername);

    strcpy(filename, "saved_roster/"); 
    strcat(filename, playername);
    strcat(filename, ".txt");

    if ((fp = fopen(filename, "r")) != NULL)
    {
      printf("ERROR: %s already exists.\n", filename);
      fclose(fp);
    }
    else
    {
      fp = fopen("competdium.txt", "r");
      while ((fscanf(fp, "%[^\n]\n%[^\n]\n%[^\n]\n%d\n\n", BP[x].battlepet, BP[x].elementalaffinity, BP[x].description, &BP[x].matchcount)) == 4)
        x++;
      fclose(fp);
      printf("\ntest: %d\n", x);

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

      for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            okflag = 0;
            do {
              printf("[%d][%d]: ", i, j);
              scanf("%s", selection);
    
              found = 0; 
              for (y = 0; y < x; y++) 
              {
                if (strcmp(selection, BP[y].battlepet) == 0)
                  {
                    strcpy(Board[i][j], selection);
                    okflag++;
                    found++;
                  }
              }
    
              if (!found) 
                printf("Incorrect input. Try again.\n");
            } while (!okflag); 
        }
      }
    
    // print selection to the player's saved_roster file
    fp = fopen(filename, "w");
    for (i=0; i<3; i++)
    {
      for (j=0; j<3; j++)
      {
        fprintf(fp, "%s\n", Board[i][j]);
      }
    }
    fclose(fp);
    
    printf("\n");
    displayBoard(Board);
  }
}


/**
 * Main function executed when the player selects 'ComPetDium'
 */
void selectComPetDium()
{
    struct BattlePet BP[MAX_BATTLEPETS];
    int competdiuminput;

    printf("\n -- ComPetDium --\n");

    displayComPetDiumOptions();
    // populateBattlePetList(Initial); //this should come from a file initially
    printf("\n>> ");
    scanf("%d", &competdiuminput);

    switch(competdiuminput)
    {
        case 1: viewBattlePets(BP); break;

        case 2: addBattlePet(BP); break;

        case 3: editBattlePet(BP); break;

        case 4: deleteBattlePet(BP); break;

        case 5: saveRoster(BP); break;

        default: printf("Incorrect input. Try again.\n");
    }
    printf("\n");

}
