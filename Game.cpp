//
// Created by Alex on 12/15/2015.
//
#include <iomanip>
#include <iostream>
#include <string>
#include <set>

#include "ErrorContext.h"
#include "Gaming.h"
#include "Game.h"
#include "Exceptions.h"
#include "Simple.h"
#include "Strategic.h"
#include "Food.h"
#include "Advantage.h"

namespace Gaming {
    const unsigned Game::MIN_WIDTH = 3;
    const unsigned Game::MIN_HEIGHT = 3;
    const double Game::STARTING_AGENT_ENERGY = 20;
    const double Game::STARTING_RESOURCE_CAPACITY = 10;
    const unsigned Game::NUM_INIT_AGENT_FACTOR = 4;
    const unsigned Game::NUM_INIT_RESOURCE_FACTOR = 2;

    Gaming::PositionRandomizer Gaming::Game::__posRandomizer;

    void Game::populate() {
        this->__numInitAgents = (__width * __height) / NUM_INIT_AGENT_FACTOR;
        this->__numInitResources = (__width * __height) / NUM_INIT_RESOURCE_FACTOR;

        unsigned int numStrategic = __numInitAgents / 2;
        unsigned int numSimple = __numInitAgents - numStrategic;
        unsigned int numAdvantages = __numInitResources / 4;
        unsigned int numFoods = __numInitResources - numAdvantages;

        std::default_random_engine gen;
        std::uniform_int_distribution<int> d(0, __width * __height);

        // Populate Strategic
        while (numStrategic > 0) {
            int i = d(gen);
            if(__grid[i] == nullptr) {
                Position pos(i / __width, i % __width);
                __grid[i] = new Strategic(*this, pos, Game::STARTING_AGENT_ENERGY);
                numStrategic--;
            }
        }

        // Populate Simple
        while (numSimple > 0) {
            int i = d(gen);
            if(__grid[i] == nullptr) {
                Position pos(i / __width, i % __width);
                __grid[i] = new Simple(*this, pos, Game::STARTING_AGENT_ENERGY);
                numSimple--;
            }
        }

        // Populate Advantage
        while (numAdvantages > 0) {
            int i = d(gen);
            if(__grid[i] == nullptr) {
                Position pos(i / __width, i % __width);
                __grid[i] = new Advantage(*this, pos, Game::STARTING_RESOURCE_CAPACITY);
                numAdvantages--;
            }
        }

        // Populate Food
        while (numFoods > 0) {
            int i = d(gen);
            if(__grid[i] == nullptr) {
                Position pos(i / __width, i % __width);
                __grid[i] = new Food(*this, pos, Game::STARTING_RESOURCE_CAPACITY);
                numFoods--;
            }
        }
    }


    Game::Game() :
            __width(Game::MIN_WIDTH), __height(Game::MIN_HEIGHT), __numInitAgents(0), __numInitResources(0),
            __status(NOT_STARTED), __round(0) {
        __grid.resize(__width * __height);
        for (int i = 0; i < (__height * __width) - 1; i++) {
            __grid[i] = nullptr;
        }
    }

    Game::Game(unsigned width, unsigned height, bool manual) :
            __width(width), __height(height), __numInitAgents(0), __numInitResources(0), __status(NOT_STARTED),
            __round(0), __verbose() {
        if (__width < Game::MIN_WIDTH || __height < Game::MIN_HEIGHT) {
            throw InsufficientDimensionsEx(MIN_WIDTH, MIN_HEIGHT, width, height);
        }
        __grid.resize(__width * __height);
        for (int i = 0; i < (__height * __width) - 1; i++) {
            __grid[i] = nullptr;
        }
        if (manual == false)
            populate();
    }

    Game::~Game() {

    }


