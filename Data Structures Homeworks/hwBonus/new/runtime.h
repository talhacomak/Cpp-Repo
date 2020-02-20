/*
 * runtime.h
 *
 *      Author: Talha Çomak
 *      Number: 150160726
 */

#ifndef RUNTIME_H_
#define RUNTIME_H_

#include <string>

using namespace std;

struct Statement{
    string type;
    string arg1;
    string arg2;
};

typedef unsigned AddressValue;
typedef int ScalarValue;
bool start = false;

template <typename T>
struct node{
	T x;
	node* next;
};

template <typename T>
struct Stack{
	node<ScalarValue>* top;
	void create(){
		top = NULL;
	}
    void push(T x){
    	node<ScalarValue>* newnode = new node<ScalarValue>;
    	newnode->x = x;
    	newnode->next = top;
    	top = newnode;
	}
	T pop(){
		node<ScalarValue>* topnode;
		T temp;
		topnode = top;
		temp = top->x;
		top = top->next;
		delete topnode;
		return temp;
	}
	bool isEmpty(){
		return !top;
	}
};

AddressValue executeStatement(const Statement &statement, const AddressValue currentAddress, ScalarValue variables [5], 
Stack <ScalarValue> & callStack, const AddressValue addressOfCalleeIfCall, bool & isDone );

#endif
