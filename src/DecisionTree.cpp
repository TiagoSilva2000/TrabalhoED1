#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <inttypes.h>
#include "../include/miscfunctions.h"
#include "../include/DecisionTree.h"
#include "../include/CountriesList.h"


void printTree (DecisionTree* decisionTree)
{
    if (!decisionTree)
        return;
    printf("%i -> %s\n", decisionTree->index, decisionTree->text);
    printTree(decisionTree->right);
    printTree(decisionTree->left);
}


DecisionTree* addNode (DecisionTree* decisionTree, int auxIndex, char* auxText)
{
    if (!decisionTree)
    {
        DecisionTree* newNode = (DecisionTree*) malloc(sizeof(DecisionTree));
        if(!newNode) exit (1);
        newNode->index = auxIndex;
        strcpy(newNode->text, auxText);

        return newNode;
    }

    if (auxIndex > decisionTree->index)
        decisionTree->right = addNode(decisionTree->right, auxIndex, auxText);

    else if (auxIndex < decisionTree->index)
        decisionTree->left = addNode(decisionTree->left, auxIndex, auxText);

    return decisionTree;
}

DecisionTree** buildTree (void)
{
    DecisionTree** decisionTree;
    FILE *countriesFile, *questionsFile;
    uint8_t treeIndex;
    char auxText[100];

    countriesFile = fopen("../files/countries.txt", "r");
    check_file_integrity(countriesFile);
    questionsFile = fopen ("../files/questions.txt", "r");
    check_file_integrity(questionsFile);
    decisionTree = (DecisionTree**) malloc(sizeof(DecisionTree*));
    checkPointerIntegrity(decisionTree);

    rewind(countriesFile);    
    rewind(questionsFile);    
    *decisionTree = NULL;

    while (fscanf(questionsFile, "%" SCNu8 ";%[^\n]s", &treeIndex, auxText) > 0)
        *decisionTree = addNode(*decisionTree, treeIndex, auxText);

    while (fscanf(countriesFile, "%" SCNu8 ";%[^\n]s", &treeIndex, auxText) > 0)
        *decisionTree = addNode(*decisionTree, treeIndex, auxText);

    fclose(countriesFile);
    fclose(questionsFile);

    return decisionTree;
}

int decidingCountry (DecisionTree* decisionTree)
{   
    if (!decisionTree->right && !decisionTree->left)
    {
        printf("Yaay! Voceh vai viajar para %s!\n", decisionTree->text);
        return decisionTree->index;
    }
    printf("%s[y/n]\n", decisionTree->text);
    
    char answer;
    do
    {
        scanf("%c", &answer); setbuf(stdin, 0);
        answer = tolower(answer);   
    } while (answer != 'y' && answer != 'n');
    
    if (answer == 'y')
        return decidingCountry(decisionTree->right);
 
    return decidingCountry(decisionTree->left);
}

void registerTravel (Country** countriesList, uint8_t* countryID, FILE* clientsFile, Client* tempClient, bool decided)
{   
    char select;
    int premiumTravel;
    clientsFile = fopen("../files/clients.txt", "a+");
    Client* newClient = (Client*) malloc(sizeof(Client));
    checkPointerIntegrity(newClient);
    newClient->next = NULL;
    newClient->idCode = tempClient->idCode;
    strcpy(newClient->name, tempClient->name);

    check_file_integrity(clientsFile);
    clearBuffer();
    do 
    {
        printf("Voceh deseja uma viagem simples ou premium? [0 - simples/1 - premium]\n");
        scanf("%c", &select); setbuf(stdin, 0);
    } while (select != '1' && select != '0');
    
    premiumTravel = (int) select - '0';

    if (addClient(countriesList, &newClient, decided, premiumTravel, *countryID))
    {
        fprintf(clientsFile, "%llu;%" PRIu8 ";%" PRIu8 ";%i;%s\n", tempClient->idCode, *countryID, decided, (int)premiumTravel, tempClient->name);
        printf("Cliente perfeitamente adicionado\n");
        getc(stdin);
        setbuf(stdin, 0);
    }
    else
        printf("Erro no cadastro do cliente!\n");

    fclose(clientsFile);
}

void travelling (DecisionTree** decisionTree, Country** countriesList)
{   
    Client currentClient;
    uint8_t tempCountryID;
    bool decided = true;
    FILE* clientsFile;

    printf("Insira seu cpf: "); scanf("%llu", &currentClient.idCode); 
    clearBuffer();

    printf("Insira seu nome, por favor: "); scanf("%[^\n]", currentClient.name); 
    clearBuffer();
    
    clearScreen();
    printf("Bem, vamos decidir seu pais agora!\n");
    
    printCountriesList (*countriesList);
    printf("Se quiser ir a um dos paises acima, digite seu numero correspondente.\nSe nao tiver certeza, digite qualquer outro numero: ");
    scanf("%" SCNu8, &tempCountryID);

    if (tempCountryID < 1 || tempCountryID > 16)
    {
        tempCountryID = decidingCountry(*decisionTree);
        decided = false;
    }
    else
        tempCountryID = ((tempCountryID-1) * 2) + 1;

    registerTravel (countriesList, &tempCountryID, clientsFile, &currentClient, decided);
}