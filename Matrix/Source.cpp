#include <sstream> // stringstream
#include <iostream> // cout, cerr
#include <fstream> // ifstream
#include <istream>
#include "Matrix.h"
#include "BinaryImage.h"

using namespace std;

// Input data are provided in .txt format and can be converted to .pgm files for visualization
// Download (free) ImageJ for plotting images in .pgm format
// http://rsb.info.nih.gov/ij/download.html

// Reads .txt file representing an image of R rows and C Columns stored in filename 
// and converts it to a 1D array of doubles of size R*C
// Memory allocation is performed inside readTXT
double* readTXT(char *fileName, int sizeR, int sizeC);

int square(int input);

// Converts a 1D array of doubles of size R*C to .pgm image of R rows and C Columns 
// and stores .pgm in filename
// Use Q = 255 for greyscale images and Q=1 for binary images.
void WritePGM(char *filename, double *data, int sizeR, int sizeC, int Q);

const int threshhold = 110;


int main()
{
	// This part will show you how to use the two functions.

	//M and N represent the number of rows and columns in the image
	int M = 512; int N = 512;

	// input_data is a pointer to a 1D array of M*N doubles stored in heap. Memory allocation is performed 
	// inside readTXT. readTXT will read an image (in .pgm format) of size MxN and will  store the result in input_data.
	// once you're done with data DO NOT forget to delete the memory as in the end of this main() function
	double* input_data = 0;

	std::cout << endl;
	std::cout << "Data from text file -------------------------------------------" << endl;

	//Create shuffled image matrix object
	char* inputFileName = "shuffled_logo.txt"; 
	input_data = readTXT(inputFileName, M, N);
	Matrix shuffledLogo(M, N, input_data); 

	//Create noisy image matrix object
	inputFileName = "unshuffled_logo_noisy.txt"; 
	input_data = readTXT(inputFileName, M, N);
	Matrix noisyLogo(M, N, input_data/*, threshhold*/); 

	noisyLogo.denoise(threshhold);

	Matrix outputLogo(M, N);

	for (int i = 0; i < 16 * 16; i++) //For each 32 x 32 pixel block in shuffled
	{
		Matrix referanceBlock = noisyLogo.getBlock((i - (i % 16)) * 2, (i - (i % 16)) * 2 + 31, (i * 32) % M, (i * 32) % M + 31);
		Matrix tempBlock = shuffledLogo.getBlock((i - (i % 16)) * 2, (i - (i % 16)) * 2 + 31, (i * 32) % M, (i * 32) % M + 31);

	//	Matrix binaryReferanceBlock(referanceBlock.getM(), referanceBlock.getN(), referanceBlock.getData(), threshhold);
	//	Matrix binaryTempBlock(tempBlock.getM(), tempBlock.getN(), tempBlock.getData(), threshhold);

		for (int j = i + 1; j < 16 * 16; j++) //For each 32 x 32 pixel block that has not been sorted
		{
			Matrix testBlock = shuffledLogo.getBlock((j - (j % 16)) * 2, (j - (j % 16)) * 2 + 31, (j * 32) % M, (j * 32) % M + 31);


		//	Matrix binaryTestBlock(testBlock.getM(), testBlock.getN(), testBlock.getData(), threshhold);

			int testSqrDiff = (referanceBlock - testBlock).getSS(); /*abs(referanceBlock.getTotal() - testBlock.getTotal())*/
			int tempSqrDiff = (referanceBlock - tempBlock).getSS(); /*abs(referanceBlock.getTotal() - tempBlock.getTotal())*/

			if (testSqrDiff <= tempSqrDiff)
			{
				shuffledLogo.setBlock((j - (j % 16)) * 2, (j - (j % 16)) * 2 + 31, (j * 32) % M, (j * 32) % M + 31,tempBlock);
				tempBlock = testBlock;
				//binaryTempBlock = binaryTestBlock;
				shuffledLogo.setBlock((i - (i % 16)) * 2, (i - (i % 16)) * 2 + 31, (i * 32) % M, (i * 32) % M + 31, tempBlock);
			}
		}
	}

	

	// writes data back to .pgm file stored in outputFileName
	char* outputFileName = "logo_restored.pgm";//logo_restored
	// Use Q = 255 for greyscale images and 1 for binary images.
	int Q = 255;
	WritePGM(outputFileName, shuffledLogo.getData(), M, N, Q);

	delete[] input_data;

	std::cout << "fin" << endl;
	getchar();

	return 0;
}


int square(int input)
{
	return abs(abs(input * input));
}


// Read .txt file with image of size RxC, and convert to an array of doubles
double* readTXT(char *fileName, int sizeR, int sizeC)
{
	double* data = new double[sizeR*sizeC];
	int i = 0;
	ifstream myfile(fileName);
	if (myfile.is_open())
	{

		while (myfile.good())
		{
			if (i>sizeR*sizeC - 1) break;
			myfile >> *(data + i);
			// cout << *(data+i) << ' ';  
			i++;
		}
		myfile.close();
	}
	else std::cout << "Unable to open file";
	//cout << i;

	return data;
}

// convert data from double to .pgm stored in filename
void WritePGM(char *filename, double *data, int sizeR, int sizeC, int Q)
{

	int i, j;
	unsigned char *image;
	ofstream myfile;

	image = (unsigned char *) new unsigned char[sizeR*sizeC];

	// convert the integer values to unsigned char

	for (i = 0; i<sizeR*sizeC; i++)
		image[i] = (unsigned char)data[i];

	myfile.open(filename, ios::out | ios::binary | ios::trunc);

	if (!myfile) {
		std::cout << "Can't open file: " << filename << endl;
		exit(1);
	}

	myfile << "P5" << endl;
	myfile << sizeC << " " << sizeR << endl;
	myfile << Q << endl;

	myfile.write(reinterpret_cast<char *>(image), (sizeR*sizeC)*sizeof(unsigned char));

	if (myfile.fail()) {
		std::cout << "Can't write image " << filename << endl;
		exit(0);
	}

	myfile.close();

	delete[] image;

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
	delete[] data;

	return temp;
}