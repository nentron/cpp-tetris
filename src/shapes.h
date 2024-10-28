#pragma once

#include "common.h"

#include <array>


using ShapeShift = std::vector<std::array<Position, 3>>;

const ShapeShift O = {{Position{0, -1}, Position{1, -1}, Position{1, 0}}};

const ShapeShift L = {{Position{0, -1}, Position{0, -2}, Position{1, 0}},
                      {Position{0, -1}, Position{1, -1}, Position{2, -1}},
                      {Position{0, -1}, Position{0, -2}, Position{-1, -2}},
                      {Position{0, -1}, Position{-1, 0}, Position{-2, 0}}};

const ShapeShift J = {{Position{-1, 0}, Position{0, -1}, Position{0, -2}},
                      {Position{0, -1}, Position{1, 0}, Position{2, 0}},
                      {Position{0, -1}, Position{0, -2}, Position{1, -2}},
                      {Position{0, -1}, Position{-1, -1}, Position{-2, -1}}};

const ShapeShift I = {{Position{0, -1}, Position{0, -2}, Position{0, -3}},
                      {Position{1, 0}, Position{2, 0}, Position{3, 0}},
                      {Position{0, -1}, Position{0, -2}, Position{0, -3}},
                      {Position{-1, 0}, Position{-2, 0}, Position{-3, 0}}};

const ShapeShift T = {{Position{-1, -1}, Position{0, -1}, Position{1, -1}},
                      {Position{0, -1}, Position{-1, -1}, Position{0, -2}},
                      {Position{-1, 0}, Position{1, 0}, Position{0, -1}},
                      {Position{0, -1}, Position{1, -1}, Position{0, -2}}};

const ShapeShift Z = {{Position{-1, -1}, Position{0, -1}, Position{1, 0}},
                      {Position{0, -1}, Position{1, -1}, Position{1, -2}}};

const ShapeShift S = {{Position{-1, 0}, Position{0, -1}, Position{1, -1}},
                       {Position{0, -1}, Position{-1, -1}, Position{-1, -2}}};

const std::array<const ShapeShift*, MAX_SHAPES> SHAPES_SHIFTS{&O, &L, &J, &I, &T, &Z, &S};

class ShapesShifts{
public:
    enum class Shape{
        O, L, J,
        I, T, Z,
        S
    };
private:
    const std::array<const ShapeShift*, MAX_SHAPES>& shapes_shifts_ =
        SHAPES_SHIFTS;
    int shape_num_ = GetRandom();
    int shape_pos_ = 0;
    const ShapeShift& GetShape() const;
public:
    const std::array<Position, 3>& GetShifts() const;
    void Next();
    void Previous();
    void Reset();
    Shape GetShapeNum() const;
};
