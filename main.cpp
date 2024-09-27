#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <limits.h>
#include <errno.h>
#include <string>

#include "matrix.hpp"
#include "jord.hpp"

int main(int argc, char *argv[])
{
	if(argc!=4)
	{
		printf("Wrong input!\n");
		printf("Usage: prog InputMode (1 for file from matrix, 2 for creating random matrix) file name/size of matrix  size of minor you want to see\n");
		return -1;
	}
	else
	{
	int n, m;
	int rezult;
	int inputMode;
	int* index = NULL;
	double* a = NULL;
	double* b = NULL;
	double* x = NULL;
	FILE* fin = NULL;
	clock_t t;

	inputMode = std::stoi(argv[1]);

	switch (inputMode)
	{
	case 1:
		fin = fopen(argv[2], "r");

		if (!fin)
		{
			printf("Can't open file!\n");

			return -1;
		}

		if (fscanf(fin, "%d", &n) != 1)
		{
			printf("Error in reading from file!\n");

			fclose(fin);

			return -2;
		}

		m=std::stoi(argv[3]);
		if(m>n)
			m=n;
		if(m<=0)
		{
			printf("size of minor must be positive\n");
			return -2;
		}

		break;
	case 2:
		n=std::stoi(argv[2]);


		break;

	default:
		printf("Incorrect mode!\n");
		return -3;
	}

	if (n < 1)
	{
		printf("Incorrect N!\n");

		if (inputMode == 1)
			fclose(fin);

		return -4;
	}
	else
	{
		m=std::stoi(argv[3]);
		if(m<=0)
		{
			printf("size of minor must be positive\n");
			return -2;
		}
		if(m>n)
			m=n;

	}

	index = (int*)malloc(n * sizeof(int));
	a = (double*)malloc(n * n * sizeof(double));
	b = (double*)malloc(n * sizeof(double));
	x = (double*)malloc(n * sizeof(double));

	if (!(index && a && b && x))
	{
		printf("Not enough memory!\n");

		if (index)
			free(index);
		if (a)
			free(a);
		if (b)
			free(b);
		if (x)
			free(x);

		if (inputMode == 1)
			fclose(fin);

		return -5;
	}

	rezult = InputMatrix(n, a, b, inputMode, fin);

	if (inputMode == 1)
		fclose(fin);

	if (rezult == -1)
	{
		printf("Error in reading from file!\n");

		free(index);
		free(a);
		free(b);
		free(x);

		return -6;
	}

	printf("\nMatrix A:\n");
	PrintMatrix(n, m, a, b);
	printf("\n");

	printf("Calculating...\n");

	t = clock();
	rezult = SolveSystem(n, a, b, x, index);
	t = clock() - t;

	switch (rezult)
	{
	case -1:
		printf("Can't solve - matrix is deteriorated.\n");

		break;
	case 0:
		printf("\nRezulting vector:");
		PrintVector(n, m, x);
		printf("\n");

		printf("Solution time = %.3f sec.\n\n", (double)t / CLOCKS_PER_SEC);

		if (inputMode == 1)
		{
			fin = fopen(argv[2], "r");
			fscanf(fin, "%d", &n);
		}

		InputMatrix(n, a, b, inputMode, fin);

		if (inputMode == 1)
			fclose(fin);

		printf("Solution error ||Ax - b|| = %e\n", SolutionError(n, a, b, x));

		break;
	default:
		printf("Unknown error!\n");

		break;
	}

	free(index);
	free(a);
	free(b);
	free(x);
	}

	return 0;
}
