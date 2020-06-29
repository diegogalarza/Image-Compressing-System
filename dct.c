
#define PI 3.14159265359
double DCT(int** matrix, int startR, int startC, double rows, double columns, int k1, int k2)
{
	double x = 0.0;

	double piR = (PI*k1)/(2.0*rows);
	double piC = (PI*k2)/(2.0*columns);
	for (int n1 = startR; n1 < startR+rows; n1++)
	{
		for(int n2 = startC; n2 < startC+columns; n2++)
		{
			x += matrix[n1][n2] * cos( (piR)*(2.0*(n1-startR) + 1.0)) * cos ( piC*(2.0*(n2-startC)+ 1.0));
		}
	}

	double ort = (k1 == 0) ? (1.0/sqrt(2.0)) : 1;
    double ortt = (k2 == 0) ? (1.0/sqrt(2.0)) : 1;
	
	x *= (1.0/4.0)*ort*ortt;

    if (fabs(x) < 1)
        return 0;

	return x;
}


double IDCT(int** matrix, int startR, int startC, double rows, double columns, int k1, int k2)
{
	double x = 0.0;

	for (int n1 = startR; n1 < startR+rows; n1++)
	{
		double ort = ((n1-startR) == 0) ? (1.0/sqrt(2.0)) : 1.0;
		for (int n2 = startC; n2 < startC+columns; n2++)
		{
			double ortt = ((n2-startR) == 0) ? (1.0/sqrt(2.0)) : 1.0;
			x += matrix[n1][n2] * cos(((2.0*k1 + 1.0)*PI*(double)(n1-startR))/(2.0*rows)) 
								* cos ( ((2.0*k2 + 1.0)*PI*(double)(n2-startC))/(2.0*columns) ) 
								* ort * ortt;
		}
	}

    x *= 1.0/4.0;

	return x;
}

///////////////////////////////////////////////////////////////

double** matrixDCT(double** newM, int** matrix, int rows, int columns, int startR, int startC)
{
	for (int i = startR; i < startR+rows; i++)
	{
		for(int j = startC; j < startC+columns; j++)
		{
			newM[i][j] = DCT(matrix, startR, startC, (double)rows, (double)columns, i-startR, j-startC);
		}
	}

	return newM;

}

int** matrixIDCT(int** newM, int** matrix, int rows, int columns, int startR, int startC, newValues pgm)
{
    for (int i = startR; i < startR+rows; i++)
    {
        for(int j = startC; j < startC+columns; j++)
        {
            newM[i][j] = (int)round(IDCT(matrix, startR, startC, (double)rows, (double)columns, i-startR, j-startC))+ (pgm->maxVal)/2;
        }
    }

    return newM;

}

///////////////////////////////////////////////////////////////////////////7

double** compressDCT(int** matrix, int rows, int cols, int n, PGMinfo pgm)
{
	for (int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
			matrix[i][j] -= (pgm->maxVal)/2;
	}

	double** newM = createNewMatrixD(rows, cols);

	if (rows <= cols)
	{
		if (rows < n)
			n = rows;
	}

	else if (cols < rows)
	{
		if (cols < n)
			n = cols;
	}

	for (int startR = 0; startR+n <= rows; startR = startR+n){
		for(int startC = 0; startC+n <= cols; startC = startC+n){
			newM = matrixDCT(newM, matrix, n, n, startR, startC);
		}	
	}
	return newM;
}

int** decompressIDCT(int** matrix, int rows, int cols, int n, newValues pgm)
{
	int** newM = createNewMatrix(rows, cols);
	for (int i = 0; i < rows; i++)
	{
    	for (int j = 0; j < cols; j++)
    		newM[i][j] = 0;
    }

    if (rows < cols)
	{
		if (rows < n)
			n = rows;
	}

	else if (cols < rows)
	{
		if (cols < n)
			n = cols;
	}
	
	for (int startR = 0; startR+n <= rows; startR = startR+n)
	{
		for(int startC = 0; startC+n <= cols; startC = startC+n)
		{
			newM = matrixIDCT(newM, matrix, n, n, startR, startC, pgm);
		}
		
	}

	return newM;
}