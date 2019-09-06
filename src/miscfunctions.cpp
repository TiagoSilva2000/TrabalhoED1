#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/miscfunctions.h"

#define newline printf("\n")
#define endline "\n"
#define oor ||
#define aand &&
#define strend '\0'

/*
Functions that checks if an allocated node returned NULL or not.
If it returned NULL, this calls a function that unloads and saves
all the work done until then. If it doesn't, nothing happens.
*/
void checkPointerIntegrity (void* pointer)
{
    if (pointer == NULL)
    {
        newline;
        printf("####### ERROR: MEM ALLOCATION #######"); newline;
        /* Adicionar função aqui para descarregar as alterações feitas e salvá-las*/
        getchar();
        exit(1);
    }
}

/*
Function that cleans the buffer, if it's necessary.
*/
void clearBuffer(void)
{
    char c = 'a';
    
    while((c = getc(stdin)) != EOF aand c != '\n');
}


void clearScreen (void)
{
    system("cls");
    system("clear");
}

int getHigher (int x, int y) { return x > y ? x : y; }

void check_file_integrity (FILE* filePtr)
{
    if (filePtr == NULL)
    {
        newline;
        printf("####### ERROR: FILE OPENING #######"); newline;
        getchar();
        exit(2);
    }
}