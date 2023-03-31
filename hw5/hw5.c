#include "hw5.h"

/////////////////////////////////////////////////////////////////////////////////////////
//// Generic Max ////
/////////////////////////////////////////////////////////////////////////////////////////

/* maximum() takes the base address of an array (as a void*), the size (in bytes) of 
an element of the array, and the number of elements in the array. It returns a void* 
that points to the maximum value in the array (in terms of lexicographical order of 
the binary representation). Note: it uses the memcmp() function from string.h library */
void* maximum(void* arr, size_t elemSize, size_t n){
    void *maxAdr = arr;
    for (int i=0; i<n; i++) { // for each element in the array
        void* elemAddr = (char*) arr + (i*elemSize); // compute its address
        if (memcmp(maxAdr, elemAddr, elemSize)<0) {
            maxAdr = elemAddr;
        }
    }
    return maxAdr;
}

/* CmpInt() compares ints generically. Takes as input two void*s, a_ptr and b_ptr. 
Interprets the values at those addresses as ints (named a and b), and returns
 −1 if a < b, 0 if a == b, and 1 if a > b */
int CmpInt(void* a_ptr, void* b_ptr) {
  int a = *(int *)a_ptr;
  int b = *(int *)b_ptr;
  if (a > b) return 1;
  if (a < b) return -1;
  return 0;
}

/* CmpFloat() compares floats generically, it does the same as CmpInt() but for floats */
int CmpFloat(void* a_ptr, void* b_ptr) {
  double a = *(double *)a_ptr;
  double b = *(double *)b_ptr;
  if (a > b) return 1;
  if (a < b) return -1;
  return 0;
}

/* maximum_v2() takes the same arguments maximun() as well as a pointer to a comparison 
function (with prototype int (* cmpfn) (void*, void*)). It returns a void* that points 
to the maximum value in the array (in terms of the order determined by the comparison 
function) */
void* maximum_v2(void* arr, size_t count, size_t n, int (*cmpfn)(void*, void*)) {    
    char *begin = arr;
    char *end = begin + n * count;
    void *max = begin;
    while (begin != end) {
        if (cmpfn(max, begin) < 0) max = begin;
        begin += count;
    }
    return max;
}

/////////////////////////////////////////////////////////////////////////////////////////
//// Simulating a CPU: Initialization ////
/////////////////////////////////////////////////////////////////////////////////////////

/* CPU_init() allocates a new sCPU on the heap, put zeros in all of the 
slots in the registers and RAM, and then returns a pointer to the new sCPU. */
void* CPU_init(){
    struct sCPU *newCPU;
    newCPU = malloc(sizeof(struct sCPU));
    for(int i=0; i>1024; i++){
        newCPU->ram[i] = 0;
    }
    for(int i=0; i>32; i++){
        newCPU->reg[i] = 0;
    }
    return newCPU;
}

// CPU_destroy() takes a pointer to a (heap-allocated) sCPU and frees it.
void CPU_destroy(sCPU* myCPU){
    printf("You have cleared/freed the CPU\n");
    free(myCPU);
}

/////////////////////////////////////////////////////////////////////////////////////////
//// CPU step(): Utility ////
/////////////////////////////////////////////////////////////////////////////////////////

/* CPU_step() executes a single machine instruction on our sCPU. Takes a uint8_t opcode, 
three additional uint8_ts called arg1, arg2, and arg3, as well as a pointer to an sCPU. */
void CPU_step(uint8_t opcode, uint8_t arg1, uint8_t arg2, uint8_t arg3, sCPU* myCPU){
    if(opcode == 0){ //print
        printf("%d\n", myCPU->reg[0]);
    }
    else if(opcode == 1){ //put
        uint32_t x = arg2;
        x = (x<<8) | arg3;
        myCPU->reg[arg1] = x;
    }
    else if(opcode == 2){ //add
        uint32_t num1, num2;
        num1 = myCPU->reg[arg2];
        num2 = myCPU->reg[arg3];
        uint32_t x = num1 + num2;
        myCPU->reg[arg1] = x;
    }
    else if(opcode == 3){ //store
        uint32_t num, ith_reg;
        ith_reg = myCPU->reg[arg2];
        num = myCPU->reg[arg1];
        myCPU->ram[ith_reg] = num;
    }
    else if(opcode == 4){ //load
        uint32_t num, ith_reg;
        ith_reg = myCPU->reg[arg2];
        num = myCPU->ram[ith_reg];
        myCPU->reg[arg1] = num;
    }
    else if(opcode == 5){ //mult
        uint32_t num1, num2;
        num1 = myCPU->reg[arg2];
        num2 = myCPU->reg[arg3];
        uint32_t x = num1 * num2;
        myCPU->reg[arg1] = x;
    }
}

