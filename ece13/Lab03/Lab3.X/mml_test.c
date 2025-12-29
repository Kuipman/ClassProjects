// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CMPE13 Support Library
#include "BOARD.h"




// User libraries:
#include "MatrixMath.h"


// Module-level variables (for global testing)
float zero_matrix[3][3] = {{},{},{}};
float one_matrix[3][3] = {{1,1,1},{1,1,1},{1,1,1}};
float matBasic[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
float matBasic2[3][3] = {{3,5,7},{-5,3,-7},{1,2,-8}};
float matScalar1[3][3] = {{5,23,7},{45,8,66},{21,14,9}};
float matScalar2[3][3] = {{11,4,15},{26,4,22},{6,42,33}};
float matFloat1[3][3] = {{3.14,22.66445,7.0001},{5.334,-73.1,12.755},{7.588,64.3213,4.5}};
float matFloat2[3][3] = {{9.442,3.678,-42.115},{64.3329,23.9887,-11.9},{45.2959,1.8556,8.566}};

int main()
{
    BOARD_Init();

    printf("Beginning NKuipers's mml test harness, compiled on %s %s\n", __DATE__, __TIME__);
    float addResult[3][3] = {{},{},{}};
    
    // Tests for MatrixPrint())
    printf("Demonstrating MatrixPrint():\n");
    MatrixPrint(zero_matrix);
    printf("\n");
    MatrixPrint(matBasic);
    
    // Tests for MatrixEquals()
    float eqMat1[3][3] = {{8.1,3.3322,8.66},{3.6674,9.5333,5.354},{1.221,6.43,9.3324}};
    float eqMat2[3][3] = {{1.5,3.1,9.3},{7.44223,8.22443,5.334},{2.654,3.7774,1.11112}};
    float eqMat3[3][3] = {{1.5,3.1,9.3},{7.44223,8.22443,5.333},{2.654,3.7774,1.11112}};
    float eqMat4[3][3] = {{1.5,3.1,9.3},{7.44223,8.22444,5.333},{2.654,3.7774,1.11112}};
    printf("\n==============================================");
    printf("\nDemonstrating MatrixEquals() where True = 1 and False = 0:\n");
    printf("Trivial Test of two zero matrices: %i\n", MatrixEquals(zero_matrix, zero_matrix));      //trivial case
    printf("Test of two alike matrices: %i\n",MatrixEquals(eqMat1, eqMat1));                            //two matching matrices = true
    printf("Test of two very different matrices: %i\n",MatrixEquals(eqMat1, eqMat2));                   //non-matching matrices = false
    printf("Test of two matrices with one different element: %i\n",MatrixEquals(eqMat2, eqMat3));
    printf("Test of two matrices with one different element (less than 0.0001): %i\n",MatrixEquals(eqMat3, eqMat4));
    
    // Tests for MatrixAddition()
    printf("\n==============================================");
    printf("\nDemonstrating MatrixAdd() with result:\n");
    printf("Trivial Test of two matrices comprised of ones:\n");
    MatrixAdd(one_matrix, one_matrix, addResult);
    MatrixPrint(addResult);
    float matTestA1[3][3] = {{2,2,2},{2,2,2},{2,2,2}};
    printf("Matrix above should reflect 2's across the board (1 for true): %i", MatrixEquals(addResult, matTestA1));
    printf("\n\nTest of adding two matrices containing scalars:\n");
    MatrixPrint(matScalar1);
    printf("+\n");
    MatrixPrint(matScalar2);
    printf("=\n");
    MatrixAdd(matScalar1, matScalar2, addResult);
    MatrixPrint(addResult);
    float matTestA2[3][3] = {{16,27,22},{71,12,88},{27,56,42}};
    printf("Matrix addition was successful (1 for true): %i", MatrixEquals(addResult, matTestA2));
    printf("\n\nTest of adding two matrices containing floating points:\n");
    MatrixPrint(matFloat1);
    printf("+\n");
    MatrixPrint(matFloat2);
    printf("=\n");
    MatrixAdd(matFloat1, matFloat2, addResult);
    MatrixPrint(addResult);
    float matTestA3[3][3] = {{12.5820,26.3424,-35.1149},{69.6669,-49.1113,0.8550},{52.8839,66.1769,13.0660}};
    printf("Matrix addition was successful (1 for true): %i", MatrixEquals(addResult, matTestA3));
    printf("\n");
    
    
    //Tests for MatrixScalarAddition
    printf("\n==============================================");
    printf("\nDemonstrating MatrixScalarAdd() and displaying result:\n");
    printf("Trivial Test of a scalar one added to a matrix comprised of ones:\n");
    MatrixScalarAdd(1, one_matrix, addResult);
    MatrixPrint(addResult);
    float matTestB1[3][3] = {{2,2,2},{2,2,2},{2,2,2}};
    printf("Matrix above should reflect 2's across the board (1 for true): %i\n", MatrixEquals(addResult, matTestB1));
    printf("\nTest of a scalar 5 added to a matrix of basic values:\n");
    MatrixPrint(matBasic);
    printf("+ 5 =\n");
    MatrixScalarAdd(5, matBasic, addResult);
    MatrixPrint(addResult);
    float matTestB2[3][3] = {{6,7,8},{9,10,11},{12,13,14}};
    printf("MatrixScalarAddition successful? (1 if true): %i\n", MatrixEquals(addResult, matTestB2));
    printf("\nTest of a scalar -7 added to a matrix of float values:\n");
    MatrixPrint(matFloat1);
    printf("+ (-7) =\n");
    MatrixScalarAdd(-7, matFloat1, addResult);
    MatrixPrint(addResult);
    float matTestB3[3][3] = {{-3.86,15.6644,0.0001},{-1.666,-80.1,5.755},{0.588,57.3213,-2.5}};
    printf("MatrixScalarAddition successful? (1 if true): %i\n", MatrixEquals(addResult, matTestB3));
    
    
    //Tests for MatrixScalarMultiplication
    printf("\n==============================================");
    printf("\nDemonstrating MatrixScalarMultiply() and displaying result:\n");
    printf("Trivial Test of a matrix comprised of ones multiplied by a scalar one:\n");
    MatrixScalarMultiply(1, one_matrix, addResult);
    MatrixPrint(addResult);
    printf("Matrix above should reflect 1's across the board (1 for true): %i\n", MatrixEquals(addResult, one_matrix));
    printf("\nTest of a basic matrix of values multiplied by a scalar 4:\n");
    MatrixPrint(matBasic);
    printf("* 4 =\n");
    MatrixScalarMultiply(4, matBasic, addResult);
    MatrixPrint(addResult);
    float matTestC1[3][3] = {{4,8,12},{16,20,24},{28,32,36}};
    printf("MatrixScalarMultiplication successful? (1 if true): %i\n", MatrixEquals(addResult, matTestC1));
    printf("\nTest of a matrix of float values multiplied by a scalar -6:\n");
    MatrixPrint(matFloat2);
    printf("* (-6) =\n");
    MatrixScalarMultiply(-6, matFloat2, addResult);
    MatrixPrint(addResult);
    float matTestC2[3][3] = {{-56.6520,-22.0680,252.69},{-385.9974,-143.9322,71.4000},{-271.7751,-11.1336,-51.3960}};
    printf("MatrixScalarMultiplication successful? (1 if true): %i\n", MatrixEquals(addResult, matTestC2));
    
    // Tests for MatrixMultiplication()
    printf("\n==============================================");
    printf("\nDemonstrating MatrixMultiply() and displaying result:\n");
    printf("Trivial Test of a matrix comprised of ones multiplied by another matrix comprised of ones:\n");
    MatrixMultiply(one_matrix, one_matrix, addResult);
    MatrixPrint(addResult);
    printf("MatrixMultiplication successful? (1 if true): %i\n", MatrixEquals(addResult, one_matrix));
    printf("\nTest of two matrices with basic values multiplied together:\n");
    MatrixPrint(matBasic);
    printf("*\n");
    MatrixPrint(matBasic2);
    printf("=\n");
    MatrixMultiply(matBasic, matBasic2, addResult);
    MatrixPrint(addResult);
    float matTestD1[3][3] = {{3,-10,3},{20,15,12},{49,-56,-72}};
    printf("MatrixMultiplication successful? (1 if true): %i\n", MatrixEquals(addResult, matTestD1));
    printf("\nTest of two matrices with float values multiplied together:\n");
    MatrixPrint(matFloat1);
    printf("*\n");
    MatrixPrint(matFloat2);
    printf("=\n");
    MatrixMultiply(matFloat1, matFloat2, addResult);
    MatrixPrint(addResult);
    float matTestD2[3][3] = {{29.6479,1458.0698,317.0756},{19.6185,-1753.5740,23.6682},{-319.5686,-765.4234,38.5470}};
    printf("MatrixMultiplication successful? (1 if true): %i\n", MatrixEquals(addResult, matTestD2));
    
    // Tests for MatrixTrace()
    printf("\n==============================================");
    printf("\nDemonstrating MatrixTrace() and displaying result:\n");
    printf("Trivial Test of the trace of a 3x3 matrix comprised of 1's:\n");
    MatrixPrint(one_matrix);
    printf("\nTrace of above matrix: %f", MatrixTrace(one_matrix));
    printf("\n\nTest of the trace of a 3x3 matrix with basic values:\n");
    MatrixPrint(matBasic2);
    printf("\nTrace of above matrix: %f", MatrixTrace(matBasic2));
    printf("\n\nTest of the trace of a 3x3 matrix with float values:\n");
    MatrixPrint(matFloat2);
    printf("\nTrace of above matrix: %f", MatrixTrace(matFloat2));
    
    // Tests for Transpose()
    printf("\n==============================================");
    printf("\nDemonstrating MatrixTranspose() and displaying result:\n");
    printf("Trivial Test of the transpose of a 3x3 matrix comprised of 1's:\n");
    MatrixTranspose(one_matrix, addResult);
    MatrixPrint(addResult);
    printf("Matrix Transpose successful? (1 if true): %i\n", MatrixEquals(addResult, one_matrix));
    printf("\nTest of the transpose of a 3x3 matrix of basic values:\n");
    MatrixPrint(matBasic2);
    printf("T =\n");
    MatrixTranspose(matBasic2, addResult);
    MatrixPrint(addResult);
    float matTestE1[3][3] = {{3,-5,1},{5,3,2},{7,-7,-8}};
    printf("Matrix Transpose successful? (1 if true): %i\n", MatrixEquals(addResult, matTestE1));
    printf("\nTest of the transpose of a 3x3 matrix of float values:\n");
    MatrixPrint(matFloat1);
    printf("T =\n");
    MatrixTranspose(matFloat1, addResult);
    MatrixPrint(addResult);
    float matTestE2[3][3] = {{3.14,5.334,7.588},{22.6644,-73.1,64.3213},{7.0001,12.755,4.5}};
    printf("Matrix Transpose successful? (1 if true): %i\n", MatrixEquals(addResult, matTestE2));
    
    
    
    // Tests for Submatrix()
    float subResult[2][2] = {{},{}};
    printf("\n==============================================");
    printf("\nDemonstrating MatrixSubmatrix() and displaying result:\n");
    printf("Trivial Test of a submatrix of a 3x3 matrix comprised of 1's\nwith the first row and column removed:\n");
    MatrixSubmatrix(1, 1, one_matrix, subResult);
    float one_compare[2][2] = {{1,1},{1,1}};
    int truth = 1;
    for(int i = 0; i < 2; i++) 
    {
        printf("[");
        for(int j = 0; j < 2; j++)
        {
            printf("%10.4f ", subResult[i][j]);
            if(subResult[i][j] != one_compare[i][j])
            {
                truth = 0;
                break;
            }
        }
        printf(" ]\n");
    }
    printf("Result of submatrix (0 = error, 1 = working): %i\n", truth); 
    truth = 1;
    printf("\nTest of a submatrix of a 3x3 matrix comprised of basic scalar values:\n");
    MatrixSubmatrix(2, 1, matBasic, subResult);
    float basic_compare[2][2] = {{1,3},{4,6}};
    for(int i = 0; i < 2; i++) 
    {
        printf("[");
        for(int j = 0; j < 2; j++)
        {
            printf("%10.4f ", subResult[i][j]);
            if(subResult[i][j] != basic_compare[i][j])
            {
                truth = 0;
            }
        }
        printf(" ]\n");
    }
    printf("Result of submatrix (0 = error, 1 = working): %i\n", truth);
    printf("\nTest of a submatrix of a 3x3 matrix comprised of floating point values:\n");
    MatrixSubmatrix(1, 2, matFloat2, subResult);
    truth = 1;
    float float_compare[2][2] = {{9.442,3.6780},{45.2959,1.8556}};
    for(int i = 0; i < 2; i++) 
    {
        printf("[");
        for(int j = 0; j < 2; j++)
        {
            printf("%10.4f ", subResult[i][j]);
            if(subResult[i][j] != float_compare[i][j])
            {
                truth = 0;
            }
        }
        printf(" ]\n");
    }
    printf("Result of submatrix (0 = error, 1 = working): %i\n", truth);
    
    
    // Test cases for MatrixDeterminant()
    printf("\n==============================================");
    printf("\nDemonstrating MatrixDeterminant() and displaying result:\n");
    printf("Trivial Test to find the determinant of a 3x3 matrix comprised of 1's: \n");
    printf("Result of MatrixDeterminant: %f\n", MatrixDeterminant(one_matrix));
    printf("Calculation successful if answer is 0.\n");
    printf("\nTest to find determinant of a 3x3 matrix of scalar values: \n");
    float value1 = -356;
    printf("Expected value: %f\nCalculated Value: %f\nCalculation successful if these are equal.\n", value1, MatrixDeterminant(matBasic2));
    printf("\nTest to find determinant of a 3x3 matrix of floating point values: \n");
    float value2 = 4325.0444;
    printf("Expected value: %f\nCalculated Value: %f\nCalculation successful if these are equal.\n", value2, MatrixDeterminant(matFloat1));
    
    
    
    BOARD_End();
    while (1);
}

