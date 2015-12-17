//
// Created by Alex on 12/15/2015.
//

#include "DefaultAgentStrategy.h"
#include "Game.h"

namespace Gaming {
    DefaultAgentStrategy::DefaultAgentStrategy() { }
    DefaultAgentStrategy::~DefaultAgentStrategy() { }

    ActionType DefaultAgentStrategy::operator()(const Surroundings &s) const {
        std::vector<int> adv;
        std::vector<int> food;
        std::vector<int> emp;
        std::vector<int> sim;
        Position thispos(1, 1);

        for(int i = 0; i < 9; i++){
            if(s.array[i] == ADVANTAGE)
                adv.push_back(i);
            else if(s.array[i] == FOOD)
                food.push_back(i);
            else if(s.array[i] == EMPTY)
                emp.push_back(i);
            else if(s.array[i] == SIMPLE)
                sim.push_back(i);
        }
        if(adv.size() > 0)
            return Game::reachSurroundings(thispos, Game::randomPosition(adv));
        else if(food.size() > 0)
            return Game::reachSurroundings(thispos, Game::randomPosition(food));
        else if(emp.size() > 0)
            return Game::reachSurroundings(thispos, Game::randomPosition(emp));
        else if(sim.size() > 0)
            return Game::reachSurroundings(thispos, Game::randomPosition(sim));
        else
            return STAY;


    }
}