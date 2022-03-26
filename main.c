#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pokemon.h"



/*  Ths function loads data from the file given by the user at the start of the program aka 'Pokemons.txt'  */
void loadData(FILE *fp, char *buff, Pokemon *location, int *len){
    while(fscanf(fp, "%s", buff) != EOF){
        location[(*len)] = *((Pokemon *)malloc(sizeof(Pokemon)));
        location[(*len)] = *(getPokemonData(fp, buff));
        ++(*len);
    }
}

/* given an array(Pokemon Database) and a filter i.e 'fire' this
function will return a nums of elements in filtered  */
int filterList(Pokemon database[], char *type, int size, Pokemon filteredDB[]){
    int curr = 0;
    for (int i = 0; i < size; i++)
    {
        if (strcmp(database[i].type1, type) == 0 || ((database[i].type2 == NULL) ? 0 : strcmp(database[i].type2, type) == 0))
        {
            filteredDB[curr] = *((Pokemon *)malloc(sizeof(Pokemon)));
            filteredDB[curr] = database[i];
            ++curr;
        }
    }
    return curr;
}

/*  given an array Ths function saves the array in a file   */
void writeToFile(Pokemon data[], int len, char *fname){
    FILE *fptr;
    fptr = fopen(strcat(fname, ".txt") ,"w");
    char none[2] = " ";

    for (int i = 0; i < len; i++)
    {
        fprintf(fptr, "%s %s %s %s\n", data[i].number, data[i].name, data[i].type1, (data[i].type2 != NULL ? data[i].type2 : none));
    }
    fclose(fptr);
}

/*  Ths function adds a pokemon to the trainers bank  */
void sendToBank(Pokemon *bank, Pokemon *item, int *len){
    int Newlen = *len + 1;
    int lenn = *len;
    *(bank+lenn) = *((Pokemon *)malloc(sizeof(Pokemon)));
    *(bank+lenn) = *item;
    Pokemon *cr = (bank+lenn);
    printf("Your inventory is full %s sent to the bank!' \n", cr->name);
    ++(*len);
}

/*  Ths function adds a pokemon to the currently held trainners pokemons  */
void addToCurrent(Pokemon *list, int *len, Pokemon *item){
    int cur = (*len);
    *(list+cur) = *((Pokemon *)malloc(sizeof(Pokemon)));
    *(list+cur) = *item;
    Pokemon *cr = (list+cur);
    printf("%s is now traveling with you!\n", cr->name);
    ++(*len);
}




int main(int argc, char **argv)
{

    system("cls");
    /* Intialize Program Vars */
    int amountofPokemons = 0;
    int amountofPokemonInBank = 0;
    int amountofCurrentlyHeld= 0;
    FILE *fp;
    Trainer trainerP;
    trainerP.pokemonsInBank = (Pokemon*)malloc(sizeof(Pokemon));
    Pokemon database[1024] = {'\0'};
    char buff[1024] = {'\0'};
    fp = fopen(argv[1], "r");
    loadData(fp, buff, database, &amountofPokemons);

    /* Get User Data */
    char fbuff[128], lbuff[128] = {'\0'};
    printf("Please enter your name:\n");
    scanf("%s %s", fbuff, lbuff);
    trainerP.firstName = (char *)malloc(strlen(fbuff) + 1);
    trainerP.lastName = (char *)malloc(strlen(lbuff) + 1);
    strcpy(trainerP.firstName, fbuff);
    strcpy(trainerP.lastName, fbuff);

    int f;
    char coloum[32] = {'\0'};
    int send, take;
    Pokemon *pok = (Pokemon*)malloc(sizeof(Pokemon));

    /* Run Program */
    while (1)
    {
        int selection;
        displayMenu(trainerP);
        printf("\tSelection -> ");
        scanf("%d", &selection);

        switch (selection)
        {
        case 1:
            ChangeName(&trainerP);
            break;
        case 2:
            LoadNewFile(database, &amountofPokemons);
            break;
        case 3:
            ListPokemonsTypeBased(database, amountofPokemons);
            break;
        case 4:
            ExportPokemonsTypeBased(database, amountofPokemons);
            break;
        case 5:
            printf("Please enter by which coloum you wish to order:\n");
            scanf("%s",coloum);
            strcmp("name", coloum) == 0 ? sortPokemonsByName(database, amountofPokemons) : sortPokemonsByType(database, amountofPokemons);
            break;
        case 6: // Catch Pokemon
            pok = GetPokemonFromUser(database, amountofPokemons);
            if (pok != NULL){
                if (amountofCurrentlyHeld < 6){
                    addToCurrent(trainerP.pokemonsHeldByTheTrainer, &amountofCurrentlyHeld, pok);
                }else{
                    ((Pokemon*)realloc(trainerP.pokemonsInBank, (sizeof(Pokemon)*(amountofPokemonInBank+1))));
                    sendToBank(trainerP.pokemonsInBank, pok, &amountofPokemonInBank);   
                }
            }
            break;
        case 7:
            printf("Please enter by ID of the pokemon you want to swap:\n");
            scanf("%d %d", &send, &take);
            printf("'%s is now your companion and %s sent to bank for safe keeping\n", (trainerP.pokemonsInBank+take)->name, (trainerP.pokemonsHeldByTheTrainer+send)->name);
            Pokemon *temp = (Pokemon*)malloc(sizeof((trainerP.pokemonsInBank+take)));
            *temp = *(trainerP.pokemonsInBank+take);
            *(trainerP.pokemonsInBank+take) = *(trainerP.pokemonsHeldByTheTrainer+send);
            *(trainerP.pokemonsHeldByTheTrainer+send) = *temp;
            break;
        case 8:
            
            printf("Please enter ID of the pokemon you want to free!\n");
            printf("-> ");
            scanf("%d", &f);
            if ((trainerP.pokemonsHeldByTheTrainer+f) != NULL){
                printf("You sent %s free :(\n", (trainerP.pokemonsHeldByTheTrainer+f)->name);
                trainerP.pokemonsHeldByTheTrainer[f] = trainerP.pokemonsHeldByTheTrainer[amountofCurrentlyHeld-1];
                trainerP.pokemonsHeldByTheTrainer[amountofCurrentlyHeld-1].name = NULL;
                trainerP.pokemonsHeldByTheTrainer[amountofCurrentlyHeld-1].type1 = NULL;
                trainerP.pokemonsHeldByTheTrainer[amountofCurrentlyHeld-1].type2 = NULL;
                trainerP.pokemonsHeldByTheTrainer[amountofCurrentlyHeld-1].number = NULL;
                amountofCurrentlyHeld -= 1;
            }
            break;
        case 9:
            ListTrainersPokemons(trainerP.pokemonsHeldByTheTrainer, amountofCurrentlyHeld);
            break;
        case 10:
            ListTrainersPokemons(trainerP.pokemonsInBank, amountofPokemonInBank);
            break;
        case 0:
            return 0;
            break;
        
      
        }
    }
}

