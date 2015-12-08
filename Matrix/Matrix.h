#pragma once
class Matrix
{
public:
	//constructors
	Matrix();
	Matrix(int sizeR, int sizeC, double* inputData);
	Matrix::Matrix(int M, int N, double* input_data, double threshold);
	Matrix(const Matrix& m);
	Matrix(int sizeR, int sizeC);

	//destructor
	~Matrix();

	//operator overloads
	Matrix Matrix::operator+(const Matrix& other);
	Matrix Matrix::operator=(const Matrix& other);
	Matrix Matrix::operator-(const double mean);



	Matrix Matrix::getBlock(int start_row, int end_row, int start_column, int end_column);
	int Matrix::setBlock(int start_row, int end_row, int start_column, int end_column, Matrix& block);
	int Matrix::getM();
	int Matrix::getN();
	//int Matrix::getTotal();
	virtual int Matrix::getTotal();
	double* Matrix::getData();
	double get(int i, int j);
	double Matrix::getMean();


	Matrix Matrix::add(const Matrix& other);

private:
	int _M, _N;
	double* _data;
};
