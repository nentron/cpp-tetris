#include "common.h"

int GetRandom(){
    return rand() % MAX_SHAPES;
}

Position operator+(Position pos1, Position pos2){
    return Position{pos1.x_ + pos2.x_, pos1.y_ + pos2.y_};
}
