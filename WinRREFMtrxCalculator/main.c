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
	int xSize = 0, ySize = 0, pivotPos = 0;
	float multiplier = 0;
	bool allZeroes = true;
	
	printf("--------------------------------\nRREF Matrix Calculator         |\nCopyright (C) 2023 David Badiei|\n--------------------------------\n");

	xSize = getIntegerValue("\nEnter size of matrix in x dimension (max 10): ");
	ySize = getIntegerValue("Enter size of matrix in y dimension (max 10): ");
	printf("\n");

	for (int i = 0; i < xSize * ySize; i++)
	{
		printf("Enter matrix [%d][%d]: ", i % xSize, (int)floor(i / xSize));
		while (!scanf("%f", &matrixArr[i]));
	}

	printf("\nOriginal Matrix:\n");
	displayMatrix(matrixArr, xSize, ySize);

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

	multiplier = 1 / matrixArr[0];
	multiplyMatrixConstant(matrixArr, 0, xSize, multiplier);

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

	printf("\nREF Matrix:\n");
	displayMatrix(matrixArr, xSize, ySize);

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

	printf("\nRREF Matrix:\n");
	displayMatrix(matrixArr, xSize, ySize);
	
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
