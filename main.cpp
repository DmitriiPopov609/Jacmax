#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <limits.h>
#include <errno.h>
#include <string>

#include "matrix.hpp"
#include "jacob.hpp"

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
	int i;
	int j;
	int n, m;
	int iter;
	int rezult;
	int inputMode;
	double eps = 1e-10;
	double inv1;
	double inv2;
	double* a = NULL;
	double* values = NULL;
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

	a = (double*)malloc(n * n * sizeof(double));
	values = (double*)malloc(n * sizeof(double));

	if (!(a && values))
	{
		printf("Not enough memory!\n");

		if (a)
			free(a);
		if (values)
			free(values);

		if (inputMode == 1)
			fclose(fin);

		return -5;
	}

	rezult = InputMatrix(n, a, inputMode, fin);

	if (inputMode == 1)
		fclose(fin);

	if (rezult == -1)
	{
		printf("Error in reading from file!\n");

		free(a);
		free(values);

		return -6;
	}

	printf("\nMatrix A:\n");
	PrintMatrix(n, m, a);
	printf("\n");

	printf("Calculating...\n");

	inv1 = 0.0;
	inv2 = 0.0;
	for (i = 0; i < n; ++i)
	{
		inv1 -= a[i * n + i];
		for (j = 0; j < n; ++j)
			inv2 -= a[i * n + j] * a[j * n + i];
	}

	t = clock();
	FindValues(n, a, values, eps, &iter);
	t = clock() - t;

	for (i = 0; i < n; ++i)
	{
		inv1 += values[i];
		inv2 += values[i] * values[i];
	}

	printf("\nValues:\n");
	PrintVector(n, m, values);
	printf("\n");

	printf("Finding time\t= %.2f sec.\n", (double)t / CLOCKS_PER_SEC);
	printf("Iterations\t= %d\n\n", iter);

	printf("Sum(x_i) - Sum(a_i)\t\t= %g\n", inv1);
	printf("Sum(x_i ^ 2) - Sum(a_ij * a_ji)\t= %g\n", inv2);

	free(a);
	free(values);


	return 0;
	}
}
