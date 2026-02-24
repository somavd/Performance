//In this code, we will try to optimize the classical matrix multiplication algorithm better memory access patterns

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>
using namespace std;

using Matrix = vector<vector<long long>>;
using namespace chrono;

/* ================= RANDOM MATRIX ================= */

Matrix generateMatrix(int n) {
    Matrix mat(n, vector<long long>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            mat[i][j] = rand() % 10;  // values 0-9
    return mat;
}

/* ================= CLASSICAL MULTIPLICATION ================= */

Matrix classicalMultiply(const Matrix &A, const Matrix &B) {
    int n = A.size();
    Matrix C(n, vector<long long>(n, 0));

    for (int i = 0; i < n; i++)
        for (int k = 0; k < n; k++)
            for (int j = 0; j < n; j++)
                C[i][j] += A[i][k] * B[k][j];

    return C;
}
/* ================= MAIN BENCHMARK ================= */

int main() {
    srand(time(0));
    int trials = 5;
    int powers = 12;
    vector<int> results(powers, 0);

    for (int i = 0; i < trials; i++) {
        cout << "Trial " << i + 1 << "\n";

        cout << "Size\tClassical(ms)\n";

        for (int power = 1; power <= powers; power++) {
            int n = 1 << power;   // 2^power (2, 4, 8, 16, ..., 4096)

            Matrix A = generateMatrix(n);
            Matrix B = generateMatrix(n);

            auto start = high_resolution_clock::now();
            Matrix C1 = classicalMultiply(A, B);
            auto end = high_resolution_clock::now();
            auto classicalTime = duration_cast<milliseconds>(end - start).count();

            cout << n << "\t" 
                << classicalTime << "\n";
            results[power - 1] += classicalTime;
        }
    }
    
    ofstream outFile("results/output_data.csv");
    outFile.clear();
    outFile << "Name";
    for(int i = 0; i < powers; i++) {
        outFile << "," << (1 << (i + 1));
    }
    outFile << "\n";
    outFile << "Classical";
    for (int i = 0; i < powers; i++) {
        outFile << "," << results[i] / trials;
    }
    outFile << "\n";
    outFile.close();
    return 0;
}