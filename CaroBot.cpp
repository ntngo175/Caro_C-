#include "CaroBot.h"

int evaluateLine(char a, char b, char c, char d, char player) {
    int score = 0;
    char opponent = (player == 'X') ? 'O' : 'X';

    // 4 ô
    if (a == player && b == player && c == player && d == player) {
        score += 500;
    } else if (a == opponent && b == opponent && c == opponent && d == opponent) {
        score -= 500;
    }
    
    // 3 ô cùng 1 hàng có khoảng trống ở giữa
    if ((a == player && b == player && c == player && d == ' ') ||
        (a == ' ' && b == player && c == player && d == player) ||
        (a == player && b == ' ' && c == player && d == player) ) {
        score += 10;
    } else if ((a == opponent && b == opponent && c == opponent && d == ' ') ||
               (a == ' ' && b == opponent && c == opponent && d == opponent) ||
               (a == opponent && b == ' ' && c == opponent && d == opponent)) {
        score -= 10;
    }

    // 2 ô có khoảng trống
    if ((a == player && b == player && c == ' ' && d == ' ') ||
        (a == ' ' && b == player && c == player && d == ' ') ||
        (a == ' ' && b == ' ' && c == player && d == player)) {
        score += 5;
    } else if ((a == opponent && b == opponent && c == ' ' && d == ' ') ||
               (a == ' ' && b == opponent && c == opponent && d == ' ') ||
               (a == ' ' && b == ' ' && c == opponent && d == opponent)) {
        score -= 5;
    }

    if ((a == opponent && b == ' ' && c == opponent && d == ' ')) {
        score -= 20;
    }
    if ((a == opponent && b == opponent && c == ' ' && d == opponent)) {
        score -= 50;
    }
    return score;
}


/*
int evaluateLine(char a, char b, char c, char d, char player) {
    int score = 0;
    char opponent = (player == 'X') ? 'O' : 'X';

    // Đếm số lượng các ô của người chơi và đối thủ
    int playerCount = (a == player) + (b == player) + (c == player) + (d == player);
    int opponentCount = (a == opponent) + (b == opponent) + (c == opponent) + (d == opponent);
    int emptyCount = (a == ' ') + (b == ' ') + (c == ' ') + (d == ' ');

    // Trường hợp 4 ô của người chơi
    if (playerCount == 4) {
        score += 1000;
    }
    // Trường hợp 3 ô của người chơi và 1 ô trống
    else if (playerCount == 3 && emptyCount == 1) {
        score += 100;
    }
    // Trường hợp 2 ô của người chơi và 2 ô trống
    else if (playerCount == 2 && emptyCount == 2) {
        score += 10;
    }
    // Trường hợp 1 ô của người chơi và 3 ô trống
    else if (playerCount == 1 && emptyCount == 3) {
        score += 1;
    }
    // Trường hợp 2 ô của người chơi với khoảng trống ở giữa
    else if ((a == player && b == ' ' && c == player && d == ' ') ||
             (a == ' ' && b == player && c == ' ' && d == player)) {
        score += 5;
    }
    // Trường hợp 3 ô của người chơi với khoảng trống ở giữa
    else if ((a == player && b == player && c == ' ' && d == player) ||
             (a == player && b == ' ' && c == player && d == player)) {
        score += 90;
    }

    // Trường hợp 4 ô của đối thủ
    if (opponentCount == 4) {
        score -= 1000;
    }
    // Trường hợp 3 ô của đối thủ và 1 ô trống
    else if (opponentCount == 3 && emptyCount == 1) {
        score -= 100;
    }
    // Trường hợp 2 ô của đối thủ và 2 ô trống
    else if (opponentCount == 2 && emptyCount == 2) {
        score -= 10;
    }
    // Trường hợp 1 ô của đối thủ và 3 ô trống
    else if (opponentCount == 1 && emptyCount == 3) {
        score -= 1;
    }
    // Trường hợp 2 ô của đối thủ với khoảng trống ở giữa
    else if ((a == opponent && b == ' ' && c == opponent && d == ' ') ||
             (a == ' ' && b == opponent && c == ' ' && d == opponent)) {
        score -= 5;
    }
    // Trường hợp 3 ô của đối thủ với khoảng trống ở giữa
    else if ((a == opponent && b == opponent && c == ' ' && d == opponent) ||
             (a == opponent && b == ' ' && c == opponent && d == opponent)) {
        score -= 90;
    }

    return score;
}
 */

