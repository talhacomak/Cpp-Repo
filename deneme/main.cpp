#include <iostream>
#include <string.h>
using namespace std;

struct as{
    char a[10];
    char b[10];
    as* next;
};
int main(){
    as d;
    cin>> d.a;
    d.next = nullptr;
    as* e = &d;
    as c;
    e->next = &c;
    *(e->next) = *e;
    e->next->next = nullptr;
    if(!e->next->next) cout<<"null";
    return 0;
}