    // Getters
    unsigned int Game::getNumPieces() const {
        unsigned int numPieces = 0;
        for (int i = 0; i < (__height * __width); i++) {
            if (__grid[i] != nullptr)
                numPieces++;
        }
        return numPieces;
    }
    unsigned int Game::getNumAgents() const{
        return getNumSimple() + getNumStrategic();
    }
    unsigned int Game::getNumSimple() const{
        int sum = 0;
        for(int i = 0; i < this->__width * this->__height; i++){
            if(this->__grid[i] != nullptr && this->__grid[i]->getType() == SIMPLE){
                sum++;
            }
        }
        return sum;
    }
    unsigned int Game::getNumStrategic() const {
        int sum = 0;
        for(int i = 0; i < this->__width * this->__height; i++){
            if(this->__grid[i] != nullptr && this->__grid[i]->getType() == STRATEGIC){
                sum++;
            }
        }
        return sum;
    }
    unsigned int Game::getNumResources(){
        int sum = 0;
        for(int i = 0; i < this->__width * this->__height; i++){
            if(this ->__grid[i] != nullptr && (this->__grid[i]->getType() == FOOD || this->__grid[i]->getType() == ADVANTAGE)){
                sum++;
            }
        }
        return sum;
    }

    // Grid Population Methods
    bool Game::addSimple(const Position &position) {
        bool didAdd = false;
        if(position.x > this->__height || position.y > this->__width){
            throw OutOfBoundsEx(this->__width, this->__height, position.y, position.x);
        }
        int sum = 0;
        for(int i = 0; i < position.x; i++) {
            sum += this->getWidth();
        }
        sum += position.y;

        if(this->__grid[sum] == nullptr){
            this->__grid[sum] = new Simple(*this, position, Game::STARTING_AGENT_ENERGY);
            didAdd = true;
        }
        return didAdd;
    }
    bool Game::addSimple(unsigned x, unsigned y) {
        bool didAdd = false;
        if(x > this->__height || y > this->__width){
            throw OutOfBoundsEx(this->__width, this->__height, y, x);
        }
        int sum = 0;
        for(int i = 0; i < x; i ++){
            sum += this->getWidth();
        }
        sum += y;

        if(this->__grid[sum] == nullptr){
            this->__grid[sum] = new Simple(*this, Position(x,y), Game::STARTING_AGENT_ENERGY);
            didAdd = true;
        }

        return didAdd;
    }
    bool Game::addStrategic(const Position &position, Strategy *s) {
        bool didAdd = false;
        if(position.x > this->__height || position.y > this->__width){
            throw OutOfBoundsEx(this->__width, this->__height, position.y, position.x);
        }
        int sum = 0;
        for(int i = 0; i < position.x; i++) {
            sum += this->getWidth();
        }
        sum += position.y;

        if(this->__grid[sum] == nullptr){
            this->__grid[sum] = new Strategic(*this, position, Game::STARTING_AGENT_ENERGY, s);
            didAdd = true;
        }
        return didAdd;
    }
    bool Game::addStrategic(unsigned x, unsigned y, Strategy *s) {
        bool didAdd = false;
        if(x > this->__height || y > this->__width){
            throw OutOfBoundsEx(this->__width, this->__height, y, x);
        }
        int sum = 0;
        for(int i = 0; i < x; i ++){
            sum += this->getWidth();
        }
        sum += y;

        if(this->__grid[sum] == nullptr){
            this->__grid[sum] = new Strategic(*this, Position(x,y), Game::STARTING_AGENT_ENERGY, s);
            didAdd = true;
        }

        return didAdd;
    }
    bool Game::addFood(const Position &position) {
        bool didAdd = false;
        if(position.x > this->__height || position.y > this->__width){
            throw OutOfBoundsEx(this->__width, this->__height, position.y, position.x);
        }
        int sum = 0;
        for(int i = 0; i < position.x; i++) {
            sum += this->getWidth();
        }
        sum += position.y;

        if(this->__grid[sum] == nullptr){
            this->__grid[sum] = new Food(*this, position, Game::STARTING_RESOURCE_CAPACITY);
            didAdd = true;
        }
        return didAdd;
    }
    bool Game::addFood(unsigned x, unsigned y) {
        bool didAdd = false;
        if(x > this->__height || y > this->__width){
            throw OutOfBoundsEx(this->__width, this->__height, y, x);
        }
        int sum = 0;
        for(int i = 0; i < x; i ++){
            sum += this->getWidth();
        }
        sum += y;

        if(this->__grid[sum] == nullptr){
            this->__grid[sum] = new Food(*this, Position(x,y), Game::STARTING_RESOURCE_CAPACITY);
            didAdd = true;
        }

        return didAdd;
    }
    bool Game::addAdvantage(const Position &position) {
        bool didAdd = false;
        if(position.x > this->__height || position.y > this->__width){
            throw OutOfBoundsEx(this->__width, this->__height, position.y, position.x);
        }
        int sum = 0;
        for(int i = 0; i < position.x; i++) {
            sum += this->getWidth();
        }
        sum += position.y;

        if(this->__grid[sum] == nullptr){
            this->__grid[sum] = new Advantage(*this, position, Game::STARTING_RESOURCE_CAPACITY);
            didAdd = true;
        }
        return didAdd;
    }
    bool Game::addAdvantage(unsigned x, unsigned y) {
        bool didAdd = false;
        if(x > this->__height || y > this->__width){
            throw OutOfBoundsEx(this->__width, this->__height, y, x);
        }
        int sum = 0;
        for(int i = 0; i < x; i ++){
            sum += this->getWidth();
        }
        sum += y;

        if(this->__grid[sum] == nullptr){
            this->__grid[sum] = new Advantage(*this, Position(x,y), Game::STARTING_RESOURCE_CAPACITY);
            didAdd = true;
        }

        return didAdd;
    }
    const Surroundings Game::getSurroundings(const Position &pos) const {
        Surroundings s;

        int counter = 0;

        for(int i = -1; i < 2; i++) {
            for(int j = -1; j < 2; j++){
                if(i == 0 && j == 0 ) {
                    // Set SELF
                    s.array[counter] = SELF;
                } else if ((i + static_cast<int>(pos.x)) < 0) {
                    s.array[counter] = INACCESSIBLE;
                } else if ((j + static_cast<int>(pos.y)) < 0) {
                    s.array[counter] = INACCESSIBLE;
                } else if ((i + static_cast<int>(pos.x)) >= this->__height) {
                    s.array[counter] = INACCESSIBLE;
                } else if ((j + static_cast<int>(pos.y)) >= this->__width) {
                    s.array[counter] = INACCESSIBLE;
                } else {
                    int newX = pos.x + i;
                    int newY = pos.y + j;

                    int sum = 0;
                    for(int k = 0; k < newX; k++) {
                        sum += this->getWidth();
                    }
                    sum += newY;

                    if (this->__grid[sum] == nullptr)
                        s.array[counter] = EMPTY;
                    else
                        s.array[counter] = this->__grid[sum]->getType();
                }
                counter++;
            }
        }

        return s;
    }

