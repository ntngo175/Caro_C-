#include "Match.h"

Match::Match() {
    bot = new CaroBot(*this); // Khởi tạo bot với đối tượng Match hiện tại
}
// Match::Match() {};

Match::~Match() {
    delete bot; // Giải phóng bộ nhớ khi đối tượng Match bị hủy
}

//Hàm gán giá trị cho board
void Match::setBoard(Board _board){
    board = _board;
}

//Hàm trả về board
Board& Match::getBoard(){
    return board;
}

//Hàm trả về tên
// string Match::getNAME() {
// 	return NAME;
// }

//Hàm trả về ID
int Match::getID() {
    return ID;
}

//Hàm trả về player1
Player& Match::getPlayer1() {
    return player1;
}

//Hàm trả về player2
Player& Match::getPlayer2() {
    return player2;
}

//Hàm kiểm tra ký tự trống trong bảng
bool Match::checkChar(vector<vector<char>> v, int row, int column){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            if(v[i][j] == ' '){
                return false;
            }
        }
    }
    return true;
}

//Hàm nhập thông tin player
void Match::enterPlayer(){
    set<int> existingIDs;  // Set để lưu các ID đã tồn tại
    ifstream inputFile("Replay.txt");
    string line;
    
    // Đọc tệp và lưu các ID đã tồn tại vào set
    while (getline(inputFile, line)) {
        size_t idPos = line.find("ID:");
        if (idPos != string::npos) {
            size_t spacePos = line.find(" ", idPos);
            int existingID = stoi(line.substr(idPos + 3, spacePos - (idPos + 3)));
            existingIDs.insert(existingID);
        }
    }
    inputFile.close();
    
    // Nhập ID và kiểm tra xem ID đã tồn tại chưa
    int matchID;
    while (true) {
        cout << "Select Match ID: ";
        cin >> matchID;
        
        if (existingIDs.find(matchID) != existingIDs.end()) {
            cout << "ID already exists. Please enter a different ID." << endl;
        } else {
            break;
        }
    }
    
    // Ghi thông tin vào tệp
    ofstream file("Replay.txt", ios::app);
    file << "ID:" << matchID << " ";
    string p1, p2;

    cout<<"Enter player 1: ";
    cin>>p1;
    file<<p1<<" ";
    player1.setName(p1);

    cout<<"Enter player 2: ";
    cin>>p2;
    file<<p2<<" "<<endl;
    player2.setName(p2);
}

void Match::updatePerson() {
    static bool isPlayerInfoWritten = false; // Biến cờ để kiểm tra thông tin người chơi đã được ghi hay chưa

    // Điều kiện để xác định người chơi 1 hay 2
    ID = (ID % 2) ? 1 : 2;

    char mark;
    string currentPlayerName;


    // Nếu ID = 1 thì người chơi 1 là X
    if (ID == 1) {
        mark = 'X';
        currentPlayerName = player1.getName();
    }
    // Nếu ID = 2 thì người chơi 2 là O
    else if (ID == 2) {
        mark = 'O';
        currentPlayerName = player2.getName();

    }

    int x, y;
    bool invalidInput = false;
    // Trong vòng lặp này, người chơi sẽ đánh vào ô, nếu ô đó trống, sẽ tiếp tục đánh tiếp ô khác cho đến khi hợp lệ
    do {
        if (invalidInput) {
            cout << "Invalid input! Please enter valid coordinates." << endl;
        }
        cout << "Player " << ID << " is " << currentPlayerName << " turn: ";
        cin >> x >> y;
        invalidInput = (x > board.getRows() - 1 || y > board.getColumns() - 1 || board.getPoint()[x][y] != ' ');
    } while (invalidInput);

    // Cập nhật bảng mới nhất
    if (board.getPoint()[x][y] == ' ') {
        if (mark == 'X') {
            cout << GREEN_COLOR;
        } else {
            cout << YELLOW_COLOR;
        }
        board.getPoint()[x][y] = mark;
        cout << RESET_COLOR;
    }
    // Ghi thông tin người chơi vào tệp một lần khi bắt đầu trò chơi
    ofstream file("Replay.txt", ios::app);
    cout<<"\n";
    // Ghi tên người chơi và tọa độ vào tệp
    file << currentPlayerName << " " << x << " " << y << endl;

    bool isGameOver = false;
    bool draw = false;
    isGameOver = checkWin(draw);
    if (isGameOver){
        if(draw){
            file << "Game draw"<<endl;
        }
        else{
            if(getID() == 1){
                file <<"Player 1 is "<<getPlayer1().getName() <<" win"<<endl;
            }else{
                file <<"Player 2 is "<<getPlayer2().getName() <<" win"<<endl;
            }
        }
    }
    file.close();

    // Chuyển người chơi
    ID++;
}

void Match::updateBot(int depth) {
    ID = (ID % 2) ? 1 : 2;
    
    if (ID % 2 == 1) {
        // Lượt của người chơi
        int x, y;
        do {
            cout << "Player " << ID << " is " << player1.getName() << " turn: ";
            cin >> x >> y;
        } while (x >= board.getRows() || y >= board.getColumns() || board.getPoint()[x][y] != ' ');

        board.getPoint()[x][y] = 'X';
        ID++;
    } else {
        if(depth == 0){
            // Lượt của bot
            cout<<"Bot...";
            auto [x, y] = bot->findBestMove(0);
            board.getPoint()[x][y] = 'O';
            ID++;
        }
        else if (depth == 2){
            // Lượt của bot
            cout<<"Bot...";
            auto [x, y] = bot->findBestMove(2);
            board.getPoint()[x][y] = 'O';
            ID++;
        }
        else if(depth == 3){
            // Lượt của bot
            cout<<"Bot OverThinking, Please wait...";
            auto [x, y] = bot->findBestMove(3);
            board.getPoint()[x][y] = 'O';
            ID++;
        }
    }
}


