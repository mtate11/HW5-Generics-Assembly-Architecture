#ifndef HW_FIVE
#define HW_FIVE
#include <stdint.h>

/////////////////////////////////////////////////////////////////////////////////////////
//// Generic Max Declarations (Problem 1) ////
/////////////////////////////////////////////////////////////////////////////////////////

/* maximum() takes the base address of an array (as a void*), the size (in bytes) of 
an element of the array, and the number of elements in the array. It returns a void* 
that points to the maximum value in the array (in terms of lexicographical order of 
the binary representation). Note: it uses the memcmp() function from string.h library */
void* maximum(void*, size_t, size_t);

/* CmpInt() compares ints generically. Takes as input two void*s, a_ptr and b_ptr. 
Interprets the values at those addresses as ints (named a and b), and returns
 −1 if a < b, 0 if a == b, and 1 if a > b */
int CmpInt(void*, void*);

/* CmpFloat() compares floats generically, it does the same as CmpInt() but for floats */
int CmpFloat(void*, void*);

/* maximum_v2() takes the same arguments maximun() as well as a pointer to a comparison 
function (with prototype int (* cmpfn) (void*, void*)). It returns a void* that points 
to the maximum value in the array (in terms of the order determined by the comparison 
function) */
void* maximum_v2(void*, size_t, size_t, int (*cmpfn)(void*, void*));


/////////////////////////////////////////////////////////////////////////////////////////
//// Simulating a CPU: Initialization Declarations (Problem 3) ////
/////////////////////////////////////////////////////////////////////////////////////////

/* struct sCPU has a register set reg and a 32-kilobyte memory ram. reg is represented 
by an array of thirty two 32-bit signed integers. ram is represented by an array of 1024 
32-bit signed integers. */
typedef struct sCPU{
    int32_t reg[32];
    int32_t ram[1024];
} sCPU;

/* CPU_init() allocates a new sCPU on the heap, put zeros in all of the 
slots in the registers and RAM, and then returns a pointer to the new sCPU. */
void* CPU_init();

// CPU_destroy() takes a pointer to a (heap-allocated) sCPU and frees it.
void CPU_destroy(sCPU*);

/////////////////////////////////////////////////////////////////////////////////////////
//// CPU step(): Utility (Problems 4-6) ////
/////////////////////////////////////////////////////////////////////////////////////////

/* CPU_step() will execute a single machine instruction on our sCPU. CPU step(). Takes 
a uint8_t opcode, three additional uint8_ts called arg1, arg2, and arg3, as well as a 
pointer to an sCPU.
    print instruction: executed when the opcode is 0. Prints the value held in the 0th register.

    put instruction: executed when the opcode is 1. Treats arg2 and arg3 as a single immediate, 
    and places its value in the register indicated by arg1. In other words, it should set 
    reg[arg1] = x, where x is a 32-bit integer formed by concatenating 16 zeros followed by 
    the bits of arg2 and arg3.

    add instruction: executed when the opcode is 2. Takes the values in the registers indicated 
    by arg2 and arg3, adds them, and places their sum into the register indicated by arg1.

    mul instruction: executed when the opcode is 5. Does the same as add but with multiplication.

    store instruction: executed when the opcode is 3. Takes the value in the register indicated 
    by arg1, and place it in the ith place in RAM, where i is the value stored in the register 
    indicated by arg2.

    load instruction: executed when the opcode is 4. Takes the value stored in the ith place in 
    RAM, where i is the value stored in the register indicated by arg2, and places it in the 
    register indicated by arg1.
*/
void CPU_step(uint8_t, uint8_t, uint8_t, uint8_t, sCPU*);


#endif