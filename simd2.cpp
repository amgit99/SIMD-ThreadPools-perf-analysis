#include <bits/stdc++.h>
#include <arm_neon.h>
using namespace std;

int A[20000];
int B[20000];
int C[4];
int ans;
int32x4_t ansV;

int main(){

	#ifndef ONLINE_JUDGE
	freopen("./outputs/input.txt", "r", stdin);
    freopen("./outputs/simd2_output.txt", "w", stdout);
    #endif

    memset(A, -1, sizeof(A));
    memset(B, -1, sizeof(B));
    ans = 0;

    auto start = chrono::high_resolution_clock::now();
    for(int i=1; i<20000; i+=2) ans += A[i]*B[i];
    auto stop = chrono::high_resolution_clock::now();

    cout << "ARRAY SIZE :: " << 20000 << endl;
	cout << "OUTPUT :: " << ans << endl;
	cout << "EXECUTION TIME WITHOUT SIMD :: " << chrono::duration_cast<chrono::microseconds>(stop - start).count() << " µs";
	cout << "\n======================\n\n";


	memset(C, 0, sizeof(C));
	cout << "Hello Intrinsics !!" << endl;

	ans = 0;
	int32x4_t vec1, vec2;

    start = chrono::high_resolution_clock::now();
	for (int i = 0; i < 20000; i += 4) {
        // Load 4 elements from array1 and array2
        vec1 = vld1q_s32(&A[i]);
        vec2 = vld1q_s32(&B[i]);
        // Store the result back to the result array
        vst1q_s32(&C[0], vmlaq_s32(ansV, vec1, vec2));
        ans += C[1]+C[3];
    }
	stop = chrono::high_resolution_clock::now();

	cout << "ARRAY SIZE :: " << 20000 << endl;
	cout << "OUTPUT " << ans << endl;
	cout << "EXECUTION TIME WITH SIMD :: " << chrono::duration_cast<chrono::microseconds>(stop - start).count() << " µs";
	cout << "\n======================\n\n";

	return 0;
}