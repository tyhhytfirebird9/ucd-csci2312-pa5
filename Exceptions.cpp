//
// Created by Alex on 12/15/2015.
//

#include "Exceptions.h"
#include "Game.h"

namespace Gaming{


    DimensionEx::DimensionEx(unsigned expWidth, unsigned expHeight, unsigned width, unsigned height)
            : __exp_width(expWidth), __exp_height(expHeight), __width(width), __height(height) {}


    InsufficientDimensionsEx::InsufficientDimensionsEx(unsigned minWidth, unsigned minHeight, unsigned width, unsigned height)
            : DimensionEx(Game::MIN_WIDTH, Game::MIN_HEIGHT, width, height) { setName("InsufficientDimensionsEx"); }


    void GamingException::setName(std::string name) { __name = name; }
    unsigned DimensionEx::getExpWidth() const { return __exp_width; }
    unsigned DimensionEx::getExpHeight() const { return __exp_height; }
    unsigned DimensionEx::getWidth() const { return __width; }
    unsigned DimensionEx::getHeight() const { return __height; }



    void GamingException::__print_args(std::ostream &os) const {

    }

    void InsufficientDimensionsEx::__print_args(std::ostream &os) const {
        os << "minWidth = " <<__exp_width << ", "
        << "minHeight = " <<__exp_height << ", "
        << "width = " <<__width << ", "
        << "height = " << __height;
    }

    void OutOfBoundsEx::__print_args(std::ostream &os) const {

    }

    std::ostream &operator<<(std::ostream &os, const GamingException &ex) {
        os << "InsufficientDimensionsEx(";
        ex.__print_args(os);
        os << ")";
        return os;
    }

}

