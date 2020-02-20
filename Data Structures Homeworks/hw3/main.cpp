#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

struct stack_node{
	int x;
	stack_node* next;
};

struct stack{
	stack_node *top;
	void create(){
		top = NULL;
	}
	void push(int x){
		stack_node* newnode = new stack_node;
		newnode->x = x;
		if(!top){
			top = newnode;
			top->next = NULL;
			return;
		}
		newnode->next = top;
		top = newnode;
	}
	int pop(){
		int temp = top->x;
		stack_node *erase = top;
		top = top->next;
		delete erase;
		return temp;
	}
	bool isEmpty(){
		return top == NULL ? true : false;
	}
	void printSize(){
		stack_node* temp = top;
		int result = 0;
		while(temp){
			result++;
			temp = temp->next;
		}
		cout<<result;
	}
};

int main(int argc, char** argv){
	(void)argc;
	int tableDeckCount, playerDeckCount;
	stack deck, player1, player2, bin;
	deck.create();
	player1.create();
	player2.create();
	bin.create();
	ifstream input(argv[1]);
	if(!input.is_open()){
		cout<< argv[1] << " is not found!" << endl;
		return 1;
	}
	input>>tableDeckCount>>playerDeckCount;
	int x;
	for(int i=0; i<tableDeckCount; i++){
		input>>x;
		deck.push(x);
	}
	for(int i=0; i<playerDeckCount; i++){
		input>>x;
		player1.push(x);
	}
	for(int i=0; i<playerDeckCount; i++){
		input>>x;
		player2.push(x);
	}
	while(!deck.isEmpty() && !player1.isEmpty() && !player2.isEmpty()){
		int compare = deck.pop();
		for(int i=0; i<abs(compare); i++){
			if(compare < 0){
				int poped;
				if(!player1.isEmpty()) poped = player1.pop();
				else break;
				
				if(player2.top->x < poped) {
					player2.push(poped); 
				}
				else {
					bin.push(poped);
				}
			}
			else {
				int poped;
				if(!player2.isEmpty()) poped = player2.pop();
				else break;
				if(player1.top->x < poped){
					player1.push(poped);
				}
				else{
					bin.push(poped);
				}
			}
		}

		if(deck.isEmpty() || player1.isEmpty() || player2.isEmpty()) break;
		
		compare = deck.pop();
		for(int i=0; i<abs(compare); i++){
			if(compare < 0){
				int poped;
				if(!player2.isEmpty()) poped = player2.pop();
				else break;
				
				if(player1.top->x < poped) {
					player1.push(poped);
				}
				else {
					bin.push(poped);
				}
			}
			else {
				int poped;
				if(!player1.isEmpty()) poped = player1.pop();
				else break;
				
				if(player2.top->x < poped){
					player2.push(poped);
				}
				else{
					bin.push(poped);
				}
			}
		}
	}
	bin.printSize();
	return 0;
}
