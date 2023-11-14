#include <bits/stdc++.h>
using namespace std;

#define n 2000

vector<int> rowL(n);
vector<int> rowS(n/2);
vector<vector<int>> A(n, rowL), B(n, rowL), C(n, rowL); 
vector<vector<int>> P1(n/2,rowS), P2(n/2,rowS), P3(n/2,rowS)
				  , P4(n/2,rowS), P5(n/2,rowS), P6(n/2,rowS)
				  , P7(n/2,rowS), temp1(n/2,rowS), temp2(n/2,rowS);

int len = n/2;

class Mat {
public: 
	vector<vector<int>>& arr = A; 
	int x;
	int y;

	Mat(vector<vector<int>>& ref, int i, int j){
		this->arr = ref;
		this->x = i;
		this->y = j;
	}
};

void mul(Mat A, Mat B, Mat C){

	for(int i=0; i<len; ++i)
		for(int k=0; k<len; ++k)
			for(int j=0; j<len; ++j)
				C.arr[C.x+i][C.y+j] = A.arr[A.x+i][A.y+k] * B.arr[B.x+k][B.y+j];
}
void add(Mat A, Mat B, Mat C){

	for(int i=0; i<len; ++i)
		for(int j=0; j<len; ++j)
			A.arr[A.x+i][A.x+j] = B.arr[B.x+i][B.x+j] + C.arr[C.x+i][C.x+j];
}
void sub(Mat A, Mat B, Mat C){

	for(int i=0; i<len; ++i)
		for(int j=0; j<len; ++j)
			A.arr[A.x+i][A.x+j] = B.arr[B.x+i][B.x+j] - C.arr[C.x+i][C.x+j];
}


int main(){

	#ifndef ONLINE_JUDGE
	freopen("./outputs/input.txt", "r", stdin);
    freopen("./outputs/output_stassens.txt", "w", stdout);
    #endif

	auto start = chrono::high_resolution_clock::now();

	Mat a = Mat(A, 0, 0);
	Mat b = Mat(A, 0, len);
	Mat c = Mat(A, len, 0);
	Mat d = Mat(A, len, len);

	Mat e = Mat(B, 0, 0);
	Mat f = Mat(B, 0, len);
	Mat g = Mat(B, len, 0);
	Mat h = Mat(B, len, len);

	Mat t1 = Mat(temp1, 0, 0);
	Mat t2 = Mat(temp2, 0, 0);

	Mat p1 = Mat(P1, 0, 0);
	Mat p2 = Mat(P2, 0, 0);
	Mat p3 = Mat(P3, 0, 0);
	Mat p4 = Mat(P4, 0, 0);
	Mat p5 = Mat(P5, 0, 0);
	Mat p6 = Mat(P6, 0, 0);
	Mat p7 = Mat(P7, 0, 0);

	add(a, d, t1);
	add(e, h, t2);
	mul(t1, t2, p1); // p1

	sub(g, e, t1);
	mul(d, t1, p2);     // p2

	add(a, b, t1);
	mul(t1, h, p3);     // p3

	sub(b, d, t1);
	add(g, h, t1);
	mul(t1, t2, p4); // p4

	sub(f, h, t1);
	mul(a, t1, p5);     // p5

	add(c, d, t1);
	mul(t1, e, p6);     // p6

	sub(a, c, t1);
	add(e, f, t2);
	mul(t1, t2, p7); // p7

	for(int i=0; i<len; ++i)
		for(int j=0; j<len; ++j){
			C[i][j] = P1[i][j] + P2[i][j] - P3[i][j] + P4[i][j];
			C[i][j+len] = P5[i][j] + P3[i][j];
			C[i+len][j] = P6[i][j] + P2[i][j];
			C[i+len][j+len] = P1[i][j] + P5[i][j] - P6[i][j] - P7[i][j];
		}

	auto stop = chrono::high_resolution_clock::now();

	cout << "MATRIX SIZE :: " << 2000 << endl;
	cout << "STRASSESN'S :: " << endl;
	cout << "EXECUTION TIME :: " << chrono::duration_cast<chrono::microseconds>(stop - start).count() << " µs";
	cout << "\n======================\n\n";

	return 0;
}