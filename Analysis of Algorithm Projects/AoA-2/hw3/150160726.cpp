/* @Author
* Student Name: Talha Çomak
* Student ID : 150160726 */

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <climits>

using namespace std;

vector <vector <vector <int> > > v_trick; // this vector will used for storing the selected suits in the knapsack

int knapsack(int n, int W, vector <int> wei, vector <int> val) {
	int** M = new int* [n + 1];
	v_trick.resize(n + 1);
	for (int k = 0; k < n + 1; k++) { // assign zero to array M
		M[k] = new int[W + 1];
		v_trick[k].resize(W + 1);
		for (int i = 0; i < W + 1; i++) {
			M[k][i] = 0;
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= W; j++) {
			if (wei[i-1] > j) {
				M[i][j] = M[i - 1][j];
				for (int k = 0; k < (int)v_trick[i - 1][j].size(); k++) {	// assign the memory of the last trick to the current trick vector
					v_trick[i][j].push_back(v_trick[i - 1][j][k]);
				}
			}
			else {
				if (M[i - 1][j] < M[i - 1][j - wei[i-1]] + val[i-1]) {
					M[i][j] = M[i - 1][j - wei[i-1]] + val[i-1];
					for (int k = 0; k < (int)v_trick[i - 1][j - wei[i-1]].size(); k++) {   // assign the memory of the last trick to the current trick vector
						v_trick[i][j].push_back(v_trick[i - 1][j - wei[i-1]][k]);
					}
					v_trick[i][j].push_back(i-1);   // storing the index of the value
				}
				else {
					M[i][j] = M[i - 1][j];
					for (int k = 0; k < (int)v_trick[i - 1][j].size(); k++) {	// assign the memory of the last trick to the current trick vector
						v_trick[i][j].push_back(v_trick[i - 1][j][k]);
					}
				}

			}
		}
	}
	return M[n][W]; 	// max value == max bugs
}

int min(int x, int y, int z){ // minimum of three variables
	return (x < y ? x : y) < z ? (x < y ? x : y) : z;
}

int editDistance(vector <int> vec1, vector <int> vec2) {	// this function gives the distance of two vector integer array
	int x = vec1.size();
	int y = vec2.size();
	int** distance = new int*[x + 1];		// creating a distace array
	for (int i = 0; i < x + 1; i++) {		// creating a distace array
		distance[i] = new int[y + 1];
	}

	for (int i = 0; i <= x; i++) {		// calculating the distance
		for (int j = 0; j <= y; j++) {
			if (i == 0) distance[i][j] = j;
			else if (j == 0) distance[i][j] = i;
			else if (vec1[i - 1] == vec2[j - 1]) distance[i][j] = distance[i - 1][j - 1];
			else distance[i][j] = 1 + min(distance[i][j - 1], distance[i - 1][j], distance[i - 1][j - 1]);
		}
	}
	return distance[x][y];
}


