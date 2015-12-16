//
// Created by Alex on 12/15/2015.
//

#include "Advantage.h"

namespace Gaming{
    const char Advantage::ADVANTAGE_ID = 'D';
    const double Advantage::ADVANTAGE_MULT_FACTOR = 2.0;

    Advantage::Advantage(const Game &g, const Position &p, double capacity) :
            Resource(g, p, capacity) {}

    Advantage::~Advantage() {}

    void Advantage::print(std::ostream &os) const { }

    double Advantage::getCapacity() const { }
    double Advantage::consume() { }

}