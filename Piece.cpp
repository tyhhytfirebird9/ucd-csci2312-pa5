//
// Created by Alex on 12/15/2015.
//

#include <iomanip>
#include "Piece.h"

namespace Gaming{
    unsigned int Piece::__idGen = 1;

    Piece::Piece(const Game &g, const Position &p) : __game(g), __position(p), __id(__idGen++), __finished(false) { } // TODO implement

    Piece::~Piece() {

    }

    std::ostream &operator<<(std::ostream &os, const Piece &piece) {
        piece.print(os);
        os << piece.__id;
        return os;
    }

}