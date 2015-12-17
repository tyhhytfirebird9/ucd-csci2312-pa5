//
// Created by Alex on 12/15/2015.
//
#include "Simple.h"


namespace Gaming {
    const char Simple::SIMPLE_ID = 'S';

    Simple::Simple(const Game& g, const Position &p, double energy) :
            Agent(g, p, energy) { __energy = energy; }

    Simple::~Simple(){}

    void Simple::print(std::ostream &os) const {
        os << SIMPLE_ID;
    }

    ActionType Simple::takeTurn(const Surroundings &s) const {
        std::vector<int> resources;
        std::vector<int> empty;
        Position thispos(1,1);

        for(int i = 0; i < 9; i++){
            if(s.array[i] == FOOD || s.array[i] == ADVANTAGE){
                resources.push_back(i);
            } else if (s.array[i] == EMPTY) {
                empty.push_back(i);
            }
        }
        if (resources.size() > 0) {
            return Game::reachSurroundings(thispos, Game::randomPosition(resources));
        } else if (empty.size() > 0) {
            return Game::reachSurroundings(thispos, Game::randomPosition(empty));
        } else {
            return STAY;
        }
    }
}