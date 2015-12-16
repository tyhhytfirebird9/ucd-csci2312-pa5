//
// Created by Alex on 12/15/2015.
//
#include "Simple.h"


namespace Gaming {
    const char SIMPLE_ID = 'S';

    Simple::Simple(const Game& g, const Position &p, double energy) :
            Agent(g, p, energy) {}

    Simple::~Simple(){}

    void Simple::print(std::ostream &os) const {

    }

    ActionType Simple::takeTurn(const Surroundings &s) const {

    }
}