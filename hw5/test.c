#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <string.h>
#include "hw5.h"
#include "hw5.c"

int main(){

    /////////////////////////////////////////////////////////////////////////////////////////
    //// Generic Max Tests ////
    printf("## GENERIC MAX TESTS BELOW ##\n");
    // Arrays to find the max of
    int v[] = {5, 1, 3, 1, 34, 198, 12, 11};
    int v2[] = {11, 3, 7, 0};
    int v3[] = {3, 4, 1, 5, 2};
    double f[] = {1.23, 6.57, 9.89, 11.56};
    double f2[] = {2.2, 5.5, 3.3, 4.4, 1.1};
    double f3[] = {11.11, 22.22, 55.55, 33.33, 44.44};

    // Testing maximum()
    int *maximum1 = maximum(v, sizeof(*v), sizeof(v) / sizeof(*v));
    printf("%d, should be 198\n", *maximum1);
    int *maximum2 = maximum(v2, sizeof(*v2), sizeof(v2) / sizeof(*v2));
    printf("%d, should be 11\n", *maximum2);
    int *maximum3 = maximum(v3, sizeof(*v3), sizeof(v3) / sizeof(*v3));
    printf("%d, should be 5\n\n", *maximum3);

    // Testing maximum_v2()
    int *m = maximum_v2(v, sizeof(*v), sizeof(v) / sizeof(*v), CmpInt);
    printf("%d, should be 198\n", *m);
    int *m2 = maximum_v2(v2, sizeof(*v2), sizeof(v2) / sizeof(*v2), CmpInt);
    printf("%d, should be 11\n", *m2);
    int *m3 = maximum_v2(v3, sizeof(*v3), sizeof(v3) / sizeof(*v3), CmpInt);
    printf("%d, should be 5\n", *m3);
    double *m4 = maximum_v2(f, sizeof(*f), sizeof(f) / sizeof(*f), CmpFloat);
    printf("%f, should be 11.56\n", *m4);
    double *m5 = maximum_v2(f2, sizeof(*f2), sizeof(f2) / sizeof(*f2), CmpFloat);
    printf("%f, should be 5.5\n", *m5);
    double *m6 = maximum_v2(f3, sizeof(*f3), sizeof(f3) / sizeof(*f3), CmpFloat);
    printf("%f, should be 55.55\n", *m6);

    /////////////////////////////////////////////////////////////////////////////////////////
    //// Testing struct sCPU and CPU_step(), Problems 3-6 ////
    printf("\n## sCPU & CPU_step() TESTS BELOW ##\n");
    sCPU* cpu_ptr = CPU_init();
    CPU_step(1,0,0,0, cpu_ptr); //put 0 into r0
    CPU_step(0,0,0,0, cpu_ptr); // print r0
    CPU_step(1,0,1,1, cpu_ptr); // put 0b 00000001 00000001 = 257 into r0
    CPU_step(0,0,0,0, cpu_ptr); // print r0
    CPU_destroy(cpu_ptr);
    printf("The above should result in printing a 0, and then a 257 to the console.\n\n");

    sCPU* cpu_ptr2 = CPU_init();
    CPU_step(1,1,0,4, cpu_ptr2); // put a 4 into r1
    CPU_step(1,2,0,6, cpu_ptr2); // put a 6 into r2
    CPU_step(2,0,1,2, cpu_ptr2); // r0 = r1 + r2
    CPU_step(5,0,0,1, cpu_ptr2); // r0 = r0 * r1
    CPU_step(0,0,0,0, cpu_ptr2); // print r0
    CPU_destroy(cpu_ptr2); 
    printf("The above should result in printing 40 to the console\n\n");

    sCPU* cpu_ptr3 = CPU_init();
    CPU_step(1,1,0,4, cpu_ptr3); // put a 4 into r1
    CPU_step(1,2,0,200, cpu_ptr3); // put a 200 into r2
    CPU_step(3,1,2,0, cpu_ptr3); // store 4 into ram[200]
    CPU_step(4,0,2,0, cpu_ptr3); // load the 4 
    CPU_step(0,0,0,0, cpu_ptr3); // print r0
    CPU_destroy(cpu_ptr3);
    printf("The above should result in printing 4.\n\n");

    printf("Below is my tests I wrote for CPU_step and sCPU\n");
    sCPU* cpu_ptr4 = CPU_init();
    CPU_step(1,32,1,155, cpu_ptr4); // put a 411 into r32
    printf("%d, should print a 411 from reg[32]\n", cpu_ptr3->reg[32]);
    CPU_step(1,17,0,10, cpu_ptr4); // put a 200 into r17
    printf("%d, should print a 10 from reg[17]\n", cpu_ptr3->reg[17]);
    CPU_step(3,17,32,0, cpu_ptr4); // store 10 into ram[411]
    printf("%d, should print a 10 that was stored in ram[411]\n", cpu_ptr3->ram[411]);
    
    CPU_step(4,0,32,0, cpu_ptr4); // load the 4 from ram[200] into r0
    CPU_step(0,0,0,0, cpu_ptr4); // print r0
    printf("The above should print a 10 that was loaded from ram[411] into r0, and then printed via opcode call 0\n");
    CPU_destroy(cpu_ptr4);

    /////////////////////////////////////////////////////////////////////////////////////////
    //// Executing Machine Instructions (PROBLEM 7: Series of calls to the cpu) ////

    printf("\n## PROBLEM 7 CODE OUTPUT BELOW ##\n");
    // A) computes the sum 1 + 3 + 5 + 7 + 9 and stores the result in register 0.
    struct sCPU* cpu_ptr5 = CPU_init();
    CPU_step(1,1,0,1, cpu_ptr5); // put a 4 into r1
    CPU_step(1,2,0,3, cpu_ptr5);
    CPU_step(2,1,1,2, cpu_ptr5);  // r1 = r1 + r2
    CPU_step(1,2,0,5, cpu_ptr5);
    CPU_step(2,1,1,2, cpu_ptr5);  // r1 = r1 + r2
    CPU_step(1,2,0,7, cpu_ptr5);
    CPU_step(2,1,1,2, cpu_ptr5);  // r1 = r1 + r2
    CPU_step(1,2,0,9, cpu_ptr5);
    CPU_step(2,0,1,2, cpu_ptr5);  // r0 = r1 + r2
    CPU_step(0,0,0,0, cpu_ptr5); // print r0
    CPU_destroy(cpu_ptr5);
    printf("The above should result in printing 25.\n\n");

    // B) computes x+ +, assuming x is stored in the 20th place in ram
    struct sCPU* cpu_ptr6 = CPU_init();
    //// THE 19 IS THE X-VALUE: CHANGE TO DESIRED X-INT ////
    CPU_step(1,1,0,19, cpu_ptr6); // put a x=19 into r1 
    CPU_step(1,2,0,20, cpu_ptr6); // put a 200 into r2
    CPU_step(3,1,2,0, cpu_ptr6); // store x into ram[20]
    CPU_step(1,1,0,1, cpu_ptr6); // put a 1 in r1
    CPU_step(4,2,2,0, cpu_ptr6); // load the x from ram[20] into r2
    CPU_step(2,0,1,2, cpu_ptr6); // r0 = r1 + r2
    CPU_step(0,0,0,0, cpu_ptr6); // print r0
    CPU_destroy(cpu_ptr6);
    printf("The above should result in printing x+1 (I used x = 19, so 20 should be printed)\n\n");

    /* C) fills an array of 5 integers with the first 5 powers of 2. Uses the mul instruction 
    rather than simply puting each value. Assumes that the base address of the array is the 
    50th place in ram. */
    sCPU* cpu_ptr7 = CPU_init();
    CPU_step(1,2,0,50, cpu_ptr7); // put a 50 into r2
    CPU_step(1,1,0,2, cpu_ptr7); // put a 2 into r1
    CPU_step(3,1,2,0, cpu_ptr7); // store 2 into ram[50]

    CPU_step(1,2,0,54, cpu_ptr7); // put a 54 into r2
    CPU_step(5,0,1,1, cpu_ptr7); // r0 = r1 * r1
    CPU_step(3,0,2,0, cpu_ptr7); // store 4 into ram[54]

    CPU_step(1,2,0,58, cpu_ptr7); // put a 58 into r2
    CPU_step(5,0,0,1, cpu_ptr7); // r0 = r0 * r1
    CPU_step(3,0,2,0, cpu_ptr7); // store 8 into ram[58]
    
    CPU_step(1,2,0,62, cpu_ptr7); // put a 62 into r2
    CPU_step(5,0,0,1, cpu_ptr7); // r0 = r0 * r1
    CPU_step(3,0,2,0, cpu_ptr7); // store 16 into ram[62]
    
    CPU_step(1,2,0,66, cpu_ptr7); // put a 66 into r2
    CPU_step(5,0,0,1, cpu_ptr7); // r0 = r0 * r1
    CPU_step(3,0,2,0, cpu_ptr7); // store 32 into ram[66]

    printf("%d\n", cpu_ptr7->ram[50]);
    printf("%d\n", cpu_ptr7->ram[54]); //I used increments of 4 to mimick actually going up in ram
    printf("%d\n", cpu_ptr7->ram[58]);
    printf("%d\n", cpu_ptr7->ram[62]);
    printf("%d\n", cpu_ptr7->ram[66]);
    CPU_destroy(cpu_ptr7);
    printf("The above should output a: 2 4 8 16 and 32\n");

    return 0;
}
