#include "BinaryImage.h"
#include <iostream>


BinaryImage::BinaryImage()
{
}

BinaryImage::BinaryImage(int M, int N, double* input_data, double threshold)
{
	_M = M;
	_N = N;

	_bData = new double[_M*_N];

	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (input_data[i * N + j] > threshold)
			{
				this->_bData[i * N + j] = 1;
			}
			else
			{
				this->_bData[i * N + j] = 0;
			}
		}
	}
#ifdef DEBUG
	std::cout << "BinaryImage::BinaryImage(int M, int N, double* input_data, double threshold) is invoked" << std::endl;
#endif
}

BinaryImage::~BinaryImage()
{
#ifdef DEBUG
	std::cout << "BinaryImage::~BinaryImage() is invoked" << std::endl;
#endif
	delete[] _bData;
}
