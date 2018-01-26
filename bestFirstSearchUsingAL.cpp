// Program to simulate Best first search
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
	int hVal;					//huristic value
	struct parentNode*childOf;					//traversal check
	struct parentNode*next;		//next node in parent list
	struct childNode*child;		//child node of current parent node
};

struct listNode {
	char value;		//link to a child node i.e. a node in the parent list
	struct listNode*next;	//link to the next child
};

//pre declarations
bool isAlphabet(char);
bool isNumber(char);
void sortList(childNode **);
bool checkPrevious(parentNode*,char);
void addNodeToQueue(childNode**,childNode**,parentNode*);

//Adjecency List
class adjList {
	struct parentNode*root;
public:
	adjList() {
		root = new(parentNode);
		root ->nd = NULL;
		root ->next = NULL;
		root ->child = NULL;
		root ->childOf = NULL;
	}

	void createList(char nAry) {
		parentNode *pTemp = root;
		childNode *cTemp = NULL;
		int hv,cnt,nodes=0;
		char val;
		cout<<"\n  Root Node : ";
		while(val = getch()) {
			if(isAlphabet(val)) {
				cout<<val;
				break;
			}
		}
		pTemp -> nd = val;	
		pTemp -> hVal = 0;
		cout<<endl<<"\n  Enter huristic values follllowed by child nodes, press enter for next node"<<endl;
		while(pTemp != NULL) {
			cout<<"\n    "<<(pTemp -> nd)<<"(";
			if(nodes!=0) {
				cnt=0;
				while((val=getch())!=13 || cnt==0){
					if(isNumber(val)){
						if(cnt==0){
							hv=val-48;
							cnt++;
						} else {
							hv=hv*10;
							hv=hv+(val-48);
						}
						cout<<val;
					}
				}
				pTemp ->hVal=hv;
				hv=0;
			} else {
				cout<<"root";
			}
			cout<<") : ";
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
					pNew ->next = NULL;
					pNew ->child = NULL;
					pNew ->childOf = pTemp;
					cNew->pList = pNew;
					cNew->nChild = NULL;
					nodes++;
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

	//Best First Search
	void bestFirstSearch() {
		childNode *fQue,*tQue,*rQue,*cTrav;
		parentNode *gNode = root;
		char b = 8,gn;
		fQue = rQue = NULL;
		addNodeToQueue(&fQue,&rQue,root);
		tQue = fQue;
		cout<<"\n ";
		while(tQue != NULL) {
			if((gNode == root) || (tQue->pList->hVal) < (gNode -> hVal)) {
				gNode = tQue->pList;
			}
			cTrav = tQue -> pList -> child;
				while(cTrav != NULL) {
					addNodeToQueue(&tQue,&rQue,cTrav -> pList);
					cTrav = cTrav -> nChild;
				}
				cout<<" "<<tQue ->pList ->nd;
				if(tQue->pList != root)
					cout<<"("<<tQue->pList->hVal<<") ->";
				else cout<<" ->";
			tQue = tQue -> nChild;
			if(tQue!=NULL)
				sortList(&tQue);
		}
		int lvl=0;
		parentNode*temp;
		cout<<b<<b;
		cout<<"  \n\n  Goal Node : "<<gNode->nd<<"("<<gNode->hVal<<")"<<endl;
		cout<<"\n  Path to "<<gNode->nd<<"("<<gNode->hVal<<") :\n\n  ";
		temp=gNode;
		while(temp != root) {
			lvl++;
			temp = temp->childOf;
		}
		for(int i=0; i<=lvl;i++){
			temp=gNode;
			for(int j=i;j<lvl;j++){
				temp = temp->childOf;
			}
			cout<<(temp->nd)<<"("<<temp->hVal<<") -> ";
		}
		cout<<b<<b<<b<<"   ";
	}
};

void sortList(childNode **p) {
	childNode *fcTrav,*cTrav,*sTrav;
	fcTrav = *p;
	sTrav = new(childNode);
	while(fcTrav->nChild!=NULL) {
		cTrav = fcTrav -> nChild;
		while(cTrav!=NULL) {
			if((cTrav->pList->hVal) < (fcTrav->pList->hVal)) {
				sTrav->pList=fcTrav->pList;
				fcTrav->pList=cTrav->pList;
				cTrav->pList=sTrav->pList;
			}
			cTrav=cTrav->nChild;
		}
		fcTrav = fcTrav->nChild;
	}
}

void addNodeToQueue(childNode**front,childNode**rear,parentNode*val) {
	childNode *addNode = new(childNode);
	addNode->nChild = NULL;
	addNode->pList = val;
	if(*rear == NULL) {
		*front = *rear = addNode;
	}else{
		(*rear) -> nChild = addNode;
		(*rear) = addNode;
	}
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
	if(c>=48 && c<=57)
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
	char nAry;
	cout<<"\n\t\t\t\tBEST FIRST SEARCH\n\n";
	cout<<"  Enter the value for n : ";
	while(nAry=getch()) {
		if(isNumber(nAry)) {
			cout<<nAry<<" ary Tree."<<endl;
			break;
		}
	}
	tree.createList(nAry);
	cout<<"\n  Traversal :\n";
	tree.bestFirstSearch();
	getch();
}
