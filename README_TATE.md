## HOMEWORK_FIVE

To compile this code, run the following command:

```gcc test.c -o test```

### 1. Generic Max
- **WHERE**: code for maximum(), CmpInt(), CmpFloat(), and maximum_v2() is in hw5.c and hw5.h
- **HOW**: 
    >> a. Run maximum() inputing a base address of an array (as a void*), the size (in bytes) of an element of the array, and the number of elements in the array. It returns a void* that points to the maximum value in the array (in terms of lexicographical order of the binary representation)
    >> b. Run CmpInt() by inputing two void*s, a_ptr and b_ptr. It interprets the values at those addresses as ints (call them a and
    b), and returns −1 if a < b, 0 if a == b, and 1 if a > b.
    >> c. Run CmpFloat() by inputing two void*s, a_ptr and b_ptr. It does the same as CmpInt() but for floats.
    >> d. Run maximum_v2() by inputing the same arguments as maximum(), plus a pointer to a comparison function (with prototype int (* cmpfn) (void*, void*) ). It returns a void* that points to the maximum value in the array (in terms of the order determined by the comparison function).
- **NOTES**: maximum() only works for positive whole integers since memcmp() looks at the left most bit to determine if one number it larger than the other and doen't consider sign nor floating-point notation (since comparison is done lexicographically).

### 2. MIPS Assembly Basics
- **WHERE**: code to compute the nth power of 2 is in MIPS_hw5.s
- **HOW**: Run code by opening the file in QtSPIM and running the simulator. The user should be prompted for an n which represents a positive integer to which 2^n is printed to the user.
- **NOTES**: Only works for n up to 30 since I am using slt in the loop, so when 31 is placed in the t1 register it is labeled as 1f which messes up the conparison operation.

### 3. Simulating a CPU: Initialization
- **WHERE**: code for struct sCPU is in hw5.h. Code for CPU_init() and CPU_destroy() is in hw5.h and hw5.c.
- **HOW**: 
    >> Create a sCPU simiply by calling sCPU <name> (since sCPU is a typedef struct named sCPU). struct sCPU's have a register set 'reg' and a 32-kilobyte memory 'ram'. reg is represented by an array of thirty two 32-bit signed integers and ram is represented by an array of 1024 32-bit signed integers.
    >> Run by setting, sCPU <name> = CPU_init(). This allocates <name> as a new sCPU on the heap, puts zeros in all of the slots in the registers and RAM.
    >> Run CPU_destroy() by inputing a pointer to a (heap-allocated) sCPU, via <name>. This function frees it.
- **NOTES**: 

### 4-6. CPU step(): Utility
- **WHERE**: Code for CPU_step() is in hw5.h and hw5.c.
- **HOW**: Run CPU_step() by inputing a uint8_t opcode, three additional uint8_ts called arg1, arg2, and arg3, as well as a pointer to an sCPU.
    >> print: executed when the opcode is 0, prints the value held in the 0th register.
        Example: CPU step(0, 0, 0, 0, cpu ptr)
                should print a 0 to the console.
    >> put: executed when the opcode is 1. This instruction treats arg2 and arg3 as a single immediate, and places its value in the register indicated by arg1 (it sets reg[arg1] = x, where x is a 32-bit integer formed by concatenating 16 zeros followed by the bits of arg2 and arg3).
        Example: CPU_step(1,0,1,1, cpu_ptr);
            puts 0b00000001 00000001 = 257 into r0
    >> add: executed when the opcode is 2. Takes the values in the registers indicated by arg2 and arg3, adds them, and places their sum into the register indicated by arg1.
        Example: CPU_step(2,0,1,2, cpu_ptr);
            computes r0 = r1 + r2
    >> multiply: executed when the opcode is 5. It does the same thing as add but with multiplication.
        Example: CPU_step(5,0,0,1, cpu_ptr);
            computes r0 = r0 * r1
    >> store: executed when the opcode is 3. It takes the value in the register indicated by arg1, and places it in the ith place in RAM, where i is the value stored in the register indicated by arg2.
        Example: CPU_step(3,1,2,0, cpu_ptr);    
            stores the value at r1 into ram[value at r2].
    >> load: executed when the opcode is 4. It takes the value stored in the ith place in RAM, where i is the value stored in the register indicated by arg2, and places it in the register indicated by arg1.
        Example: CPU_step(4,0,2,0, cpu_ptr);
            loads the value from ram[value at r2] into r0.
- **NOTES**:

### 7. Executing Machine Instructions
- **WHERE**: code for the machine instuction calls, parts a, b and c is all in test.c
- **HOW**: run code for parts a, b, and c by running your named compiiled file containing test.c. Should output 25 for part a, x+1 for part b (x is noted in test.c, so one can change it), and 5 numbers (2,4,8,16,32) for part c should be output.
- **NOTES**:
