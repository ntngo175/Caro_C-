#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Match.h"
// #include "Data.h"
// #include "Player.h"
// #include "Board.h"
#include <iostream>
#include <string>

const string RED_TEXT = "\033[1;31m";
#ifndef RESET_COLOR
#define RESET_COLOR "\033[0m"   //Tránh việc định nghĩa lại không hợp lệ
#endif

using namespace std;

class Controller{
private:
    // Data d;                     //Tạo đối tượng thuộc Data
    Match m;                    //Tạo đói tượng thuộc Match
    // Board board;                //Tạo đối tượng thuộc Board
    bool isGameOver = false;
    bool draw = false;
    int botLevel;
    bool resetGame = false;

public:
    void controllerPerson();                //Hàm điều khiển trò chơi giữa 2 người với nhau
    void controllerWithBot(int depth);      //Hàm điều khiển trò chơi giữa người và bot
    void searchPlayer();                    //Hàm tìm người chơi
    Match& getMatch();                      //Hàm trả về đối tượng Match
    void rewatchMatch();                    //Hàm xem lại trận đấu
    void displayAllInf();                   //Hàm hiển thị tất cả ID, tên player của tất cả các trận đấu
};

#endif