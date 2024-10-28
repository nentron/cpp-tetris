#pragma once

#include <cstdint>
#include <random>
#include <stdexcept>


const int MAX_ROWS = 24;
const int MAX_COLS = 10;
const int MAX_SHAPES = 7;

enum class Flag: char{
    EMPTY = 'A',
    INSTALLED = 'B',
    ACTIVE = 'C'
};

enum class RowState{
    EMPTY,
    FULL,
    PARTLY
};

struct Position {
    int x_ = 0;
    int y_ = 0;

    Position() = default;

    Position(int x, int y)
        : x_(x)
        , y_(y)
    {}

    bool IsValid() const {
        return x_ >= 0 && x_ < MAX_COLS  && y_ >= 0 && y_ < MAX_ROWS;
    }
};

const Position START_POS = {4, 3};

int GetRandom();


class EndGameException: private std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

Position operator+(Position pos1, Position pos2);