//Hàm kiểm tra điều kiện win
bool Match::checkWin(bool& _draw) {
    int rows = board.getRows();
    int columns = board.getColumns();

    // Kiểm tra chiến thắng theo hàng ngang
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j <= columns - 4; j++) {
            if (board.getPoint()[i][j] != ' ' &&
                board.getPoint()[i][j] == board.getPoint()[i][j + 1] &&
                board.getPoint()[i][j] == board.getPoint()[i][j + 2] &&
                board.getPoint()[i][j] == board.getPoint()[i][j + 3]) {
                return true;
            }
        }
    }

    // Kiểm tra chiến thắng theo hàng dọc
    for (int i = 0; i <= rows - 4; i++) {
        for (int j = 0; j < columns; j++) {
            if (board.getPoint()[i][j] != ' ' &&
                board.getPoint()[i][j] == board.getPoint()[i + 1][j] &&
                board.getPoint()[i][j] == board.getPoint()[i + 2][j] &&
                board.getPoint()[i][j] == board.getPoint()[i + 3][j]) {
                return true;
            }
        }
    }

    // Kiểm tra chiến thắng theo đường chéo chính
    for (int i = 0; i <= rows - 4; i++) {
        for (int j = 0; j <= columns - 4; j++) {
            if (board.getPoint()[i][j] != ' ' &&
                board.getPoint()[i][j] == board.getPoint()[i + 1][j + 1] &&
                board.getPoint()[i][j] == board.getPoint()[i + 2][j + 2] &&
                board.getPoint()[i][j] == board.getPoint()[i + 3][j + 3]) {
                return true;
            }
        }
    }

    // Kiểm tra chiến thắng theo đường chéo phụ
    for (int i = 0; i <= rows - 4; i++) {
        for (int j = 3; j < columns; j++) {
            if (board.getPoint()[i][j] != ' ' &&
                board.getPoint()[i][j] == board.getPoint()[i + 1][j - 1] &&
                board.getPoint()[i][j] == board.getPoint()[i + 2][j - 2] &&
                board.getPoint()[i][j] == board.getPoint()[i + 3][j - 3]) {
                return true;
            }
        }
    }

    // Kiểm tra trận đấu hòa
    if (checkChar(board.getPoint(), rows, columns)) {
        _draw = true;
        return true;
    }

    return false;
}


//Hàm xem lại trận đấu
void Match::rewatchMatchByID(int matchID) {
    ifstream file("Replay.txt");
    if (!file.is_open()) {
        cout << "Unable to open file." << endl;
        return;
    }

    string line;
    string idString = "ID:" + to_string(matchID) + " ";
    bool matchFound = false;
    vector<pair<string, pair<int, int>>> moves;
    string resultMessage;


    // Tìm trận đấu theo ID
    while (getline(file, line)) {
        if (line.find(idString) == 0) {  // Tìm matchID
            matchFound = true;
            break;
        }
    }
    /*
    // Đọc nước đi nếu tìm thấy trận đấu
    if (matchFound) {
        while (getline(file, line)) {
            if (line.find("ID:") == 0) {  // Nếu gặp dòng bắt đầu bằng "ID:", dừng lại
                break;
            }
            istringstream iss(line);
            string playerName;
            int x, y;
            if (iss >> playerName >> x >> y) {
                moves.push_back({playerName, {x, y}});
            } else {
                // Không phải dòng chứa tọa độ, bỏ qua
                continue;
            }
        }
    }
    */
   if (matchFound) {
        while (getline(file, line)) {
            if (line.find("ID:") == 0) {  // Nếu gặp dòng bắt đầu bằng "ID:", dừng lại
                break;
            }
            istringstream iss(line);
            string playerName;
            int x, y;
            if (iss >> playerName >> x >> y) {
                moves.push_back({playerName, {x, y}});
            } else if (line.find("Player") == 0) {
                resultMessage = line;
            } else {
                // Không phải dòng chứa tọa độ, bỏ qua
                continue;
            }
        }
    }

    file.close();

    if (!matchFound) {
        cout << "Match ID " << matchID << " not found." << endl;
        return;
    }

    board.plotCaro();  // Đặt trạng thái bảng về ban đầu
    char mark = 'X'; // Bắt đầu với X
    for (const auto& move : moves) {
        int x = move.second.first;
        int y = move.second.second;
        board.getPoint()[x][y] = mark;
        mark = (mark == 'X') ? 'O' : 'X';

        // Clear the console
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        board.plotBoard();
        
        // Nhấn Space để tiếp tục
        cout << "Press SPACE to continue..."<<endl;
        #ifdef _WIN32
            while (!_kbhit() || _getch() != 32); 
        #else
            while (getch() != ' ');
        #endif
    }
    cout << resultMessage << endl;
}

void Match::displayAllMatches() {
    ifstream file("Replay.txt");
    if (!file.is_open()) {
        cout << "Unable to open file." << endl;
        return;
    }

    string line;
    cout << "All Matches:" << endl;
    while (getline(file, line)) {
        if (line.find("ID:") == 0) {  // Nếu dòng bắt đầu bằng "ID:"
            cout << line << endl;  // Hiển thị dòng chứa ID và tên người chơi
        }
    }

    file.close();
}
