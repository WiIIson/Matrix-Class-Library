#include "matrix.h"

int main() {
    vector<vector<double>> v1 = {{1, 1/3}, {0, 1}};
    vector<vector<double>> v2 = {{1, 0}, {-3/4, 3/8}};
    vector<vector<double>> v3 = {{1, 0}, {-2, 1}};
    vector<vector<double>> v4 = {{-1/3, 0}, {0, 1}};
    vector<vector<double>> v5 = {{-3, 1}, {2, 2}};

    Matrix m1 = Matrix(v1);
    Matrix m2 = Matrix(v2);
    Matrix m3 = Matrix(v3);
    Matrix m4 = Matrix(v4);
    Matrix m5 = Matrix(v5);

    //m1.printMatrix();
    //m2.printMatrix();

    Matrix m = m1 * m2 * m3 * m4 * m5;
    m.printMatrix();


    return 0;
}