#ifndef __POKEMON_H__
#define __POKEMON_H__

#include <stdio.h>
typedef struct Pokemon
{
    char* number; //It starts with #
    char* name;
    char* type1;
    char* type2; //Can be NULL for some
}Pokemon;

typedef struct Trainer
{
    char* firstName;
    char* lastName;
    Pokemon* pokemonsInBank; //The number of Pokémons the trainer have
    Pokemon pokemonsHeldByTheTrainer[6]; //The Pokémons currently held by the trainer
}Trainer;


Pokemon *getPokemonData(FILE *fp, char *buff);
Pokemon *searchPokemon(Pokemon database[], int len, char *name);
void handleType2(FILE *fp, char *BUFFER, Pokemon *p);
int filterList(Pokemon database[], char *type, int size, Pokemon filteredDB[]);
void loadData(FILE *fp, char *buff, Pokemon *location, int *len);
void writeToFile(Pokemon data[], int len, char *fname);
Pokemon *GetPokemonFromUser(Pokemon database[], int amountOfPokemons);
void displayPokemon(Pokemon *p);

// Interactivity
void ChangeName(Trainer *player);
void DisplayPokemonList(Pokemon list[], int size);
void displayMenu();
void LoadNewFile(Pokemon database[], int *amountofPokemons);
void ListPokemonsTypeBased(Pokemon database[], int amountofPokemons);
void CatchPokemon(Pokemon database[], int amountofPokemons, Trainer *trainer, int *CurrentlyOwned, int *inTheBank);
void ExportPokemonsTypeBased(Pokemon database[], int amountofPokemons);
void ListTrainersPokemons(Pokemon database[], int amountofPokemons);

// Sort
void sortPokemonsByType(Pokemon database[], int amountOfPokemons);
void sortPokemonsByName(Pokemon Database[], int amountOfPokemons);
void swapPokemon(Pokemon *dest, Pokemon *source);

#endif