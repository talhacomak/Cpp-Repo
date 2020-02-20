#include <iostream>
#include <vector>
#include <list>

using namespace std;

int main() {
	multimap <int, int> m;
	vector <vector <int>> vec;
	vec.resize(3);
	vec[0].push_back(3);
	vec[0].push_back(2);
	vec[0].push_back(1);
	vec[0].push_back(1);
	vec[0].push_back(4);
	vec[1].push_back(2);
	vec[1].push_back(6);
	vec[1].push_back(3);
	vec[1].push_back(5);
	vec[1].push_back(4);
	vec[2].push_back(3);
	vec[2].push_back(4);
	vec[2].push_back(3);
	vec[2].push_back(4);
	vec[2].push_back(3);
	vec[2].push_back(4);
	
	list <int> li;
    vector <vector <int>> ve;
    ve.resize(3);
    for(int i=0; i<vec.size(); i++){
        li.insert(li.begin(), vec[i].begin(), vec[i].end());
        li.sort();
        li.unique();
        ve[i].insert(ve[i].begin(), li.begin(), li.end());
        li.clear();
    }
}
