int** quantify(double** matrix, int rows, int cols, int compress)
{
	//COMPRESS: 1. Minima compresion
	//			2. Media compresion
	//			3. Alta compresion

	int Q = 10;

	if (compress == 2)
	{
		Q = 35;
	}
	else if (compress >= 3)
	{
		Q = 60;
	}

	int** m = createNewMatrix(rows, cols);

	
	for (int startR = 0; startR+8 <= rows; startR = startR+8)
	{
		for(int startC = 0; startC+8 <= cols; startC = startC+8)
		{
			for (int i = startR; i < startR+8; i++)
			{
				for (int j = startC; j < startC+8; j++)
					m[i][j] = round(matrix[i][j]/Q);
			}
			
		}
	}

	return m;
}

int** antiquantify(int** matrix, int rows, int cols, int compress)
{
	//COMPRESS: 1. Minima compresion
	//			2. Media compresion
	//			3. Alta compresion

	int Q = 10;

	if (compress == 2)
	{
		Q = 35;
	}
	else if (compress >= 3)
	{
		Q = 60;
	}

	int** m = createNewMatrix(rows, cols);


	for (int startR = 0; startR+8 <= rows; startR = startR+8)
	{
		for(int startC = 0; startC+8 <= cols; startC = startC+8)
		{
			for (int i = startR; i < startR+8; i++)
			{
				for (int j = startC; j < startC+8; j++)
					m[i][j] = round(matrix[i][j]*Q);
			}
			
		}
	}

	return matrix;
}