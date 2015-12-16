//
// Created by Alex on 12/15/2015.
//

#include "Resource.h"

namespace Gaming{
    const double RESOURCE_SPOIL_FACTOR = 1.2;

    Resource::Resource(const Game &g, const Position &p, double __capacity) :
    __capacity(__capacity), Piece(g, p) { }

    Resource::~Resource() {}

    double Resource::consume() {}

    void Resource::age() {}

    ActionType Resource::takeTurn(const Surroundings &s) const { }

    Piece &Resource::operator*(Piece &other) { }

    Piece &Resource::interact(Agent *a) { }

    Piece &Resource::interact(Resource *r) { }
}