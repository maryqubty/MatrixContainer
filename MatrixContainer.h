// Mary Qubty 206528275
// Nasem Sawaid 209290733



#pragma once
#include "Matrix.h"

template <int row, int col, typename T = int>
void listDestructor(Matrix<row, col, T>* list, int mSize)
{
	// Free memory for each matrix
	for (int i = 0; i < mSize; i++) {
		list[i].~Matrix(); //destructor of matrix
	}
}


template <int row, int col, typename T = int>
class MatrixContainer {
private:
	const int matrixRow;
	const int matrixCol;
	int mSize;
	int mCapacity;
	Matrix<row, col, T>* list;

public:
	MatrixContainer() : matrixRow(row), matrixCol(col)
	{
		mSize = 0;
		mCapacity = 1;
		list= new Matrix<row, col, T> [1]; 
	}
	~MatrixContainer()
	{
		// Free memory for each matrix
		for (int i = 0; i < mSize; i++) {
			list[i].~Matrix(); //destructor of matrix
		}
	}
	//copy
	MatrixContainer(const MatrixContainer& copy) :matrixRow(copy.matrixRow), matrixCol(copy.matrixCol)
	{
		mSize = copy.mSize;
		mCapacity = copy.mCapacity;
		list = new Matrix<row, col, T>[mCapacity];

		// initialize list and copy matrixes
		for (int i = 0; i < mSize; i++) {
			list[i] = copy.list[i];
		}
	}
	//operator = 
	MatrixContainer& operator=(const MatrixContainer<row, col, T>& that)
	{
		// Check for self-assignment
		if (this == &that) {
			return *this;
		}
		listDestructor(this->list, this->mSize); //only to free the list :)
		this->list = new Matrix<row, col, T>[that.mCapacity];
		mSize = that.mSize;
		mCapacity = that.mCapacity;
		// initialize list and copy matrixes
		for (int i = 0; i < mSize; i++) {
			list[i] = that.list[i];
		}
		return *this;
	}
	//helper function that changes the size of list suitably:
	void changeListSize(int capacity)
	{
		Matrix<row, col, T>* tmpList = this->list;
		this->list = new Matrix<row, col, T>[capacity];
		//copy previous matrixes:
		for (int i = 0; i < mSize; i++) {
			this->list[i] = tmpList[i];
		}
		//let's not forget to free the original list:
		listDestructor(tmpList, this->mSize);
	}
	//addmatrix
	void addMatrix(Matrix<row, col, T>& mat)
	{
		if (this->mSize < this->mCapacity) {
			list[mSize] = mat;
			mSize++;
			return;
		}
		//if reached here, we should expand list:
		this->changeListSize(mCapacity * 2);
		this->list[this->mSize] = mat;
		this->mSize++;
		this->mCapacity *= 2;
	}
	void removeLastMatrix() {
		if (this->mSize == 0)
			return;
		//remove the last matrix:
		this->mSize -= 1;
		this->list[this->mSize].~Matrix();
		// check if size<=capacity/4
		if (this->mSize <= this->mCapacity / 4) {
			this->changeListSize(mCapacity / 4);
		}
	}
	//get mSize
	int size()
	{
		return this->mSize;
	}
	//get mCapacity
	int capacity()
	{
		return this->mCapacity;
	}
	//print list
	friend std::ostream& operator<<(std::ostream& os, const MatrixContainer& mat)
	{
		std::cout << "There are "<<mat.mSize<<" matrices in the container.The matrices : " << std::endl;
		for (int i = 0; i < mat.mSize; i++) {
			{
			os << mat.list[i] << " ";
			}
			os << "\n";
		}
		os << "\n";
		return os;
	}
	Matrix<row, col, T>& operator[](int i) const
	{
		//check if i is legal
		if (i >= mSize) {
			i = 0;
		}
		return this->list[i];
	}
};


