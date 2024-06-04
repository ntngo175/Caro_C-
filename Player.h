#ifndef PLAYER_H
#define PLAYER_H

#include<string>
using namespace std;

class Player{
private:
    string name;
    int countWin = 0;
    int countDraw = 0;
    int countLose = 0;
public:
    //Hàm tạo và hàm hủy
    Player() = default; //Tương tự Player() {}; nhưng ngắn gọn hơn
    ~Player() = default;

    void set(string _name, int _countWin, int _countDraw, int _countLose);  //Hàm set các thuộc tính
    int getWin() const;             //Hàm trả về countWin
    int getDraw() const;            //Hàm trả về countDraw
    int getLose() const;            //Hàm trả về countLose
    void setName(string _name);     //Hàm set name
    string getName() const;         //Hàm trả về tên
};


#endif