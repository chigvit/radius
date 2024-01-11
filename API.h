//
// Created by Asus on 10.01.2024.
//

#ifndef RADIUS_API_H
#define RADIUS_API_H

class API {
public:
    // select cities by coordinate
    static std::map<double, std::shared_ptr< Data>>  getSitiesByCoordinate(CoordinateData coordinateData, uint8_t distance,
                                                                    const std::shared_ptr<DestinationManager> &destinationManager )
    {
        return  destinationManager->findDestinationsInRadius(coordinateData, distance);
    }

    // select cities by city name
    static std::map<double, std::shared_ptr< Data>>  getSitiesByName(std::string && name, uint8_t distance,
                                              const std::shared_ptr<DestinationManager> &destinationManager )
    {
        std::map<double, std::shared_ptr< Data>> vCity;
        // TODO
        return vCity;
    }

    void getAllDataFromManager(DestinationManager& manager) {
       // std::vector<std::shared_ptr<Data>> dataList = manager.getAllData();
    }

};
#endif //RADIUS_API_H
