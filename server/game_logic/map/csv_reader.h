#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "map.h"
#ifndef CSV_READER_H

// Esta clase se encarga de leer mapas en formato csv
class CSVReader {
private:
    int rows;
    int columns;
    std::ifstream file;
    std::string file_name;
    Map map;

public:
    explicit CSVReader(const std::string& file_name): map(0, 0) {
        file.open(file_name);
        std::string line;
        std::vector<std::string> sizes;
        if (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string value;
            while (std::getline(ss, value, ',')) {
                sizes.push_back(value);
            }
        }
        rows = std::stoi(sizes[0]);
        columns = std::stoi(sizes[1]);
        map = Map(rows, columns);
    }

    Map&& read_map() {

        std::string line;
        std::getline(file, line);  // Con la linea de la metadata no hacemos nada
        int current_row = 0;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string value;
            int current_column = 0;
            while (std::getline(ss, value, ',')) {
                Coordinate current_position(current_column, current_row);
                map.set(current_position, std::stoi(value));
                current_column++;
            }
            current_row++;
        }
        return std::move(map);
    }
};

#endif
