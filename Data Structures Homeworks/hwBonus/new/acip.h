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
	ScalarValue array[21];
	AddressValue ar[5];
	ScalarValue top, top2;
	void create(){
		top = 0;
		top2=0;
	}
    void push(ScalarValue x){
    	array[top++] = x;
	}
	ScalarValue pop(){
		return array[--top];
	}
	void push2(AddressValue x){
    	ar[top2++] = x;
	}
	ScalarValue pop2(){
		return ar[--top2];
	}
	bool isEmpty(){
		return !top;
	}
};

AddressValue executeStatement(const Statement &statement, const AddressValue currentAddress, ScalarValue variables [5], 
Stack <ScalarValue> & callStack, const AddressValue addressOfCalleeIfCall, bool & isDone );

#endif
