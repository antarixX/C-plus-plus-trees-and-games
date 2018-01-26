#include<iostream>
#include<conio.h>
#include<iomanip>
using namespace std;

struct rBank {
 int mis;
 int can;
};

class game {
	rBank b1;
	rBank b2;
	int boatCap;
	int bank;
public:
	game() {
		b1.can = 3;
		b1.mis = 3;
		b2.can = 0;
		b2.mis = 0;
		boatCap = 0;
		bank = 1;
	}

	int getBank() {
		return bank;
	}

	void switchBank() {
		if(bank == 1)
			bank = 2;
		else
			bank = 1;
	}

	bool bank1To2(int m,int c) {
		if((m > b1.mis) || (c > b1.can)) {
			cout<<"\n\n  Invalid move!"<<endl;
			return 0;
		}
		boatCap = m + c;
		if(boatCap > 2) {
			cout<<"\n\n  At max only two beings can be in the boat!"<<endl;
			return 0;
		} else if(boatCap == 0) {
			cout<<"\n\n  Boat requires one being to sail!"<<endl;
			return 0;
		}
		b1.mis = b1.mis - m;
		b1.can = b1.can - c;
		b2.mis = b2.mis + m;
		b2.can = b2.can + c;
		boatCap = 0;
		switchBank();
		return 1;
	}

	bool bank2To1(int m,int c) {
		if((m > b2.mis) || (c > b2.can)) {
			cout<<"\n\n  Invalid move!"<<endl;
			return 0;
		}
		boatCap = m + c;
		if(boatCap > 2) {
			cout<<"\n\n  At max only two beings can be in the boat!"<<endl;
			return 0;
		} else if(boatCap == 0) {
			cout<<"\n\n  Boat requires one being to sail!"<<endl;
			return 0;
		}
		b2.mis = b2.mis - m;
		b2.can = b2.can - c;
		b1.mis = b1.mis + m;
		b1.can = b1.can + c;
		boatCap = 0;
		switchBank();
		return 1;
	}

	bool safeState() {
		if((b1.mis!=0 && b1.can > b1.mis) || (b2.mis!=0 && b2.can > b2.mis))
			return 0;
		else
			return 1;
	}

	bool checkWin() {
		if(b2.can == 3 && b2.mis ==3)
			return 1;
		else
			return 0;
	}

	void display() {
		cout<<endl<<endl<<setw(10);
		//left river bank
		for(int i = 0; i < 3; i++) {
			if(i < b1.can)
				cout<<"C ";
			else
				cout<<"  ";
		}
		for(int i = 0; i < 3; i++){
			if(i < b1.mis)
				cout<<"M ";
			else
				cout<<"  ";
		}

		for(int i=0; i<22; i++)
			cout<<" ";
		//right river bank
		for(int i = 0; i < 3; i++) {
			if(i < b2.mis)
				cout<<"M ";
			else
				cout<<"  ";
		}
		for(int i = 0; i < 3; i++) {
			if(i < b2.can)
				cout<<"C ";
			else
				cout<<"  ";
		}
		cout<<endl<<setw(10);
		for(int i = 0; i < 6 ;i++)
			cout<<"--";
		if(bank == 1) {
			cout<<".\\____/             .";	
		} else {
			cout<<".             \\____/.";
		}

		for(int i = 0; i < 6 ;i++)
			cout<<"--";

		cout<<endl<<setw(10);
		for(int i = 0; i < 6 ;i++)
			cout<<"  ";
		for(int i = 0; i < 21; i++)
			cout<<"~";
		cout<<endl;
	}
};

void main() {
	game G;
	char c;
	int ms,cb,moves=0;
	cout<<"\n\t\t   MISSIONARIES & CANNIBALS\n"<<endl;
	cout<<"  Get Everyone safely to the other side.\n  On any side the number of C's should not exceed the number of M's.\n  Provided atleast one M is present on that side.\n"<<endl;
	cout<<"  Scene : ";
	G.display();
	do {
		cout<<"\n  Missionaries : ";
		while(c = getch()) {
			ms = c - 48;
			if((ms <= 2) && (ms >= 0)) {
				cout<<c;
				break;
			}
		}
		cout<<"  Cannibals : ";
		while(c = getch()) {
			cb = c - 48;
			if((cb <= 2) && (cb >= 0)) {
				cout<<c;
				break;
			}
		}
		moves++;
		if(G.getBank() == 1) {
			if(!G.bank1To2(ms,cb))
				continue;
			}
		else if(G.getBank() == 2) {
			if(!G.bank2To1(ms,cb))
				continue;
		}
		G.display();
		if(G.safeState()) {
			if(G.checkWin()) {
				cout<<"\n  You Win! It took you "<<moves<<" moves.\n  ";
				break;
			}
		} else {
			cout<<"\n  The Cannibals have eaten some Missionaries! You have failed!\n  ";
			break;
		}
	}while(1);
	getch();
}
