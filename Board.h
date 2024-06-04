#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <vector>
#include <iostream>
using namespace std;

const string YELLOW_COLOR = "\033[1;33m";
const string RESET_COLOR = "\033[0m";
const string WHITE_COLOR =  "\033[37m";
const string BLUE_COLOR = "\033[1;34m";
const string RED_COLOR =  "\033[1;31m";
const string GREEN_COLOR = "\033[1;32m";

using namespace std;

class Board {
private:
    int rows = 10;                  //Số hàng của bảng
    int columns = 10;               //Số cột của bảng
    vector<vector<char>> point;     //Vector 2 chiều
    
public:
    int getRows();                                  //Trả về số hàng của bảng
    int getColumns();                               //Trả về số cột của bảng
    void setPoint(vector<vector<char>>& _point);    //Thiết lập ma trận 
    vector<vector<char>>& getPoint();               //Trả về ma trận
    void plotBoard();                               //Hàm vẽ bảng
    void plotCaro();                                //Hàm thiết lập lại bảng cho người
    void plotCaroBot();                             //Hàm thiết lập lại bảng cho bot
};

#endif
