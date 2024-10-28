#pragma once

#include "barrel.h"
#include "shapes.h"

#include <array>
#include <algorithm>
#include <cstdint>
#include <iostream>


template <typename Container>
RowState GetRowState(const Container& array){
    const int filled_cells = std::count(array.begin(), array.end(), Flag::INSTALLED);

    switch (filled_cells){
        case MAX_COLS:
            return RowState::FULL;
        case 0:
            return RowState::EMPTY;
        default:
            return RowState::PARTLY;
    }
}

struct Result{
    int score_ = 0;
    int rm_lines = 0;

    void Reset(){
        score_ = 0;
        rm_lines = 0;
    }
};

class SuperTetris{
private:
    std::array<std::array<Flag, MAX_COLS>, MAX_ROWS> board_;
    Barrel<ShapesShifts, 2> barrel_;
    std::array<Position, 4> present_coords_;
    Result result_;

    int ClearFullLines();
    bool IsValidShift(Position shift) const;
    bool IsValidVeering() const;
    void SetValueByCoords(Flag c);
    void SetShapeCoords();
    void SetShift(Position shift);

public:
    SuperTetris(){
        std::for_each(board_.begin(), board_.end(), [&](auto& row){
            std::fill(row.begin(), row.end(), Flag::EMPTY);
        });

        present_coords_[0] = START_POS;
        SetShapeCoords();
        SetValueByCoords(Flag::ACTIVE);
    }
    void ResetGame();
    const std::array<std::array<Flag, MAX_COLS>, MAX_ROWS>& GetBoard() const;

    ShapesShifts::Shape GetCurrentShape() const;

    ShapesShifts::Shape GetNextShape() const;

    Result GetResult() const;

    bool CheckGameEnd() const;
    void ClearBoard();
    bool Down();
    void Left();
    void Right();
    void VeerLeft();
    void VeerRight();
    void ResetShape();
};
