
#ifndef RADIUS_LOADER_HPP
#define RADIUS_LOADER_HPP

#include <utility>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <map>
#include <memory>

// class CoordinateData for inheritance by other classes where is coordinates
struct CoordinateData  {

    double latitude;
    double longitude;

    CoordinateData(double lat, double lon) : latitude(lat), longitude(lon) {}
};


class Data {
public:
    virtual ~Data() = default;

    virtual std::string getName() const = 0;
    //virtual std::pair<double, double> getCoordinates() const = 0;
    virtual CoordinateData getCoordinateData() const = 0;
};


// Data class for Cities
class City : public Data {
protected:
    std::string name;
    //std::pair<double, double> coordinate;
    CoordinateData coordinateData{0,0};
public:

    City(std::string cityName, CoordinateData coord)
            : coordinateData(coord.latitude, coord.longitude), name(std::move(cityName)) {}

    CoordinateData getCoordinateData() const override {
        return coordinateData;
    }
    [[nodiscard]] std::string getName() const override{
        return name;
    }
};

// Data class for Hotels
class  Hotels : public Data {
protected:
    uint8_t county_id;
    uint8_t city_id;
    std::string name;
};
//etc.

//////////////////////////////////////////////////////////////////////////////////////////////////////////

class Loader {
protected:

public:
    virtual std::map<std::string, std::shared_ptr<Data>>  loadData() = 0;
    virtual std::map<std::string, std::shared_ptr<Data>> loadDataByParam( std::string&&  )  = 0;
};
//
class FileLoader : public Loader{
    std::string cvs_file;

public:
    explicit FileLoader(std::string  data_file) : cvs_file(std::move(data_file)) {
    }

    /*
     * Load data from CSV file
     */
    std::map<std::string, std::shared_ptr<Data>>  loadData() override{

        std::map<std::string, std::shared_ptr<Data>> citiesCache;

        std::ifstream ifs (cvs_file, std::ifstream::out);

        if (!ifs.is_open()){
            std::cerr << "File not open"<<std::endl;
            return citiesCache;
        }

        std::string line;

        while (std::getline(ifs, line)) {
            std::istringstream ss(line);
            std::string substr;

            // split line into 4 substrings : number id, city, latitude, longitude
            std::vector<std::string> records;
            while (std::getline(ss, substr, ',')) {
//                std::cout<<"kkk";
                records.push_back(substr);
            }
            // check valid params

            if (records.size() >= 4 && !records[2].empty() && !records[3].empty()) {

                std::string cityId = records[0];

                // check valid coordinates
                if(isDouble(records[2]) && isDouble(records[3])) {
                    double latitude = std::stod(records[2]);
                    double longitude = std::stod(records[3]);

                    CoordinateData coord{latitude, longitude};

                    citiesCache[cityId] = std::make_shared<City>( City (records[1], coord) );
                }
            }
        }

        std::cout << "Loaded cities : " << citiesCache.size() << std::endl;

        return citiesCache;
    }

    /*
     * Load data from database/file by parameters
     */
    std::map<std::string, std::shared_ptr<Data>> loadDataByParam(std::string&& query) override{
        std::map<std::string, std::shared_ptr<Data>> data;
        //TODO
        return data;
    }

private:
    bool isDouble(const std::string& s) {
        try {
            size_t pos = 0;
            std::stod(s, &pos);

            // Якщо вся стрічка була конвертована, повертаємо true
            return pos == s.length();
        } catch (...) {
            return false; // Якщо сталася помилка під час конвертації, повертаємо false
        }
    }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Same for database
 */
class DatabaseLoader : public Loader{
    std::string db_file;
public:

    explicit DatabaseLoader(std::string  data_file) : db_file(std::move(data_file)) {
    }

    std::map<std::string, std::shared_ptr<Data>> loadData() override
    {
        std::map<std::string, std::shared_ptr<Data>> data;
        // TODO
        return data;
    }
    std::map<std::string, std::shared_ptr<Data>> loadDataByParam(std::string&&) override
    {
        std::map<std::string, std::shared_ptr<Data>> data;
        // TODO
        return data;
    }
};


#endif //RADIUS_LOADER_HPP
