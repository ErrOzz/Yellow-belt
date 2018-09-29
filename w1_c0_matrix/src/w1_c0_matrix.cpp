#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

class Matrix {
public:

	Matrix() {}

	Matrix(const int& num_rows, const int& num_cols) {
		Reset(num_rows, num_cols);
	}

	void Reset(const int& num_rows, const int& num_cols) {
		IsNegativeArgs(num_rows, num_cols);
		n_cols = num_cols;
		vector<int> row(num_cols);
		matrix.assign(num_rows, row);
	}

	int At(const int& num_row, const int& num_col) const {
		IsNegativeArgs(num_row, num_col);
		IsOutOfRangeArgs(num_row, num_col);
		return matrix[num_row][num_col];
	}

	int& At(const int& num_row, const int& num_col) {
		IsNegativeArgs(num_row, num_col);
		IsOutOfRangeArgs(num_row, num_col);
		return matrix[num_row][num_col];
	}

	int GetNumRows() const {
		return int(matrix.size());
	}

	int GetNumColumns() const {
		return n_cols;
	}

private:

	void IsNegativeArgs (const int& num_row, const int& num_col) const {
		if (num_row < 0 || num_col < 0) {
			throw out_of_range("Sub-Zero argument!");
		}
	}

	void IsOutOfRangeArgs (const int& num_row, const int& num_col) const {
		if (size_t(num_row) + 1 > matrix.size() || size_t(num_col) + 1 > matrix[0].size()) {
			throw out_of_range("Shang Tsung argument!");
		}
	}

	vector<vector<int>> matrix;
	int n_cols = 0;
};

istream& operator >> (istream& stream, Matrix& matrix) {
	int num_rows, num_cols;
	stream >> num_rows >> num_cols;
	matrix.Reset(num_rows, num_cols);
	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_cols; ++j) {
			stream >> matrix.At(i, j);
		}
	}
	return stream;
}

ostream& operator << (ostream& stream, const Matrix& matrix) {
	int num_rows = matrix.GetNumRows();
	int num_cols = matrix.GetNumColumns();
	stream << num_rows << " " << num_cols << endl;
	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_cols; ++j) {
			stream << matrix.At(i, j) << [&] {	if (j + 1 != num_cols) return " ";
												else return "\n";	}();
		}
	}
	return stream;
}

bool operator == (const Matrix& lhs, const Matrix& rhs) {
	int num_rows = lhs.GetNumRows();
	int num_cols = lhs.GetNumColumns();
	if (num_rows != rhs.GetNumRows() || num_cols != rhs.GetNumColumns()) {
		return false;
	}
	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_cols; ++j) {
			if (lhs.At(i, j) != rhs.At(i, j)) {
				return false;
			}
		}
	}
	return true;
}

Matrix operator + (const Matrix& lhs, const Matrix& rhs) {
	int num_rows = lhs.GetNumRows();
	int num_cols = lhs.GetNumColumns();
	if (num_rows != rhs.GetNumRows() || num_cols != rhs.GetNumColumns()) {
		throw invalid_argument("Fatality argument!");
	}
	Matrix matrix(num_rows, num_cols);
	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_cols; ++j) {
			matrix.At(i, j) = lhs.At(i, j) + rhs.At(i, j);
		}
	}
	return matrix;
}

int main() {
	  Matrix one;
	  Matrix two;

	  cin >> one >> two;
	  cout << one + two << endl;
	  return 0;
}
