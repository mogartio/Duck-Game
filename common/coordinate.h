#ifndef COORDINATE_H
#define COORDINATE_H

class Coordinate {
public:
    int x;
    int y;
    Coordinate(int x, int y): x(x), y(y) {}
    bool operator==(const Coordinate& other) const {
        return this->x == other.x && this->y == other.y;
    }
};
#endif  // !COORDINATE_H
