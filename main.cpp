#include "Player.h"
#include "Match.h"
#include "Board.h"
#include "Controller.h"
#include "CaroBot.h"
#include "Data.h"

// Định nghĩa các mã màu ANSI
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

int main() {
    
    #if defined(_WIN32)
        system("chcp 65001");
    #endif

    int mainChoice, botChoice, resetChoice;
    bool quit = false;

    while (!quit) {
        cout << BLUE << "-----------------------" << RESET << endl;
        cout << GREEN << "Main Menu" <<RESET<< endl;
        cout << YELLOW << "Press number to choice:"<<RESET<< endl;
        cout << CYAN << "1. Play "<< RESET <<"with other player" << endl;
        cout << CYAN << "2. Play "<<RESET<<"with bot" << endl;
        cout << CYAN << "3. Replay" << RESET << endl;
        cout << CYAN << "4. Play's"<<RESET<<" Information" << endl;
        cout << CYAN << "5. Guild" << RESET << endl;
        cout << CYAN << "6. Exit" << RESET << endl;
        cout << BLUE << "-----------------------" << RESET << endl;
        cout<<"Enter choice:";
        cin >> mainChoice;

		string playerName;
		Controller c;
        Data data("players.txt");

        switch (mainChoice) {
            case 1:
                c.getMatch().enterPlayer(); // Nhập tên 2 người chơi
                c.getMatch().getBoard().plotCaro();
                c.controllerPerson();
                break;
            case 2:
                    cout <<GREEN <<"Play with bot" <<RESET<< endl;
                    cout <<YELLOW<<"Press number to choice:" <<RESET<< endl;
                    cout << "1."<<CYAN<<" Easy" <<RESET<< endl;
                    cout << "2."<<CYAN<<" Normal"<<RESET<< endl;
                    cout << "3."<<CYAN<<" Hard" <<RESET<< endl;
                    cout << "4."<<CYAN<<" Back" <<RESET<< endl;
                    cin >> botChoice;
                    if (botChoice == 1) {
                            // Code for playing with bot in Easy mode
                            cout << "Enter your name: ";
							cin >> playerName;
							c.getMatch().getPlayer1().setName(playerName);

							c.getMatch().getBoard().plotCaroBot(); 
							c.controllerWithBot(0);
                            }
                        else if(botChoice == 2){
                            cout << "Enter your name: ";
							cin >> playerName;
							c.getMatch().getPlayer1().setName(playerName); 

							c.getMatch().getBoard().plotCaroBot(); 
							c.controllerWithBot(2);
                        }
                        else if(botChoice == 3) {
							cout << "Enter your name: ";
							cin >> playerName;
							c.getMatch().getPlayer1().setName(playerName); 

							c.getMatch().getBoard().plotCaroBot(); 
							c.controllerWithBot(3);
                        }       
                break;
            case 3:
                c.displayAllInf();
                c.rewatchMatch();
                break;
            case 4:
                c.searchPlayer();
                break;
            case 5:
                // Code for guild
                cout << "Guide:" << endl;
                cout << "1. Cờ caro là trò chơi trên bảng kẻ ô vuông, thường có kích thước 10x10 ô." << endl;
                cout << "2. Người chơi có thể chọn chơi với người khác hoặc với bot." << endl;
                cout << "3. Luật chơi cơ bản: Hai người chơi lần lượt đánh dấu X hoặc O vào các ô trống trên bảng." << endl;
                cout << "4. Người chiến thắng là người đầu tiên có 4 quân cờ của mình nối liên tiếp theo hàng ngang, hàng dọc hoặc đường chéo." << endl;
                cout << "5. Hướng dẫn điều khiển:" << endl;
                cout << "Chọn tọa độ cần đánh theo thứ tự là số hàng - số cột, sau đó nhấn enter"<<endl;
                cout << "7. Chúc các bạn chơi vui vẻ và luôn thắng!" << endl;
                
                break;
            case 6:
                quit = true;
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please enter again." << endl;
        }
    }
    return 0;
}


