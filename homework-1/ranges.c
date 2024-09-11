#include <stdio.h>

void printCharRange();
void printShortRange();
void printIntRange();
void printLongRange();
void printFloatRange();
void printDoubleRange();

int main() {
    char *buffer = NULL;
    size_t length = 0;
    ssize_t size = 0;
    char user_input; // User input (should be c, s, i, l, f, or d)


    fprintf(stdout, "Enter c|s|i|l|f|d <cntl+D to exit>: ");
    while ((size = getline(&buffer, &length, stdin)) != -1) {
        int input_read = sscanf(buffer, "%c", &user_input);
        if (size == 2) { // 2 - character user enters, plus the enter key
            switch (user_input) {
	    	case 'c':
                    printCharRange();
                    break;
                case 's':
                    printShortRange();
                    break;
                case 'i':
                    printIntRange();
                    break;
                case 'l':
                    printLongRange();
                    break;
                case 'f':
                    printFloatRange();
                    break;
                case 'd':
                    printDoubleRange();
                    break;
                default: // user enters something that is not c, s, i, l, f, or d
                    fprintf(stderr, "Invalid input: Invalid char.\n");
                    break;
            }
        } else { // user enters more than one character, or just presses the enter key
            fprintf(stderr, "Invalid input: Invalid length.\n");
        }
        fprintf(stdout, "Enter c|s|i|l|f|d <cntl+D to exit>: ");
    }
    return 0;
}

void printCharRange() {
	signed char signed_mask = (1 << sizeof(char)*8 - 1); // Creates the bit mask for min signed char - 1000 0000
	fprintf(stdout, "The minimum value of signed char = %d\n", signed_mask);
	signed_mask = 0x00;
    /* Creates the bit mask for max signed char - 0111 1111
     *
     * This works by adding bit masks together, starting at 0100 0000, and iterating all the way down to 0000 0001.
    */
	for (int i = sizeof(char)*8-2; i >= 0; i--) {
		signed_mask = signed_mask + (1 << i);
	}	
	fprintf(stdout, "The maximum value of signed char = %d\n", signed_mask);

	unsigned char unsigned_mask = 0x00; // Creates the bit mask for min unigned char - 0000 0000
	fprintf(stdout, "The minimum value of unsigned char = %d\n", unsigned_mask);
    /* Creates the bit mask for max unsigned char - 1111 1111
     *
     * This works by adding bit masks together, starting at 1000 0000, and iterating all the way down to 0000 0001.
    */
	for (int i = sizeof(char)*8 - 1; i >= 0; i--) {
		unsigned_mask = unsigned_mask + (1 << i);
	}
	fprintf(stdout, "The maximum value of unsigned char = %d\n", unsigned_mask);
}

void printShortRange() {
    signed short signed_mask = (1 << sizeof(short)*8 - 1); // Creates the bit mask for min signed short - 1000 0000 0000 0000
    fprintf(stdout, "The minimum vlaue of signed short = %d\n", signed_mask);
    signed_mask = 0x00;
    /* Creates the bit mask for max signed short - 0111 1111 1111 1111
     *
     * This works by adding bit masks together, starting at 0100 0000 0000 0000, and iterating all the way down to 0000 0000 0000 0001.
    */
    for (int i = sizeof(short)*8-2; i >= 0; i--) {
        signed_mask = signed_mask + (1 << i);
    }
    fprintf(stdout, "The maximum value of signed short = %d\n", signed_mask);
    
    unsigned short unsigned_mask = 0x00; // Creates the bit mask for min unsigned short - 0000 0000 0000 0000
    fprintf(stdout, "The minimum value of unsigned short = %d\n", unsigned_mask);
    /* Creates the bit mask for max unsigned short - 1111 1111 1111 1111
     *
     * This works by adding bit masks together, starting at 1000 0000 0000 0000, and iterating all the way down to 0000 0000 0000 0001.
    */
    for (int i = sizeof(short)*8 - 1; i >= 0; i--) {
		unsigned_mask = unsigned_mask + (1 << i);
	}
	fprintf(stdout, "The maximum value of unsigned short = %d\n", unsigned_mask);
}

void printIntRange() {
    signed int signed_mask = (1 << sizeof(int)*8 - 1); // Creates the bit mask for min signed int - 1000 0000 0000 0000 0000 0000 0000 0000
    fprintf(stdout, "The minimum vlaue of signed int = %d\n", signed_mask);
    signed_mask = 0x00;
    /* Creates the bit mask for max signed int - 0111 1111 1111 1111 1111 1111 1111 1111
     *
     * This works by adding bit masks together, starting at 0100 0000 0000 0000 0000 0000 0000 0000,
     * and iterating all the way down to 0000 0000 0000 0000 0000 0000 0000 0001.
    */
    for (int i = sizeof(int)*8-2; i >= 0; i--) {
        signed_mask = signed_mask + (1 << i);
    }
    fprintf(stdout, "The maximum value of signed int = %d\n", signed_mask);

    unsigned int unsigned_mask = 0x00; // Creates the bit mask for min unsigned int - 0000 0000 0000 0000 0000 0000 0000 0000
    fprintf(stdout, "The minimum value of unsigned int = %u\n", unsigned_mask);
    /* Creates the bit mask for max unsigned int - 1111 1111 1111 1111 1111 1111 1111 1111
     *
     * This works by adding bit masks together, starting at 1000 0000 0000 0000 0000 0000 0000 0000,
     * and iterating all the way down to 0000 0000 0000 0000 0000 0000 0000 0001.
    */
    for (int i = sizeof(int)*8 - 1; i >= 0; i--) {
		unsigned_mask = unsigned_mask + (1 << i);
	}
	fprintf(stdout, "The maximum value of unsigned int = %u\n", unsigned_mask);
}

