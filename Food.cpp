//
// Created by Alex on 12/15/2015.
//

#include "Food.h"

namespace Gaming{
    const char FOOD_ID = 'F';

    Food::Food(const Game &g, const Position &p, double capacity) :
            Resource(g, p, capacity) {}

    Food::~Food() {}

    void Food::print(std::ostream &os) const { }
}