// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//Class specific libraries
#include "BOARD.h"


// User libraries
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    BOARD_Init();
    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    //Declare Variables
    float fahr, celsius, kelvin;
    int lower, upper, step;

    //initialize Variables
    lower = 0;
    upper = 300;
    step = 20;
    fahr = lower;
    kelvin = lower;
    
    //column headers for F to C table
    printf("%5c %5c\n", (char) 'F', (char) 'C');

    //Print out table for Fahrenheit to Celsius
    while (fahr <= upper) {
        celsius = (5.0 / 9.0)*(fahr - 32.0);
        printf("%7.1f %04.0f\n", (double) fahr, (double) celsius);
        fahr = fahr + step;
    }
    
    //column headers for K to F table
    printf("\n %5c %5c\n", (char) 'K', (char) 'F');
    
    //Print out table for Kelvin to Fahrenheit
    while(kelvin <= upper) {
        fahr = (kelvin - 273.15)*1.8+32;
        printf("%3.3f %5f\n", (double) kelvin, (double) fahr);
        kelvin = kelvin + step;
    }

    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks.
     **************************************************************************************************/

    // Returning from main() is bad form in embedded environments. So we sit and spin.
    while (1);
}
