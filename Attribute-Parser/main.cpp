#include <vector>
#include <iostream>
#include <sstream>
using namespace std;


int main() {
    int x, y, q;
    string k;
    vector <string> att;
	vector <vector <string>> vec;
	vec.resize(10);
	for(int i=0; i<10; i++){
		vec[i].resize(50);
	}
    cin>>x>>y;
    cin.ignore();
    int op = 0, esit=0;
    stringstream cc;
    for(int i=0; i<x; i++){
        getline(cin, k);
        if(k[1] == '/'){
        	int s;
        	string sil = cc.str();
        	for(s=sil.size()-1; s>=0; s--){
        		if(sil[s] == '.') break;
			}
			if(s == -1) {
				cc.str("");
				continue;
			}
			sil.erase(sil.begin()+s, sil.end());
			cc.str("");
			cc<<sil;
        	continue;
		}
        k.erase(k.end()-1);
        esit = 0;
        for(q=0; q<k.size(); q++){
        	if(k[q] == '=') esit++;
		}
        stringstream ss;
        ss<<k;
        string x;
        ss>>x;
        x.erase(x.begin());
        if(cc.str().empty()){
        	cc<<x;
		}
		else {
			cc<<"."<<x;
		}
		att.push_back(cc.str());
        string m,n,o;
        q=0;
        for(int r=0; r<esit; r++){
        	ss>>m>>o>>n;
        	vec[op][q] = m;
        	n.erase(n.begin());
        	n.erase(n.end()-1);
        	vec[op][q+1] = n;
        	q++;
        	q++;
		}
		op++;
    }
    string a;
    int c;
    bool che = true;
    for(int i=0; i<y; i++){
    	che = true;
    	getline(cin, k);
    	int j;
    	for(j=0; j<k.size(); j++){
    		if(k[j] == '~') break;
		}
		a.insert(a.begin(), k.begin()+j+1, k.end());
		k.erase(k.begin()+j, k.end());
		for(c=0; c<att.size(); c++){
			if(k == att[c]){
				for(int d=0;;d++){
					if(vec[c][d].empty()) break;
					if(vec[c][d] == a){
						cout<<vec[c][d+1]<<endl;
						che = false;
						break;
					}
					d++;
				}
			}
		}
		if(che) cout<<"Not Found!"<<endl;
		a.clear();
	}
	
    return 0;
}
