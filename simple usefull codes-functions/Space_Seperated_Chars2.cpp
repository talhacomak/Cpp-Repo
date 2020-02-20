#include <iostream>

using namespace std;

int main() {
    int x;
    cin>>x;
    cin.ignore();
    string k;
    for(int i=0; i<x; i++){
        getline(cin, k);
        cout<<k;
    }
    return 0;
}
