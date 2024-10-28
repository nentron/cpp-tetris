#pragma once

#include "common.h"

#include <array>
#include <cstdint>


template <typename T, int num>
class Barrel{
private:
    std::array<T, num> barrel_;
    T* present_ = nullptr;

public:
    explicit Barrel()
    {
        if (num < 2){
            throw std::runtime_error("Zero or negative size");
        }
        present_ = &barrel_[0];
    }

    const T* Next() const {
        return &barrel_[barrel_.size() - 1] == present_ ? &barrel_[0] : present_ + 1;
    }

    T* Next(){
        return &barrel_[barrel_.size() - 1] == present_ ? &barrel_[0] : present_ + 1;
    }

    T* GetPatron(){
        return present_;
    }

    const T* GetPatron() const {
        return const_cast<Barrel*>(this) -> GetPatron();
    }

    void Move(){
        present_ = Next();
    }
};
