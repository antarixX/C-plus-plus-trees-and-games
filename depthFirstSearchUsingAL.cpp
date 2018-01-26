// Program to simulate Deapth first search
// Data structure: adjacency list
#include<iostream>
#include<conio.h>
using namespace std;

struct childNode {
	struct parentNode*pList;		//link to a child node i.e. a node in the parent list
	struct childNode*nChild;	//link to the next child
};

struct parentNode {
	char nd;					//alphabet in node
	bool ck;					//traversal check
	struct parentNode*next;		//next node in parent list
	struct childNode*child;		//child node of current parent node
};

struct listNode {
	char value;		//link to a child node i.e. a node in the parent list
	struct listNode*next;	//link to the next child
};

//pre declarations
bool isAlphabet(char);
bool checkPrevious(parentNode*,char);
void pushToStack(childNode**,parentNode*);
void popNodeFromStack(childNode**);
bool checkGoals(listNode*,char);

//Adjecency List
class adjList {
	struct parentNode*root;

public:
	adjList() {
		root = new(parentNode);
		root ->nd = NULL;
		root->ck=0;
		root ->next = NULL;
		root ->child = NULL;
	}

	void createList(char nAry) {
		parentNode *pTemp = root;
		childNode *cTemp = NULL;
		char val;
		cout<<"\n  Root Node : ";
		while(val = getch()) {
			if(isAlphabet(val)) {
				cout<<val;
				break;
			}
		}
		cout<<endl;
		pTemp -> nd = val;
		cout<<"\n  Enter child nodes one by one, press enter for next node"<<endl;
		while(pTemp != NULL) {
			cout<<"\n    "<<(pTemp -> nd)<<" : ";
			for(int i = 0; i<(nAry - 48);i++) {
				while(val = getch()) {
					if(isAlphabet(val) && checkPrevious(root,val)) {
						cout<<val<<" ";
						break;
					} else if(val == 13) {
						break;
					}
				}
				if(val != 13) {
					parentNode *pTrav = pTemp;
					parentNode *pNew = new(parentNode);
					childNode *cNew = new(childNode);
					pNew->nd = val;
					pNew->ck = 0;
					pNew ->next = NULL;
					pNew ->child = NULL;
					cNew->pList = pNew;
					cNew->nChild = NULL;
					while(pTrav ->next!=NULL) {	//travel to end of list
						pTrav = pTrav ->next;
					}
					pTrav ->next = pNew;		//connect to parent list
					if(pTemp->child == NULL) {
						pTemp ->child =cNew;	//connect child and parent
						cTemp = cNew;
					}else{
						cTemp->nChild = cNew;	//connect to child list
						cTemp = cNew;
					}
				} else {
					while(i<(nAry - 48)) {
						cout<<"- ";
						i++;
					}
					break;
				}
			}
			cout<<endl;
			pTemp = pTemp -> next;
		}
	}

	//Depth First Search
	void depthFirstSearch(listNode*gNodes) {
		childNode *tStk,*cTrav;
		parentNode *pTrav = root;
		char b=8;
		tStk = NULL;
		pushToStack(&tStk,pTrav);
		pTrav ->ck = 1;
		cout<<"\n  "<<pTrav->nd<<" ->";
		while(tStk != NULL) {
			if(checkGoals(gNodes,tStk ->pList->nd)) {
				cout<<b<<b<<"  ";
				cout<<"\n\n  Goal Node Reached.\n  ";
				return;
			} else {
				cTrav = tStk ->pList ->child;
				while(cTrav !=NULL && cTrav ->pList->ck == 1) {
					cTrav = cTrav->nChild;
				}
				if(cTrav == NULL) {
					popNodeFromStack(&tStk);
					continue;
				}
				pushToStack(&tStk,cTrav->pList);
				cout<<"  "<<cTrav -> pList -> nd<<" ->";
				cTrav ->pList ->ck = 1;
			}
		}
		cout<<b<<b<<"  ";
		cout<<"\n\n  Goal Node Not Found!\n  ";
	}
};

void pushToStack(childNode**top,parentNode*val) {
	childNode *addNode = new(childNode);
	addNode->nChild = NULL;
	addNode->pList = val;
	if(*top == NULL) {
		*top = addNode;
	}else{
		addNode ->nChild = (*top);
		(*top) = addNode;
	}
}

void popNodeFromStack(childNode**top) {
	if(*top!=NULL) {
		childNode *delNode = (*top);
		if((*top)->nChild == NULL) {
			(*top) = NULL;
		} else {
			(*top) = (*top) -> nChild;
		}
		delete(delNode);
	}
}

bool checkGoals(listNode*g,char c) {
	while(g != NULL && g->value != c) {
		g = g->next;
	}
	if(g == NULL) {
		return 0;
	} else if(g->value == c) {
		return 1;
	}
}

//Goal Nodes
void createGoalList(adjList tr,listNode**p) {
	char val;
	listNode *gTrav = *p;
	cout<<"\n  Goal Nodes : ";
	while(val = getch()) {
		if(isAlphabet(val)) {
			listNode* gNode = new(listNode);
			gNode->value=val;
			gNode->next=NULL;
			if(gTrav == NULL) {
				gTrav = gNode;
				*p = gNode;
			} else {
				while(gTrav->next != NULL) {
					gTrav = gTrav -> next;
				}
				gTrav->next = gNode;
			}
			cout<<val<<" ";
		}
		else if(val == 13) {
			break;
		}
	}
	cout<<endl;
}

//check previous values
bool checkPrevious(parentNode*ck,char c) {
	while(ck!=NULL) {
		if(ck ->nd == c)
			return 0;
		ck = ck->next;
	}
	return 1;
}

//check for a number
bool isNumber(char c) {
	if(c>=49 && c<=57)
		return 1;
	else
		return 0;
}

//check for a Caps alphabet
bool isAlphabet(char c) {
	if(c>=65 && c<=90)
		return 1;
	else
		return 0;
}

void main() {
	adjList tree;
	listNode *goals = NULL;
	char nAry;
	cout<<"\n\t\t\t\tDEPTH FIRST SEARCH\n\n";
	cout<<"  Enter the value for n : ";
	
	while(nAry=getch()) {
		if(isNumber(nAry)) {
			cout<<nAry<<" ary Tree."<<endl;
			break;
		}
	}
	tree.createList(nAry);
	createGoalList(tree,&goals);
	cout<<"\n  Deapth First Search :\n";
	tree.depthFirstSearch(goals);
	getch();
}
