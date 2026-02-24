//This code compares the runtime of Strassen's algorithm and classical matrix multiplication

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;

using Matrix = vector<vector<int>>;
using namespace chrono;

/* ================= RANDOM MATRIX ================= */

Matrix generateMatrix(int n) {
    Matrix mat(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            mat[i][j] = rand() % 10;  // values 0-9
    return mat;
}

/* ================= CLASSICAL MULTIPLICATION ================= */

Matrix classicalMultiply(const Matrix &A, const Matrix &B) {
    int n = A.size();
    Matrix C(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++)
        for (int k = 0; k < n; k++)
            for (int j = 0; j < n; j++)
                C[i][j] += A[i][k] * B[k][j];

    return C;
}

/* ================= STRASSEN UTILITIES ================= */

Matrix add(const Matrix &A, const Matrix &B) {
    int n = A.size();
    Matrix C(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
    return C;
}

Matrix subtract(const Matrix &A, const Matrix &B) {
    int n = A.size();
    Matrix C(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
    return C;
}

/* ================= STRASSEN RECURSIVE ================= */

Matrix strassen(const Matrix &A, const Matrix &B) {
    int n = A.size();

    if (n == 1) {
        Matrix C(1, vector<int>(1));
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    int k = n / 2;

    Matrix A11(k, vector<int>(k)), A12(k, vector<int>(k));
    Matrix A21(k, vector<int>(k)), A22(k, vector<int>(k));
    Matrix B11(k, vector<int>(k)), B12(k, vector<int>(k));
    Matrix B21(k, vector<int>(k)), B22(k, vector<int>(k));

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j+k];
            A21[i][j] = A[i+k][j];
            A22[i][j] = A[i+k][j+k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j+k];
            B21[i][j] = B[i+k][j];
            B22[i][j] = B[i+k][j+k];
        }
    }

    Matrix M1 = strassen(add(A11, A22), add(B11, B22));
    Matrix M2 = strassen(add(A21, A22), B11);
    Matrix M3 = strassen(A11, subtract(B12, B22));
    Matrix M4 = strassen(A22, subtract(B21, B11));
    Matrix M5 = strassen(add(A11, A12), B22);
    Matrix M6 = strassen(subtract(A21, A11), add(B11, B12));
    Matrix M7 = strassen(subtract(A12, A22), add(B21, B22));

    Matrix C11 = add(subtract(add(M1, M4), M5), M7);
    Matrix C12 = add(M3, M5);
    Matrix C21 = add(M2, M4);
    Matrix C22 = add(subtract(add(M1, M3), M2), M6);

    Matrix C(n, vector<int>(n));
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = C11[i][j];
            C[i][j+k] = C12[i][j];
            C[i+k][j] = C21[i][j];
            C[i+k][j+k] = C22[i][j];
        }
    }

    return C;
}

/* ================= MAIN BENCHMARK ================= */

int main() {
    srand(time(0));

    cout << "Size\tClassical(ms)\tStrassen(ms)\n";

    for (int power = 1; power <= 12; power++) {
        int n = 1 << power;   // 2^power (2, 4, 8, 16, ..., 4096)

        Matrix A = generateMatrix(n);
        Matrix B = generateMatrix(n);

        auto start = high_resolution_clock::now();
        Matrix C1 = classicalMultiply(A, B);
        auto end = high_resolution_clock::now();
        auto classicalTime = duration_cast<milliseconds>(end - start).count();

        start = high_resolution_clock::now();
        Matrix C2 = strassen(A, B);
        end = high_resolution_clock::now();
        auto strassenTime = duration_cast<milliseconds>(end - start).count();

        cout << n << "\t" 
             << classicalTime << "\t\t" 
             << strassenTime << "\n";
    }

    return 0;
}