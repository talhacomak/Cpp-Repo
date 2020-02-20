#include <iostream>

using namespace std;

void swap(int* a, int* b){
	int t = *a;
	*a = *b;
	*b = t;
}

int fact(int* list, int k, int m){
	int i;
	if(k==m){
		for(i=0; i<=m; i++){
			cout<<list[i]<<" ";
		}
		cout<<endl;
	}
	else{
		for(i=k; i<=m; i++){
			swap(&list[k], &list[i]);
			fact(list, k+1, m);
			swap(&list[k], &list[i]);
		}
	}
}
int main(){
	int list[3] = {1,2,3};
	fact(list,0,2);
}
