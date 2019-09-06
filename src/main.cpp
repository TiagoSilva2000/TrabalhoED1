#include <stdio.h>
#include <stdlib.h>
#include "../include/Functions.h"
#include "../include/miscfunctions.h"
#include "../include/CountriesList.h"
#include "../include/DecisionTree.h"

void adm_interface (void)
{
    printf("0 - Cadastrar Cliente/Realizar Viagem\n");
    printf("1 - Listar Paises Visitados pelo Sistema\n");
    printf("2 - Listar Paises Visitados de forma Decidida\n");
    printf("3 - Listar Paises Visitados no Geral\n");
    printf("4 - Listar Paises Ainda Nao Visitados\n");
    printf("5 - Listar Pais Mais Visitado\n");
    printf("6 - Listar Clientes de Determinado Pais\n");
    printf("7 - Pegar Quantidade de Clientes de Determinado Pais\n");
    printf("8 - Printar Arvore de Decisao\n");
    printf("985 - Sair\n");
}

int main (void)
{
    int choice = -1;
    bool running = true;
    Country** countriesList;
    DecisionTree** decisionTree;
    FILE* clientsFile;

    // printf("surprised?\n");
    countriesList = buildCountriesList();
    
    clientsFile = fopen("../files/clients.txt", "a+");
    check_file_integrity(clientsFile);
    decisionTree = buildTree();
    while (running)
    {
        clearScreen();
        adm_interface();
        scanf("%i", &choice);
        clearBuffer();

        if (choice == 0)
            travelling(decisionTree, countriesList);
        else if (choice == 1)
            getUndecidedCountries(countriesList);
        else if (choice == 2)
            getDecidedCountries(countriesList);
        else if (choice == 3)
            getVisitedCountries(countriesList);
        else if (choice == 4)
            getUnvisitedCountries(countriesList);
        else if (choice == 5)
            mostPopularCountry(countriesList);
        else if (choice == 6)
            showClients(countriesList);
        else if (choice == 7)
            getClientsFromCountry(countriesList);
        else if (choice == 8)
            printTree(*decisionTree);
        else if (choice == 10)
            $dev_printAllClients(*countriesList);
        else if (choice == 985)
            running = false;
        printf("\n==pause==\n");
        fgetc(stdin);
    }



    return 0;
}