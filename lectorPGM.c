void SaltarComentarios(FILE *fp)
{
    int ch;
    char line[100];
 
    while ((ch = fgetc(fp)) != EOF && isspace(ch));
    if (ch == '#') 
    {
        fgets(line, sizeof(line), fp);
        SaltarComentarios(fp);
    }
    else if (isspace(ch))
    {
    	fgets(line, sizeof(line), fp);
    	SaltarComentarios(fp);
    }
    else
        fseek(fp, -1, SEEK_CUR);

}

int ** createNewMatrix(int rows, int cols)
{
    int **matrix;
    int i;
 
    matrix = (int **)malloc(sizeof(int *) * rows);
    if (matrix == NULL) 
    {
        perror("error en la creacion de la matriz");
        exit(EXIT_FAILURE);
    }
 
    for (i = 0; i < rows; i++) 
    {
        matrix[i] = (int *)malloc(sizeof(int) * cols);
        if (matrix[i] == NULL) 
        {
            perror("error en la creacion de la matriz");
            exit(EXIT_FAILURE);
        }
    }
 
    return matrix;
}


double ** createNewMatrixD(int rows, int cols)
{
    double **matrix;
    int i;
 
    matrix = (double **)malloc(sizeof(double *) * rows);
    if (matrix == NULL) 
    {
        perror("error en la creacion de la matriz");
        exit(EXIT_FAILURE);
    }
 
    for (i = 0; i < rows; i++)
     {
        matrix[i] = (double *)malloc(sizeof(double) * cols);
        if (matrix[i] == NULL) 
        {
            perror("error en la creacion de la matriz");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < rows; i++)
    {
    	for (int j = 0; j < cols; j++)
    		matrix[i][j] = 0.0;
    }
 
    return matrix;
}

int valorNuevo(int* array, int val)
{
	int cont = 0;
	while(array[cont] != val)
		cont++;
	return cont;
}

newValues readNEWPGM(const char *filename, newValues pgminfo1)
{
    FILE *file;
    int val;
 
    file = fopen(filename, "r+");
    if (file == NULL) 
    {
        perror("cannot open file to read");
        exit(EXIT_FAILURE);
    }
 
    SaltarComentarios(file);
    fscanf(file, "%d", &pgminfo1->rows);
    SaltarComentarios(file);
    fscanf(file, "%d", &pgminfo1->cols);
    SaltarComentarios(file);
    fscanf(file, "%d", &pgminfo1->maxVal);
    fgetc(file);
    int numCases;
    SaltarComentarios(file);
    fscanf(file, "%d", &numCases);
    putchar(numCases);
    SaltarComentarios(file);
    char str[900000];
    int i = 0;
    int * arrayChange = (int*) malloc(sizeof(int*)*numCases);
    pgminfo1->arrayCambio = arrayChange;
    int * arrayLast = (int*) malloc(sizeof(int*)*numCases);
    pgminfo1->arrayFirstNum = arrayLast;


 	while (i < numCases)
 	{
 			while(fscanf(file,"%d %d", &pgminfo1->arrayCambio[i], &pgminfo1->arrayFirstNum[i])>0) 
 			{
        		
        		i++;
 		  	}
 	}

 	int ** matriz = createNewMatrix(pgminfo1->rows, pgminfo1->cols);
    pgminfo1->matrix = matriz;
    SaltarComentarios(file);
    char valorband[2];
    fgets(valorband, sizeof(valorband), file);
    SaltarComentarios(file);
  	for (int i = 0; i < pgminfo1->rows; i++)
  	{
        for (int j = 0; j < pgminfo1->cols; j++) 
        	{
        		if (!fscanf(file, "%d", &pgminfo1->matrix[i][j])) 
          			break;
        	}
    	}

    for (int i = 0; i < pgminfo1->rows; i++)
    {
        for (int j = 0; j < pgminfo1->cols; j++) 
        	{
        		int a = valorNuevo(pgminfo1->arrayCambio, pgminfo1->matrix[i][j]);
        		pgminfo1->matrix[i][j] = pgminfo1->arrayFirstNum[a];
        	}
    	}

    fclose(file);
    return pgminfo1;
}

PGMinfo readPGM(const char *filename, PGMinfo pgminfo1)
{
    FILE *file;
    char version[3];
    int val;
 
    file = fopen(filename, "r+");
    if (file == NULL) 
    {
        perror("no se puede leer el archivo");
        exit(EXIT_FAILURE);
    }
 
    fgets(version, sizeof(version), file);
    if (strcmp(version, "P2")!= 0) 
    {
        exit(EXIT_FAILURE);
    }
    SaltarComentarios(file);
    fscanf(file, "%d", &pgminfo1->cols);
    SaltarComentarios(file);
    fscanf(file, "%d", &pgminfo1->rows);
    SaltarComentarios(file);
    fscanf(file, "%d", &pgminfo1->maxVal);
    fgetc(file);
 	int ** matriz = createNewMatrix(pgminfo1->rows, pgminfo1->cols);
    pgminfo1->matrix = matriz;
    for (int i = 0; i < pgminfo1->rows; i++)
    {
        for (int j = 0; j < pgminfo1->cols; j++) 
        	{
        		if (!fscanf(file, "%d", &pgminfo1->matrix[i][j])) 
          			break;
        	}
    	}
    fclose(file);
    return pgminfo1;
}
