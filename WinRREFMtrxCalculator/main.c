#define _CRT_SECURE_NO_WARNINGS //remove if not using msvc

#include <stdio.h>
#include <math.h>
#include <stdbool.h>

float matrixArr[100] = { 0 };

int getIntegerValue(char *prompt);
void swapMatrixRows(int row1, int row2, int rowLength, float matrixArr[]);
void displayMatrix(float matrixArr[], int xSize, int ySize);
void multiplyMatrixConstant(float matrixArr[], int rowNum, int rowLength, float multiplier);
void subtractAndSaveMatrixRow(float matrixArr[], int row1, int row2, int rowLength, int rowToSave, float multiplier);

int main()
{
	//Declare variables
	int xSize = 0, ySize = 0, pivotPos = 0;
	float multiplier = 0;
	bool allZeroes = true;
	
	//Prompt user for size of their matrix
	printf("--------------------------------\nRREF Matrix Calculator         |\nCopyright (C) 2023 David Badiei|\n--------------------------------\n");

	xSize = getIntegerValue("\nEnter size of matrix in x dimension (max 10): ");
	ySize = getIntegerValue("Enter size of matrix in y dimension (max 10): ");
	printf("\n");

	for (int i = 0; i < xSize * ySize; i++)
	{
		printf("Enter matrix [%d][%d]: ", i % xSize, (int)floor(i / xSize));
		while (!scanf("%f", &matrixArr[i]));
	}

	//Display original matrix that user entered in
	printf("\nOriginal Matrix:\n");
	displayMatrix(matrixArr, xSize, ySize);

	//Move all zero rows to bottom of matrix
	for (int i = 0; i < ySize; i++)
	{
		allZeroes = true;

		for (int x = 0; x < xSize; x++)
		{
			if (matrixArr[(int)floor(x / xSize) + i % xSize] != 0)
			{
				allZeroes = false;
			}
		}

		if (allZeroes == true)
		{
			swapMatrixRows(i, ySize-1, xSize, matrixArr);
		}
	}

	//Make sure first matrix value equals one
	multiplier = 1 / matrixArr[0];
	multiplyMatrixConstant(matrixArr, 0, xSize, multiplier);

	//Do some matrix subtraction to get the matrix in the downwards staircase, and multiply by a constant to get the pivot equalling to one
	for (int i = 1; i < ySize; i++)
	{
		for (int y = 0; y < i; y++)
		{
			for (int x = 0; x < xSize; x++)
			{
				if (matrixArr[(y * xSize) + x] != 0)
				{
					multiplier = matrixArr[(i * xSize) + x] / matrixArr[(y * xSize) + x];
					break;
				}
				
			}
		
			subtractAndSaveMatrixRow(matrixArr, i, y, xSize, i, multiplier);
		}

		for (int x = 0; x < xSize; x++)
		{
			if (matrixArr[(i * xSize) + x] != 0)
			{
				multiplier = 1 / matrixArr[(i * xSize) + x];
				break;
			}
		}

		multiplyMatrixConstant(matrixArr, i, xSize, multiplier);
	}

	//Output matrix in REF form
	printf("\nREF Matrix:\n");
	displayMatrix(matrixArr, xSize, ySize);

	//Make sure matrix is in RREF form, aka make sure the pivot is the only non-zero value in the column
	for (int y = 0; y < ySize; y++)
	{
		for (int x = 0; x < xSize; x++)
		{
			if (matrixArr[(y * xSize) + x] != 0)
			{
				pivotPos = x;
				break;
			}
			else
			{
				pivotPos = -1;
			}
		}

		if (pivotPos >= 0)
		{
			for (int y2 = 0; y2 < ySize; y2++)
			{
				if (y2 != y)
				{
					if (matrixArr[(y * xSize) + pivotPos] != 0)
					{
						multiplier = matrixArr[(y2 * xSize) + pivotPos] / matrixArr[(y * xSize) + pivotPos];
						subtractAndSaveMatrixRow(matrixArr, y2, y, xSize, y2, multiplier);
					}
				}
			}
		}
	}

	//Output RREF value
	printf("\nRREF Matrix:\n");
	displayMatrix(matrixArr, xSize, ySize);

	return 0;
	
}

void displayMatrix(float matrixArr[], int xSize, int ySize)
{
	for (int y = 0; y < ySize; y++)
	{
		for (int x = 0; x < xSize; x++)
		{
			printf("%f ", matrixArr[(y * xSize) + x]);
		}

		printf("\n");
	}
}

void multiplyMatrixConstant(float matrixArr[], int rowNum, int rowLength, float multiplier)
{
	for (int i = 0; i < rowLength; i++)
	{
		matrixArr[rowNum * rowLength + i] = matrixArr[rowNum * rowLength + i] * multiplier;

		if (matrixArr[rowNum * rowLength + i] == -0) //i have no clue why i have to do this
		{
			matrixArr[rowNum * rowLength + i] = 0;
		}
	}
}

void subtractAndSaveMatrixRow(float matrixArr[], int row1, int row2, int rowLength, int rowToSave, float multiplier)
{
	for (int i = 0; i < rowLength; i++)
	{
		matrixArr[rowToSave * rowLength + i] = matrixArr[row1 * rowLength + i] - (matrixArr[row2 * rowLength + i] * multiplier);
	}
}

void swapMatrixRows(int row1, int row2, int rowLength, float matrixArr[])
{
	float temp;

	for (int i = 0; i < rowLength; i++)
	{
		temp = matrixArr[row1 * rowLength + i];

		matrixArr[row1 * rowLength + i] = matrixArr[row2 * rowLength + i];
		matrixArr[row2 * rowLength + i] = temp;
	}
}

int getIntegerValue(char* prompt)
{
	int value;

	printf(prompt);
	while (!scanf("%d", &value));

	return value;
}
