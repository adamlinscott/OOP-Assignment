//definitions
//#define DEBUG

#include <iostream>
#include "Matrix.h"


Matrix::Matrix()
{
	_M = 1;
	_N = 1;

	_data = new double[_M*_N];

	for (int x = 0; x < _M*_N; x++)
	{
		_data[x] = 0;
	}

}


Matrix::Matrix(int sizeR, int sizeC, double* input_data)
{
#ifdef DEBUG
	std::cout << "Constructor invoked" << std::endl;
#endif
	_M = sizeR;
	_N = sizeC;

	_data = new double[_M*_N];

	for (int x = 0; x < _M*_N; x++)
	{
		_data[x] = input_data[x];
	}
}


Matrix::Matrix(int sizeR, int sizeC)
{
#ifdef DEBUG
	std::cout << "Constructor invoked" << std::endl;
#endif
	_M = sizeR;
	_N = sizeC;

	_data = new double[_M*_N];
}


//copy constructor
Matrix::Matrix(const Matrix& m)
{
#ifdef DEBUG
	std::cout << "copy constructor" << std::endl;
#endif
	_M = m._M;
	_N = m._N;

	_data = new double[_M*_N];

	for (int i = 0; i < _M*_N; i++)
	{
		_data[i] = m._data[i];
	}
}


//operator overloads
Matrix Matrix::operator+(const Matrix& other)
{
#ifdef DEBUG
	std::cout << "Operator '+' overload" << std::endl;
#endif
	Matrix temp;
	temp._M = other._M;
	temp._N = other._N;

	temp._data = new double[temp._M*temp._N];

	for (int x = 0; x < (temp._M*temp._N); x++)
	{
		temp._data[x] = this->_data[x] + other._data[x];
	}

	return temp;
}


Matrix Matrix::operator-(const double mean)
{
#ifdef DEBUG
	std::cout << "Operator '-' overload" << std::endl;
#endif
	Matrix temp;
	temp._M = _M;
	temp._N = _N;

	temp._data = new double[temp._M*temp._N];

	for (int x = 0; x < (temp._M*temp._N); x++)
	{
		temp._data[x] = this->_data[x] - mean;
	}

	return temp;
}


Matrix Matrix::operator=(const Matrix& other)
{
#ifdef DEBUG
	std::cout << "Operator '=' overload" << std::endl;
#endif
	//delete existing _data information
	delete[] _data;
	_M = other._M;
	_N = other._N;

	//reserve memory for new array
	_data = new double[_M*_N];

	for (int x = 0; x < (_M*_N); x++)
	{
		this->_data[x] = other._data[x];
	}

	return *this;
}


//functions
int Matrix::getM()
{
	return _M;
}


int Matrix::getN()
{
	return _N;
}


double Matrix::get(int i, int j)
{
	return _data[(i*_N) + j];
}


Matrix Matrix::getBlock(int start_row, int end_row, int start_column, int end_column)
{
	//set number of rows and columns in the subimage
	int rows = (end_row - start_row) + 1;
	int columns = (end_column - start_column) + 1;
	//reserve the memory for data extracted from the main image
	double* tempData = new double[rows*columns];

	//variable to set the new array index
	int count = 0;

	//iterate through the image data, extracting the values according to the rows/columns
	for (int x = start_row; x < (rows + start_row); x++)
	{
		for (int y = start_column; y < (columns + start_column); y++)
		{
			tempData[count] = get(x, y);
			count++;
		}
	}

	//create a temporary matrix based on the row/column/data extracted
	Matrix temp(rows, columns, tempData);
	//delete the heap memory reserved for the extracted data
	delete[] tempData;

	//return the temporary matrix
	return temp;
}

int Matrix::getTotal()
{
	int temp = 0;

	for (int i = 0; i < _M * _N; i++)
	{
		temp += (int) _data[i];
	}
#ifdef DEBUG
	std::cout << temp << std::endl;
#endif
	return temp;
}

double Matrix::getMean() 
{
	return (getTotal() / (_M * _N));
}

double* Matrix::getData()
{
	return _data;
}

int Matrix::setBlock(int start_row, int end_row, int start_column, int end_column, Matrix& block)
{
	for (int i = 0; i < end_row - start_row + 1; i++)
	{
		for (int j = 0; j < end_column - start_column + 1; j++)	
		{
			this->_data[(i + start_row) * _M + (j + start_column)] = block._data[i * block._M + j];
		}
	}
	return 0;
}

Matrix Matrix::add(const Matrix& other)
{
	//create temporary array of row*colum size
	double* data = new double[other._M*other._N];

	//fill the array with other._data
	for (int x = 0; x < (other._M*other._N); x++)
	{
		data[x] = this->_data[x] + other._data[x];
	}

	//create a temporary Matrix object with the row/column/data info
	Matrix temp(other._M, other._N, data);
	//delete the data array 
	delete[] data;

	return temp;
}

Matrix::~Matrix()
{
#ifdef DEBUG
	std::cout << "Destructor" << std::endl;
#endif
	delete[] _data;
}