// tic tac toe game
// Player vs Player
#include<iostream>
#include<conio.h>
#include<iomanip>
#include<string>
using namespace std;

class ticTacToe {
	char board[3][3];
	char turn;
public:
	ticTacToe() {
		turn = 'X';
		for(int i = 0; i < 3; i++) {
			for(int j = 0; j < 3; j++) {
				board[i][j] = ' ';
			}
		}
	}

	char getTurn(){
		return turn;
	}

	bool switchTurn()  {
		if(turn == 'X') {
			turn = 'O';
		} else if(turn == 'O') {
			turn = 'X';
		} else {
			return 0;
		}
		return 1;
	}

	bool fillLocation(int p,int q) {
		if(board[p][q] == ' ') {
			board[p][q] = turn;
			return 1;
		} else {
			cout<<"\n  Invalid Location! Try again.\n"<<endl;
			return 0;
		}
	}

	bool checkForWin() {
		int win = 0;

		//Horizontal Check
		for(int i = 0; i < 3; i++) {
			for(int j = 0; j < 3; j++) {
				if(board[i][j] == turn)
					win++;
			}
			if(win == 3) return 1;
			win = 0;
		}

		//Vertical Check
		for(int i = 0; i < 3; i++) {
			for(int j = 0; j < 3; j++) {
				if(board[j][i] == turn)
					win++;
			}
			if(win == 3) return 1;
			win = 0;
		}

		//Back Diagonal Check
		for(int i = 0,j = 0; i<3; i++,j++)
			if(board[i][j] == turn) win++;
		if(win == 3) return 1;
		
		win = 0;
		
		//Front Diagonal Check
		for(int i = 0,j = 2; i<3; i++,j--)
			if(board[i][j] == turn) win++;
		if(win == 3) return 1;

		return 0;
	}

	bool boardFull() {
		for(int i = 0; i < 3; i++) {
			for(int j = 0; j < 3; j++) {
				if(board[i][j] == ' ')
					return 0;
			}
		}
		return 1;
	}

	void displayBoard() {
		int w =20;
		cout<<endl;
		for(int i = 0; i < 3; i++) {
			cout<<setw(w);
			for(int j = 0; j < 3; j++) {
				cout<<board[i][j];
				if(j<2)
					cout<<"|";
			}
			cout<<endl<<setw(w);
			if(i<2) {
				for(int j = 0; j < 3; j++) {
					cout<<"-";
					if(j<2)
						cout<<"+";
				}
				cout<<endl;
			}
		}
		cout<<endl;
	}

};

void main() {
	ticTacToe ttt;
	string player1,player2;
	char p1,p2,ct;
	int c1,c2;
	cout<<"\n\t\t\t\tTic Tac Toe\n"<<endl;
	cout<<"  Player 1 name : ";
	cin>>player1;
	cout<<"\n  Player 2 name : ";
	cin>>player2;
	cout<<"\n  'X' playes first.\n  "<<player1<<" playes : ";
	while(p1 = getch()){
		if(p1 == 'X' || p1 == 'O') {
			cout<<p1;
			if(p1 == 'X')
				p2 = 'O';
			else
				p2 = 'X';
			break;
		}
		
	}
	
	cout<<"\n\n  Start : ";
	while(ct = ttt.getTurn()) {
		
		ttt.displayBoard();
		
		if(ct == p1) {
			cout<<"\n  "<<player1<<"'s turn, "<<p1<<endl;
		} else {
			cout<<"\n  "<<player2<<"'s turn, "<<p2<<endl;
		}
		do {
			cout<<"  Enter location (p,q) : (";
			while(ct = getch()) {
				c1 = ct - 48;
				if(c1 < 3 && c1 >= 0) {
					cout<<c1<<",";
					break;
				}
			}
			while(ct = getch()) {
				c2 = ct - 48;
				if(c2 < 3 && c2 >= 0) {
					cout<<c2<<")"<<endl;
					break;
				}
			}
		}while(!ttt.fillLocation(c1,c2));
		
		if(ttt.checkForWin()) {
			ttt.displayBoard();
			if(ttt.getTurn() == p1) {
				cout<<player1<<" Wins!"<<endl;
			} else {
				cout<<player2<<" Wins!"<<endl;
			}
			break;
		} else if(ttt.boardFull()) {
			ttt.displayBoard();
			cout<<"  It's a Draw !";
			break;
		}
		ttt.switchTurn();
	}
	cout<<"\n  ";
	getch();
}
