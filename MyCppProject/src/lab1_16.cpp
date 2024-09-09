#include <stdlib.h>  
#include "../include/lab1_16.h"

int NOD(int a, int b) {
    a = abs(a); 
    b = abs(b); 

    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}