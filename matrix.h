#include <iostream>
#include <vector>

using namespace std;

class Matrix {
    private:
        vector<vector<double>> data;  // Internal data storage
        int rows;       // Number of rows
        int cols;       // Number of columns

    public:
        
        Matrix() {
            rows = 0;
            cols = 0;
        }
        // Create an empty matrix of zeros of a specified dimension
        Matrix(int r, int c) {
            rows = r;
            cols = c;
            vector<double> newRow;
            for (int i = 0; i < rows; i++) {
                newRow.clear();
                for (int j = 0; j < cols; j++) {
                    newRow.push_back(0);
                }
                data.push_back(newRow);
            }
        }
        // Create a matrix from a vector
        Matrix(vector<double> r) {
            rows = 1;
            cols = r.size();
            data.push_back(r);
        }
        // Create a matrix from a 2d vector
        Matrix(vector<vector<double>> d) {
            rows = d.size();
            cols = d[0].size();
            for (int i = 1; i < d.size(); i++) {
                if (cols != d[i].size()) {
                    throw invalid_argument("Inequal number of columns");
                }
            }
            data = d;
        }

        // Get a row as a vector
        vector<double> getRow(int index) {
            if (index > rows || index < 0) {
                throw invalid_argument("Row index out of bounds");
            }
            else {
                vector<double> row;
                for (int i = 0; i < cols; i++) {
                    row.push_back(data[index][i]);
                }
                return row;
            }
        }
        // Add a new row to the end of the matrix
        void expandRow(vector<double> r) {
            if (r.size() != cols) {
                throw invalid_argument("Cannot add a row of size " + 
                    to_string(r.size()) + " to a matrix with " + to_string(cols) +
                    " column length.");
            }
            else {
                data.push_back(r);
                rows++;
            }
        }

        // Get a column as a vector
        vector<double> getCol(int index) {
            if (index > cols || index < 0) {
                throw invalid_argument("Column index out of bounds");
            }
            else {
                vector<double> col;
                for (int i = 0; i < rows; i++) {
                    col.push_back(data[i][index]);
                }
                return col;
            }
        }
        // Add a new column to the end of the matrix
        void expandCol(vector<double> c) {
            if (c.size() != rows) {
                throw invalid_argument("Cannot add a column of size " + 
                    to_string(c.size()) + " to a matrix with " + to_string(rows) +
                    " row length.");
            }
            else {
                for (int i = 0; i < rows; i++) {
                    data[i].push_back(c[i]);
                }
            }
            cols++;
        }

        // Print the matrix
        void printMatrix() {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    cout << data[i][j] << "\t";
                }
                cout << endl;
            }
            return;
        }

        Matrix transpose() {
            Matrix m = Matrix(this->getCol(0));
            for (int i = 1; i < cols; i++) {
                m.expandRow(this->getCol(i));
            }
            return m;
        }

        // Swap two rows
        void rowSwap(int i1, int i2) {
            vector<double> temp = data[i1];
            data[i1] = data[i2];
            data[i2] = temp;
            return;
        }
        // Multiply a row by a scalar
        void rowScal(int index, double scalar) {
            for (int i = 0; i < cols; i++) {
                data[index][i] = data[index][i] * scalar;
            }
            return;
        }
        // Add s * row i2 to i1
        void rowSum(int i1, int i2, double s = 1) {
            for (int i = 0; i < cols; i++) {
                data[i1][i] += s * data[i2][i];
            }
            return;
        }

        // Assign a matrix with a 2d vector
        void operator=(vector<vector<double>> d) {
            if (rows != d.size()) {
                throw invalid_argument("Inequal number of rows");
            }
            for (int i = 0; i < d.size(); i++) {
                if (cols != d[i].size()) {
                    throw invalid_argument("Inequal number of columns");
                }
            }
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    data[i][j] = d[i][j];
                }
            }
            return;
        }
};