#include <iostream>
using namespace std;

struct New{
char* a = new char[10];
int elementnumber;
New* y;
char* CountElmt(){
    return a;
}
};

int main(){
    New stu;
    cin.getline(stu.a, 10);
    char* x = new char[10];
    x = stu.CountElmt();
    cout<<x;
    return 0;
}