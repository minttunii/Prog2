#include "player.hh"
#include <iostream>

namespace  {
    const int MOLKKY_WIN_SCORE = 50;
    const int MOLKKY_RESET_SCORE = 25;
}

Player::Player(const std::string &name):
    name_(name), score_(0){
}

const std::string& Player::get_name()
{
    return name_;
}

int Player::get_points()
{
    return score_;
}

bool Player::has_won()
{
    return score_ == MOLKKY_WIN_SCORE;
}

void Player::add_points(int points)
{
    score_ += points;
    if(score_ > MOLKKY_WIN_SCORE){
        score_ = MOLKKY_RESET_SCORE;
        std::cout << get_name() << " gets penalty points!" << std::endl;
    }
}
