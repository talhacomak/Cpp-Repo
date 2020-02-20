/*  Author: Talha Çomak
	Number: 150160726
*/

#include "runtime.h"
#include <iostream>
#include <sstream>

using namespace std;

AddressValue executeStatement(const Statement &statement,
                              const AddressValue currentAddress,
                              ScalarValue variables[5],
                              Stack <ScalarValue> &callStack,
                              const AddressValue addressOfCalleeIfCall,
                              bool &isDone) {
    if (!start) {
        start = true;
        callStack.create();
    }
    if (statement.type == "function") {
    	
    } 
	else if (statement.type == "inc") {
        if (statement.arg1 == "a") {
            if (statement.arg2 == "a") {
                variables[0] += variables[0];
            } else if (statement.arg2 == "b") {
                variables[0] += variables[1];
            } else if (statement.arg2 == "c") {
                variables[0] += variables[2];
            } else if (statement.arg2 == "d") {
                variables[0] += variables[3];
            } else if (statement.arg2 == "e") {
                variables[0] += variables[4];
            } else {
                stringstream ss;
                ScalarValue value;
                ss << statement.arg2;
                ss >> value;
                variables[0] += value;
            }
        } else if (statement.arg1 == "b") {
            if (statement.arg2 == "a") {
                variables[1] += variables[0];
            } else if (statement.arg2 == "b") {
                variables[1] += variables[1];
            } else if (statement.arg2 == "c") {
                variables[1] += variables[2];
            } else if (statement.arg2 == "d") {
                variables[1] += variables[3];
            } else if (statement.arg2 == "e") {
                variables[1] += variables[4];
            } else {
                stringstream ss;
                ScalarValue value;
                ss << statement.arg2;
                ss >> value;
                variables[1] += value;
            }
        } else if (statement.arg1 == "c") {
            if (statement.arg2 == "a") {
                variables[2] += variables[0];
            } else if (statement.arg2 == "b") {
                variables[2] += variables[1];
            } else if (statement.arg2 == "c") {
                variables[2] += variables[2];
            } else if (statement.arg2 == "d") {
                variables[2] += variables[3];
            } else if (statement.arg2 == "e") {
                variables[2] += variables[4];
            } else {
                stringstream ss;
                ScalarValue value;
                ss << statement.arg2;
                ss >> value;
                variables[2] += value;
            }
        } else if (statement.arg1 == "d") {
            if (statement.arg2 == "a") {
                variables[3] += variables[0];
            } else if (statement.arg2 == "b") {
                variables[3] += variables[1];
            } else if (statement.arg2 == "c") {
                variables[3] += variables[2];
            } else if (statement.arg2 == "d") {
                variables[3] += variables[3];
            } else if (statement.arg2 == "e") {
                variables[3] += variables[4];
            } else {
                stringstream ss;
                ScalarValue value;
                ss << statement.arg2;
                ss >> value;
                variables[3] += value;
            }
        } else if (statement.arg1 == "e") {
            if (statement.arg2 == "a") {
                variables[4] += variables[0];
            } else if (statement.arg2 == "b") {
                variables[4] += variables[1];
            } else if (statement.arg2 == "c") {
                variables[4] += variables[2];
            } else if (statement.arg2 == "d") {
                variables[4] += variables[3];
            } else if (statement.arg2 == "e") {
                variables[4] += variables[4];
            } else {
                stringstream ss;
                ScalarValue value;
                ss << statement.arg2;
                ss >> value;
                variables[4] += value;
            }
        }
    } 
	else if (statement.type == "div") {
        if (statement.arg1 == "a") {
            if (statement.arg2 == "a") {
                variables[0] /= variables[0];
            } else if (statement.arg2 == "b") {
                variables[0] /= variables[1];
            } else if (statement.arg2 == "c") {
                variables[0] /= variables[2];
            } else if (statement.arg2 == "d") {
                variables[0] /= variables[3];
            } else if (statement.arg2 == "e") {
                variables[0] /= variables[4];
            } else {
                stringstream ss;
                ScalarValue value;
                ss << statement.arg2;
                ss >> value;
                variables[0] /= value;
            }
        } else if (statement.arg1 == "b") {
            if (statement.arg2 == "a") {
                variables[1] /= variables[0];
            } else if (statement.arg2 == "b") {
                variables[1] /= variables[1];
            } else if (statement.arg2 == "c") {
                variables[1] /= variables[2];
            } else if (statement.arg2 == "d") {
                variables[1] /= variables[3];
            } else if (statement.arg2 == "e") {
                variables[1] /= variables[4];
            } else {
                stringstream ss;
                ScalarValue value;
                ss << statement.arg2;
                ss >> value;
                variables[1] /= value;
            }
        } else if (statement.arg1 == "c") {
            if (statement.arg2 == "a") {
                variables[2] /= variables[0];
            } else if (statement.arg2 == "b") {
                variables[2] /= variables[1];
            } else if (statement.arg2 == "c") {
                variables[2] /= variables[2];
            } else if (statement.arg2 == "d") {
                variables[2] /= variables[3];
            } else if (statement.arg2 == "e") {
                variables[2] /= variables[4];
            } else {
                stringstream ss;
                ScalarValue value;
                ss << statement.arg2;
                ss >> value;
                variables[2] /= value;
            }
        } else if (statement.arg1 == "d") {
            if (statement.arg2 == "a") {
                variables[3] /= variables[0];
            } else if (statement.arg2 == "b") {
                variables[3] /= variables[1];
            } else if (statement.arg2 == "c") {
                variables[3] /= variables[2];
            } else if (statement.arg2 == "d") {
                variables[3] /= variables[3];
            } else if (statement.arg2 == "e") {
                variables[3] /= variables[4];
            } else {
                stringstream ss;
                ScalarValue value;
                ss << statement.arg2;
                ss >> value;
                variables[3] /= value;
            }
        } else if (statement.arg1 == "e") {
            if (statement.arg2 == "a") {
                variables[4] /= variables[0];
            } else if (statement.arg2 == "b") {
                variables[4] /= variables[1];
            } else if (statement.arg2 == "c") {
                variables[4] /= variables[2];
            } else if (statement.arg2 == "d") {
                variables[4] /= variables[3];
            } else if (statement.arg2 == "e") {
                variables[4] /= variables[4];
            } else {
                stringstream ss;
                ScalarValue value;
                ss << statement.arg2;
                ss >> value;
                variables[4] /= value;
            }
        }
    } 
	else if (statement.type == "call") {
        callStack.push(variables[0]);
        callStack.push(variables[1]);
        callStack.push(variables[2]);
        callStack.push(variables[3]);
        callStack.push(variables[4]);
        callStack.push2(currentAddress);
        cout << "Executing " << statement.type << " at line " << currentAddress << endl;
        if (statement.arg2 == "a") {
            variables[1] = variables[2] = variables[3] = variables[4] = 0;
        } else if (statement.arg2 == "b") {
            variables[0] = variables[2] = variables[3] = variables[4] = 0;
        } else if (statement.arg2 == "c") {
            variables[0] = variables[1] = variables[3] = variables[4] = 0;
        } else if (statement.arg2 == "d") {
            variables[0] = variables[1] = variables[2] = variables[4] = 0;
        } else if (statement.arg2 == "e") {
            variables[0] = variables[1] = variables[2] = variables[3] = 0;
        }
        
        return addressOfCalleeIfCall+1;
    } 
	else if (statement.type == "mul") {
        if (statement.arg1 == "a") {
            if (statement.arg2 == "a") {
                variables[0] *= variables[0];
            } else if (statement.arg2 == "b") {
                variables[0] *= variables[1];
            } else if (statement.arg2 == "c") {
                variables[0] *= variables[2];
            } else if (statement.arg2 == "d") {
                variables[0] *= variables[3];
            } else if (statement.arg2 == "e") {
                variables[0] *= variables[4];
            } else {
                stringstream ss;
                ScalarValue value;
                ss << statement.arg2;
                ss >> value;
                variables[0] *= value;
            }
        } else if (statement.arg1 == "b") {
            if (statement.arg2 == "a") {
                variables[1] *= variables[0];
            } else if (statement.arg2 == "b") {
                variables[1] *= variables[1];
            } else if (statement.arg2 == "c") {
                variables[1] *= variables[2];
            } else if (statement.arg2 == "d") {
                variables[1] *= variables[3];
            } else if (statement.arg2 == "e") {
                variables[1] *= variables[4];
            } else {
                stringstream ss;
                ScalarValue value;
                ss << statement.arg2;
                ss >> value;
                variables[1] *= value;
            }
        } else if (statement.arg1 == "c") {
            if (statement.arg2 == "a") {
                variables[2] *= variables[0];
            } else if (statement.arg2 == "b") {
                variables[2] *= variables[1];
            } else if (statement.arg2 == "c") {
                variables[2] *= variables[2];
            } else if (statement.arg2 == "d") {
                variables[2] *= variables[3];
            } else if (statement.arg2 == "e") {
                variables[2] *= variables[4];
            } else {
                stringstream ss;
                ScalarValue value;
                ss << statement.arg2;
                ss >> value;
                variables[2] *= value;
            }
        } else if (statement.arg1 == "d") {
            if (statement.arg2 == "a") {
                variables[3] *= variables[0];
            } else if (statement.arg2 == "b") {
                variables[3] *= variables[1];
            } else if (statement.arg2 == "c") {
                variables[3] *= variables[2];
            } else if (statement.arg2 == "d") {
                variables[3] *= variables[3];
            } else if (statement.arg2 == "e") {
                variables[3] *= variables[4];
            } else {
                stringstream ss;
                ScalarValue value;
                ss << statement.arg2;
                ss >> value;
                variables[3] *= value;
            }
        } else if (statement.arg1 == "e") {
            if (statement.arg2 == "a") {
                variables[4] *= variables[0];
            } else if (statement.arg2 == "b") {
                variables[4] *= variables[1];
            } else if (statement.arg2 == "c") {
                variables[4] *= variables[2];
            } else if (statement.arg2 == "d") {
                variables[4] *= variables[3];
            } else if (statement.arg2 == "e") {
                variables[4] *= variables[4];
            } else {
                stringstream ss;
                ScalarValue value;
                ss << statement.arg2;
                ss >> value;
                variables[4] *= value;
            }
        }
    } 
	else if (statement.type == "dec") {
        if (statement.arg1 == "a") {
            if (statement.arg2 == "a") {
                variables[0] -= variables[0];
            } else if (statement.arg2 == "b") {
                variables[0] -= variables[1];
            } else if (statement.arg2 == "c") {
                variables[0] -= variables[2];
            } else if (statement.arg2 == "d") {
                variables[0] -= variables[3];
            } else if (statement.arg2 == "e") {
                variables[0] -= variables[4];
            } else {
                stringstream ss;
                ScalarValue value;
                ss << statement.arg2;
                ss >> value;
                variables[0] -= value;
            }
        } else if (statement.arg1 == "b") {
            if (statement.arg2 == "a") {
                variables[1] -= variables[0];
            } else if (statement.arg2 == "b") {
                variables[1] -= variables[1];
            } else if (statement.arg2 == "c") {
                variables[1] -= variables[2];
            } else if (statement.arg2 == "d") {
                variables[1] -= variables[3];
            } else if (statement.arg2 == "e") {
                variables[1] -= variables[4];
            } else {
                stringstream ss;
                ScalarValue value;
                ss << statement.arg2;
                ss >> value;
                variables[1] -= value;
            }
        } else if (statement.arg1 == "c") {
            if (statement.arg2 == "a") {
                variables[2] -= variables[0];
            } else if (statement.arg2 == "b") {
                variables[2] -= variables[1];
            } else if (statement.arg2 == "c") {
                variables[2] -= variables[2];
            } else if (statement.arg2 == "d") {
                variables[2] -= variables[3];
            } else if (statement.arg2 == "e") {
                variables[2] -= variables[4];
            } else {
                stringstream ss;
                ScalarValue value;
                ss << statement.arg2;
                ss >> value;
                variables[2] -= value;
            }
        } else if (statement.arg1 == "d") {
            if (statement.arg2 == "a") {
                variables[3] -= variables[0];
            } else if (statement.arg2 == "b") {
                variables[3] -= variables[1];
            } else if (statement.arg2 == "c") {
                variables[3] -= variables[2];
            } else if (statement.arg2 == "d") {
                variables[3] -= variables[3];
            } else if (statement.arg2 == "e") {
                variables[3] -= variables[4];
            } else {
                stringstream ss;
                ScalarValue value;
                ss << statement.arg2;
                ss >> value;
                variables[3] -= value;
            }
        } else if (statement.arg1 == "e") {
            if (statement.arg2 == "a") {
                variables[4] -= variables[0];
            } else if (statement.arg2 == "b") {
                variables[4] -= variables[1];
            } else if (statement.arg2 == "c") {
                variables[4] -= variables[2];
            } else if (statement.arg2 == "d") {
                variables[4] -= variables[3];
            } else if (statement.arg2 == "e") {
                variables[4] -= variables[4];
            } else {
                stringstream ss;
                ScalarValue value;
                ss << statement.arg2;
                ss >> value;
                variables[4] -= value;
            }
        }
    } 
	else if (statement.type == "return") {
        cout << "Executing " << statement.type << " at line " << currentAddress << endl;
        if (callStack.isEmpty()) isDone = true;

        if (isDone) {
            if (statement.arg1 == "a") {
                cout << variables[0] << endl;
            } else if (statement.arg1 == "b") {
                cout << variables[1] << endl;
            } else if (statement.arg1 == "c") {
                cout << variables[2] << endl;
            } else if (statement.arg1 == "d") {
                cout << variables[3] << endl;
            } else {
                cout << variables[4] << endl;
            }
            return 0;
        } else {
            AddressValue tempAdress = callStack.pop2();
            if (statement.arg1 == "a") {
                variables[4] = callStack.pop();
                variables[3] = callStack.pop();
                variables[2] = callStack.pop();
                variables[1] = callStack.pop();
                callStack.pop();
            } else if (statement.arg1 == "b") {
                variables[4] = callStack.pop();
                variables[3] = callStack.pop();
                variables[2] = callStack.pop();
                callStack.pop();
                variables[0] = callStack.pop();
            } else if (statement.arg1 == "c") {
                variables[4] = callStack.pop();
                variables[3] = callStack.pop();
                callStack.pop();
                variables[1] = callStack.pop();
                variables[0] = callStack.pop();
            } else if (statement.arg1 == "d") {
                variables[4] = callStack.pop();
                callStack.pop();
                variables[2] = callStack.pop();
                variables[1] = callStack.pop();
                variables[0] = callStack.pop();
            } else {
                callStack.pop();
                variables[3] = callStack.pop();
                variables[2] = callStack.pop();
                variables[1] = callStack.pop();
                variables[0] = callStack.pop();
            }
            return tempAdress + 1;
        }

    }

    cout << "Executing " << statement.type << " at line " << currentAddress << endl;

    return currentAddress + 1;
}
