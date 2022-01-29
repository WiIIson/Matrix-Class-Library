#include <iostream>
#include <vector>

using namespace std;

// A more simplified 2D vector
class Matrix {
    protected:
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
                throw invalid_argument(
                    "Tried to add a row with " + 
                    to_string(r.size()) + " columns to a Matrix with " + 
                    to_string(cols) + " columns."
                );
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
                throw invalid_argument(
                    "Tried to add a column with " + 
                    to_string(c.size()) + " rows to a Matrix with " +
                    to_string(rows) + " rows."
                );
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

        Matrix inverse() {

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
        
        Matrix operator*(Matrix m) {
            if (cols != m.rows) {
                throw invalid_argument(
                    "Trying to multiply a " + to_string(rows) + "x" +
                    to_string(cols) + " Matrix by a " + to_string(m.rows) +
                    "x" + to_string(m.cols) + " Matrix"
                );
            }
            Matrix n = Matrix(rows, m.cols);
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < m.cols; j++) {
                    int rowSum = 0;
                    for (int k = 0; k < cols; k++) {
                        rowSum += data[i][k] * m.data[k][j];
                    }
                    n.data[i][j] = rowSum;
                }
            }
            return n;
        }
};

// A matrix representing a formula, which can be solved using 
// elementary row operations
class Augmatrix: public Matrix {
    public:
        Augmatrix(vector<vector<double>> v) : Matrix(v) { }

        void printMatrix() {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols - 1; j++) {
                    cout << data[i][j] << "\t";
                }
                cout << "\t|\t" << data[i][cols] << endl;
            }
            return;
        }
};