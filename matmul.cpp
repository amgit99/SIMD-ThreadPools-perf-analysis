#include<bits/stdc++.h>

#define n 2000

using namespace std;

int A[n][n];
int B[n][n];
int C[n][n];

int main(){

	#ifndef ONLINE_JUDGE
	freopen("./outputs/input.txt", "r", stdin);
    freopen("./outputs/output.txt", "a", stdout);
    #endif

	auto start = chrono::high_resolution_clock::now();
	
	for(int i=0; i < n ; ++i)
		for(int k=0; k < n ; ++k)
			for(int j=0; j < n ; ++j)
				C[i][j] += A[i][k]*B[k][j];

	auto stop = chrono::high_resolution_clock::now();
	cout << "MATRIX SIZE :: " << n << endl;
	cout << "LOOP ORDER :: " << "j k i" << endl;
	cout << "EXECUTION TIME :: " << chrono::duration_cast<chrono::microseconds>(stop - start).count() << " µs";
	cout << "\n======================\n\n";

	return 0;
}