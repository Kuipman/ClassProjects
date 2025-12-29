/*
 *
 *
 *
 */

#include <stdio.h>

#define FP_DELTA 0.0001
/*
 *  This calculates and returns the absolute value of an element. Used in the MatrixEquals function
 */

float Abs(float value)
{
    if(value < 0)
        value = value * -1;
    return value;
}

/*
 *  Resets a matrix so elements are zero
 */
void reset(float mat[3][3])
{
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            mat[i][j] = 0;
}

/*
 *  This function prints out a standard 3x3 matrix to the console
 *      - in cases where we need to print out a 2x2 matrix, the matrix will be expanded
 *           with zeros prior to reaching this function
 */
void MatrixPrint(float mat[3][3])
{
    for(int i = 0; i < 3; i++)
    {
        printf("[ ");
        for(int j = 0; j < 3; j++)
        {
            printf("%10.4f ", mat[i][j]);
        }
        printf("   ]\n");
    }
}

/*
 *  This function compares each corresponding element between two matrices using two for loops
 *      -absolute values for both elements are subtracted, if result is less than 0.0001 then they are equal
 *      -if one discrepancy is found both loops terminate and the function returns false (0)
 *      -otherwise, function returns true (1)
 */
int MatrixEquals(float mat1[3][3], float mat2[3][3])
{
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
        {
            float subResult = Abs(mat1[i][j]) - Abs(mat2[i][j]);
            if(Abs(subResult) > FP_DELTA)
                return 0;      //if one set of elements isn't equal, matrices aren't equal. Returns false
        }
    return 1;           //if comparison was successful for all values, returns 1
}

/*
 *  Adds two matrices together (both size 3x3), and places result in a third 3x3 matrix
 */

void MatrixAdd(float mat1[3][3], float mat2[3][3], float result[3][3])
{
    reset(result);
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            result[i][j] = mat1[i][j] + mat2[i][j];
}

/*
 *  Adds a scalar value to every element in the matrix, places result in a separate 3x3 matrix
 */

void MatrixScalarAdd(float x, float mat[3][3], float result[3][3])
{
    reset(result);
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            result[i][j] = mat[i][j] + x;
}

/*
 *  Multiplies every element in a matrix with a scalar value, places result in a separate 3x3 matrix
 */

void MatrixScalarMultiply(float x, float mat[3][3], float result[3][3])
{
    reset(result);
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            result[i][j] = mat[i][j] * x;
}

/*
 *  Takes two 3x3 matrices and multiplies them together, result is placed in separate 3x3 matrix
 */
void MatrixMultiply(float mat1[3][3], float mat2[3][3], float result[3][3])
{
    reset(result);
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            result[i][j] = mat1[i][j] * mat2[j][i];
}

/*
 *  Adds all diagonal elements starting from the top left, returns the sum
 */

float MatrixTrace(float mat[3][3])
{
    float sum = 0;
    for(int i = 0; i < 3; i++)
        sum = sum + mat[i][i];
    return sum;       
}

/*
 * Mirrors a matrix's elements across the diagonal
 */

void MatrixTranspose(float mat[3][3], float result[3][3])
{
    reset(result);
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            result[i][j] = mat[j][i];
}

/*
 *  'Removes row i and column j from a 3x3 matrix, result is placed in a 2x2 matrix
 */
void MatrixSubmatrix(int i, int j, float mat[3][3], float result[2][2])
{
    int x = 0;
    int y = 0;
    for(int m = 0; m < 3; m++) 
        for(int n = 0; n < 3; n++)
            if((m != i) && (n != j))
            {
                result[x][y] = mat[m][n];
                    if(y == 0)
                        y = 1;
                    else
                    {
                        y = 0;
                        x = 1;
                    }
            }
            
}

/*
 *  Helper function for MatrixDeterminant()
 */

float MatrixDeterminant2x2(float mat[2][2])
{
    return ((mat[0][0] * mat[1][1]) - (mat[0][1] * mat[1][0]));   //(a*d - b*c)
}

/*
 *  Finds the determinant of a 3x3 matrix through the use of a helper function that finds the determinant
 *      of a 2x2 matrix
 */

float MatrixDeterminant(float mat[3][3])
{
    float temp[2][2] = {{},{}};
    float sum;
    for(int i = 0; i < 3; i++)
    {
        MatrixSubmatrix(0, i, mat, temp);
        if((i%2) == 1)
            sum = sum - mat[0][i]*MatrixDeterminant2x2(temp);
        else
            sum = sum + mat[0][i]*MatrixDeterminant2x2(temp);
    }
    return sum;
}

void MatrixInverse(float mat[3][3], float result[3][3])
{
    
}