int main(int argv, char* argc[]) {
	ifstream file;
	if (argc[1] == NULL) {
		cout << "No parameter!" << endl;
		return 1;
	}
	file.open(argc[1]);	// 	KOMUT SATIRINDAN OKUCAN UNUTMA !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	string s;
	int MaxAllowed;
	file >> s;			// reading empty/redundant strings
	file >> s;
	file >> s;
	file >> s;
	file >> MaxAllowed;
	file >> s;
	file >> s;
	file >> s;
	file >> s;			// reading empty/redundant strings
	getline(file, s);		//  reading empty lines
	int bugs, runTime;
	vector <int> bugsAr, runTimeAr;		// for keeping the bugs and runtimes in that vectors
	int size = 0;		// for the keys of the map mp
	multimap<int, string> mp;	// using for storing testcases in the suites. 
								// keys are order of suites
	while (!file.eof()) {	// reading the data.txt file line by line
		getline(file, s);
		if(s.size() == 0) continue;	// if there is an empty line	
		stringstream ss(s);		// for parsing the line
		ss >> s;				// first string
		ss >> bugs;
		ss >> runTime;
		bugsAr.push_back(bugs);		
		runTimeAr.push_back(runTime);
		while (ss >> s) mp.insert({ size, s }); // mp keeps the testcases by key, keys are the Suite orders
		size++;
	}
	int n = (int)bugsAr.size();		// n is size of the bugsAr and runTime vectors (equal to suite count)
	int res = knapsack(n, MaxAllowed, runTimeAr, bugsAr); // Total weight, knapsack

	cout << "Total amount of bugs: " << res << endl;

	vector <int> keys;
	int totalRunTime = 0;
	int suite_count = (int)v_trick[n][MaxAllowed].size();	// this suite_count is calculated in knapsack, for max. bugs in given time
	vector <vector <string> > Suites(suite_count);	// this is actually redundant but it was used for debugging
	vector <vector <int> > indexTrick(suite_count);		// it tracks order of indexes of the testcases
	vector <int> max;		// it keeps the indexes of the testcases have maximum covered statements
	for (int i = 0; i < suite_count; i++) {
		int key = v_trick[n][MaxAllowed][i]; // getting keys of map mp, keys are suit orders
		totalRunTime += runTimeAr[key];
		keys.push_back(key);
		int testCaseCount = mp.count(key); // testCase count in the map mp (in one suite)
		auto itr = mp.find(key);
		int testCaseSize = (itr->second.size() + 1) / 2; // size of the testCase

		int element;
		vector <vector <int> > testcases(testCaseCount); // testcases in one suite
		int index = 0;
		for (auto itr = mp.find(key); itr != mp.find(key + 1); itr++) {  // testcases[case1-2-3..][0-1-0-0-1-1....] vector is creating
			stringstream ss;
			ss.str(itr->second);
			Suites[i].push_back(itr->second);
			char c;
			while (ss >> element) {
				testcases[index].push_back(element);
				ss >> c;
			}
			index++;
		}
		// testcases sorting
		int compare = 0;
		vector <int> indexes;
		vector <int> totals;
		for (index = 0; index < testCaseCount; index++) {
			int total = 0;
			for (int j = 0; j < testCaseSize; j++) { 	// finding the highest coverage
				if (testcases[index][j]) total++;
				indexes.push_back(j); // creating an index array
			}
			totals.push_back(total);
			if (total > compare) {			// finding the highest coverage
				compare = total;
			}
			for (int j = 0; j < testCaseSize - 1; j++) {		// sorting the elements of testcases high to low, at the same time indexes of theat elements are sorted with them
				for (int k = 0; k < testCaseSize - j - 1; k++) {
					if (testcases[index][k] > testcases[index][k + 1]) {
						int temp = testcases[index][k + 1];
						testcases[index][k + 1] = testcases[index][k];
						testcases[index][k] = temp;
						int in = indexes[k];
						indexes[k] = indexes[k + 1];
						indexes[k + 1] = in;
					}
				}
			}
			//cout << index << ". testcases indexes: ";
			for (int j = 0; j < testCaseSize; j++) { 	// puting indexes into testcases vector
				testcases[index][j] = indexes[j];
				//cout<<indexes[j]<< " ";
			}
			//cout<<endl;
			indexes.clear();
		}

		for (index = 0; index < testCaseCount; index++) {
			if (totals[index] == compare) {
				max.push_back(index);
			}
		}

		vector <int> distance;
		//cout<<"Distances: ";
		int d = 0;
		for (int j = 0; j < testCaseCount; j++) { 		// EDIT DISTANCE, FINDING DISTANCE
			indexTrick[i].push_back(j);
			if (d < (int)max.size() && j == max[d]) {
				distance.push_back(INT_MAX);
				d++;
			}
			else distance.push_back(editDistance(testcases[j], testcases[max[0]]));
			//cout<<distance[j]<<" ";
		}
		for (int j = 0; j < (int)distance.size() - 1; j++) {		// Sorting distances
			for (int k = 0; k < (int)distance.size() - j - 1; k++) {
				if (distance[k] < distance[k + 1]) {
					int temp = distance[k + 1];
					distance[k + 1] = distance[k];
					distance[k] = temp;
					int in = indexTrick[i][k];
					indexTrick[i][k] = indexTrick[i][k + 1];
					indexTrick[i][k + 1] = in;
				}
			}
		}
		max.clear();
	}
	cout << "Total amount of running time:" << totalRunTime << endl;
	//PRIINTINGGGGGGGGGGGGG
	for (int i = 0; i < suite_count; i++) {
		cout << "TS" << keys[i] +1 << " ";
		for (int j = 0; j < (int)Suites[i].size(); j++) {
			cout << indexTrick[i][j] + 1 << " ";
		}
		cout << endl;
	}
}
