//
// Created by Alex on 12/15/2015.
//

#include "Agent.h"
#include "Resource.h"
#include "Food.h"
#include "Advantage.h"

namespace Gaming{
    const double Agent::AGENT_FATIGUE_RATE = 0.3;

    Agent::Agent(const Game &g, const Position &p, double energy) :
            Piece(g, p)  { __energy = energy; } // TODO implement

    Agent::~Agent(){

    }// TODO implement

    void Agent::age() {
        __energy -= AGENT_FATIGUE_RATE;
    }

    Piece &Agent::operator*(Piece &other) {
        Piece* agent = dynamic_cast<Agent*>(&other);
        if(agent)
            return interact(dynamic_cast<Agent*>(&other));

        Piece* resource = dynamic_cast<Resource*>(&other);
        if(resource)
            return interact(dynamic_cast<Resource*>(&other));
    }

    Piece &Agent::interact(Agent *a) {
        if(__energy > a->__energy){
            __energy -= a->__energy;
            a->__energy = 0;
            a->finish();
        } else if (__energy == a->__energy){
            __energy = 0;
            a->__energy = 0;
            a->finish();
            finish();
        } else {
            a->__energy -= __energy;
            __energy = 0;
            finish();
        }

        return *this;
    }

    Piece &Agent::interact(Resource *r) {
        Resource* food = dynamic_cast<Food*>(r);
        if(food){
            this->addEnergy(food->consume());
            r->interact(this);
        }

        Resource* advantage = dynamic_cast<Advantage*>(r);
        if(advantage){
            this->addEnergy(advantage->consume());
            r->interact(this);
        }
        return *this;
    }
}