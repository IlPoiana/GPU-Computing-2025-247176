#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "lib.h"

double avg (double * arr, int nelem){
    double average = 0;
    printf("nelem: %d\n", nelem);
    for(int i = 0; i< nelem; i++){
        average = average + arr[i] / nelem;
    }
    return average;
}

int main(int argc, char *args[]){

    double arr[2] = {4,2};
    printf("average: %lf\n", avg(arr,2));
}