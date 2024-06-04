#ifndef MATCH_H
#define MATCH_H


#include "Board.h"
#include "Player.h"
#include "CaroBot.h"
#include "Data.h"
#include <set>
#include <fstream>
#include <conio.h>
// #include "CaroBot.h"
#include <iostream>
#include <sstream>
#include <thread>
using namespace std;

class CaroBot;

class Match{
private:
    CaroBot* bot;               //Con trỏ trỏ đến đối tượng CaroBot
    // Data dt;                   //Con trỏ trỏ đến đối tượng Data
    Board board;                //Khởi tạo bảng
    int matchID;
    Player player1, player2;    //Khởi tạo 2 player thuộc lớp Player
    int ID = 1;
    string NAME;
    bool isGameOver = false;
    bool draw = false;
    
public:
    Match();                       //Hàm tạo
    ~Match();                      //Hàm hủy
    // string getNAME();              //Hàm trả về NAME
    int getID();                   //Hàm trả về ID
    Player& getPlayer1() ;         //Hàm trả về player1
    Player& getPlayer2() ;         //Hàm trả về player2
    void setBoard(Board _board);   //Hàm gán giá trị board
    Board& getBoard();             //Hàm trả về board
    bool checkChar(vector<vector<char>> v, int row, int column);    //Hàm kiểm tra ký tự trống
    void updatePerson();           //Hàm điều khiển người
    bool checkWin(bool& draw);     //Hàm check win
    void enterPlayer();            //Hàm nhập player
    void updateBot(int depth);     //Hàm điều khiển bot
    void rewatchMatchByID(int matchID); //Hàm xem lại trận đấu
    void displayAllMatches();       //Hàm hiển thị tất cả các ID
};

#endif