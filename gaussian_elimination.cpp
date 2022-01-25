#include "matrix.h"

int main() {
    vector<vector<double>> v = {{1, 2, 3}, {4, 5, 6}};
    Matrix m = Matrix(v);

    vector<double> newRow = {7, 8, 9};
    m.expandRow(newRow);
    vector<double> newCol = {1, 2, 3};
    m.expandCol(newCol);
    
    m.rowSum(1,0,-4);
    m.rowSum(2,0,-7);

    m.printMatrix();


    return 0;
}