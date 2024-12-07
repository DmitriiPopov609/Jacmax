#include <stdio.h>
#include <math.h>

#include "matrix.hpp"

double f(int n,int k,int i, int j)
{
    switch(k){
        case 2:
            return n-1 - fmax(i,j)+1;
        case 3:
            if (i==j){
                return 2;
            } else if(abs(i-j)==1){
                return -1;
            } else {
                return 0;
            }
        case 4:
            if (i==j && i<n-1 && j<n-1){
                return 1;
            } else if(j==n-1){
                return i;
            } else if(i==n-1){
                return j;
            } else{
                return 0;
            }
        case 5:
            return 1.0/(i+j+1);
        default:
            return -3;
    }
}
int InputMatrix(int n, double* a, int inputMode, FILE* fin)
{
	int i;
	int j;

	if (inputMode == 1)
	{
		for (i = 0; i < n; ++i)
		{
			for (j = 0; j < n; ++j)
				if (fscanf(fin, "%lf", &a[i * n + j]) != 1)
					return -1;
		}
	}
	else
	{
		for (i = 0; i < n; ++i)
			for (j = 0; j < n; ++j)
				a[i * n + j] = f(n, inputMode, i, j);
	}

	return 0;
}

void PrintMatrix(int n, int m, double* a)
{
	int i;
	int j;
	int nPrint;

	nPrint = (n > m) ? m : n;

	for (i = 0; i < nPrint; ++i)
	{
		if(i!=0)
			printf("\n");
		for (j = 0; j < nPrint; ++j)
			printf("%10.3g ", a[i * n + j]);
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
