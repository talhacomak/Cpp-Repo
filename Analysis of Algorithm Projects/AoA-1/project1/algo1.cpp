#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <time.h> 

using namespace std;

void merge(vector <int> &vec, int l, int m, int h)
{
	int i, j, k;
	int x = m - l + 1;
	int y = h - m;
	vector <int> R;
	vector <int> L;
	for (i = 0; i < x; i++)
		L.push_back(vec[l + i]);
	for (j = 0; j < y; j++)
		R.push_back(vec[m + 1 + j]);

	i = 0; j = 0;  k = l;
	
	while (i < x && j < y)
	{
		if (L[i] <= R[j])
		{
			vec[k] = L[i];
			i++;
		}
		else
		{
			vec[k] = R[j];
			j++;
		}
		k++;
	}
	while (i < x)
	{
		vec[k] = L[i];
		i++;
		k++;
	}
	while (j < y)
	{
		vec[k] = R[j];
		j++;
		k++;
	}
}


void mergeSort(vector <int> &vec, int l, int h)
{
	if (l < h)
	{
		int m = l + (h - l) / 2;
		mergeSort(vec, l, m);
		mergeSort(vec, m + 1, h);
		merge(vec, l, m, h);
	}
}

int main(int argv, char* argc[]) {
	ifstream sort(argc[3]);
	if (!sort.is_open()) {
		cout << argc[3] << " cannot open!\n";
		return 1;
	}
	stringstream ss;
	ss << argc[2];
	int n;
	ss >> n;
	int x;
	vector <int> vec;
	int i = 0;
	while (sort >> x && i<n) {
		vec.push_back(x);
		i++;
	}
	clock_t t;
	if (argc[1][0] == 'b') { // BUBBLE SORT
		int k;
		t = clock();
		bool sorted = false;
		for (int i = n; i > 1 && sorted == false; i--) {
			sorted = true;
			for (int j = 1; j < i; j++) {
				if (vec[j] < vec[j - 1]) {
					k = vec[j];
					vec[j] = vec[j - 1];
					vec[j - 1] = k;
					sorted = false;
				}
			}
		}
		t = clock() - t;
	}
	else if (argc[1][0] == 'm') { // MERGE
		t = clock();
		mergeSort(vec, 0, n - 1);
		t = clock() - t;
	}
	else {
		cout<<"no search method is selected!";
		return 1;
	}

	ofstream of("output.txt");
	for (i = 0; i < n; i++) {
		of << vec[i] << "\n";
	}

	cout << argc[1][0] << " " << ((float)t) / CLOCKS_PER_SEC << " seconds took\n";
	return 0;
}
