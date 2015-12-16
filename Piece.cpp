//
// Created by Alex on 12/15/2015.
//

#include "Piece.h"

namespace Gaming{
    unsigned int Piece::__idGen = 1;

    Piece::Piece(const Game &g, const Position &p) : __game(g), __position(p), __id(__idGen++) { } // TODO implement

    Piece::~Piece() {} // TODO implement

    std::ostream &operator<<(std::ostream &os, const Piece &piece) {

    }
}