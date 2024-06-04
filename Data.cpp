#include "Data.h"
#include <fstream>
#include <sstream>


Data::Data() : filename("default.txt") {}  // Constructor mặc định gán giá trị mặc định cho filename


Data::Data(const string& fname) : filename(fname) {}

//Hàm lưu thông tin người chơi
void Data::savePlayer(const Player& player) {
    ofstream file(filename, ios::app);
    if (file.is_open()) {
        file << player.getName() << " " << player.getWin() << " " << player.getDraw() << " " << player.getLose() << endl;
        file.close();
    }
}

//Hàm load player
vector<Player> Data::loadPlayers() {
    ifstream file(filename);
    vector<Player> players;
    string line, name;
    int win, draw, lose;
    while (getline(file, line)) {
        // Sử dụng stringstream để phân tách dữ liệu trong mỗi dòng thành các thành phần riêng biệt
        stringstream ss(line);
        //Đọc thông tin
        ss >> name >> win >> draw >> lose;
        Player player;
        player.set(name, win, draw, lose);
        players.push_back(player);  //push player vào vector
    }
    file.close();
    return players;
}


//Định nghĩa hàm cập nhật thông tin người chơi để update số trận thắng, hòa, thua
void Data::updatePlayerStats(const string& name, int win, int draw, int lose) {
    vector<Player> players = loadPlayers(); //Tải thông tin player
    bool found = false;

    //Duyệt qua tất cả player, nếu có player trùng tên thì cập nhật
    for (auto& player : players) {
        if (player.getName() == name) {
            player.set(name, player.getWin() + win, player.getDraw() + draw, player.getLose() + lose);
            found = true;
            break;
        }
    }

    // Nếu không tìm thấy, push vào vector
    if (!found) {
        Player newPlayer;
        newPlayer.set(name, win, draw, lose);
        players.push_back(newPlayer);
    }

    //Ghi dữ liệu
    ofstream file(filename, ios::trunc);    //Mở tệp và xóa nội dung cũ nếu tệp đã có, sau đó cập nhật
    for (const auto& player : players) {
        file << player.getName() << " " << player.getWin() << " " << player.getDraw() << " " << player.getLose() << endl;
    }
    file.close();
}

//Hàm tìm player
Player Data::findPlayerByName(const string& name) {
    vector<Player> players = loadPlayers();
    //Nếu tìm thấy thì trả về player
    for (const auto& player : players) {
        if (player.getName() == name) {
            return player;
        }
    }
    // Nếu không tìm thấy, trả về một Player mặc định với thông báo lỗi
    Player notFound;
    notFound.set("Not Found", 0, 0, 0);
    return notFound;
}

//Hàm tìm người chơi có cùng đẳng cấp
vector<Player> Data::findPlayersByLevel(int level) {
    vector<Player> players = loadPlayers();
    vector<Player> result;  //Vector chứa những người cùng đẳng cấp
    for (const auto& player : players) {
        int playerLevel = player.getWin(); //Cấp độ được xác định bằng số trận thắng
        if (playerLevel == level) {
            result.push_back(player);
        }
    }
    return result;
}