    // Game Play Methods
    const ActionType Game::reachSurroundings(const Position &from, const Position &to) {
        if(from.x > to.x && from.y > to.y)
            return NW;
        if(from.x > to.x && from.y == to.y)
            return N;
        if(from.x > to.x && from.y < to.y)
            return NE;
        if(from.x == to.x && from.y > to.y)
            return W;
        if(from.x == to.x && from.y == to.y)
            return STAY;
        if(from.x == to.x && from.y < to.y)
            return E;
        if(from.x < to.x && from.y > to.y)
            return SW;
        if(from.x < to.x && from.y == to.y)
            return S;
        if(from.x < to.x && from.y < to.y)
            return SE;
        return STAY;
    }
    bool Game::isLegal(const ActionType&ac, const Position &pos) const {
        Surroundings s = this->getSurroundings(pos);
        bool valid = true;
        switch(ac){
            case NW:
                if(s.array[0] == INACCESSIBLE)
                    valid = false;
                break;
            case N:
                if(s.array[1] == INACCESSIBLE)
                    valid = false;
                break;
            case NE:
                if(s.array[2] == INACCESSIBLE)
                    valid = false;
                break;
            case W:
                if(s.array[3] == INACCESSIBLE)
                    valid = false;
                break;
            case STAY:
                valid = true;
                break;
            case E:
                if(s.array[5] == INACCESSIBLE)
                    valid = false;
                break;
            case SW:
                if(s.array[6] == INACCESSIBLE)
                    valid = false;
                break;
            case S:
                if(s.array[7] == INACCESSIBLE)
                    valid = false;
                break;
            case SE:
                if(s.array[8] == INACCESSIBLE)
                    valid = false;
                break;
            default :
                valid = false;
                break;
        }
        return valid;
    }
    const Position Game::move(const Position &pos, const ActionType &ac) const {
        int newX;
        int newY;

        switch(ac) {
            case NW:
                newX = static_cast<int>(pos.x) - 1;
                newY = static_cast<int>(pos.y) - 1;
                break;
            case N:
                newX = static_cast<int>(pos.x) - 1;
                newY = static_cast<int>(pos.y) - 0;
                break;
            case NE:
                newX = static_cast<int>(pos.x) - 1;
                newY = static_cast<int>(pos.y) + 1;
                break;
            case W:
                newX = static_cast<int>(pos.x) - 0;
                newY = static_cast<int>(pos.y) - 1;
                break;
            case STAY:
                return pos;
                break;
            case E:
                newX = static_cast<int>(pos.x) - 0;
                newY = static_cast<int>(pos.y) + 1;
                break;
            case SW:
                newX = static_cast<int>(pos.x) + 1;
                newY = static_cast<int>(pos.y) - 1;
                break;
            case S:
                newX = static_cast<int>(pos.x) + 1;
                newY = static_cast<int>(pos.y) - 0;
                break;
            case SE:
                newX = static_cast<int>(pos.x) + 1;
                newY = static_cast<int>(pos.y) + 1;
                break;
        }
        return Position(newX, newY);
    }

