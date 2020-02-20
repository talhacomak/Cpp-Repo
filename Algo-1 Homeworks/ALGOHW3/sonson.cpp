#include <iostream>
#include <vector>
#include <climits>
#include "hw3.h"
#include "BST.h"

using namespace std;

struct Node{
	int size;
	int ordinal;
};

/*
int east[] = { 2,2,3 };
int eor[] = { 2,4,5 };
int west[] = { 1,1,1,5,6 };
int wor[] = { 4,5,7,1,2 };*/

int main(){
	int east[] = { 11,18,7,2,15,16,3,12,17 };
	int eor[] = { 32,5,16,6,2,4,13,7,13 };
	int west[] = { 27,3,4,8,11,2,3 };
	int wor[] = { 15,8,22,6,4,7,10 };
	HW3_Result hw = hw3(9, east, eor, 7, west, wor);
	cout<<hw.blackNodeCount<<" "<<hw.packageCount<< " " <<hw.redNodeCount;
}

HW3_Result hw3(int eastWarehousePackageCount, int eastWarehousePackageSizes [], int eastWarehousePackageOrdinals [], 
			   int westWarehousePackageCount, int westWarehousePackageSizes [], int westWarehousePackageOrdinals [] ){
	vector <Node> East;
	vector <Node> West;
	int i = 0;
	for(; i<eastWarehousePackageCount && i<westWarehousePackageCount; i++){
		East.push_back({eastWarehousePackageSizes[i], eastWarehousePackageOrdinals[i]});
		West.push_back({westWarehousePackageSizes[i], westWarehousePackageOrdinals[i]});
	}
	int higher = eastWarehousePackageCount > westWarehousePackageCount ? eastWarehousePackageCount : westWarehousePackageCount;
	if (higher == eastWarehousePackageCount){
		for(; i<higher; i++){
			East.push_back({eastWarehousePackageSizes[i], eastWarehousePackageOrdinals[i]});
		}
	}
	else{
		for(; i<higher; i++){
			West.push_back({westWarehousePackageSizes[i], westWarehousePackageOrdinals[i]});
		}
	}
	
	bool sorted = false;
	for (i = eastWarehousePackageCount; i > 1 && sorted == false; i--) {
		sorted = true;
		for (int j = 1; j < i; j++) {
			if (East[j].size < East[j - 1].size) {
				Node k = East[j];
				East[j] = East[j - 1];
				East[j - 1] = k;
				sorted = false;
			}
		}
	}
	
	sorted = false;
	for (i = westWarehousePackageCount; i > 1 && sorted == false; i--) {
		sorted = true;
		for (int j = 1; j < i; j++) {
			if (West[j].size < West[j - 1].size) {
				Node k = West[j];
				West[j] = West[j - 1];
				West[j - 1] = k;
				sorted = false;
			}
		}
	}
	

	int compare = East[0].size;
	i = 0;
	while(compare == East[i].size && i < East.size()){
		i++;
	}
	vector <Node> package;
	package.assign(East.begin(), East.begin()+i); 
	East.erase(East.begin(), East.begin()+i);

	int low_ordinal = INT_MAX;
	for(i = 0; i<package.size(); i++){
		if(package[i].ordinal < low_ordinal) low_ordinal = package[i].ordinal;
	}
	

	while(West.size() != 0 && East.size() != 0){
		//WESTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
		vector <Node> tempPack;
		if(low_ordinal <= West.size()){
			tempPack.push_back({West[low_ordinal-1].size, West[low_ordinal-1].ordinal});
			West.erase(West.begin()+low_ordinal-1);
			for(i=0; i<West.size(); i++){
				if(package[0].size < West[i].size){
					West.insert(West.begin() + i, package.begin(), package.end());
					break;
				}
			}

			if (i >= West.size()) {
				West.insert(West.end(), package.begin(), package.end());
			}
			package.clear();
			package.push_back({tempPack[0].size, tempPack[0].ordinal});
			tempPack.clear();
		}
		else{
			compare = West[0].size;
			i = 0;
			while(i < West.size() && compare == West[i].size){
				i++;
			}
			package.clear();
			package.assign(West.begin(), West.begin()+i); 
			West.erase(West.begin(), West.begin()+i);
		}
		low_ordinal = INT_MAX;
		for (i = 0; i < package.size(); i++) {
			if (package[i].ordinal < low_ordinal) low_ordinal = package[i].ordinal;
		}

		if(West.size() == 0 || East.size() == 0) break;
		
		//EASTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
		if (low_ordinal <= East.size()) {
			tempPack.push_back({ East[low_ordinal - 1].size, East[low_ordinal - 1].ordinal });
			East.erase(East.begin() + low_ordinal - 1);
			for (i = 0; i < East.size(); i++) {
				if (package[0].size < East[i].size) {
					East.insert(East.begin() + i, package.begin(), package.end());
					break;
				}
			}

			if (i >= East.size()) {
				East.insert(East.end(), package.begin(), package.end());
			}
			package.clear();
			package.push_back({ tempPack[0].size, tempPack[0].ordinal });
			tempPack.clear();
		}
		else {
			compare = East[0].size;
			i = 0;
			while (i < East.size() && compare == East[i].size) {
				i++;
			}
			package.clear();
			package.assign(East.begin(), East.begin() + i );
			East.erase(East.begin(), East.begin() + i );
		}
		low_ordinal = INT_MAX;
		for (i = 0; i < package.size(); i++) {
			if (package[i].ordinal < low_ordinal) low_ordinal = package[i].ordinal;
		}
	}

	int red;
	int count;
	if(East.size() == 0){
		for(i=0; i<West.size(); i++){
			if(package[0].size < West[i].size){
				West.insert(West.begin() + i, package.begin(), package.end());
				break;
			}
		}
		if(i == West.size()) West.insert(West.end(), package.begin(), package.end());
		package.clear();
		RBTree t;
		for(i=0; i<West.size(); i++){
			t.insert(West[i].size, West[i].ordinal);
		}
		count = West.size();
		red = t.get_red();
	}
	else{
		for(i=0; i<East.size(); i++){
			if(package[0].size < East[i].size){
				East.insert(East.begin() + i, package.begin(), package.end());
				break;
			}
		}
		if(i == East.size()) East.insert(East.end(), package.begin(), package.end());
		package.clear();
		RBTree t;
		for(i=0; i<East.size(); i++){
			t.insert(East[i].size, East[i].ordinal);
		}
		count = East.size();
		red = t.get_red();
	}
	
	return {count, red, count-red};
}