int CaroBot::evaluateBoard(Board& board, char player) {
    int score = 0;
    int rows = board.getRows();
    int columns = board.getColumns();

    // Đánh giá các hàng
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j <= columns - 4; j++) {
            score += evaluateLine(board.getPoint()[i][j], 
                                  board.getPoint()[i][j + 1], 
                                  board.getPoint()[i][j + 2], 
                                  board.getPoint()[i][j + 3], 
                                  player);
        }
    }

    // Đánh giá các cột
    for (int i = 0; i <= rows - 4; i++) {
        for (int j = 0; j < columns; j++) {
            score += evaluateLine(board.getPoint()[i][j], 
                                  board.getPoint()[i + 1][j], 
                                  board.getPoint()[i + 2][j], 
                                  board.getPoint()[i + 3][j], 
                                  player);
        }
    }

    // Đánh giá các đường chéo từ trái sang phải (\)
    for (int i = 0; i <= rows - 4; i++) {
        for (int j = 0; j <= columns - 4; j++) {
            score += evaluateLine(board.getPoint()[i][j], 
                                  board.getPoint()[i + 1][j + 1], 
                                  board.getPoint()[i + 2][j + 2], 
                                  board.getPoint()[i + 3][j + 3], 
                                  player);
        }
    }

    // Đánh giá các đường chéo từ phải sang trái (/)
    for (int i = 0; i <= rows - 4; i++) {
        for (int j = 3; j < columns; j++) {
            score += evaluateLine(board.getPoint()[i][j], 
                                  board.getPoint()[i + 1][j - 1], 
                                  board.getPoint()[i + 2][j - 2], 
                                  board.getPoint()[i + 3][j - 3], 
                                  player);
        }
    }

    return score;
}



//Hàm tạo hash cho bảng hiện tại
string CaroBot::boardHash(Board& board) {
    string hash;
    for (int i = 0; i < board.getRows(); i++) {
        for (int j = 0; j < board.getColumns(); j++) {
            hash += board.getPoint()[i][j];
        }
    }
    return hash;
}

int CaroBot::minimax(Board& board, int depth, bool isMax, char player, int alpha, int beta, TranspositionTable& table) {
    char opponent = (player == 'X') ? 'O' : 'X';
    string hash = boardHash(board);

    // Kiểm tra nếu trạng thái đã được lưu trong bảng tra cứu
    if (table.find(hash) != table.end()) {
        return table[hash];
    }

    int score = evaluateBoard(board, player);
    
    //Nếu đạt được trạng thái thắng hoặc hòa, trả về điểm số
    if (score == INT_MIN || score == INT_MAX) {
        table[hash] = score;
        return score;
    }

    bool draw = false;
    if (depth == 0 || match.checkWin(draw)) {
        table[hash] = score;
        return score;
    }
    
    if (isMax) {
        int best = -10000;
        for (int i = 0; i < board.getRows(); i++) {
            for (int j = 0; j < board.getColumns(); j++) {
                if (board.getPoint()[i][j] == ' ') {
                    Board newBoard = board; // Tạo một bản sao của bảng
                    newBoard.getPoint()[i][j] = player; // Thử nghiệm nước đi mới
                    best = max(best, minimax(newBoard, depth - 1, !isMax, player, alpha, beta, table));
                    alpha = max(alpha, best);
                    if (beta <= alpha) {
                        table[hash] = best;
                        // return best; // Cắt nhánh
                        break;
                    }
                }
            }
        }
        table[hash] = best;
        return best;
    } else {
        int best = 10000;
        for (int i = 0; i < board.getRows(); i++) {
            for (int j = 0; j < board.getColumns(); j++) {
                if (board.getPoint()[i][j] == ' ') {
                    Board newBoard = board; // Tạo một bản sao của bảng
                    newBoard.getPoint()[i][j] = opponent; // Thử nghiệm nước đi mới
                    best = min(best, minimax(newBoard, depth - 1, !isMax, player, alpha, beta, table));
                    beta = min(beta, best);
                    if (beta <= alpha) {
                        table[hash] = best;
                        // return best; // Cắt nhánh
                        break;
                    }
                }
            }
        }
        table[hash] = best;
        return best;
    }
}

// Hàm tìm nước đi tốt nhất dựa trên thuật toán minimax
pair<int, int> CaroBot::findBestMove(int depth) {
    int bestVal = -1000;
    pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < match.getBoard().getRows(); i++) {
        for (int j = 0; j < match.getBoard().getColumns(); j++) {
            if (match.getBoard().getPoint()[i][j] == ' ') {
                // Check xung quanh ô đã được đánh dấu
                bool isAdjacent = false;
                for (int di = -1; di <= 1; di++) {
                    for (int dj = -1; dj <= 1; dj++) {
                        int ni = i + di;
                        int nj = j + dj;
                        if (ni >= 0 && ni < match.getBoard().getRows() &&
                            nj >= 0 && nj < match.getBoard().getColumns() &&
                            match.getBoard().getPoint()[ni][nj] != ' ') {
                            isAdjacent = true;
                            break;
                        }
                    }
                }
                if (isAdjacent) {
                    Board newBoard = match.getBoard(); // Tạo một bản sao của bảng
                    newBoard.getPoint()[i][j] = 'O'; // Thử nghiệm nước đi mới
                    
                    // Tính toán giá trị hash của trạng thái bảng
                    string boardHash = this->boardHash(newBoard);
                    int moveVal = minimax(newBoard, depth, false, 'O', -1000, 1000, transpositionTable);

                    // Lưu giá trị nước đi vào bảng tra cứu sử dụng hash của trạng thái bảng
                    transpositionTable[boardHash] = moveVal;

                    if (moveVal > bestVal) {
                        bestMove = {i, j};
                        bestVal = moveVal;
                    }
                }
            }
        }
    }
    return bestMove;
}


