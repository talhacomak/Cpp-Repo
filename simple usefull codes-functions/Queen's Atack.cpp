#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

int queensAttack(int n, int k, int r_q, int c_q, vector<vector<int> > obstacles) {
    if(n<10000){  //engel varken Queen's Atack
    int** saha = new int*[n];
    int i, j, m, x, res=0;
    r_q--;
    c_q--;
    for(i=0; i<n; i++){
        saha[i] = new int[n];
        for(j=0; j<n; j++){
            saha[i][j] = 0;
        }
    }
    for(i=0; i<k; i++){
        m=obstacles[i][0];
        x=obstacles[i][1];
        saha[m-1][x-1] = 1;
    }
    
    for(i=r_q+1; i<n; i++){
        if(saha[i][c_q] == 1) break;
        res++;
    }
    for(i=r_q-1; i>=0; i--){
        if(saha[i][c_q] == 1) break;
        res++;
    }
    for(i=c_q+1; i<n; i++){
        if(saha[r_q][i] == 1) break;
        res++;
    }
    for(i=c_q-1; i>=0; i--){
        if(saha[r_q][i] == 1) break;
        res++;
    }
    
    j=c_q;
    for(i=r_q+1; i<n; i++){
        j++;
        if(j>=n){
            break;
        }
        if(saha[i][j] == 1) {
            break;
        }
        res++;
    }
    
    j=c_q;
    for(i=r_q-1; i>=0; i--){
        j--;
        if(j<0){
            break;
        }
        if(saha[i][j] == 1) {
            break;
        }
        res++;
    }
    
    j=c_q;
    for(i=r_q+1; i<n; i++){
        j--;
        if(j<0){
            break;
        }
        if(saha[i][j] == 1) {
            break;
        }
        res++;
    }
    
    j=c_q;
    for(i=r_q-1; i>=0; i--){
        j++;
        if(j>=n){
            break;
        }
        if(saha[i][j] == 1) {
            break;
        }
        res++;
    }
    return res;
    }
    else{ // engel yokken Queen's Atack
        (double)n;
        if(fabs(n/2-r_q) > fabs(n/2-c_q)){
            if(n/2>r_q){
                return (int)(3*n-3 + 2*(r_q-1) + 0.5);
            }
            else{
                return (int)(3*n-3 + 2*(n-r_q) + 0.5);
            }
        }
        else{
            if(n/2>c_q){
                return (int)(3*n-3 + 2*(c_q-1) + 0.5);
            }
            else{
                return (int)(3*n-3 + 2*(n-c_q) + 0.5);
            }
        }
    }
}

int main()
{
    int n, k, r_q, c_q;
    cin>>n>>k;
	cin>>r_q>>c_q;
    vector <vector <int> > obstacles(k);
    for (int i = 0; i < k; i++) {
        obstacles[i].resize(2);

        for (int j = 0; j < 2; j++) {
            cin >> obstacles[i][j];
        }
    }

    int result = queensAttack(n, k, r_q, c_q, obstacles);

    cout << result << "\n";


    return 0;
}


