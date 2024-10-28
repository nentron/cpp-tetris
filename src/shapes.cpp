#include "shapes.h"


const std::array<Position, 3>& ShapesShifts::GetShifts() const {
    return GetShape().at(shape_pos_);
}

const ShapeShift& ShapesShifts::GetShape() const {
    return *shapes_shifts_.at(shape_num_);
}

void ShapesShifts::Next(){
    shape_pos_ = shape_pos_ == GetShape().size() - 1 ? 0 : ++shape_pos_;
}

void ShapesShifts::Previous(){
    shape_pos_ = shape_pos_ == 0 ? GetShape().size() - 1 : --shape_pos_;
}

void ShapesShifts::Reset(){
    shape_num_ = GetRandom();
    shape_pos_ = 0;
}

ShapesShifts::Shape ShapesShifts::GetShapeNum() const {
    return static_cast<ShapesShifts::Shape>(shape_num_);
}
