#include <iostream>
#include <ostream>
#include <vector>
#include <sstream>
#include "../../common/coordinate.h"
#ifndef MAP_H
#define MAP_H

class Map{
private:
    int rows;
    int columns;
    std::vector<std::vector<int>> matrix;

public:
    Map(int rows, int columns): rows(rows), columns(columns) {
        matrix.resize(rows, std::vector<int>(columns));
    }
    void set(const Coordinate& position, const int& value){
        if (out_of_range(position)){
        std::cout << "Error. Posicion" << position.x << "," 
                << position.y << "fuera de rango" << std::endl;
        }
        matrix[position.y][position.x] = value;
    }
    int get(const Coordinate& position){
        if (out_of_range(position)){
        std::cout << "Error. Posicion" << position.x << "," 
                << position.y << "fuera de rango" << std::endl;
        }
        return matrix[position.y][position.x];
    }
    bool out_of_range(const Coordinate& position){
        return !(position.x < matrix.size() && position.x >= 0 
                 && position.y < matrix[0].size() && position.y >= 0);
    }

    void print(){
        for (int i=0; i < rows; i++){
            std::stringstream stream;
            for (int j=0; j < columns; j++){
                stream << "|" << matrix[j][i];
            }
            std::cout << stream.str() << std::endl; 
        }
    }
};

#endif
