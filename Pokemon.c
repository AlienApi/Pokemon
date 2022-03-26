#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "Pokemon.h"


// /* this function handles the parsing of type 2 
// such that in cases in which it doesnt exist the p is set to NULL
// */
void handleType2(FILE *fp, char *BUFFER, Pokemon *p){
    fscanf(fp, "%s", BUFFER);
        if (BUFFER[0] == '#') {
            p->type2 = NULL;
            fseek(fp, -(strlen(BUFFER)), SEEK_CUR);
        }else if (strcmp(BUFFER, p->type1) == 0)
        {
            p->type2 = NULL;
        }else{
            p->type2 = (char *)malloc(strlen(BUFFER) + 1);
            strcpy(p->type2, BUFFER);
        }
}



/* this function scans one line in the file and returns the pokemon as an object */
Pokemon *getPokemonData(FILE *fp, char *buff){
    Pokemon *curr = (Pokemon *)malloc(sizeof(Pokemon));
        
    curr->number = (char *)malloc(strlen(buff) + 1);
    strcpy(curr->number, buff);
        
    fscanf(fp, "%s", buff);
    curr->name = (char *)malloc(strlen(buff) + 1);
    strcpy(curr->name, buff);
        

    fscanf(fp, "%s", buff);
    curr->type1 = (char *)malloc(strlen(buff) + 1);
    strcpy(curr->type1, buff);
        
    handleType2(fp, buff, curr);
    return curr;
}

/* searches for pokemon struct given a database if doesnt exist return null*/
Pokemon *searchPokemon(Pokemon database[], int len, char *name){
    for (int i = 0; i < len; i++)
    {
        if (strcmp(database[i].name, name) == 0)
        {
            return (database+i);
        }
    }
    printf("Pokemon doesnt exist!\n");
    return NULL;
}

/*  Ths function sorts an array A-z by name  */
void sortPokemonsByName(Pokemon database[], int amountOfPokemons){
    int i,j;
    for(i=0;i<amountOfPokemons;i++){
        for(j=i+1;j< amountOfPokemons;j++){
            if( strcmp(database[i].name, database[j].name ) > 0 ){
            Pokemon *temp = (Pokemon*)malloc(sizeof(database[i]));
            *temp = database[j];
            database[j] = database[i];
            database[i] = *temp;
            free(temp);
            }
        }
    }
    char name[100] = "NameSorted";
    writeToFile(database, amountOfPokemons, name);
}

/*  Ths function sorts an array A-z by type  */
void sortPokemonsByType(Pokemon database[], int amountOfPokemons){
    int i,j;
    for(i=0;i<amountOfPokemons;i++){
        for(j=i+1;j< amountOfPokemons;j++){
            if( strcmp(database[i].type1, database[j].type1 ) > 0 ){
            Pokemon *temp = (Pokemon*)malloc(sizeof(database[i]));
            *temp = database[j];
            database[j] = database[i];
            database[i] = *temp;
            free(temp);
            }
        }
    }
    char name[100] = "TypeSorted";
    writeToFile(database, amountOfPokemons, name);
}

// /* This function displays a a pokemons data given its pointer */
void displayPokemon(Pokemon *p){
    if (p->type2 != NULL)
    {
        printf("%s %s %s %s\n", p->number, p->name, p->type1, p->type2);
        
    }else{
        printf("%s %s %s\n", p->number, p->name, p->type1);
    }
}
/* This function displays a list Pokemons given an array */
void DisplayPokemonList(Pokemon list[], int size){
    for (int i = 0; i < size; i++){
        Pokemon *temp = (list+i);
        displayPokemon(temp);
    }
}

/*  Ths function gets a pokemon name from user and returns its struct  */
Pokemon *GetPokemonFromUser(Pokemon database[], int amountOfPokemons){
    printf("Please enter a name:\n");
    char bu[128];
    scanf("%s", bu);
    char *name = (char *)malloc(strlen(bu) + 1);
    strcpy(name, bu);
    Pokemon *pok = (Pokemon *)malloc(sizeof(Pokemon));
    pok = searchPokemon(database, amountOfPokemons, name);
    return pok;
}