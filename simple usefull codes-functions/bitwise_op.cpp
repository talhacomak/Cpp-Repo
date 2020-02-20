#include <iostream>
#include <sstream>

using namespace std;

/*
 * sum of i=0 -> 100 => (a xor (b shl i))
 */
int xorAndSum(string a, string c) {
    long long sum=0;
    string b;
    for(int i=0; i<100; i++){  
        for(int j = 0; j<=i; j++){  // b shl i
            b = c;
            b+= '0';    
        }
        if(a.size()>b.size()){  // (a xor b)
            unsigned long long x = a.size() - b.size();
            string s = a;
            for(long long j=0; j<b.size(); j++){
                if(a[x+j] == b[j]) s[j]='0';
                if(a[x+j] != b[j]) s[j]='1';
            }
            stringstream ss;
            ss<<s;
            long long k;
            ss>>k;
            sum += k;
        }        
        
        else{                   // (a xor b)
            long long x = b.size() - a.size();
            string s = b;
            for(long long j=0; j<a.size(); j++){
                if(b[x+j] == a[j]) s[j]='0';
                if(b[x+j] != a[j]) s[j]='1';
            }
            stringstream ss;
            ss<<s;
            long long k;
            ss>>k;
            sum += k;
        }
    }
    return sum;
}

int main()
{
    string a,b;
    cin>>a>>b;
    int k = xorAndSum(a,b);
    cout<<k;

    return 0;
}

