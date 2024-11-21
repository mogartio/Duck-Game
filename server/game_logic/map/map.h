#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include <iostream>
#include <tuple>
#include <sstream>
#include <cstdint>
#include <vector>
#include <ostream>
#include "../../../common/coordinate.h"

/*
* Map class that holds the information of the map and allows to set and get values from it.
*/
class Map {

private:
    std::string name;
    int rows;
    int columns;
    std::vector<std::vector<int>> matrix;
    std::vector<std::tuple<Coordinate>> players_spawn_sites;
    std::vector<std::tuple<Coordinate, int>> items_spawn_sites;

public:
    Map(std::string new_map_name, int rows, int columns, std::vector<std::vector<int>> matrix, std::vector<std::tuple<Coordinate>> players_spawn_sites, std::vector<std::tuple<Coordinate, int>> items_spawn_sites) : name(new_map_name), rows(rows), columns(columns), matrix(matrix), players_spawn_sites(players_spawn_sites), items_spawn_sites(items_spawn_sites) {}

    
    /**
     * @brief Sets the value at the specified position in the matrix.
     */
    void set(const Coordinate& position, const int& value) {
        if (out_of_range(position)) {
            // lanzar excepcion
        }
        matrix[position.y][position.x] = value;
    }

    /**
     * @brief Retrieves the value at the specified position in the matrix.
     */
    int get(const Coordinate& position) {
        if (out_of_range(position)) {
            // lanzar excepcion
        }
        return matrix[position.y][position.x];
    }

    /**
     * @brief Returns the number of rows in the map.
     */
    uint16_t get_rows() {
        return rows;
    }

    /**
     * @brief Returns the number of columns in the map.
     */
    uint16_t get_columns() {
        return columns;
    }

    /**
     * @brief Returns the matrix of the map.
     */
    std::vector<std::vector<int>> get_matrix() {
        return matrix;
    }

    /**
     * @brief Returns the players spawn points.
     */
    std::vector<std::tuple<Coordinate>> get_players_spawn_sites() {
        return players_spawn_sites;
    }

    /**
     * @brief Returns the items spawn points.
     */
    std::vector<std::tuple<Coordinate, int>> get_items_spawn_sites() {
        return items_spawn_sites;
    }

    /**
     * @brief Checks if a given coordinate is out of the map's range.
     */
    bool out_of_range(const Coordinate& position) {
        return !(static_cast<size_t>(position.y) < matrix.size() && position.y >= 0 &&
                 static_cast<size_t>(position.x) < matrix[0].size() && position.x >= 0);
    }


    void print() {
        for (int i = 0; i < rows; i++) {
            std::stringstream stream;
            for (int j = 0; j < columns; j++) {
                if (matrix[i][j] == 2 || matrix[i][j] == 1) {
                    stream << "\033[31m"
                           << "|" << matrix[i][j] << "\033[0m";  // Rojo para el número 2
                } else if (matrix[j][i] == 5 || matrix[i][j] == 6) {
                    stream << "\033[34m"
                           << "|" << matrix[i][j] << "\033[0m";  // Rojo para el número 2
                } else if (matrix[i][j] == 8 || matrix[i][j] == 7) {
                    stream << "\033[33m"
                           << "|" << matrix[i][j] << "\033[0m";  // Rojo para el número 2
                } else if (matrix[j][i] == 4) {
                    stream << "\033[32m"
                           << "|" << matrix[i][j] << "\033[0m";  // Rojo para el número 2
                } else {
                    stream << "|" << matrix[i][j];  // Imprimir el valor normalmente
                }
            }
            std::cout << stream.str() << std::endl;
        }
    }

    std::vector<uint16_t> get_vector_representation() {
        std::vector<uint16_t> res;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                res.push_back(static_cast<uint16_t>(matrix[i][j]));
            }
        }
        return res;
    }

};

#endif // MAP_H 
