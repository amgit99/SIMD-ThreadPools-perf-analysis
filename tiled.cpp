#include<bits/stdc++.h>

#define n 2048

using namespace std;

int A[n][n];
int B[n][n];
int C[n][n];

int tile_size = 32;

int main(int argc, char* argv[]){
	#ifndef ONLINE_JUDGE
	freopen("./outputs/input.txt", "r", stdin);
    freopen("./outputs/tiled_output.txt", "a", stdout);
    #endif

	tile_size = stoi(argv[1]);

	auto start = chrono::high_resolution_clock::now();

    for(int tx=0; tx < n/tile_size; ++tx){
        for(int ty=0; ty < n/tile_size; ++ty){

            for(int i=0; i<tile_size; ++i){
                for(int k=0; k<n; ++k){
                    for(int j=0; j<tile_size; ++j)
                        C[tx+i][ty+j] = A[tx+i][k]*B[k][tx+j];
                }
            }
        }
    }

	auto stop = chrono::high_resolution_clock::now();

	cout << "MATRIX SIZE :: " << n << endl;
	cout << "TILE SIZE :: " << tile_size << endl;
	cout << "TILED NO THREADING, LOOP ORDER :: " << "j k i" << endl;
	cout << "EXECUTION TIME :: " << chrono::duration_cast<chrono::microseconds>(stop - start).count() << " µs";
	cout << "\n======================\n\n";

	return 0;
}