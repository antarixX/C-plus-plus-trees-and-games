// water jug problem 
#include<iostream>
#include<conio.h>
#include<iomanip>

using namespace std;

class waterJug{
	int threeJ;
	int fourJ;
public:
	waterJug() {
		threeJ = 0;
		fourJ = 0;
	}

	bool fillFourJ() {
		if(fourJ < 4) {
			fourJ = 4;
			return 1;
		}
		return 0;
	}

	bool fillThreeJ() {
		if(threeJ < 3) {
			threeJ = 3;
			return 1;
		}
		return 0;
	}

	bool emptyFourJ() {
		if(fourJ > 0) {
			fourJ = 0;
			return 1;
		}
		return 0;
	}

	bool emptyThreeJ() {
		if(threeJ > 0) {
			threeJ = 0;
			return 1;
		}
		return 0;
	}

	bool pourThreeInFour() {
		if(fourJ < 4) {
			while(fourJ != 4 && threeJ != 0) {
				fourJ++;
				threeJ--;
			}
			return 1;
		}
		cout<<"\n     Cannot transfer . . . "<<endl;
		return 0;
	}

	bool pourFourInThree() {
		if(threeJ < 3) {
			while(threeJ != 3 && fourJ != 0) {
				threeJ++;
				fourJ--;
			} 
			return 1;
		}
		cout<<"\n     Cannot transfer . . . "<<endl;
		return 0;
	}

	int checkFourJ() {
		return fourJ;
	}

	void displayJ() {
		int wd = 10,threef=0,fourf=0;
		cout<<"\n  "<<setw(22)<<"";
		
		if(fourJ == 4) {
			cout<<"|~~~~~|";
			fourf++;
		} else cout<<"|     |";
		
		cout<<endl;
		
		for(int i=3;i>0;i--) {
			cout<<setw(wd)<<"|";

			//contents of 3ltr
			if(threeJ > 0 && i <= threeJ) {
				
				if(threef == 0) {
					cout<<"~~~~~";
				} else {
					if(threef%2) cout<<"- - -";
					else cout<<" - - ";
				}
				threef++;
			}
			else
				cout<<"     "; 

			cout<<"|"<<setw(wd-2)<<""<<"|";

			//contents of 4ltr
			if(fourJ > 0 && i <= fourJ) {
				if(fourf == 0) {
					cout<<"~~~~~";
				} else {
					if(fourf%2) cout<<"- - -";
					else cout<<" - - ";
				}
				fourf++;
			}
			else
				cout<<"     "; 

			cout<<"|"<<endl;
		}
		cout<<setw(wd)<<""<<"-----"<<setw(wd)<<""<<"-----";
		cout<<"\n  "<<setw(wd)<<""<<"3L"<<setw(wd)<<""<<"   4L"<<endl;
	}

};

void main() {
	waterJug w;
	char act;
	int nact,moves = 0;
	cout<<"\n\t\tWATER JUG PROBLEM"<<endl;
	cout<<"\n  Get 2 liters of water in the 4L Jug."<<endl;
	w.displayJ();
	do {
		cout<<"\n  1.Fill Jug   2.Transfer  3.Empty Jug\n  ";
		while(act = getch()) {
			nact = act - 48;
			if(nact <= 3 && nact > 0) {
				break;
			}
		}
		switch(act) {
			case '1':
				cout<<"\n"<<setw(5)<<""<<"Fill ";
				while(act = getch()) {
					if(act == '3' || act == '4') {
						cout<<act<<" liter jug."<<endl;
						break;
					}
				}
				if(act == '3') { 
					if(!w.fillThreeJ()) {
						cout<<"\n     It's already filled . . . "<<endl;
						continue;
					}
				} else { 
					if(!w.fillFourJ()) {
						cout<<"\n     It's already filled . . . "<<endl;
						continue;
					}
				} 
				break;

			case '2':
				cout<<"\n"<<setw(5)<<""<<"Transfer from ";
				while(act = getch()) {
					if(act == '3' || act == '4') {
						cout<<act<<" liter to ";
						break;
					}
				}
				if(act == '3') {
					cout<<" 4 liter jug."<<endl;
					w.pourThreeInFour();
				} else {
					cout<<" 3 liter jug."<<endl;
					w.pourFourInThree();
				}
				break;
			case '3':
				cout<<"\n"<<setw(5)<<""<<"Empty ";
				while(act = getch()) {
					if(act == '3' || act == '4') {
						cout<<act<<"L jug."<<endl;
						break;
					}
				}
				if(act == '3') { 
					if(!w.emptyThreeJ()) {
						cout<<"\n     It's already empty . . . "<<endl;
						continue;
					}
				}
				else {
					if(!w.emptyFourJ()) {
						cout<<"\n     It's already empty . . . "<<endl;
						continue;
					}
				}
				break;
		}
		w.displayJ();
		moves ++;
	} while(w.checkFourJ() != 2);

	cout<<"\n     Success! You got 2 liters in 4L jug\n\n     It took you "<<moves<<" moves.\n  ";

	getch();
}
