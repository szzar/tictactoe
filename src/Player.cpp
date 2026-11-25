#include "Player.h"

Player::Player(){
    name_ = "Player";
    wins_ = 0;
    losses_ = 0;
    draws_ = 0;
}

Player::Player(const std::string& name){
    name_ = name;
    wins_ = 0;
    losses_ = 0;
    draws_ = 0;
}

const std::string& Player::getName() const{
    return name_;
}

int Player::getWins() const{
    return wins_;
}

int Player::getLosses() const{
    return losses_;
}

int Player::getDraws() const{
    return draws_;
}

void Player::setName(const std::string& name){
    name_ = name;
}

void Player::addWin(){
    ++wins_;
}

void Player::addLoss(){
    ++losses_;
}

void Player::addDraw(){
    ++draws_;
}

bool Player::operator==(const Player& other) const{
    return name_ == other.name_;
}
