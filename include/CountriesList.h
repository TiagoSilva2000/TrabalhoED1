#ifndef COUNTRIESLIST_H_INCLUDED
#define COUNTRIESLIST_H_INCLUDED
#include <inttypes.h>

    typedef struct country Country;
    typedef struct travelClass TravelClass;
    typedef struct client Client;

    struct country
    {
        char name[50];
        uint8_t id;
        Country *next;
        TravelClass** travelClass;
    };
    
    struct travelClass
    {
        bool isPremium = true; 
        uint32_t decidedQnt = 0, undecidedQnt = 0;
        TravelClass *next;
        Client **decidedClients, **undecidedClients;
    };

    struct client
    {
        char name[80];
        unsigned long long int idCode;
        Client *next;
    };

    Country** buildCountriesList (void);
    bool addClient (Country** countriesList, Client** newClient, uint8_t decided, uint8_t premium, uint8_t countryId);
    void printCountriesList (Country* countriesList);

#endif // COUNTRIESLIST_H_INCLUDED
