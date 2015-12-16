//
// Created by Alex on 12/15/2015.
//


#include "ErrorContext.h"
#include "Game.h"
#include "Exceptions.h"

namespace Gaming {
    const unsigned Game::MIN_WIDTH = 3;
    const unsigned Game::MIN_HEIGHT = 3;
    const double Game::STARTING_AGENT_ENERGY = 20;
    const double Game::STARTING_RESOURCE_CAPACITY = 10;
    const unsigned Game::NUM_INIT_AGENT_FACTOR = 4;
    const unsigned Game::NUM_INIT_RESOURCE_FACTOR = 2;


    Game::Game() :
            __width(Game::MIN_WIDTH), __height(Game::MIN_HEIGHT), __numInitAgents(0), __numInitResources(0),
            __status(NOT_STARTED) {
        __grid.resize(__width * __height);
        for (int i = 0; i < (__height * __width) - 1; i++) {
            __grid[i] = nullptr;
        }
    }

    Game::Game(unsigned width, unsigned height, bool manual) :
            __width(width), __height(height), __numInitAgents(0), __numInitResources(0), __status(NOT_STARTED),
            __round(0) {
        if (__width < Game::MIN_WIDTH || __height < Game::MIN_HEIGHT) {
            throw InsufficientDimensionsEx(MIN_WIDTH, MIN_HEIGHT, width, height);
        }
        __grid.resize(__width * __height);
        for (int i = 0; i < (__height * __width) - 1; i++) {
            __grid[i] = nullptr;
        }
    }

    Game::~Game() {

    }


    unsigned int Game::getNumPieces() const {
        unsigned int numPieces = 0;
        for (int i = 0; i < (__height * __width) - 1; i++) {
            if (__grid[i] != nullptr)
                numPieces++;
        }
        return numPieces;
    }

    std::ostream &operator<<(std::ostream &os, const Game &game) {
        //std::cout << "ELEMS: " << game.__round << " " << game.__width << " " << game.__height << std::endl;
        //os << std::endl;
        os << "Round: " << game.__round << std::endl;
        for (int i = 0; i < game.__height; i++) {
            for (int j = 0; j < game.__width; j++) {
                os << "[" << "     " << "]";
            }
            os << std::endl;
        }
        os << "Status: " << game.__status << std::endl;
        return os;
    }
}
