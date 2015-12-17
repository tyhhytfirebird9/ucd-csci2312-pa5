//
// Created by Alex Foreman on 12/16/15.
//

#include "AggressiveAgentStrategy.h"
#include "Game.h"

namespace Gaming {
    const double AggressiveAgentStrategy::DEFAULT_AGGRESSION_THRESHOLD = Game::STARTING_AGENT_ENERGY * 0.75;

    AggressiveAgentStrategy::AggressiveAgentStrategy(double agentEnergy) : __agentEnergy(agentEnergy) { }
    AggressiveAgentStrategy::~AggressiveAgentStrategy() { }

    ActionType AggressiveAgentStrategy::operator()(const Surroundings &s) const {
        std::vector<int> agent;
        std::vector<int> adv;
        std::vector<int> food;
        std::vector<int> emp;
        Position thispos(1, 1);

        for(int i = 0; i < 9; i++){
            if(s.array[i] == SIMPLE || s.array[i] == STRATEGIC)
                agent.push_back(i);
            if(s.array[i] == ADVANTAGE)
                adv.push_back(i);
            if(s.array[i] == FOOD)
                food.push_back(i);
            if(s.array[i] == EMPTY)
                emp.push_back(i);
        }

        if(__agentEnergy >= DEFAULT_AGGRESSION_THRESHOLD && agent.size() > 0)
            return Game::reachSurroundings(thispos, Game::randomPosition(agent));
        else if(adv.size() > 0)
            return Game::reachSurroundings(thispos, Game::randomPosition(adv));
        else if(food.size() > 0)
            return Game::reachSurroundings(thispos, Game::randomPosition(food));
        else if(emp.size() > 0)
            return Game::reachSurroundings(thispos, Game::randomPosition(emp));
        else
            return STAY;
    }

}