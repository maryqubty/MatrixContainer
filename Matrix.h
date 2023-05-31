// Mary Qubty 206528275
// Nasem Sawaid 209290733




#pragma once
#include <string>
#include <typeinfo>
#include <iostream>


template <int row, int col, typename T = int>
class Matrix {
private:
	const int matrixRow;
	const int matrixCol;
	T** matrix;

public:

	//another helper function:
	friend T getSumMul(T** m1, T** m2, int row, int col, int size);
	//constructor
	Matrix(T num = 0) : matrixRow(row), matrixCol(col)
	{
		// Allocate memory for the rows
		matrix = new T * [this->matrixRow];
		if (matrix == NULL) return;

		// Allocate memory for each row and initialize with num
		for (int i = 0; i < this->matrixRow; i++) {
			matrix[i] = new T[this->matrixCol];
			if (matrix[i] == NULL) return;
			for (int j = 0; j < this->matrixCol; j++) {
				matrix[i][j] = num;
			}
		}
	}
	//destructor
	~Matrix()
	{
		// Free memory for each row
		for (int i = 0; i < matrixRow; i++) {
			delete[] matrix[i];
		}

		// Free memory for the rows
		delete[] matrix;
	}
	//copy
	Matrix(const Matrix& copy) :matrixRow(copy.matrixRow), matrixCol(copy.matrixCol)
	{
		// Allocate memory for the rows
		this->matrix = new T * [matrixRow];
		if (this->matrix == NULL) return;

		// Allocate memory for each row and initialize with num
		for (int i = 0; i < matrixRow; i++) {
			matrix[i] = new T[matrixCol];
			if (matrix[i] == NULL) return;
			for (int j = 0; j < matrixCol; j++) {
				matrix[i][j] = copy.matrix[i][j];
			}
		}
	}
	//operator = 
	Matrix& operator=(const Matrix& that)
	{
		    if (this == &that) {
			    return *this;
			 }		
		//now let's copy values
		for (int i = 0; i < that.matrixRow; i++) {
			for (int j = 0; j < that.matrixCol; j++) {
				this->matrix[i][j] = that.matrix[i][j];
			}
		}
		return *this;
	}
	//operator + matrix
	Matrix operator+(const Matrix& mat) const
	{
		Matrix<row, col, T>  matTmp;
		//now, add:
		for (int i = 0; i < this->matrixRow; i++) {
			for (int j = 0; j < this->matrixCol; j++) {
				matTmp.matrix[i][j] = this->matrix[i][j] + mat.matrix[i][j];
			}
		}
		return matTmp;
	}
	//operator + scalar
	 Matrix operator+(T scalar) const
	{
		Matrix<row, col, T>  mat;
		//now, add:
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				mat.matrix[i][j] = this->matrix[i][j] + scalar;
			}
		}
		return mat;
	}
	//an overloaded + operator for scalar + matrix
	friend Matrix operator+(const T i, const Matrix& mat) {
		Matrix<row, col, T>  matTmp;
		matTmp = mat + i;
		return matTmp;
	}
	///an overloaded += operator for scalar += matrix
	Matrix& operator+=(const T i) {
		*this = *this + i;
		return *this;
	}

	//operator -:
	Matrix operator-(T scalar) const
	{
		//let's just call the add operator with -scalar
		Matrix<row, col, T>  matTmp;
		matTmp = *this + (-1*scalar);
		return matTmp;
	}
	//an overloaded - operator for scalar - matrix
	friend Matrix operator-(const T i, const Matrix& mat) {

		Matrix<row, col, T>  matTmp;
		matTmp = mat * T(-1);
		matTmp = matTmp + i;
		return matTmp;
	}
	//an overloaded - operator for (-matrix)
	friend Matrix operator-(const Matrix& mat) {

		return (mat * T(-1));
	}
	//an overloaded - operator for matrix - matrix:
	Matrix operator-(const Matrix& mat2) const
	{
		return *this + (-mat2);
	}
	//an overloaded -= operator 
	Matrix& operator-=(const T i) {
		*this = *this - i;
		return *this;
	}
	//operator * scalar:
	Matrix operator*(T scalar) const
	{
		Matrix<row, col, T> matTmp;
		//now, multiply:
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				matTmp.matrix[i][j] = ((this->matrix[i][j]) * scalar);
			}
		}
		return matTmp;
	}
	//operator * matrix:
	Matrix operator*(const Matrix& that) const {

		//check if col = row:
		if (that->row != that->col) {
			return *this;
		}
		Matrix<row, col, T>  mat1;
		//now, let's get to work:
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				mat1.matrix[i][j] = getSumMul(this->matrix, that->matrix, i, j, row);
			}
		}
		return mat1;
	}
	//get identity matrix:
	Matrix getIdentityMatrix() const
	{
		Matrix<row, col, T>  identity;

		for (int i = 0; i < this->matrixRow; i++) {
			for (int j = 0; j < this->matrixCol; j++) {
				if (i == j) {
					identity.matrix[i][j] = 1;
				}
				else
					identity.matrix[i][j] = 0;
			}
		}
		return identity;
	}
	//operator ++ prefix
	Matrix& operator++() {
		*this = *this + T(1);
		return (*this);
	}
	//operator ++ postfix
	const Matrix operator++(int)
	{
		Matrix<row, col, T>  old = *this;
		++(*this);
		return old;
	}
	//prefix --
	Matrix& operator--()
	{
		*this = *this - T(1);
		return *this;
	}
	//postfix --
	const Matrix operator--(int)
	{
		Matrix<row, col, T>  old = *this;
		--(*this);
		return old;
	}
	//get diag:
	T* getDiag(int& num) const
	{
		int len = std::min(this->matrixRow, this->matrixCol);
		T* diag = new T[len];
		for (int i = 0; i < len; i++) {
			diag[i] = this->matrix[i][i];
		}
		num = len;
		return diag;
	}
	//operator == 
	bool operator==(const Matrix& that) const
	{
		if (that == NULL) return false;

		//now check matrix' value
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (this->matrix[i][j] - that.matrix[i][j] > DBL_EPSILON) {
					return false;
				}
			}
		}
		return true;
	}
	//operator !=
	bool operator!=(const Matrix& that) const
	{
		return !(*this == that);
	}
	//trace:
	operator T() const
	{
		T count = 0;
		//now strat counting
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (i == j) {
					count += this->matrix[i][j];
					break;
				}
			}
		}
		return count;
	}
	//print:
	friend std::ostream& operator<<(std::ostream& os, const Matrix& mat)
	{
		for (int i = 0; i < mat.matrixRow; i++) {
			for (int j = 0; j < mat.matrixCol; j++) {
				os << mat.matrix[i][j] << " ";
			}
			os << "\n";
		}
		return os;
	}
	//get mat[i][j]
	T& operator()(int r, int c) const
	{
		return this->matrix[r][c];
	}

};

//this function, multiplies row with col
template <int row, int col, typename T>
T getSumMul(T** m1, T** m2, int r, int c, int size) {
	T count = 0;
	for (int i = 0; i < size; i++) {
		count += m1[r][i] * m2[i][c];
	}
	return count;
}
