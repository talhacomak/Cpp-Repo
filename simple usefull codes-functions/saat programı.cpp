#include <iostream>
#include <sstream>
using namespace std;

// Complete the timeInWords function below.
int main() {
	int h, m;
	cin>>h>>m;
string chx, chy;
    if(m>30) h++;
    switch(h){
        case 1:
            chx = "one";
            break;
        case 2:
            chx = "two";
            break;
        case 3:
            chx = "three";
            break;
        case 4:
            chx = "four";
            break;
        case 5:
            chx = "five";
            break;
        case 6:
            chx = "six";
            break;
        case 7:
            chx = "seven";
            break;
        case 8:
            chx = "eight";
            break;
        case 9:
            chx = "nine";
            break;
        case 10:
            chx = "ten";
            break;
        case 11:
            chx = "eleven";
            break;
        case 12:
            chx = "twelf";
            break;
    }
    
    switch(m){
        case 1:
            chy = "one";
            break;
        case 2:
            chy = "two";
            break;
        case 3:
            chy = "three";
            break;
        case 4:
            chy = "four";
            break;
        case 5:
            chy = "five";
            break;
        case 6:
            chy = "six";
            break;
        case 7:
            chy = "seven";
            break;
        case 8:
            chy = "eight";
            break;
        case 9:
            chy = "nine";
            break;
        case 10:
            chy = "ten";
            break;
        case 11:
            chy = "eleven";
            break;
        case 12:
            chy = "twelf";
            break;
        case 13:
            chy = "thirteen";
            break;
        case 14:
            chy = "fourteen";
            break;
        case 16:
            chy = "sixteen";
            break;
        case 17:
            chy = "seventeen";
            break;
        case 18:
            chy = "eighteen";
            break;
        case 19:
            chy = "nineteen";
            break;
        case 20:
            chy = "twenty";
            break;
        case 21:
            chy = "twenty one";
            break;
        case 22:
            chy = "twenty two";
            break;
        case 23:
            chy = "twenty three";
            break;
        case 24:
            chy = "twenty four";
            break;
        case 25:
            chy = "twenty five";
            break;
        case 26:
            chy = "twenty six";
            break;
        case 27:
            chy = "twenty seven";
            break;
        case 28:
            chy = "twenty eight";
            break;
        case 29:
            chy = "twenty nine";
            break;
        default:
            switch(m){
        case 59:
            chy = "one";
            break;
        case 58:
            chy = "two";
            break;
        case 57:
            chy = "three";
            break;
        case 56:
            chy = "four";
            break;
        case 55:
            chy = "five";
            break;
        case 54:
            chy = "six";
            break;
        case 53:
            chy = "seven";
            break;
        case 52:
            chy = "eight";
            break;
        case 51:
            chy = "nine";
            break;
        case 50:
            chy = "ten";
            break;
        case 49:
            chy = "eleven";
            break;
        case 48:
            chy = "twelf";
            break;
        case 47:
            chy = "thirteen";
            break;
        case 46:
            chy = "fourteen";
            break;
        case 44:
            chy = "sixteen";
            break;
        case 43:
            chy = "seventeen";
            break;
        case 42:
            chy = "eighteen";
            break;
        case 41:
            chy = "nineteen";
            break;
        case 40:
            chy = "twenty";
            break;
        case 39:
            chy = "twenty one";
            break;
        case 38:
            chy = "twenty two";
            break;
        case 37:
            chy = "twenty three";
            break;
        case 36:
            chy = "twenty four";
            break;
        case 35:
            chy = "twenty five";
            break;
        case 34:
            chy = "twenty six";
            break;
        case 33:
            chy = "twenty seven";
            break;
        case 32:
            chy = "twenty eight";
            break;
        case 31:
            chy = "twenty nine";
            break;
        break;
    }
    }
    
    stringstream ss;
    if(m==0){
        ss<<chx<<" o' clock";
    }
    else if (m == 15){
        ss<<"quarter past "<<chx;
    }
    else if (m == 30){
        ss<<"half past "<<chx;
    }
    else if(m==45){
        ss<<"quarter to "<<chx;
    }
    else if(m<30) ss<< chy <<" minutes past "<<chx;
    else if(m>30) ss<< chy <<" minutes to "<<chx;
    string res = ss.str();
	cout<<res;
	return 0;
}

