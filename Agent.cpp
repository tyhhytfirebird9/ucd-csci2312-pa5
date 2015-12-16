//
// Created by Alex on 12/15/2015.
//

#include "Agent.h"

namespace Gaming{
    const double AGENT_FATIGUE_RATE = 0.3;

    Agent::Agent(const Game &g, const Position &p, double energy) :
            __energy(energy), Piece(g, p) {} // TODO implement

    Agent::~Agent(){}// TODO implement

    void Agent::age() {
        //__energy -= AGENT_FATIGUE_RATE;
    }

    Piece &Agent::operator*(Piece &other) {

    }

    Piece &Agent::interact(Agent *a) {

    }

    Piece &Agent::interact(Resource *r) {

    }

}