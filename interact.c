#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "Pokemon.h"


/*  this function loads up new data from a file given by the user [during the program is running] */
void LoadNewFile(Pokemon database[], int *amountofPokemons){
    char buff[1024] = {'\0'};
    FILE *fp2;
    char bu[128];
    printf("Please enter the Name of the File:\n");
    scanf("%s", bu);
    char *filename = (char *)malloc(strlen(bu) + 1);
    strcpy(filename, bu);
    fp2 = fopen(filename, "r");
    loadData(fp2, buff, database, amountofPokemons);
    fclose(fp2);
}

/*  print pokemons of a specific tpye to a file */
void ListPokemonsTypeBased(Pokemon database[], int amountofPokemons){
    printf("Please enter a type:\n");
    Pokemon filtered[1024] = {'\0'};
    char bu[128];
    scanf("%s", bu);
    char *type = (char *)malloc(strlen(bu) + 1);
    strcpy(type, bu);
    int curr = filterList(database, type, amountofPokemons, filtered);
    DisplayPokemonList(filtered, curr);
}

/*  export pokemons of a specific tpye to a file */
void ExportPokemonsTypeBased(Pokemon database[], int amountofPokemons){
    printf("Please enter a type:\n");
    Pokemon filtered[1024] = {'\0'};
    char bu[128];
    scanf("%s", bu);
    char *type = (char *)malloc(strlen(bu) + 1);
    strcpy(type, bu);
    int curr = filterList(database, type, amountofPokemons, filtered);
    writeToFile(filtered, curr, type);
}


/*  Ths function prints the pokemons that are inside trainers struct [with ID]  */
void ListTrainersPokemons(Pokemon *database, int amountofPokemons){
    printf("|ID|number|name|type1|type2\n");
    for (int i = 0; i < amountofPokemons; i++)
    {
        if (database[i].type2 != NULL){
        printf("%d %s %s %s %s\n", i, database[i].number, database[i].name, database[i].type1, database[i].type2);
        }else{
        printf("%d %s %s %s\n", i, database[i].number, database[i].name, database[i].type1);
        }
    }
    
}

// /* [Trainer] change the name of the trainer */
void ChangeName(Trainer *player){
    
    char fname[1024];
    char lname[1024];
    printf("Please enter your new name:\n");

    scanf("%s %s", fname, lname);
    player->firstName = (char *)malloc(strlen(fname) + 1);
    player->lastName = (char *)malloc(strlen(lname) + 1);
    strcpy(player->firstName, fname);
    strcpy(player->lastName, lname);
}


/*  Ths function displays the menu  */
void displayMenu(Trainer *t){
    printf("\t[Player]: %s   \t|\t Press 0 to exit\n\n", t->firstName);
    printf("1 - Change Name\t\t\t\t6 - Catch Pokemon\n");
    printf("2 - Load Pokemons From File\t\t7 - Swap Pokemon From Bank\n");
    printf("3 - Print Pokemons (Type Based)\t\t8 - Free Pokemon\n");
    printf("4 - Export All Pokemons (Type Based) \t9 - List Pokemons in your Possession \n");
    printf("5 - Export Pokemons (A-Z Sorted)\t10 - List your Pokemons (from bank)\n");
}