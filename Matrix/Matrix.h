#pragma once
class Matrix
{
public:
	//constructor
	Matrix();
	//constructor with arguments
	Matrix(int sizeR, int sizeC, double* inputData);
	//coppy constructor
	Matrix::Matrix(const Matrix& m);

	//destructor
	~Matrix();

	//operator overloads
	Matrix Matrix::operator+(const Matrix& other);
	Matrix Matrix::operator=(const Matrix& other);



	Matrix Matrix::getBlock(int start_row, int end_row, int start_column, int end_column);
	int Matrix::getM();
	int Matrix::getN();
	double* Matrix::getData();
	double get(int i, int j);


	Matrix Matrix::add(const Matrix& other);

private:
	int _M, _N;
	double* _data;
};
