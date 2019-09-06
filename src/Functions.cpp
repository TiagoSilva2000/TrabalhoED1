#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/Functions.h"
#include "../include/DecisionTree.h"
#include "../include/CountriesList.h"

void $dev_printClientsFromAll (Client* clientList)
{
    if(!clientList)
    {
        printf("\n");
        return;
    }
    while (clientList)
    {
        printf("    %llu -  %s\n", clientList->idCode, clientList->name);
        clientList = clientList->next;
    }
    printf("\n\n");
}

void $dev_printAllClients (Country* countriesList)
{
    Client* clienWalker;

    while (countriesList)
    {   
        printf("PAIS-%" PRIu8 ": %s", countriesList->id, countriesList->name);
        $dev_printClientsFromAll ( *((*(countriesList->travelClass))->decidedClients) );
        $dev_printClientsFromAll ( *((*(countriesList->travelClass))->undecidedClients) );
        $dev_printClientsFromAll ( *((*(countriesList->travelClass))->next->decidedClients) );
        $dev_printClientsFromAll ( *((*(countriesList->travelClass))->next->undecidedClients) );

        countriesList = countriesList->next;
    }
    printf("\n\n==============\n\n");
}


void printClients (Client** clientList)
{
    if(!clientList) return;
    Client* cliWalker = *clientList;

    printf("teste!\n");
    while (cliWalker)
    {
        printf("%s - %llu\n", cliWalker->name, cliWalker->idCode);
        cliWalker = cliWalker->next;
    }
    printf("\n\n");
}

bool getVisitedCountries (Country** countriesList)
{
    if (!countriesList) return false;
    if (!(*countriesList)) return false;

    Country* cWalker = *countriesList;
    TravelClass* tWalker;

    cWalker = *countriesList;
    printf("\nPaises visitados no geral:\n");
    while (cWalker)
    {   
        tWalker = (*cWalker->travelClass);
        if (tWalker->undecidedQnt + tWalker->next->undecidedQnt + 
            tWalker->decidedQnt + tWalker->next->decidedQnt > 0)
            printf("%s\n", cWalker->name);
        
        cWalker = cWalker->next;
    }

    return true;
}

bool getUnvisitedCountries (Country** countriesList)
{
    Country* cWalker = *countriesList;
    TravelClass* tWalker;

    cWalker = *countriesList;
    printf("\nPaises nao visitados:\n");
    while (cWalker)
    {   
        tWalker = (*cWalker->travelClass);
        if (tWalker->undecidedQnt + tWalker->next->undecidedQnt + 
            tWalker->decidedQnt + tWalker->next->decidedQnt == 0)
            printf("%s\n", cWalker->name);
        
        cWalker = cWalker->next;
    }
    return true;
}


void printMessage (Country* country, char* messageType)
{
    printf("Pais mais visitado por %s: %s\n", messageType, 
            country == NULL ? "Nenhum pais visitado ainda" : country->name);
}

bool mostPopularCountry (Country** countriesList)
{
    Country* cWalker = *countriesList;
    TravelClass* tWalker;
    unsigned int undHigher = 0, decHigher = 0, tempQnt;
    Country* decCountryHolder = NULL, *undCountryHolder = NULL;

    while (cWalker)
    {
        tWalker = *(cWalker->travelClass);
        
        tempQnt = tWalker->decidedQnt + tWalker->next->decidedQnt;
        if (tempQnt > decHigher)
        {
            decCountryHolder = cWalker;
            decHigher = tempQnt;
        }

        tempQnt = tWalker->undecidedQnt + tWalker->next->undecidedQnt;
        if (tempQnt > undHigher)
        {
            undCountryHolder = cWalker;
            undHigher = tempQnt;
        }

        cWalker = cWalker->next;
    }

    printMessage(decCountryHolder, (char*)"pessoas decididas");
    printMessage(undCountryHolder, (char*)"pessoas indecisas");

    return true;
}

bool getClientsFromCountry (Country** countriesList)
{
    if (!countriesList) return false;
    if (!(*countriesList)) return false;

    Country* cWalker = *countriesList;
    TravelClass* tWalker;
    char tempName[80];

    printf("Indique o pais: "); scanf("%[^\n]", tempName);
    cWalker = *countriesList;
    while (cWalker && strcmp(tempName, cWalker->name) != 0)
        cWalker = cWalker->next;
    if (!cWalker) return false;

    tWalker = *(cWalker->travelClass);
    printf("clientes premium: %u\n", tWalker->decidedQnt + tWalker->undecidedQnt); 
    printf("clientes simples: %u\n", tWalker->next->decidedQnt + tWalker->next->undecidedQnt);

    getc(stdin);
    setbuf(stdin, 0);
    return true;
}


char showClients (Country** countriesList)
{
    if (!countriesList) return '1';
    if (!(*countriesList)) return '1';

    Country* cWalker = *countriesList;
    TravelClass* tWalker;
    char tempName[80];


    printf("Indique o pais: "); scanf("%[^\n]", tempName);
    while (cWalker && strcmp(tempName, cWalker->name) != 0)
        cWalker = cWalker->next;
    if (!cWalker) return '2';

    printf("pais: %s\n", cWalker->name);
    tWalker = *(cWalker->travelClass);

    printf("#### Premium e Decididas ####");
    printClients(tWalker->decidedClients);
    printf("#### Premium e Indecisas ####");
    printClients(tWalker->undecidedClients);
    
    tWalker = tWalker->next;
    printf("\n");
    printf("#### Simples e Decididas ####");
    printClients(tWalker->decidedClients);
    printf("#### Simples e Indecisas ####");
    printClients(tWalker->undecidedClients);

    getc(stdin);
    setbuf(stdin, 0);
    return '0';
}

bool getUndecidedCountries (Country** countriesList)
{   

    if (!countriesList) return false;
    if (!(*countriesList)) return false;
    
    Country* cWalker = *countriesList;
    TravelClass* tWalker;

    printf("\nPaises com pessoas indecisas:\n");
    while (cWalker)
    {   
        tWalker = (*cWalker->travelClass);
        if (tWalker->undecidedQnt + tWalker->next->undecidedQnt > 0)
            printf("%s\n", cWalker->name);
        
        cWalker = cWalker->next;
    }

    return true;
}

bool getDecidedCountries (Country** countriesList)
{
    if (!countriesList) return false;
    if (!(*countriesList)) return false;

    Country* cWalker = *countriesList;
    TravelClass* tWalker;

    printf("Paises com pessoas decididas:\n");
    while (cWalker)
    {   
        tWalker = (*cWalker->travelClass);
        if (tWalker->decidedQnt + tWalker->next->decidedQnt > 0)
            printf("%s\n", cWalker->name);

        cWalker = cWalker->next;
    }   

    return true;
}