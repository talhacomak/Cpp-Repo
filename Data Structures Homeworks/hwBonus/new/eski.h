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
struct Stack{
	T array[25];
	ScalarValue top;
	void create(){
		top = 0;
	}
    void push(T x){
    	array[top++] = x;
	}
	T pop(){
		return array[--top];
	}
	bool isEmpty(){
		return !top;
	}
};

AddressValue executeStatement(const Statement &statement, const AddressValue currentAddress, ScalarValue variables [5], 
Stack <ScalarValue> & callStack, const AddressValue addressOfCalleeIfCall, bool & isDone );

#endif
