#ifndef CAROBOT_H
#define CAROBOT_H

#include "Board.h"
#include "Player.h"
#include "Match.h"
#include <string> 
#include <utility>
#include <unordered_map>

class Match; // Khai báo forward cho Match

class CaroBot {
private:
    Match& match;   //Tham chiếu đến game đấu hiện tại
    Player player;  //Tạo 1 carobot là player
    // Định nghĩa một kiểu dữ liệu cho transposition table
    using TranspositionTable = unordered_map<string, int>;
    TranspositionTable transpositionTable; // Khai báo transpositionTable
    int depth;  //Độ sâu thuật toán minimax
public:
    CaroBot(Match& _match) : match(_match) {}           //Constructor có tham số  
    string boardHash(Board& board);                     //Tạo hash cho bảng hiện tại
    int evaluateBoard(Board& board, char player);       //Hàm đánh giá Heurictic
    //Thuật toán minimax
    int minimax(Board& board, int depth, bool isMax, char player, int alpha, int beta, TranspositionTable& table);
    pair<int, int> findBestMove(int depth);             //Tìm nước đi tốt nhất

};

#endif
