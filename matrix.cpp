#include <stdio.h>
#include <math.h>

#include "matrix.hpp"

static double f(int i, int j)
{
	return 1.0 / (i + j + 1.0);
}

int InputMatrix(int n, double* a, double* b, int inputMode, FILE* fin)
{
	int i;
	int j;
	double tmp;

	if (inputMode == 1)
	{
		for (i = 0; i < n; ++i)
		{
			for (j = 0; j < n; ++j)
				if (fscanf(fin, "%lf", &a[i * n + j]) != 1)
					return -1;

			if (fscanf(fin, "%lf", &b[i]) != 1)
				return -1;
		}
	}
	else
	{
		for (i = 0; i < n; ++i)
		{
			tmp = 0.0;
			for (j = 0; j < n; ++j)
			{
				a[i * n + j] = f(i, j);
				if (j % 2 == 0)
					tmp += a[i * n + j];
			}
			b[i] = tmp;
		}
	}

	return 0;
}

void PrintMatrix(int n, int m, double* a, double* b)
{
	int i;
	int j;
	int nPrint;

	nPrint = (n > m) ? m : n;

	for (i = 0; i < nPrint; ++i)
	{
		printf("| ");
		for (j = 0; j < nPrint; ++j)
			printf("%10.3g ", a[i * n + j]);
		printf("|\t%10.3g |\n", b[i]);
	}
}

void PrintVector(int n, int m, double* x)
{
	int i;
	int nPrint;

	nPrint = (n > m) ? m : n;

	for (i = 0; i < nPrint; ++i)
	{
		if(i==0)
			printf("(");
		printf("%-.3g", x[i]);
		if(i!=nPrint-1)
			printf(",");
		else
		{
			if(n==m)
				printf(")");
			else
				printf("...");
		}
	}
	printf("\n");
}

double SolutionError(int n, double* a, double* b, double* x)
{
	int i;
	int j;
	double tmp;
	double rezult;

	rezult = 0.0;
	for (i = 0; i < n; ++i)
	{
		tmp = 0.0;
		for (j = 0; j < n; ++j)
			tmp += a[i * n + j] * x[j];
		tmp -= b[i];

		rezult += tmp * tmp;
	}

	return sqrt(rezult);
}
