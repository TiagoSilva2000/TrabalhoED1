#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include "CountriesList.h"

    bool getDecidedCountries (Country** countriesList);
    bool getUndecidedCountries (Country** countriesList);
    bool getVisitedCountries (Country** countriesList);
    bool getUnvisitedCountries (Country** countriesList);
    bool mostPopularCountry (Country** countriesList);
    bool getClientsFromCountry (Country** countriesList);
    char showClients (Country** countriesList);
    void $dev_printAllClients (Country* countriesList);

#endif // FUNCTIONS_H_INCLUDED
