#include <cstdint>
#include <iostream>
#include <ostream>
#include <sstream>
#include <vector>

#include "../../../common/coordinate.h"
#ifndef MAP_H
#define MAP_H

class Map {
private:
    int rows;
    int columns;
    std::vector<std::vector<int>> matrix;

public:
    Map(int rows, int columns): rows(rows), columns(columns) {
        matrix.resize(rows, std::vector<int>(columns));
    }
    void set(const Coordinate& position, const int& value) {
        if (out_of_range(position)) {
            // TODO: que sea una excepcion
            std::cout << "Error. Posicion" << position.x << "," << position.y << "fuera de rango"
                      << std::endl;
            return;
        }
        matrix[position.y][position.x] = value;
    }
    int get(const Coordinate& position) {
        if (out_of_range(position)) {
            std::cout << "Error. Posicion" << position.x << "," << position.y << "fuera de rango"
                      << std::endl;
            return -1;
        }
        return matrix[position.y][position.x];
    }
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

#endif
