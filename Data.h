#ifndef DATA_H
#define DATA_H

#include <string>
#include <vector>
#include "Player.h"
#include <iostream>
using namespace std;

class Data {
private:
    //Khai báo thuộc tính
    string filename;
    Player player;  //Đối tượng của Player

public:
    Data();  // Constructor mặc định
    Data(const string& fname);  //Hàm mặc định có tham số

    void savePlayer(const Player& player);          //Hàm lưu thông tin người chơi vào file
    vector<Player> loadPlayers();                   //Hàm load thông tin
    
    //Hàm cập nhật số trận thắng, hòa, thua
    void updatePlayerStats(const string& name, int win, int draw, int lose);
    Player findPlayerByName(const string& name);    //Hàm tìm người chơi theo tên
    vector<Player> findPlayersByLevel(int level);   //Hàm tìm người chơi theo cấp độ
};

#endif
