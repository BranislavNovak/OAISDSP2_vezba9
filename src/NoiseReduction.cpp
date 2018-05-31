#include "NoiseReduction.h"
#include <algorithm>
#include "ImageFilter.h"
	
void performMovingAverage (uchar input[], int xSize, int ySize)
{
	//TO DO
	int N = 5;
	double filterCoeff[25];
	for (int i = 0; i < 25; i++) {
		filterCoeff[i] = 1.0 / 25;
	}

	convolve2D(input, xSize, ySize, filterCoeff, N);
}

void calculateGaussKernel(double kernel[], int N, double sigma)
{
	//TO DO
	double C = 0;
	for (int n = 0; n < N; n++)
	{
		for (int k = 0; k < N; k++)
		{
			kernel[n*N + k] = exp(-((n - N / 2)*(n - N / 2) + (k - N / 2)*(k - N / 2))
				/ (2 * sigma * sigma));
			C += kernel[n*N + k];
		}
	}
	C = 1.0 / C;
	for (int n = 0; n < N; n++)
	{
		for (int k = 0; k < N; k++)
		{
			kernel[n*N + k] *= C;
		}
	}
}

void performGaussFilter (uchar input[], int xSize, int ySize, double sigma)
{
	//TO DO
	int N = 5;
	double filterCoeff[25];
	
	calculateGaussKernel(filterCoeff, N, sigma);

	convolve2D(input, xSize, ySize, filterCoeff, N);
}

void performMedianFilter (uchar input[], int xSize, int ySize)
{
	//TO DO
	const int N = 3;
	int d = (N - 1) / 2;

	uchar* extended_Y = new uchar[(xSize + N - 1) * (ySize + N - 1)];

	extendBorders(input, xSize, ySize, extended_Y, d);

	for (int j = 0; j < ySize; j++)
	{
		for (int i = 0; i < xSize; i++)
		{
			int tmp[N*N];
			int c = 0;

			for (int m = 0; m < N ; m++)
			{
				for (int k = 0; k < N; k++)
				{
					tmp[c] = extended_Y[(j + m)*(xSize + N-1) + (i + k)];
					c++;
				}
			}

			std::sort(tmp, tmp + N*N);
			input[(j) * xSize + i] = tmp[N*N/2];

		}
	}
	delete extended_Y;
}