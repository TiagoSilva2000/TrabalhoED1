#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "../include/CountriesList.h"
#include "../include/miscfunctions.h"
#include "../include/DecisionTree.h"

void $dev_printCountries (Country* countriesList)
{
    while (countriesList)
    {
        printf("%i %s = ", countriesList->id, countriesList->name);
        countriesList = countriesList->next;
    }
    printf("\n\n");
}

void printCountriesList (Country* countriesList)
{
    int i = 1;

    while (countriesList)
    {
        printf("%i - %s ", i++, countriesList->name);
        if (i%3 == 0)
            printf("\n");
        countriesList = countriesList->next;
    }
    printf("\n\n");
}

Client** iniClientList (void)
{
    Client** newClientList = (Client**) malloc(sizeof(Client*));
    if(!newClientList) exit(1);
    *newClientList = NULL;

    return newClientList;
}

Country** initCountriesList (void)
{
    Country** newCountries = (Country**) malloc(sizeof(Country*));
    checkPointerIntegrity(newCountries);
    *newCountries = NULL;

    return newCountries;
}

TravelClass** initTravelClasses (void)
{
    TravelClass** travelClasses = (TravelClass**) malloc(sizeof(TravelClass*));
    if(!travelClasses) exit(1);
    *travelClasses = NULL;


    TravelClass* premiumClass = (TravelClass*) malloc(sizeof(TravelClass));
    checkPointerIntegrity(premiumClass);
    premiumClass->decidedClients = iniClientList();
    premiumClass->undecidedClients = iniClientList();


    TravelClass* basicClass = (TravelClass*) malloc(sizeof(TravelClass));
    checkPointerIntegrity(basicClass);
    basicClass->isPremium = false;
    basicClass->decidedClients = iniClientList();
    basicClass->undecidedClients = iniClientList();    
    basicClass->next = NULL;


    premiumClass->next = basicClass;
    *travelClasses = premiumClass;

    return travelClasses;
}


void pushCountry (Country** countriesList, char* tempName, uint8_t* countryID, Country** listEnd)
{
    Country* newCountry = (Country*) malloc(sizeof(Country));
    checkPointerIntegrity(newCountry);
    newCountry->id = *countryID;
    strcpy(newCountry->name, tempName);
    newCountry->next = NULL;
    newCountry->travelClass = initTravelClasses (); 


    if (!(*countriesList))
        *countriesList = newCountry;
    else
        (*listEnd)->next = newCountry;
    
    *listEnd = newCountry;
}



bool pushClient (Client** clientsList, Client** newClient)
{   
    if(!clientsList) return false;

    if (*clientsList == NULL)
        *clientsList = *newClient;
    else
    {
        Client* clientWalker = *clientsList;
        while (clientWalker->next)
            clientWalker = clientWalker->next;
        clientWalker->next = *newClient;
    }

    return true;
}

bool addClient (Country** countriesList, Client** newClient, uint8_t decided, uint8_t premium, uint8_t countryId)
{
    if (!countriesList) return false;

    Country* cWalker = *countriesList;
    TravelClass* tWalker;
    Client* cliWalker;

    while (cWalker != NULL && cWalker->id != countryId)
        cWalker = cWalker->next;
    if (!cWalker) return false;
    
    tWalker = premium ? *(cWalker->travelClass) : (*(cWalker->travelClass))->next;

    if (!decided)
    {
        pushClient(tWalker->undecidedClients, newClient);
        (tWalker->undecidedQnt)++;
    }
    else
    {
        pushClient(tWalker->decidedClients, newClient);
        (tWalker->decidedQnt)++;
    }
    
    return true;   
}

void loadClientsTo (Country** countriesList)
{   
    FILE* clientsFile = fopen("../files/clients.txt", "r");
    char tempName[80];
    unsigned long long int tempID;
    uint8_t tempCountryId, tempClass, tempDecision;
    char aux[80];


    check_file_integrity(clientsFile);
    rewind(clientsFile);
    // while (fscanf(clientsFile, "%llu;%i;%i;%i;%[^\n]", &tempidCode, &countryId, &tempDecision, &tempClass, tempName) > 0);
    while (fgets(aux, 80, clientsFile) != NULL)
    {
        sscanf(aux, "%llu;%" SCNu8 ";%" SCNu8 ";%" SCNu8 ";%[^\n]", &tempID, &tempCountryId, &tempDecision, &tempClass, tempName);
        
        printf("%llu;%" PRIu8 ";%" PRIu8 ";%" PRIu8 ";%s\n", tempID, tempCountryId, tempDecision, tempClass, tempName);
        Client* newClient = (Client*) malloc(sizeof(Client));
        checkPointerIntegrity(newClient);
        newClient->next = NULL;
        strcpy(newClient->name, tempName);
        newClient->idCode = tempID;
        // printf("olah\n");
        if (!(addClient(countriesList, &newClient, tempDecision, tempClass, tempCountryId)))
            printf("ERROR ERROR ERROR ERROR ERROR\n");
    }
    
    printf("passed!\n");

    fclose(clientsFile);
}



Country** buildCountriesList (void)
{   
    Country** countriesList;
    FILE* countriesFile;
    Country* eend;
    uint8_t countryID;
    char tempName[80];


    countriesFile = fopen("../files/countries.txt", "r");
    check_file_integrity (countriesFile);
    countriesList = initCountriesList();
    eend = *countriesList;

    // rewind(countriesFile);    
    while (fscanf(countriesFile, "%" SCNu8 ";%[^\n]s", &countryID, tempName) > 0)
    {
        printf("%" PRIu8 " %s\n", countryID, tempName);
        pushCountry(countriesList, tempName, &countryID, &eend);
    }
    loadClientsTo(countriesList);

    printf("one more time\n");
    fclose(countriesFile);
    printf("one more timeeee\n");
    return countriesList;
}