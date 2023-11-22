
#define n 4000
int A[n];
int X[n];
int B[n][n];

int main(){
    for (int i = 0; i < n - 1; i++) {
        A[i] = 0;
        for (int j = 1; j < n - 1; j++)
            A[i] += 0.33*(B[i][j] * X[j]);
    }
    return 0;
}