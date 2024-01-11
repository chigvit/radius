#include <iostream>
#include "Loader.h"
#include <string>
#include <memory>
#include "destination_manager.h"
#include "API.h"

int main() {

    // create loader from the file
    std::shared_ptr<Loader> spFileLoader  = std::make_shared<FileLoader>("destinations.csv");
    // create data storage cache
    std::map<std::string, std::shared_ptr<Data>> citiesCache;
    // load all data from file into the cache
    citiesCache = spFileLoader->loadData();
    // create destination manager and inited by cache
    std::shared_ptr<DestinationManager> destinationManager = std::make_shared<DestinationManager>(citiesCache);

    //   std::map<std::string, std::shared_ptr<Data>> vCities;
    auto vCities = API::getSitiesByCoordinate(CoordinateData(45.7123985290527, 9.53472995758056), 10, destinationManager);


    // print selected data
    for(const auto & a :  vCities) {
        std::cout << a.second->getName() <<"\n"
        <<" latitude : "<<a.second->getCoordinates().first <<" longitude : "<< a.second->getCoordinates().second
        << "  Distance : " << a.first << std::endl;
    }
    std::cout<<" Total : "<<vCities.size()<<" Cities"<<std::endl;

    return 0;
}

/*
 * the some we can do for database
 *     spFileLoader  = std::make_shared<DatabaseLoader>("database_db");

 */