void printLongRange() {
    signed long signed_mask = (1L << (sizeof(long)*8 - 1)); // Creates the bit mask for min signed long
    fprintf(stdout, "The minimum vlaue of signed long = %ld\n", signed_mask);
    signed_mask = 0;
    /* Creates the bit mask for max signed long - 0111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111
     *
     * This works by adding bit masks together, starting at 0100 0000 ....... 0000,
     * and iterating all the way down to 0000 ..... 0001.
    */
    for (int i = (sizeof(long)*8-2); i >= 0; i--) { // Creates the bit mask for max signed long
        signed_mask = signed_mask + (1L << i);
    }
    fprintf(stdout, "The maximum value of signed long = %ld\n", signed_mask);

    unsigned long unsigned_mask = 0; // Creates the bit mask for min unsigned long - 0
    fprintf(stdout, "The minimum value of unsigned long = %lu\n", unsigned_mask);
    /* Creates the bit mask for max unsigned long - 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111
     *
     * This works by adding bit masks together, starting at 1000 0000 ...... 0000,
     * and iterating all the way down to 0000 0000 ....... 0001.
    */
    for (int i = sizeof(long)*8 - 1; i >= 0; i--) {
		unsigned_mask = unsigned_mask + (1L << i);
	}
	fprintf(stdout, "The maximum value of unsigned long = %lu\n", unsigned_mask);
}

void printFloatRange() {
    
    float mask = 0;
    // Creates a integer pointer to the address of mask, which is casted as an int*. This enables the use of bit operators
    int* mask_ptr = (int*)&mask;
    for (int i = 0; i < 23; i++) {
        *mask_ptr = *mask_ptr + (1 << i);
    }
    for (int i = 24; i < 31; i++) {
        *mask_ptr = *mask_ptr + (1 << i);
    }
    fprintf(stdout, "The minimum value of float = %.10e\n", mask);
    
    // Resetting the mask and making it the max value of float.
    *mask_ptr = *mask_ptr + (1 << 31);
    fprintf(stdout, "The maximum value of float = %.10e\n", mask);

    mask = 0.0; // Resetting the mask and using a for-loop to set it equal to -0.
    for (size_t i = 0; i < (sizeof(float)*8); i++) {
	    mask = mask + (1 << i);
    }
    fprintf(stdout, "The hex representation of -0 in float = 0x%X\n", mask);
    fprintf(stdout, "The hex representation of 0 in float = 0x%X\n", 0);

    mask = 0.0;
    for (int i = 23; i < 32; i++) {
        *mask_ptr = *mask_ptr + (1 << i);
    }
    fprintf(stdout, "The hex representation of -INF in float = 0x%X\n", mask);
    mask = 0.0;
    for (int i = 23; i < 32; i++) {
        *mask_ptr = *mask_ptr + (1 << i);
    }
    *mask_ptr = *mask_ptr + 1;
    fprintf(stdout, "The hex representation of NaN in float = 0x%X\n", mask);

}

void printDoubleRange() {
    double mask = 0;
    // Creates a long pointer to the address of mask, which is casted as an long*. This enables the use of bit operators
    long* mask_ptr = (long*)&mask;
    for (int i = 0; i < 23; i++) {
        *mask_ptr = *mask_ptr + (1 << i);
    }
    for (int i = 24; i < 31; i++) {
        *mask_ptr = *mask_ptr + (1 << i);
    }
    fprintf(stdout, "The minimum value of double = %.10e\n", mask);
    
    // Resetting the mask and making it the max value of double.
    mask = 0;
    for (int i = 0; i < 52; i++) {
        *mask_ptr = *mask_ptr + (1 << i);
    }
    fprintf(stdout, "The maximum value of double = %.10e\n", mask);

    mask = 0.0; // Resetting the mask and using a for-loop to set it equal to -0.
    *mask_ptr = ((long)1 << 31);
    fprintf(stdout, "The hex representation of -0 in double = 0x%X\n", mask);
    mask = 0; // Resetting the mask to +0.
    fprintf(stdout, "The hex representation of 0 in double = 0x%X\n", mask);

    mask = 0.0;
    for (int i = 52; i < 64; i++) {
        *mask_ptr = *mask_ptr + (1 << i);
    }
    fprintf(stdout, "The hex representation of -INF in double = 0x%X\n", mask);
    mask = 0.0;
    for (int i = 52; i < 63; i++) {
        *mask_ptr = *mask_ptr + (1 << i);
    }
    fprintf(stdout, "The hex representation of NaN in double = 0x%X\n", mask);
}