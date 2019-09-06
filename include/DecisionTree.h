#ifndef DECISIONTREE_H_INCLUDED
#define DECISIONTREE_H_INCLUDED
#include "stdint.h"
#include "CountriesList.h"

    typedef struct decisionTree DecisionTree;
    struct decisionTree
    {
        uint8_t index;
        char text[100];
        DecisionTree *right, *left;
    
    };
    DecisionTree** buildTree (void);
    void travelling (DecisionTree** decisionTree, Country** countriesList);
    void printTree (DecisionTree* decisionTree);
    void destroyTree (DecisionTree** decisionTree);
    /*
    DecisionTree* addNode (DecisionTree* decisionTree, DecisionTree* newDNode);
    void registerTravel (int* countryID, Client* tempClient, Country** countriesList, bool isDecided);
    int decidingCountry (DecisionTree* decisionTree);
    */
    
    
    
#endif // DECISIONTREE_H_INCLUDED
