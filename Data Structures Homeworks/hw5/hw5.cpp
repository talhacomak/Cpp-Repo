/* @Author
Student Name: <Talha Çomak>
Student ID : <150160726>
Date: <date> */

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// i did not add comment for the stack and queue structs becouse these are general information

struct stack_node{ 
	int k;
	stack_node* next;
};

struct stack{
	stack_node* head;
	void create(){
		head = NULL;
	}
	void push(int num){
		stack_node* newnode = new stack_node;
		newnode->k = num;
		newnode->next = head;
		head = newnode;
	}
	int pop(){
		stack_node* del = head;
		int poped = del->k;
		head = head->next;
		delete del;
		return poped;
	}
	bool isEmpty(){
		return head == NULL;
	}
};

struct node{
	int data;
	node *next;
};

struct queue{
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
	void erase(){
		node *p;
		while (front){
			p = front;
			front = front->next;
			delete p;
		}
	}
	bool isempty(){
		return front == NULL;
	}
};

queue preorder; // this queue will used for store the sums of integers in the preorder_find function of Tree structure

struct tree_node{ // nod of Tree structure
   int value; 
   char key[20];
   tree_node *left;
   tree_node *right;
};

struct Tree{
	tree_node *root;
	void create(){
		root = NULL;
	}
	void insert(int key, tree_node *leaf){
		
		if(key < leaf->value){
			if(leaf->left != NULL){
				insert(key, leaf->left);
			}else{
				leaf->left = new tree_node;
				leaf->left->value = key;
				leaf->left->left = NULL;
				leaf->left->right = NULL;
			}
		}else if(key >= leaf->value){
			if(leaf->right != NULL){
				insert(key, leaf->right);
			}else{
				leaf->right = new tree_node;
				leaf->right->value = key;
				leaf->right->right = NULL;
				leaf->right->left = NULL;
			}
		}
	}
	void insert(int key){
		if(root != NULL){
			insert(key, root);
		}else{
			root = new tree_node;
			root->value = key;
			root->left = NULL;
			root->right = NULL;
		}
	}
	
	tree_node* search(int key, tree_node *leaf){
		if(leaf != NULL){
			if(key == leaf->value){
				return leaf;
			}
			if(key < leaf->value){
				return search(key, leaf->left);
			}else{
				return search(key, leaf->right);
			}
		}else{
			return NULL;
		}
	}
	
	tree_node* search(int key){
		return search(key, root);
	}
};

int main(int argc, char** argv){	
	Tree t;	
	t.create();		
	int num;	// this variable get the integers and transfer them to t tree
	fstream file(argv[1]);
	if(!file.is_open()){
		cout<<"File not found!";
		return 1;
	}
	string str; 	// this string gets the lines of file
	getline(file, str);	
	stringstream ss;	// due to convert string to integer
	ss<<str;	// str going to ss
	while(ss>>num){		// the integers in the ss transfered to integer num
		t.insert(num);		// num will add to t tree
	}
	getline(file, str);	// reading the second line
	stringstream cc;
	cc<<str;
	cc>>num;	// num store the asked number
	bool found = false;	// found variable will use the knowledge of presence of the path
	preorder.create();	// preorder queue is creating
	t.preorder_find(t.root->left);	// seeking for the presence of path in the left path according to preorder
	while(!preorder.isempty()){		// if the preorder queue is not empty
		if(preorder.dequeue() == num) break;	// if any sum of the node of t tree is equal the asked number than exit the loop 
		preorder.dequeue();		// releasing the order of element (nodecount of element of tree)
	}
	
	int j = 0;
	if(!preorder.isempty()) j = preorder.dequeue(); // if we found the equal sum in the preorder queue we equalize j integer to order of found element
	if(j == 0){ 		// if the order is zero this mean there is no number and we found anything
		found = false;
	}
	else{
		cout<<"Path Found: ";
		t.print(j);		// print the path
		found = true;
	}
	preorder.erase();	// deleting element is the preorder queue
	preorder.create();	// creating new queue
	t.preorder_find(t.root->right);		// seeking for the presence of path in the right path according to preorder
	// ** the rest is same with before **
	
	while(!preorder.isempty()){
		if(preorder.dequeue() == num) break;
		preorder.dequeue();
	}
	j = 0;
	if(!preorder.isempty()) j = preorder.dequeue();
	if(j == 0){
		if(!found) found = false;
	}
	else{
		cout<<"Path Found: ";
		t.print(j);
		found = true;
	}
	if(!found) cout<<"No Path Found"<<endl; // if can not found any path print that 
	
	return 0;
}
