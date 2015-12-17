//
// Created by Alex on 12/15/2015.
//

#include "Resource.h"

namespace Gaming{
    const double Resource::RESOURCE_SPOIL_FACTOR = 1.2;

    Resource::Resource(const Game &g, const Position &p, double __capacity) :
    __capacity(__capacity), Piece(g, p) { }

    Resource::~Resource() {}

    double Resource::consume() {
        double temp = __capacity;
        __capacity = 0;
        return temp;
    }

    void Resource::age() {
        __capacity /= RESOURCE_SPOIL_FACTOR;
        if(__capacity < 1){
            __capacity = 0;
        }
    }

    ActionType Resource::takeTurn(const Surroundings &s) const {
        return STAY;
    }

    Piece &Resource::operator*(Piece &other) { return other; }

    Piece &Resource::interact(Agent *a) { finish(); }

    Piece &Resource::interact(Resource *r) { finish(); }


}