#include <iostream>
#include "Loader.hpp"
#include <string>
#include <memory>
#include "DestinationManager.hpp"
#include "API.h"

void printResult(std::map<double, std::shared_ptr< Data>> mpCities){

    for(const auto & a :  mpCities) {
        std::cout << a.second->getName() <<"\n"
                  <<" latitude : "<<a.second->getCoordinateData().latitude <<" longitude : "<< a.second->getCoordinateData().longitude
                  << "  Distance : " << a.first << std::endl;
    }
    std::cout<<" Total : "<<mpCities.size()<<" Cities"<<std::endl;

}

int checkIncomingParams(int argc, char* argv[])
{
//    if (argc < 2) {
//        std::cerr << "Usage: " << argv[0] << " <city_name> OR " << argv[0] << " <latitude> <longitude>" << std::endl;
//        return 1;
//    }

    std::string cityName;
    double latitude, longitude;

    // Check if the user provided coordinates or a city name
    if (argc == 2) {
        std::cout<<"argc == 2";
        cityName = argv[1];
    } else if (argc == 3) {
        std::cout<<"argc == 3\n";
        try {
            latitude = std::stod(argv[1]);
            longitude = std::stod(argv[2]);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid coordinates provided." << std::endl;
            return 1;
        }
    } else {
        std::cout<<"else";
        std::cerr << "Invalid number of arguments." << std::endl;
        return 1;
    }


    return 0;
}

int main(int argc, char* argv[]) {

    //int ret = checkIncomingParams(argc, argv);
//    if(ret)
//    {
//        std::cerr<<"Invalid args"<<std::endl;
//        return ret;
//    }

    // create loader from the file
    std::shared_ptr<Loader> spFileLoader  = std::make_shared<FileLoader>("destinations.csv");

    // create data storage cache
    std::map<std::string, std::shared_ptr<Data>> citiesCache;

    // load all data from file into the cache
    citiesCache = spFileLoader->loadData();


    // create destination manager and inited by cache
    std::shared_ptr<DestinationManager> destinationManager = std::make_shared<DestinationManager>(citiesCache);

    //   std::map<std::string, std::shared_ptr<Data>> ;
    std::map<double, std::shared_ptr< Data>> mpCities;
    //  f
    mpCities = API::getSitiesByCoordinate(CoordinateData(45.7123985290527, 9.53472995758056),
                                         50, destinationManager);
    printResult(mpCities);

    mpCities = API::getSitiesByName("Merate", 20.0, destinationManager);
    printResult(mpCities);
    // print selected data

    return 0;
}


