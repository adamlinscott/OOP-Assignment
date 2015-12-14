#pragma once
#include "Matrix.h"
class BinaryImage : public Matrix
{
public:
	//constructors
	BinaryImage();
	BinaryImage(int M, int N, double* input_data, double threshold);

	//destructor
	~BinaryImage();


private:
	int _M, _N;
	double* _bData;
};

