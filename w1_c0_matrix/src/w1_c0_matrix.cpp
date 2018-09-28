#include <iostream>
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
		return matrix.size();
	}

	int GetNumCols() const {
		return matrix[0].size();
	}

private:

	void IsNegativeArgs (const int& num_row, const int& num_col) const {
		if (num_row < 0 || num_col < 0) {
			throw out_of_range("Sub-Zero argument!");
		}
	}

	void IsOutOfRangeArgs (const int& num_row, const int& num_col) const {
		if (static_cast<size_t>(num_row) > matrix.size() - 1 || static_cast<size_t>(num_col) > matrix[0].size()) {
			throw out_of_range("Shang Tsung argument!");
		}
	}

	vector<vector<int>> matrix;
};

int main() {
	Matrix tmp(2, 2);
	tmp.At(0, 0) = 5;
	cout << tmp.At(1, 0);
	return 0;
}
