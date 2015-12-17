//
// Created by Alex on 12/15/2015.
//

#include "strategic.h"

namespace Gaming{
    const char Strategic::STRATEGIC_ID = 'T';

    Strategic::Strategic(const Game &g, const Position &p, double energy, Strategy *s) :
            __strategy(s), Agent(g, p, energy) { }

    Strategic::~Strategic() { delete __strategy; }

    void Strategic::print(std::ostream &os) const {
        os << STRATEGIC_ID;
    }

    ActionType Strategic::takeTurn(const Surroundings &s) const { return (*__strategy)(s); }

}