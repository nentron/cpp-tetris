#pragma once

#include "barrel.h"
#include "common.h"
#include "test.h"
#include "test_shapes.h"
#include "shapes.h"

#include <algorithm>
#include <array>
#include <cassert>
#include <vector>

const Position START = {3, 3};

template<typename Matrix, typename T>
void SetShapeByCoords(const std::array<Position, 3>& shifts, Matrix& matrix, T value){

    for (auto shift : shifts){
        const Position pos = START + shift;
        matrix[pos.y_][pos.x_] = value;
    }
}

template<typename Matrix, typename T>
void FillMatrixByValue(Matrix& matrix, T value){
    std::for_each(matrix.begin(), matrix.end(), [value](auto& row){
        std::fill(row.begin(), row.end(), value);
    });
}


void TestShape(){
    using namespace std::literals;

    const std::vector<std::vector<std::vector<int>>> shapes{
        SQUARE, L0, L1, L2, L3, J0, J1, J2, J3,
        I0, I1, I2, I3, T0, T1, T2, T3, Z0, Z1,
        S0, S1
    };
    int shape_idx = 0;
    std::vector<std::vector<int>> board{
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0}
    };

    for (const auto shape_coords : SHAPES_SHIFTS){
        for (const auto& coords : *shape_coords){
            SetShapeByCoords(coords, board, 1);
            assert(testrunner::AssertEqual(board, shapes[shape_idx],
                 "Test shape failed, shape num: "s + std::to_string(shape_idx))
            );
            ++shape_idx;
            SetShapeByCoords(coords, board, 0);
        }
    }
}


void TestShapesShifts(){

    ShapesShifts sh;

    for (int shape_num = 0; shape_num < MAX_SHAPES; ++shape_num){
        for (int i = 0; i < 10; ++i){
            sh.Next();
            sh.GetShifts();
        }

        for (int j = 0; j < 10; ++j){
            sh.Previous();
            sh.GetShifts();
        }
        sh.Reset();
    }
}

void TestBarrel(){
    try {
        Barrel<ShapesShifts, 2> s;
    } catch (const std::runtime_error){
    } catch (...){
        throw std::runtime_error("Don't throw write exception in case 0 or less constructor value");
    }

    class Test{
    private:
        int num_ = 0;
    public:
        int GetValue() const {
            return num_;
        }

        void Increase(){
            ++num_;
        }
    };

    Barrel<Test, 3> bar;

    for (int i = 0; i < 9; ++i){
        bar.GetPatron() -> Increase();
        bar.Move();
    }

    for (int i = 0; i < 3; ++i){
        assert(bar.GetPatron() -> GetValue() == 3);
        bar.Move();
    }

    for (int i = 0; i < 5; ++i){
        assert(bar.GetPatron() != bar.Next());
        bar.Move();
    }
}
