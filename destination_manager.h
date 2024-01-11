
#ifndef RADIUS_DESTINATION_MANAGER_H
#define RADIUS_DESTINATION_MANAGER_H
#include "Loader.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>
#include <memory>
// class calculate distances
class DestinationManager {
private:

    std::map<std::string, std::shared_ptr<Data>>& dataCache;
public:
    explicit DestinationManager( std::map<std::string, std::shared_ptr<Data>> &_dataCache) : dataCache(_dataCache) {
    }

    void setDataCache(std::map<std::string, std::shared_ptr<Data>> &_dataCache){
        dataCache = _dataCache;
    }

    std::map<double, std::shared_ptr<Data>> findDestinationsInRadius( CoordinateData center, double radius)  {

        std::map<double, std::shared_ptr<Data>> vCities;

        for (const auto & city : dataCache)
        {
            auto citCoord = city.second->getCoordinates();
            double distance =  getDistance(center, CoordinateData(citCoord.first,citCoord.second));

            if(distance <= radius && distance != 0 )
            {
                vCities[distance] =   std::make_shared<City>(City{city.second->getName(), citCoord.first, citCoord.second});
            }
        }

        return std::move(vCities);
    }

private:
    // calc distance betaine two points
    static double getDistance(const CoordinateData& a, const CoordinateData& b) {
        constexpr double EarthRadius = 6371.0; // radius of the earth

        double dLat = (b.latitude - a.latitude) * M_PI / 180.0;
        double dLon = (b.longitude - a.longitude) * M_PI / 180.0;

        double lat1 = a.latitude * M_PI / 180.0;
        double lat2 = b.latitude * M_PI / 180.0;

        double x = sin(dLat / 2) * sin(dLat / 2) + sin(dLon / 2) * sin(dLon / 2) * cos(lat1) * cos(lat2);
        double y = 2 * atan2(sqrt(x), sqrt(1 - x));

        return EarthRadius * y;
    }

    static bool isPointInRadius(double circle_x, double circle_y, double radius, double point_x, double point_y)
    {
        if (((point_x - circle_x) * (point_x - circle_x) + (point_y - circle_y) * (point_y - circle_y)) < radius * radius) {
            //point into the circle
            return true;
        } else {
            //point not in the circle
            return false;
        }
    }
};


#endif //RADIUS_DESTINATION_MANAGER_H
