#include "pch.h"
#include "Matrix.h"

using namespace std;

int main()
{
    cout << "Begin program!\n\n";

    const size_t mat1_rows = 1024;
    const size_t mat1_cols = 1024;
    const size_t mat2_rows = mat1_cols;
    const size_t mat2_cols = 1024;
    cout << "Matrix 1: " << mat1_rows << "x" << mat1_cols << " (rols x cols)\n";
    cout << "Matrix 2: " << mat2_rows << "x" << mat2_cols << " (rols x cols)\n\n";

    Matrix<float, mat1_rows, mat1_cols>* matrix1 = new Matrix<float, mat1_rows, mat1_cols>;
    Matrix<float, mat2_rows, mat2_cols>* matrix2 = new Matrix<float, mat2_rows, mat2_cols>;
    
    matrix1->Fill(0, 5);
    matrix2->Fill(0, 5);

    auto time1 = chrono::high_resolution_clock::now();
    Matrix<float, mat1_rows, mat2_cols>* result1 = matrix1->NaiveMultiply(matrix2);

    auto time2 = chrono::high_resolution_clock::now();
    Matrix<float, mat1_rows, mat2_cols>* result2 = matrix1->TransposeMultiply(matrix2);

    auto time3 = chrono::high_resolution_clock::now();
    Matrix<float, mat1_rows, mat2_cols>* result3 = matrix1->MultiThreadMultiply(matrix2);

    auto time4 = chrono::high_resolution_clock::now();
    
    auto naiveTime = chrono::duration_cast<chrono::milliseconds>(time2 - time1);
    auto transposeTime = chrono::duration_cast<chrono::milliseconds>(time3 - time2);
    auto multiThreadTime = chrono::duration_cast<chrono::milliseconds>(time4 - time3);

    cout << "Naive multiply took " << naiveTime.count() << " milliseconds\n";
    cout << "Transposed multiply took " << transposeTime.count() << " milliseconds\n";
    cout << "Multi Thread multiply took " << multiThreadTime.count() << " milliseconds\n";

    delete matrix1;
    delete matrix2;
    delete result1;
    delete result2;
    delete result3;

    return 0;
}