#include "supertetris.h"

#include <array>


bool SuperTetris::CheckGameEnd() const {
    return std::any_of(board_.begin(), board_.begin() + 4, [](const auto& row){
        return std::any_of(row.begin(), row.end(), [](const Flag flag){
            return flag == Flag::INSTALLED;
        });
    });
}

int SuperTetris::ClearFullLines(){
    bool is_valid = true;
    int i = MAX_ROWS - 1;
    std::array<Flag, MAX_COLS>* cleared_row = nullptr;
    int cleared_rows = 0;

    do {
        const RowState state = GetRowState(board_[i]);

        switch (state){
            case RowState::EMPTY:
                is_valid = false;
                break;
            case RowState::FULL:
                std::fill(board_[i].begin(), board_[i].end(), Flag::EMPTY);
                if (!cleared_row){
                    cleared_row = &board_[i];
                }
                ++cleared_rows;
                break;
            case RowState::PARTLY:
                if (cleared_row){
                    cleared_row -> swap(board_[i]);
                    --cleared_row;
                }
                break;
        }

        --i;
    } while (is_valid && i >= 0);

    return cleared_rows;
}

void SuperTetris::ClearBoard(){
    std::for_each(board_.begin(), board_.end(), [](auto& row){
        std::fill(row.begin(), row.end(), Flag::EMPTY);
    });
}

void SuperTetris::SetShapeCoords(){
    Position init = present_coords_[0];
    for (int i = 1; i < present_coords_.size(); ++i){
        present_coords_[i] = init + barrel_.GetPatron() -> GetShifts()[i - 1];
    }
}

void SuperTetris::SetValueByCoords(Flag c){
    for (auto pos : present_coords_){
        board_[pos.y_][pos.x_] = c;
    }
}

bool SuperTetris::IsValidShift(Position shift) const {
    return std::all_of(present_coords_.begin(), present_coords_.end(), [shift, this](const Position& pos){
        const Position new_pos = shift + pos;
        return new_pos.IsValid() && board_[new_pos.y_][new_pos.x_] != Flag::INSTALLED;
    });
}

bool SuperTetris::IsValidVeering() const {
    const auto& shifts = barrel_.GetPatron() -> GetShifts();
    return std::all_of(shifts.begin(), shifts.end(), [this](auto shift){
        const Position pos = present_coords_[0] + shift;
        return pos.IsValid() && board_[pos.y_][pos.x_] != Flag::INSTALLED;
    });
}

void SuperTetris::SetShift(Position pos){
    std::for_each(present_coords_.begin(), present_coords_.end(), [&pos](auto& present){
        present = present + pos;
    });
}

void SuperTetris::Left(){
    if (IsValidShift(Position{-1, 0})){
        SetValueByCoords(Flag::EMPTY);
        SetShift(Position{-1, 0});
        SetValueByCoords(Flag::ACTIVE);
    }
}

void SuperTetris::Right(){
    if (IsValidShift(Position{1, 0})){
        SetValueByCoords(Flag::EMPTY);
        SetShift(Position{1, 0});
        SetValueByCoords(Flag::ACTIVE);
    }
}

bool SuperTetris::Down(){
    if (IsValidShift(Position{0, 1})){
        SetValueByCoords(Flag::EMPTY);
        SetShift(Position{0, 1});
        SetValueByCoords(Flag::ACTIVE);
        return false;
    } else {
        SetValueByCoords(Flag::INSTALLED);
        int cleared_lines = ClearFullLines();
        result_.rm_lines += cleared_lines;
        result_.score_ += 100 * cleared_lines;
        return true;
    }
}

void SuperTetris::VeerLeft(){
    barrel_.GetPatron() -> Previous();
    if (IsValidVeering()){
        SetValueByCoords(Flag::EMPTY);
        SetShapeCoords();
        SetValueByCoords(Flag::ACTIVE);
    } else {
        barrel_.GetPatron() -> Next();
    }
}

void SuperTetris::VeerRight(){
    barrel_.GetPatron() -> Next();
    if (IsValidVeering()){
        SetValueByCoords(Flag::EMPTY);
        SetShapeCoords();
        SetValueByCoords(Flag::ACTIVE);
    } else {
        barrel_.GetPatron() -> Previous();
    }
}

void SuperTetris::ResetShape(){
    barrel_.GetPatron() -> Reset();
    barrel_.Move();
    present_coords_[0] = START_POS;
    SetShapeCoords();
    SetValueByCoords(Flag::ACTIVE);
}

const std::array<std::array<Flag, MAX_COLS>, MAX_ROWS>& SuperTetris::GetBoard() const {
    return board_;
}

ShapesShifts::Shape SuperTetris::GetCurrentShape() const {
    return barrel_.GetPatron() -> GetShapeNum();
}

ShapesShifts::Shape SuperTetris::GetNextShape() const {
    return barrel_.Next() -> GetShapeNum();
}

Result SuperTetris::GetResult() const {
    return result_;
}

void SuperTetris::ResetGame(){
    std::for_each(board_.begin(), board_.end(), [&](auto& row){
            std::fill(row.begin(), row.end(), Flag::EMPTY);
        }
    );

    present_coords_[0] = START_POS;
    SetShapeCoords();
    SetValueByCoords(Flag::ACTIVE);
    result_.Reset();
}
