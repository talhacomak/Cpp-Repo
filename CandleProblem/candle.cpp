#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <stack>

using namespace std;

map<int,int> m;
stack<int> s;

void fun(vector <vector <int>> vec, int k, int p){
    for(int i=0; i<vec[p].size(); i++){
        bool b=0;
        if(m.find(vec[p][i]) == m.end()){
            m.insert(pair<int,int>(vec[p][i], 0));
            //auto it = m.find(vec[p][i]);
            //cout<<it->first<<" "<<p<<" "<<i<<endl<<endl;
            b=1;
        }
        if(!b) continue; 
        if(p+1<k) {
        	fun(vec, k, p+1);
		}
        else {
        	s.push(1);
		}
        m.erase(vec[p][i]);
    }
}

int candlesCounting(int k, vector<vector<int>> candles) {
    vector<vector<int>> vec;
    vec.resize(k);
    for(int i=0; i<candles.size(); i++){
        vec[candles[i][1]-1].push_back(candles[i][0]);
    }
    list <int> li;
    vector <vector <int>> ve;
    ve.resize(k);
    for(int i=0; i<vec.size(); i++){
        li.insert(li.begin(), vec[i].begin(), vec[i].end());
        li.sort();
        li.unique();
        ve[i].insert(ve[i].begin(), li.begin(), li.end());
        li.clear();
    }
    
    fun(ve, k, 0);
    return s.size()%1000000007;
}

int main(){
	vector<vector<int>> candles;
	candles.resize(8);
	candles[0].push_back(3);
	candles[0].push_back(2);
	
	candles[1].push_back(1);
	candles[1].push_back(1);
	
	candles[2].push_back(4);
	candles[2].push_back(2);
	
	candles[3].push_back(6);
	candles[3].push_back(3);
	
	candles[4].push_back(9);
	candles[4].push_back(4);
	
	candles[5].push_back(13);
	candles[5].push_back(4);
	
	candles[6].push_back(3);
	candles[6].push_back(4);
	
	candles[7].push_back(7);
	candles[7].push_back(5);
	cout<<candlesCounting(5,candles);
}
