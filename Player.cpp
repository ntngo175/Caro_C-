#include "Player.h"


//Định nghĩa các hàm
void Player::set(string _name, int _countWin, int _countDraw, int _countLose){
    name = _name;
    countDraw = _countDraw;
    countWin = _countWin;
    countLose   = _countLose;
}

int Player::getWin() const{
    return countWin;
}

int Player::getDraw() const{
    return countDraw;
}

int Player::getLose() const{
    return countLose;
}

void Player::setName(string _name){
    name = _name;
}

string Player::getName() const{
    return name;
}

