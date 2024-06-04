#include "Board.h"

//Định nghĩa hàm lấy cột và hàng
int Board::getRows() { return rows; }
int Board::getColumns() { return columns; }

//Hàm set point
void Board::setPoint(vector<vector< char>>& _point) {
	point = _point;
}

//Hàm get point
vector<vector< char>>& Board::getPoint() { return point; }


//Hàm in bảng ra console
void Board::plotBoard() {
    cout << "   0   1   2   3   4   5   6   7   8   9" << endl;
    cout << BLUE_COLOR;
    cout << " -----------------------------------------" << endl;
    for (int i = 0; i < rows; i++) {
        cout << RESET_COLOR;
        cout << i;
        for (int j = 0; j < columns; j++) {
        	cout << BLUE_COLOR;
            cout << "| ";
			cout << RESET_COLOR;
            if (point[i][j] == 'X') {
                cout << GREEN_COLOR << point[i][j];
            } else if (point[i][j] == 'O') {
                cout << YELLOW_COLOR << point[i][j];
            } else {
                cout << point[i][j];
            }
            cout << RESET_COLOR << " ";
        }
		cout<<BLUE_COLOR;
        cout << "|" << endl;
        cout << " -----------------------------------------" << endl;
		cout<<RESET_COLOR;
    }
    cout << RESET_COLOR;
}



//Set up các ô trong bảng là ô trống
void Board::plotCaro()
{
	point.resize(rows);
	for (int i = 0; i < rows; ++i)
		point.at(i).resize(columns);
	// Tạo ô trống để điền XO
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			point.at(i).at(j) = ' ';
		}
	}
}

void Board::plotCaroBot()
{
	point.resize(rows);
	for (int i = 0; i < rows; ++i)
		point.at(i).resize(columns);
	// Tạo ô trống để điền XO
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			point.at(i).at(j) = ' ';
		}
	}
	point.at(4).at(5) = 'O';
}



