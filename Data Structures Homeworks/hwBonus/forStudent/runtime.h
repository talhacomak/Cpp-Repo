/*
 * runtime.h
 *
 *      Author: YOUR STUDENT NAME HERE
 *      Number: YOUR STUDENT ID HERE
 */

#ifndef RUNTIME_H_
#define RUNTIME_H_

#include<string>

struct Statement
{
    std::string type;
    std::string arg1;
    std::string arg2;
};

typedef unsigned AddressValue;
typedef int ScalarValue;

template<typename T>
struct Stack
{
    //implement your stack here
};

AddressValue executeStatement( const Statement & statement, const AddressValue currentAddress, ScalarValue variables [5], Stack<ScalarValue> & callStack, const AddressValue addressOfCalleeIfCall, bool & isDone );

#endif /* RUNTIME_H_ */
