#include <iostream>
#include "Matrix.h"

Matrix add(Matrix& one, Matrix& two);

int main()
{
	double* data = new double[4];
	for (int x = 0; x < 4; x++)
	{
		data[x] = x + 1;
	}

	Matrix c(2, 2, data);
	Matrix d(2, 2, data);


	std::cout << c.get(1, 1) << std::endl;

	Matrix f;
	f = c;

	std::cout << f.get(1, 1) << std::endl;
	//non-member function
	f = add(c, d);

	std::cout << f.get(1, 1) << std::endl;

	////member functions
	f = c.add(d);

	std::cout << f.get(1, 1) << std::endl;

	////operator '+' overload
	f = c + d;
	std::cout << f.get(1, 1) << std::endl;

	delete[] data;
	getchar();
	return 0;
}

Matrix add(Matrix& one, Matrix& two)
{
	//create 'new' data array on heap
	double* data = new double[one.getM()*one.getN()];

	//fill that data array
	for (int x = 0; x < (one.getM()*one.getN()); x++)
	{
		data[x] = one.getData()[x] + two.getData()[x];
	}

	//create new Matrix object with the row/column/data information
	Matrix temp(one.getM(), one.getN(), data);
	//delete 'data' array
	//remember: because of 'deep copy' we can delete this array, as it has been 'deep copied'
	//when the 'temp' object was created.
	delete[] data;

	return temp;
}