    void Game::round() {
        for(int i = 0; i < __width * __height; i++) {
            if (__grid[i] != nullptr && !(__grid[i]->isViable())){
                delete __grid[i];
                __grid[i] = nullptr;
            } else if (__grid[i] != nullptr && !(__grid[i]->getTurned())) {
                __grid[i]->setPosition(move(__grid[i]->getPosition(), __grid[i]->takeTurn(getSurroundings(__grid[i]->getPosition()))));
                __grid[i]->setTurned(true);
                if(__grid[i]->isViable()) {
                    Position newPos = __grid[i]->getPosition();
                    __grid[newPos.x * __width + newPos.y] = __grid[i];
                    __grid[i] = nullptr;
                }

            }
        }
        for(int i = 0; i < __width * __height; i++) {
            if(__grid[i] != nullptr){
                if(__grid[i]->isViable()){
                    __grid[i]->age();
                    __grid[i]->setTurned(false);
                    if(!(__grid[i]->isViable())){
                        delete __grid[i];
                        __grid[i] = nullptr;
                    }
                }
            }
        }
        __round++;
    }
    void Game::play(bool verbose) {
        __status = PLAYING;
        while(__status != OVER){
            if(verbose)
                std::cout << *this;
            round();
            if(getNumResources() == 0)
                __status = OVER;
        }
        if (verbose)
            std::cout << *this;
    }



    std::ostream &operator<<(std::ostream &os, const Game &game) {
        std::cout << std::endl;
        os << "Round " << game.__round << ":" << std::endl;
        for (int i = 0; i < game.__height; i++) {
            for (int j = 0; j < game.__width; j++) {
                if(game.__grid[(i * game.__width) + j] == nullptr){
                    os << "[" << std::setw(5) << " " << "]";
                }
                else {
                    std::stringstream ss;
                    ss << *(game.__grid[(i * game.__width) + j]);
                    std::string s;
                    getline(ss, s);
                    os << "[" << std::left << std::setw(5) << s << "]";
                }
            }
            os << std::endl;
        }
        std::string s = "";
        switch (game.__status) {
            case(Game::NOT_STARTED) :
                s = "NOT_STARTED";
                break;
            case(Game::PLAYING):
                s = "Playing...";
                break;
            case(Game::OVER):
                s = "Over!";
                break;
            default:
                s = "UNDEF";
                break;
        }
        os << "Status: " << s << std::endl;
        return os;
    }

}
