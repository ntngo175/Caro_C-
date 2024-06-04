#include "Controller.h"

void Controller::controllerPerson() {
    Data data("players.txt");
    int resetGame; 
    while (!isGameOver) {
        // Xóa màn hình console
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        cout << RED_TEXT << "   Player 1:" << RESET_COLOR << " X - " << RED_TEXT << "Player 2/Bot:" << RESET_COLOR <<" O"<<endl;
        m.getBoard().plotBoard(); //Vẽ bản hiện tại
        m.updatePerson(); //Update nước đi tiếp theo

        isGameOver = m.checkWin(draw);  //Check điều kiện chiến thắng

        if (isGameOver) {
            // Xóa màn hình console
            #ifdef _WIN32
                system("cls");
            #else
                system("clear");
            #endif

            m.getBoard().plotBoard(); //Vẽ lại bảng để hiển thị bước đi cuối cùng
            if (draw) {
                cout << "GAME DRAW";
                data.updatePlayerStats(m.getPlayer1().getName(), 0, 1, 0);
                data.updatePlayerStats(m.getPlayer2().getName(), 0, 1, 0);
            } else {
                if (m.getID() == 2) { // Player 1 wins
                    cout << "Player 1 " << m.getPlayer1().getName() << " win" << endl;
                    data.updatePlayerStats(m.getPlayer1().getName(), 1, 0, 0);
                    data.updatePlayerStats(m.getPlayer2().getName(), 0, 0, 1);
                } else { // Player 2 wins
                    cout << "Player 2 " << m.getPlayer2().getName() << " win" << endl;
                    data.updatePlayerStats(m.getPlayer2().getName(), 1, 0, 0);
                    data.updatePlayerStats(m.getPlayer1().getName(), 0, 0, 1);
                }
                cout << "Do you want to reset the game?" << endl;
                cout << "1. Yes" << endl;
                cout << "2. No" << endl;
                cin >> resetGame;
                switch (resetGame) {
                    case 1:
                        m.getBoard().plotCaro(); // Reset bảng về trạng thái ban đầu
                        isGameOver = false; // Đặt lại trạng thái trận đấu
                        break;
                    case 2:
                        break;
                    default:
                        cout << "Invalid choice. Please enter again." << endl;
                        break;
                }
            }
        }
    }
}

//Hàm điều khiển bot đấu với player
void Controller::controllerWithBot(int depth) {
    while (!isGameOver) {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        cout << RED_TEXT << "   Player 1:" << RESET_COLOR << " X - " << RED_TEXT << "Player 2/Bot:" << RESET_COLOR <<" O"<<endl;
        m.getBoard().plotBoard();
        
        m.updateBot(depth);

        isGameOver = m.checkWin(draw);
        if (isGameOver) {
            #ifdef _WIN32
                system("cls");
            #else
                system("clear");
            #endif
            m.getBoard().plotBoard();
            if (draw) {
                cout << "GAME DRAW";
            } else {
                // cout << "Player " << (m.getID() - 1) << "" << m.getNAME() << " is winner" << endl;
                if (m.getID() == 2) {
                    cout << "Player " << (m.getID() - 1) << " " << m.getPlayer1().getName() << " is winner" << endl;
                } else {
                    cout << "Bot win" << endl;
                }
            }
            return;
        }
    }
}

void Controller::searchPlayer() {
    Data data("players.txt");
    string playerName;
    cout << "Enter player name: ";
    cin >> playerName;

    Player player = data.findPlayerByName(playerName);
    if (player.getName() == "Not Found") {
        cout << "Player not found." << endl;
        return;
    }

    // In thông tin của người chơi
    cout << "Name: " << player.getName() << endl;
    cout << "Wins: " << player.getWin() << endl;
    cout << "Draws: " << player.getDraw() << endl;
    cout << "Loses: " << player.getLose() << endl;

    // Tìm và in ra những người chơi có cùng cấp độ
    int level = player.getWin(); // Giả sử cấp độ được xác định bằng số trận thắng
    vector<Player> sameLevelPlayers = data.findPlayersByLevel(level);
    cout << "Players with the same level (" << level << " wins):" << endl;
    for (const auto& p : sameLevelPlayers) {
        if (p.getName() != player.getName()) { // Loại bỏ chính người chơi đang tìm kiếm
            cout << "Name: " << p.getName() << " Wins: " << p.getWin() << " Draws: " << p.getDraw() << " Loses: " << p.getLose() << endl;
        }
    }
}

void Controller::displayAllInf(){
    m.displayAllMatches();
}

void Controller::rewatchMatch() {
    int matchID;
    cout << "Enter the Match ID to rewatch: ";
    cin >> matchID;
    m.rewatchMatchByID(matchID);
}


Match& Controller::getMatch(){
        return m;
}