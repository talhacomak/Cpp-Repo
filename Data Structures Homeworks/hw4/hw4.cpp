/* @Author
Student Name: <Talha Çomak>
Student ID : <150160726>
Date: <13.12.2018> */

#include <iostream>
#include <fstream>

using namespace std;

struct node{
	int data;
	node *next;
};

struct queueAnt{
	node *front;
	node *back;
	void create(){
		front = back = NULL;
	}
	void enqueue(int input){
		node *newnode = new node;
		newnode->data = input;
		newnode->next = NULL;
		if(isempty()){
			back = newnode;
			front = back;
		}
		else {
			back->next = newnode;
			back = newnode;
		}
	}
	int dequeue(){
		node *topnode;
		int temp;
		topnode = front;
		front = front->next;
		temp = topnode->data;
		delete topnode;
		return temp;
	}
	bool isempty(){
		return front == NULL;
	}
};

struct stackAnt{
	node* head;
	void create(){
		head = NULL;
	}
	void push(int data){
		node *newnode = new node;
		newnode->data = data;
		newnode->next = head;
		head = newnode;
	}
	int pop(){
		node *topnode;
		int temp;
		topnode = head;
		temp = topnode->data;
		head = head->next;
		delete topnode;
		return temp;
	}
	bool isEmpty(){
		return head == NULL;
	}
};

struct Ants {
	queueAnt ants;
	queueAnt holeDepths;
	stackAnt hole;
	void ReadFile (char* input){
		holeDepths.create();
		ants.create();
		hole.create();
		ifstream file(input);
		if(!file.is_open()){
			cout<<"File error!"<<endl;
			return;
		}
		int ant_num, hole;
		file>>ant_num;
		for(int i=1; i<ant_num+1; i++){
			ants.enqueue(i);
		}
		while(file>>hole){
			holeDepths.enqueue(hole);
		}
	}
	void ShowContents (bool x){
		node* temp;
		if(x){
			temp = ants.front;
			while(temp){
				cout<< temp->data<<" ";
				temp = temp->next;
			}
		}
		else{
			temp = holeDepths.front;
			while(temp){
				cout<< temp->data<<" ";
				temp = temp->next;
			}
		}
		cout<<endl;
	}
	void CrossRoad (){
		while(holeDepths.front){
			int loop = holeDepths.dequeue();
			for(int i=0; i<loop; i++){
				int will_push = ants.dequeue();
				hole.push(will_push);
			}
			while(!hole.isEmpty()){
				ants.enqueue(hole.pop());	
			}
		}
	}
};

int main (int argc , char ** argv ){
	Ants a;
	a. ReadFile ( argv [1]); // store the number of ants and depths of holes
	cout << "The initial Ant sequence is: ";
	a. ShowContents (1); // list ant sequence ( initially : 1, 2, ... , N)
	cout << "The depth of holes are : ";
	a. ShowContents (0); // list depth of holes
	a. CrossRoad ();
	cout << "The final Ant sequence is: ";
	a. ShowContents (1);
	return 0;
}
