#ifndef MAP_H
#define MAP_H

#include <vector>
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
    void set_position(const Coordinate& position, const int& value) {
        if (out_of_range(position)) {
            // lanzar excepcion
        }
        matrix[position.y][position.x] = value;
    }

    /**
     * @brief Retrieves the value at the specified position in the matrix.
     */
    int get_position(const Coordinate& position) {
        if (out_of_range(position)) {
            // lanzar excepcion
        }
        return matrix[position.y][position.x];
    }

    /**
     * @brief Returns the number of rows in the map.
     */
    int get_rows() {
        return rows;
    }

    /**
     * @brief Returns the number of columns in the map.
     */
    int get_columns() {
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

};

#endif // MAP_H 
